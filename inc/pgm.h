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

		static double epsilon;
		static double ratio;

		Pgm(void);
		Pgm(const Pgm &from);
		Pgm(std::string filename);
		~Pgm();

		void save(std::string filename);
		Pgm addNoise(Vector &noise);
		Pgm binarizedNoise(Vector &noise);

		int getW() const {return w;}
		int getH() const {return h;}
		int getMaxWhite() const {return maxWhite;}
		std::string getFilename() const {return filename;}
};

#endif

