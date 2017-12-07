#ifndef __CLOTHES_H
#define __CLOTHES_H

#include "KinectSkeleton.h"

class Clothes
{
public:
	Clothes();
	~Clothes();
	void setBasis( pos_3d vx, pos_3d vy, pos_3d vz);
    CvMat* getBasisptr();
private:
	CvMat *BasisC;//column 1 : x-axix
				  //column 2 : y-axix
				  //column 3 : z-axix
};


