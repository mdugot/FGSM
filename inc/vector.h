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

		static Vector oneHotVector(int numberLabels, int label);
		static Vector randomVector(int size, double min, double max);

		Vector(void);
		Vector(const Vector &from);
		Vector(double *values, int size);
		Vector(int size, double value = 0);
		~Vector();

		void print(int precision = 2);

		double getMax();
		double getMin();
		double sum();
		int getSize() const {return size;}
		double get(int i) const {return values[i];}

		double &operator[](int i) const {return values[i];}
		Vector operator+(Vector const &v2);
		Vector operator-(Vector const &v2);
		Vector& operator=(Vector const &v2);

		Vector relu();
		Vector softmax();
		Vector binarize();
		int argmax(double *v = NULL);
};

bool operator== (const Vector &v1, const Vector &v2);
bool operator!= (const Vector &v1, const Vector &v2);

#endif
