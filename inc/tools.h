#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <time.h>
#include <limits>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#define PRINT_DEBUG true
#define DEBUG if (PRINT_DEBUG) std::cerr
#define PRINT_OUT true
#define ERR if (PRINT_ERR) std::cerr
#define PRINT_ERR true
#define OUT if (PRINT_OUT) std::cout
#define ABS(x) (x >= 0 ? x : -x)
#define SIGN(x) (x >= 0 ? 1 : -1)
#define BINARIZE(x) (x >= 0.5 ? 1 : 0)

#define DOUBLE_EPSILON 0.000001

class FgsmException;

enum ATTACK_TYPE {
	FGSM_NOISE, RANDOM_NOISE, FGSM_B_NOISE, RANDOM_B_NOISE, NO_ATTACK
};

void test(bool result, std::string message);
void unitest();
enum ATTACK_TYPE getAttackType(std::string arg);
void help();

#endif
