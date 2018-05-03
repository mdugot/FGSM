#include "vector.h"

Vector::Vector(void) : values(NULL), size(0) {}

Vector::Vector(const Vector &from) : size(from.getSize())
{
	this->values = new double[size];
	for (int i = 0; i < size; i++) {
		this->values[i] = from[i];
	}
}

Vector::Vector(double *values, int size) : size(size)
{
	this->values = new double[size];
	for (int i = 0; i < size; i++) {
		this->values[i] = values[i];
	}
}

Vector::Vector(int size, double value) : size(size)
{
	values = new double[size];
	for (int i = 0; i < size; i++) {
		values[i] = value;
	}
}

Vector::~Vector() {
	delete values;
}

double Vector::getMax() {
	double max = std::numeric_limits<double>::lowest();
	for (int i = 0; i < size; i++) {
		if (values[i] > max)
			max = values[i];
	}
	return max;
}

double Vector::getMin() {
	double min = std::numeric_limits<double>::max();
	for (int i = 0; i < size; i++) {
		if (values[i] < min)
			min = values[i];
	}
	return min;
}

void Vector::print(int precision) {
	int width = 1 + precision;
	int min = getMin();
	int max = getMax();
	if (min < 0 && min * -1 > max)
		max = min * -1;
	while (max > 0) {
		max /= 10;
		width++;
	}
	for (int i = 0; i < size; i++) {
		printf("%*.*f ", width, precision, values[i]);
		printf("\n");
	}
	printf("\n");
}

Vector Vector::operator+(Vector const &v2) {
	if (size != v2.getSize())
		throw FgsmException("sum vectors of different sizes");
	Vector result(size);
	for (int i = 0; i < size; i++) {
		result[i] = values[i] + v2[i];
	}
	return result;
}

Vector& Vector::operator=(Vector const &v2) {
	if (this == &v2)
		return *this;

	delete(values);
	size = v2.getSize();
	values = new double[size];
	for (int i = 0; i < size; i++) {
		values[i] = v2[i];
	}
	return *this;
}

Vector Vector::relu() {
	Vector result(size);

	for (int i = 0; i < size; i++) {
		result[i] = (values[i] >= 0 ? values[i] : 0);
	}
	return result;
}

Vector Vector::softmax() {
	Vector result(size);

	double expSum = 0;
	for (int i = 0; i < size; i++) {
		expSum += exp(values[i]);
	}
	for (int i = 0; i < size; i++) {
		result[i] = exp(values[i]) / expSum;
	}
	return result;
}

int Vector::argmax() {
	double max = std::numeric_limits<double>::lowest();
	int result = 0;
	for (int i = 0; i < size; i++) {
		if (values[i] > max) {
			max = values[i];
			result = i;
		}
	}
	return result;
}
