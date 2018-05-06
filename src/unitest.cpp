#include "tools.h"
#include "vector.h"
#include "matrix.h"

void test(bool result, std::string message) {
	printf("%-30s", message.c_str());
	OUT << " : " << (result ? "OK" : "ERROR") << "\n";
}

void unitest() {
	OUT << "UNITEST:\n";
	Vector v1((double[4]){0, 0.5, 1, 1.5}, 4);
	Vector v2((double[4]){-0.2, -0.4, 0.2, 0.4}, 4);
	Matrix m((double[12]){1,2,3,4, 0.2,0.4,0.6,0.8, 0,-1,-10,-100}, 3, 4);

	Vector checkSum((double[4]){-0.2, 0.1, 1.2, 1.9}, 4);
	Vector checkSub((double[4]){0.2, 0.9, 0.8, 1.1}, 4);
	Vector checkProduct((double[4]){10,2,-160.5}, 3);
	Matrix checkTranspose((double[12]){1,0.2,0, 2,0.4,-1, 3,0.6,-10, 4,0.8,-100}, 4, 3);
	Vector checkRelu((double[4]){0,0,1,1}, 4);
	Vector checkSoftmax((double[4]){0.1015363,0.1674051,0.2760043,0.4550542}, 4);

	test(v1[2] == 1 && v1.get(3) == 1.5, "vector accessor");
	test(m[2][1] == -1 && m.get(0,3) == 4, "matrix accessor");
	test(v1.getSize() == 4, "vector size");
	test(m.rowSize() == 3 && m.columnSize() == 4, "matrix dimensions");
	test(v1.getMax() == 1.5, "vector max");
	test(v2.getMin() == -0.4, "vector min");
	test(m.getMax() == 4, "matrix max");
	test(m.getMin() == -100, "matrix min");
	test((v1 + v2) == checkSum, "vectors addition");
	test((v1 - v2) == checkSub, "vectors subtraction");
	test((m * v1) == checkProduct, "matrix and vector product");
	test(m.transpose() == checkTranspose, "matrix transpose");
	test(v2.relu() == checkRelu, "vector relu");
	test(v1.softmax() == checkSoftmax, "vector softmax");
}

