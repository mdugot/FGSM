#ifndef PGM_H
#define PGM_H

#include "vector.h"

class Pgm : public Vector
{
	private:

		int w,h;
		int maxWhite;
	
	public:

		Pgm(void);
		Pgm(std::string filename);
		~Pgm();

		void save(std::string filename);
};

#endif

