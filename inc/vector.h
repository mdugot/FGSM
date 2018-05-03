#ifndef VECTOR_H
#define VECTOR_H

#include "tools.h"
#include "fgsmException.h"

class Vector
{
	protected:

		double *values;
		int size;
	
	public:

		Vector(void);
		Vector(const Vector &from);
		Vector(double *values, int size);
		Vector(int size, double value = 0);
		~Vector();

		void print(int precision = 2);

		double getMax();
		double getMin();
		int getSize() const {return size;}

		double &operator[](int i) const {return values[i];}
		Vector operator+(Vector const &v2);
		Vector& operator=(Vector const &v2);

		Vector relu();
		Vector softmax();
		int argmax();
};

#endif
