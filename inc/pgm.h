#ifndef PGM_H
#define PGM_H

#include "vector.h"
#include <map>

class Pgm : public Vector
{
	private:

		int w,h;
		int maxWhite;
		std::string filename;
	
	public:

		Pgm(void);
		Pgm(const Pgm &from);
		Pgm(std::string filename);
		~Pgm();

		void save(std::string filename);
		Pgm addNoise(Vector &noise, double epsilon = 0.1);
		Pgm binarizedNoise(Vector &noise, double ratio = 0.01);

		int getW() const {return w;}
		int getH() const {return h;}
		int getMaxWhite() const {return maxWhite;}
		std::string getFilename() const {return filename;}
};

#endif

