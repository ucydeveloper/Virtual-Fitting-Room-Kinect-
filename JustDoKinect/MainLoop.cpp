#include "MainLoop.h"
#include <iostream>
//	HANDLE thread_seg = 0;
//	thread_seg = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)RenderScene_Thread,(void*)0,0,&tid_Render);

CKinectSkeleton KinectClass;
// Global variable
//CvMat *PreBasis = cvCreateMatHeader(3,3,CV_32FC1);
//CvMat *Rotation = cvCreateMatHeader(3,3,CV_32FC1);

// Function Declaration
void RotationMatrix( CvMat Rotation, CvMat *BasisB, CvMat *BasisC);
pos_3d Unitised(pos_3d v);
float dot(pos_3d a,pos_3d b);




// Do the projection from u,v,depth to X,Y,Z directly in an opengl matrix
// These numbers come from a combination of the ros kinect_node wiki, and
// nicolas burrus' posts.
void LoadVertexMatrix()
{
    float fx = 594.21f;
    float fy = 591.04f;
    float a = -0.0030711f;
    float b = 3.3309495f;
    float cx = 339.5f;
    float cy = 242.7f;
    GLfloat mat[16] = {
        1/fx,        0,  0,  0,
            0,  -1/fy,  0,  0,
            0,        0,  0,  a,
     -cx/fx,  cy/fy, -1, b
    };
    glMultMatrixf(mat);
}
//void warpedmatrix( CvPoint originalInd[3], CvPoint desiredInd[3],float *Array3)


// This matrix comes from a combination of nicolas burrus's calibration post
// and some python code I haven't documented yet.
void LoadRGBMatrix()
{
    float mat[16] = {
        5.34866271e+02,   3.89654806e+00,   0.00000000e+00,   1.74704200e-02,
        -4.70724694e+00,  -5.28843603e+02,   0.00000000e+00,  -1.22753400e-02,
        -3.19670762e+02,  -2.60999685e+02,   0.00000000e+00,  -9.99772000e-01,
        -6.98445586e+00,   3.31139785e+00,   0.00000000e+00,   1.09167360e-02
    };
    glMultMatrixf(mat);
}

void mouseMoved(int x, int y)
{
    if (mx>=0 && my>=0) {
        rotangles[0] += y-my;
        rotangles[1] += x-mx;
    }
    mx = x;
    my = y;
}

void mousePress(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mx = x;
        my = y;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mx = -1;
        my = -1;
    }
}


void DrawGLScene()
{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//
//	//glPushMatrix();
//    glScalef(zoom,zoom,1);
//    glTranslatef(0,0,0);
//    glRotatef(rotangles[0], 1,0,0);
//    glRotatef(rotangles[1], 0,1,0);
//    glTranslatef(0,0,0);
//	gluLookAt(
//	0,0,-1,
//	0,0,1,
//	0,1,0 );
//	glPushMatrix();
//
////-----------------------ALL----------------------------------//
//	//modern basis
//	CvMat *Basis = cvCreateMatHeader(3,3,CV_32FC1);
//	for(int i=0;i<6;i++)
//	{
//		if(KinectClass.pedeindex[i])
//		{
//			switch(i)
//			{
//				case 0:
//					glColor3f(1.,1.,1.);
//					break;				
//				case 1:
//					glColor3f(1.,0.,0.);
//					break;
//				case 2:
//					glColor3f(0.,1.,0.);
//					break;
//				case 3:
//					glColor3f(0.,1.,1.);
//					break;
//				case 4:
//					glColor3f(1.,1.,0.);
//					break;
//				default:
//					glColor3f(1.,0.5,1.);
//					break;
//			}
//
//
//		pos_3d head, shoulderL, shoulderR, elbowL, elbowR, wristL, wristR, spine, shoulderC;
//		pos_3d BasisBx, BasisBy, BasisBz, ClothesTri1, ClothesTri2, ClothesTri3;
//		
//		head.Pos[0] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HEAD].x;
//		head.Pos[1] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HEAD].y;
//		head.Pos[2] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HEAD].z/3.0;
//		elbowR.Pos[0] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT].x;
//		elbowR.Pos[1] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT].y;
//		elbowR.Pos[2] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT].z/3.0;
//		shoulderR.Pos[0] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_RIGHT].x;
//		shoulderR.Pos[1] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_RIGHT].y;
//		shoulderR.Pos[2] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_RIGHT].z/3.0;
//		wristR.Pos[0] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_WRIST_RIGHT].x;
//		wristR.Pos[1] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_WRIST_RIGHT].y;
//		wristR.Pos[2] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_WRIST_RIGHT].z/3.0;
//		elbowL.Pos[0] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT].x;
//		elbowL.Pos[1] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT].y;
//		elbowL.Pos[2] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT].z/3.0;
//		shoulderL.Pos[0] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_LEFT].x;
//		shoulderL.Pos[1] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_LEFT].y;
//		shoulderL.Pos[2] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_LEFT].z/3.0;
//		wristL.Pos[0] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_WRIST_LEFT].x;
//		wristL.Pos[1] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_WRIST_LEFT].y;
//		wristL.Pos[2] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_WRIST_LEFT].z/3.0;
//		spine.Pos[0]=KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SPINE].x;
//		spine.Pos[1]=KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SPINE].y;
//		spine.Pos[2]=KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SPINE].z/3.0;
//		shoulderC.Pos[0] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER].x;
//		shoulderC.Pos[1] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER].y;
//		shoulderC.Pos[2] = KinectClass.SkeletonFrame.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER].z/3.0;



		//glPushMatrix();
		//	glBegin(GL_LINE_STRIP);
		//	glVertex3f(wristL.Pos[0],wristL.Pos[1],wristL.Pos[2]);
		//	glVertex3f(elbowL.Pos[0],elbowL.Pos[1],elbowL.Pos[2]);
		//	glVertex3f(shoulderL.Pos[0],shoulderL.Pos[1],shoulderL.Pos[2]);
		//	glVertex3f(shoulderR.Pos[0],shoulderR.Pos[1],shoulderR.Pos[2]);
		//	glVertex3f(elbowR.Pos[0],elbowR.Pos[1],elbowR.Pos[2]);
		//	glVertex3f(wristR.Pos[0],wristR.Pos[1],wristR.Pos[2]);
		//	glEnd();

		//	glBegin(GL_LINE_STRIP);
		//	glVertex3f(shoulderC.Pos[0],shoulderC.Pos[1],shoulderC.Pos[2]);
		//	glVertex3f(spine.Pos[0],spine.Pos[1],spine.Pos[2]);
		//	glEnd();


		//	glPointSize (10); 
		//	glBegin ( GL_POINTS ); 
		//	glVertex3f(head.Pos[0],head.Pos[1],head.Pos[2]);
		//	glEnd();

		//	glPointSize (10); 
		//	glBegin ( GL_POINTS ); 
		//	glVertex3f(shoulderC.Pos[0],shoulderC.Pos[1],shoulderC.Pos[2]);
		//	glEnd();

		//	glPointSize (10); 
		//	glBegin ( GL_POINTS ); 
		//	glVertex3f(shoulderR.Pos[0],shoulderR.Pos[1],shoulderR.Pos[2]);
		//	glEnd();

		//	glPointSize (10); 
		//	glBegin ( GL_POINTS ); 
		//	glVertex3f(shoulderL.Pos[0],shoulderL.Pos[1],shoulderL.Pos[2]);
		//	glEnd();

		//	glPointSize (10); 
		//	glBegin ( GL_POINTS ); 
		//	glVertex3f(elbowR.Pos[0],elbowR.Pos[1],elbowR.Pos[2]);
		//	glEnd();

		//	glPointSize (10); 
		//	glBegin ( GL_POINTS ); 
		//	glVertex3f(elbowL.Pos[0],elbowL.Pos[1],elbowL.Pos[2]);
		//	glEnd();

		//	glPointSize (10); 
		//	glBegin ( GL_POINTS ); 
		//	glVertex3f(wristL.Pos[0],wristL.Pos[1],wristL.Pos[2]);
		//	glEnd();

		//	glPointSize (10); 
		//	glBegin ( GL_POINTS ); 
		//	glVertex3f(wristR.Pos[0],wristR.Pos[1] ,wristR.Pos[2] );
		//	glEnd();

		//	glPointSize (10); 
		//	glBegin ( GL_POINTS ); 
		//	glVertex3f(head.Pos[0],head.Pos[1],head.Pos[2]);
		//	glEnd();

		//	glPointSize (10); 
		//	glBegin ( GL_POINTS ); 
		//	glVertex3f(spine.Pos[0],spine.Pos[1],spine.Pos[2]);
		//	//printf("spine:%f %f %f\n",spine.Pos[0],spine.Pos[1],spine.Pos[2]);
		//	glEnd();


		//    
		//
		//	glColor3f(0.5,0.5,1.0);
  //          glBegin(GL_TRIANGLES);
	 //       glVertex3f(shoulderL.Pos[0],shoulderL.Pos[1],shoulderL.Pos[2]);
  //          glVertex3f(shoulderR.Pos[0],shoulderR.Pos[1],shoulderR.Pos[2]);
  //          glVertex3f(spine.Pos[0],spine.Pos[1],spine.Pos[2]);
		//	glEnd();


		//glPopMatrix();

		/*}

	}

	glPopMatrix();
	glutSwapBuffers();


*/
}



void keyPressed(unsigned char key, int x, int y)
{
    if (key == 27) {
		KinectClass.Nui_UnInit();
        glutDestroyWindow(window);
        exit(0);
    }
	if (key == 'k')
		HRESULT hr = KinectClass.GetKinectSkeleton();
    if (key == 'w')
        zoom *= 1.1f;
    if (key == 's')
        zoom /= 1.1f;
	if (key == 'f')
        color = !color;

}

void ReSizeGLScene(int Width, int Height)
{
    glViewport(0,0,Width,Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45, 4/3, 0.3, 200000);
	gluPerspective(45, 4/3., 0.3, 200);
	//glOrtho(-5,5,-5,5,-5,5);      
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void InitGL(int Width, int Height)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glGenTextures(1, &gl_rgb_tex);
    glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    ReSizeGLScene(Width, Height);
}

void PrintMatrix(CvMat *Matrix,int Rows,int Cols,int Channels)
{
    for(int i=0;i<Rows;i++)
    {
        for(int j=0;j<Cols;j++)
        {
            for(int k=0;k<Channels;k++)
            {
                printf("%.2f ",cvGet2D(Matrix,i,j).val[k]);
            }
        }
        printf("\n");
    }
}


int main(int argc, char **argv)
{

 //   glutInit(&argc, argv);

	//cvNamedWindow("clothes",1);
    //cvShowImage("clothes",ClothesImg);




	//IplImage *person;
	//IplImage *clothes;
	//person = cvLoadImage("person.jpg",1);
	//clothes = cvLoadImage("frontm.jpg",1);

	//                CvPoint ClothesJ[3] = {{118,46},{523,47},{320,500}};
	//				CvPoint bodyJ[3] = { {120,258},{355,295},{250,555} }; 
	//				CvMat *R = cvCreateMat(3,3,CV_32FC1);
	//				float *RotationArray = new float[6];
	//				warpedmatrix( ClothesJ, bodyJ, RotationArray );
	//				
	//				/*for(int i=0;i<3;i++){
	//					for(int j=0;j<3;j++)
	//						printf( "%f  ",R->data.fl[i*R->cols+j]);
	//					printf("\n");
	//					}*/

	//				for(int i =44;i<clothes->width;i++)
	//					for(int j=0;j<clothes->height;j++){
	//						int sum = cvGet2D(clothes,j,i).val[0] + cvGet2D(clothes,j,i).val[1] + cvGet2D(clothes,j,i).val[2];
	//						//printf("i=%d j=%d, r=%f g=%f b=%f\n",i,j,cvGet2D(ClothesImg,j,i).val[0],cvGet2D(ClothesImg,j,i).val[1],cvGet2D(ClothesImg,j,i).val[2]);
	//						if( sum<700 ){//not white pixel
	//							CvMat *temp = cvCreateMat(3,1,CV_32FC1);
	//							CvMat *Result = cvCreateMat(3,1,CV_32FC1);
	//							float Array[3] = {i,j,1};
	//							cvSetData(temp,Array,temp->step);


	//							cvmMul(R,temp,Result);

	//							//in the boundary of video image
	//							int position[2] = { (int)(cvmGet(Result,0,0)), (int)(cvmGet(Result,1,0)) };
	//							//printf("result:%f %f\n",cvmGet(Result,0,0),cvmGet(Result,1,0));
	//							//printf("result:%f %f  r:%f g:%f b:%f\n",cvGet2D(Result,0,0).val[0],cvGet2D(Result,1,0).val[0],cvGet2D(clothes,i,j).val[0],cvGet2D(clothes,i,j).val[1],cvGet2D(clothes,i,j).val[2]);
	//							if( position[0]>=0 && position[1]<person->width && position[1]>=0 && position[1]<person->height){
	//									cvSet2D( person, position[1], position[0], CV_RGB(cvGet2D(clothes,i,j).val[0],cvGet2D(clothes,i,j).val[1],cvGet2D(clothes,i,j).val[2]) );
	//									//printf("%d %d r:%f g:%f b:%f\n",position[1], position[0],cvGet2D(clothes,i,j).val[0],cvGet2D(clothes,i,j).val[1],cvGet2D(clothes,i,j).val[2]);
	//							}
	//						cvReleaseMat(&temp);
	//						cvReleaseMat(&Result);
	//						}
	//					}
	//				cvReleaseMat(&R);

	//cvSet2D( person,50,0, CV_RGB(255,0,0) );
 //   cvNamedWindow("test",1);
 //   cvShowImage("test",person);

	//cvWaitKey(0);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(320, 240);
    glutInitWindowPosition(750, 0);

    window = glutCreateWindow("JustDoKinect");


    glutDisplayFunc(&DrawGLScene);
    glutIdleFunc(&DrawGLScene);
    glutReshapeFunc(&ReSizeGLScene);
    glutKeyboardFunc(&keyPressed);
    glutMotionFunc(&mouseMoved);
    glutMouseFunc(&mousePress);

    InitGL(320, 240);

	glutMainLoop();


	//cvReleaseImage(&ClothesImg);
    //cvDestroyWindow("clothes");


    return 0;
}



//void warpedmatrix( CvPoint originalInd[3], CvPoint desiredInd[3],float *Array3){
//	CvMat *A = cvCreateMat(6,6,CV_32FC1);
//	CvMat *B = cvCreateMat(6,1,CV_32FC1);
//	CvMat *ResultMatrix = cvCreateMat(6,1,CV_32FC1);
//	CvMat *InvA=cvCreateMat(6,6,CV_32FC1);
//	float Array1[36]={originalInd[0].x,originalInd[0].y,1,0,0,0,\
//					  0,0,0,originalInd[0].x,originalInd[0].y,1,\
//					  originalInd[1].x,originalInd[1].y,1,0,0,0,\
//				      0,0,0,originalInd[1].x,originalInd[1].y,1,\
//				      originalInd[2].x,originalInd[2].y,1,0,0,0,\
//				      0,0,0,originalInd[2].x,originalInd[2].y,1};
//	cvSetData(A,Array1,A->step);
//	float Array2[6]={desiredInd[0].x,desiredInd[0].y,\
//					 desiredInd[1].x,desiredInd[1].y,\
//					 desiredInd[2].x,desiredInd[2].y};
//	cvSetData(B,Array2,B->step);
//	cvInvert(A,InvA,CV_LU);
//	cvmMul(InvA,B,ResultMatrix);
//
//
//	for(int i=0;i<6;i++)
//		Array3[i] = cvGet2D(ResultMatrix,i,0).val[0];
//	Array3[6] = 0;
//	Array3[7] = 0;
//	Array3[8] = 1;
//	
//	
//	
//	cvReleaseMat(&A);
//	cvReleaseMat(&B);
//	cvReleaseMat(&InvA);
//	cvReleaseMat(&ResultMatrix);
//}













//void RotationMatrix( CvMat *Rotation, CvMat *BasisB, CvMat *BasisC)
//{ 
//	cvSetData(A,MatrixData1,A->step);
//	cvSetData(B,MatrixData1,B->step);
//
//	cvmMul(A,B,C);
//	cvMatMul(A,B,C);
//    PrintMatrix(C,3,3,1);
//
//}

pos_3d Unitised(pos_3d v){
    float sum = 0;
	for(int i =0;i<3;i++)
		sum += v.Pos[i]*v.Pos[i];
	pos_3d d = { v.Pos[0]/sum, v.Pos[1]/sum, v.Pos[2]/sum };
	return d;
}

float dot(pos_3d a, pos_3d b){
	float sum = 0;
	for(int i=0;i<3;i++)
		sum += a.Pos[i]*b.Pos[i];
	return sum;
}