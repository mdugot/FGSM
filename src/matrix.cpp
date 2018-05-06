#include "matrix.h"

bool operator== (const Matrix &m1, const Matrix &m2) {
	if (m1.rowSize() != m2.rowSize())
		return false;
	if (m1.columnSize() != m2.columnSize())
		return false;
	for (int i = 0; i < m1.rowSize(); i++) {
		for (int j = 0; j < m1.columnSize(); j++) {
			if (ABS(m1.get(i,j) - m2.get(i,j)) > DOUBLE_EPSILON)
				return false;
		}
	}
	return true;
}

bool operator!= (const Matrix &m1, const Matrix &m2) {
	return !(m1 == m2);
}

Matrix::Matrix(const Matrix &from) : rows(from.rowSize()), columns(from.columnSize())
{
	this->values = new double*[rows];
	for (int i = 0; i < rows; i++) {
		this->values[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			this->values[i][j] = from.get(i,j);
		}
	}
}

Matrix::Matrix(double *values, int rows, int columns) : rows(rows), columns(columns)
{
	this->values = new double*[rows];
	for (int i = 0; i < rows; i++) {
		this->values[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			this->values[i][j] = values[i*columns + j];
		}
	}
}

Matrix::Matrix(int rows, int columns, double value) : rows(rows), columns(columns)
{
	values = new double*[rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			values[i][j] = value;
		}
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < rows; i++) {
		delete values[i];
	}
	delete values;
}

double Matrix::getMax() {
	double max = std::numeric_limits<double>::lowest();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (values[i][j] > max)
				max = values[i][j];
		}
	}
	return max;
}

double Matrix::getMin() {
	double min = std::numeric_limits<double>::max();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (values[i][j] < min)
				min = values[i][j];
		}
	}
	return min;
}

void Matrix::print(int precision) {
	int width = 1 + precision;
	int min = getMin();
	int max = getMax();
	if (min < 0 && min * -1 > max)
		max = min * -1;
	while (max > 0) {
		max /= 10;
		width++;
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			printf("%*.*f ", width, precision, values[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

Vector Matrix::row(int i) {
	return Vector(values[i], columns);
}

Vector Matrix::column(int i) {
	Vector result(rows);
	for (int j = 0; j < rows; j++) {
		result[j] = values[j][i];
	}
	return result;
}

Matrix& Matrix::operator=(Matrix const &m2) {
	if (this == &m2)
		return *this;
	
	for (int i = 0; i < rows; i++) {
		delete values[i];
	}
	delete values;
	rows = m2.rowSize();
	columns = m2.columnSize();
	values = new double*[rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			values[i][j] = m2.get(i,j);
		}
	}
	return *this;
}

Vector Matrix::operator*(Vector const &v2) {
	if (columns != v2.getSize())
		throw FgsmException("multiply matrix and vector of wrong dimensions");

	Vector result(rows);
	double tmp;
	for (int i = 0; i < rows; i++) {
		tmp = 0;
		for (int j = 0; j < columns; j++) {
			tmp += v2[j] * values[i][j];
		}
		result[i] = tmp;
	}
	return result;
}

Matrix Matrix::transpose() {
	Matrix result(columns, rows);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			result[j][i] = values[i][j];
		}
	}
	return result;
}
