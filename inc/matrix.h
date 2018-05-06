#ifndef MATRIX_H
#define MATRIX_H

#include "tools.h"
#include "vector.h"

class Matrix
{
	private:

		double **values;
		int rows, columns;
	
	public:

		Matrix(const Matrix &from);
		Matrix(double *values, int rows, int columns);
		Matrix(int rows, int columns, double value = 0);
		~Matrix();

		void print(int precision = 2);

		double getMax();
		double getMin();
		int rowSize() const {return rows;}
		int columnSize() const {return columns;}
		double get(int i, int j) const {return values[i][j];}

		Vector row(int i);
		Vector column(int i);

		double* &operator[](int i) {return values[i];}
		Matrix& operator=(Matrix const &m2);
		Vector operator*(Vector const &v2);

		Matrix transpose();
};

bool operator== (const Matrix &m1, const Matrix &m2);
bool operator!= (const Matrix &m1, const Matrix &m2);

#endif
