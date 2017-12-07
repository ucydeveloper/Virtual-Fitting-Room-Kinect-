#ifndef  __KINECTSKELETON_H 
#define __KINECTSKELETON_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <ole2.h>

#include <mmsystem.h>

#pragma comment ( lib, "winmm.lib" )

#include "NuiApi.h"

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"


#include "vector" 

#define PI 3.14159265

using namespace std;

static const CvScalar g_JointColorTable[NUI_SKELETON_POSITION_COUNT] = 
{
	CV_RGB(169, 176, 155), // NUI_SKELETON_POSITION_HIP_CENTER
	CV_RGB(169, 176, 155), // NUI_SKELETON_POSITION_SPINE
	CV_RGB(168, 230, 29),  // NUI_SKELETON_POSITION_SHOULDER_CENTER
	CV_RGB(200, 0,   0),   // NUI_SKELETON_POSITION_HEAD
	//CV_RGB(79,  84,  33),  // NUI_SKELETON_POSITION_SHOULDER_LEFT
	CV_RGB(0,  255,  0),
	CV_RGB(84,  33,  42),  // NUI_SKELETON_POSITION_ELBOW_LEFT
	CV_RGB(255, 126, 0),   // NUI_SKELETON_POSITION_WRIST_LEFT
	CV_RGB(215,  86, 0),   // NUI_SKELETON_POSITION_HAND_LEFT
	//CV_RGB(33,  79,  84),  // NUI_SKELETON_POSITION_SHOULDER_RIGHT
	CV_RGB(255,  0,  0), 
	CV_RGB(33,  33,  84),  // NUI_SKELETON_POSITION_ELBOW_RIGHT
	CV_RGB(77,  109, 243), // NUI_SKELETON_POSITION_WRIST_RIGHT
	CV_RGB(37,   69, 243), // NUI_SKELETON_POSITION_HAND_RIGHT
	CV_RGB(77,  109, 243), // NUI_SKELETON_POSITION_HIP_LEFT
	CV_RGB(69,  33,  84),  // NUI_SKELETON_POSITION_KNEE_LEFT
	CV_RGB(229, 170, 122), // NUI_SKELETON_POSITION_ANKLE_LEFT
	CV_RGB(255, 126, 0),   // NUI_SKELETON_POSITION_FOOT_LEFT
	CV_RGB(181, 165, 213), // NUI_SKELETON_POSITION_HIP_RIGHT
	CV_RGB(71, 222,  76),  // NUI_SKELETON_POSITION_KNEE_RIGHT
	CV_RGB(245, 228, 156), // NUI_SKELETON_POSITION_ANKLE_RIGHT
	CV_RGB(77,  109, 243)  // NUI_SKELETON_POSITION_FOOT_RIGHT
};

typedef struct _pos
{
    float x;
    float y;
    float z;
} pos;

typedef struct pos_3d
{
	float Pos[3]; //0 -> x
				  //1 -> y
				  //2 -> z
}pos_3d;



typedef struct _skeleton_joint
{
	pos spine;
	pos shoulder_center;
	pos head;

	pos left_shoulder;
	pos left_elbow;
	pos left_wrist;
	pos left_hand;
	pos right_shoulder;
	pos right_elbow;
	pos right_wrist;
	pos right_hand;	
	//test[18];
	//pos *mspine ; //= new pos [6];
	//pos *mhead ;

	float mspine[18];
	float mhead[18];
	vector <int> head_ssss;

}skeleton_joint;




class Clothes
{
public:
	Clothes();
	~Clothes();
	void setBasis( pos_3d vx, pos_3d vy, pos_3d vz);
	void setBasis( _pos vx, _pos vy, _pos vz);
    CvMat* getBasisptr();
private:
	CvMat *BasisC;//column 1 : x-axix
				  //column 2 : y-axix
				  //column 3 : z-axix
};








class CKinectSkeleton
{
public:
	    CKinectSkeleton();
        ~CKinectSkeleton();

		HRESULT                GetKinectSkeleton( );         
		void                   Nui_Zero( );
		void                   Nui_UnInit( );
		void                   SkeletonMapping( );
		void				   warpedmatrix( CvPoint originalInd[3], CvPoint desiredInd[3] ,float *Array3);

		IplImage               *image, *depthimg, *depthcol, *small_img,*ClothesImg;
		BYTE                   buf[320*240*3];
		skeleton_joint         ArmCrdSkltnJt;
		vector <int>           head;
		int                    num_person;
		int                    pedeindex[6];
		int                    prepedeindex[6];
		INuiSensor*            m_pNuiSensor;
		BSTR                   m_instanceId;      		
		bool                   bFoundSkeleton, bdep, bcol;
		USHORT                 * pBuff;
		NUI_SKELETON_FRAME     SkeletonFrame;

		CvPoint                ClothesJ[3],bodyJ[3];;
		//CvMat                  *Rotation;
		void PrintMatrix(CvMat *Matrix,int Rows,int Cols,int Channels);

private:
		static DWORD WINAPI    Nui_ProcessThread(LPVOID pParam);
		DWORD WINAPI           Nui_ProcessThread();

		void                   Nui_GotDepthAlert( );
		void                   Nui_GotVideoAlert( );
		void                   Nui_GotSkeletonAlert( );
		RGBQUAD                Nui_ShortToQuad_Depth( USHORT s );


		RGBQUAD                m_rgbWk[640*480];
		HDC                    m_SkeletonDC;
		HPEN                   m_Pen[NUI_SKELETON_COUNT];
		int                    m_PensTotal;

		POINT				   m_Points[NUI_SKELETON_COUNT][NUI_SKELETON_POSITION_COUNT],\
			                   m_Points_dep[NUI_SKELETON_COUNT][NUI_SKELETON_POSITION_COUNT];

		DWORD                  m_SkeletonIds[NUI_SKELETON_COUNT];
		
		HANDLE				   m_hNextDepthFrameEvent;
		HANDLE				   m_hNextColorFrameEvent;
		HANDLE				   m_hNextVideoFrameEvent;
		HANDLE				   m_hNextSkeletonEvent;

		HANDLE				   m_pDepthStreamHandle;
		HANDLE				   m_pVideoStreamHandle;

		HANDLE				   m_hThNuiProcess;
		HANDLE				   m_hEvNuiProcessStop;

		DWORD				   m_LastDepthFPStime;
		DWORD				   m_LastSkeletonFoundTime;

		int                    m_DepthFramesTotal;
		int                    m_LastDepthFramesTotal;

		bool                   m_bScreenBlanked;
		bool				   m_bAppTracking;


		float				   *RotationArray;
		//CvMat				   *temp;
		//CvMat				   *Result;
		float				   ClothesPixel[3];

		CvMat				   *A;
		CvMat				   *B;
		CvMat				   *ResultMatrix;
		CvMat				   *InvA;

		float				   Array1[36];
		float				   Array2[6];

		int					   PixelSum;
		float				   result[2];
		int					   position[2];

};







#endif