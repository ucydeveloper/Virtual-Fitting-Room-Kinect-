#include "KinectSkeleton.h"
#include<iostream>

Clothes::Clothes()
{
	BasisC = cvCreateMat(3,3,CV_32FC1);
	float v[9] = {0,0,0,0,0,0,0,0,0};
	cvSetData( BasisC,v,BasisC->step );
}

Clothes::~Clothes()
{
   cvReleaseMatHeader(&BasisC);
}

void Clothes::setBasis(pos_3d vx, pos_3d vy, pos_3d vz){

	float v[9] = { vx.Pos[0], vy.Pos[0], vz.Pos[0], vx.Pos[1], vy.Pos[1], vz.Pos[1], vx.Pos[2], vy.Pos[2], vz.Pos[2] };
	cvSetData( BasisC,v,BasisC->step );
}

void Clothes::setBasis(_pos vx, _pos vy, _pos vz){

	float v[9] = { vx.x, vy.x, vz.x, vx.y, vy.y, vz.y, vx.z, vy.z, vz.z };
	cvSetData( BasisC,v,BasisC->step );
}


CvMat* Clothes::getBasisptr()
{
	return BasisC;
}