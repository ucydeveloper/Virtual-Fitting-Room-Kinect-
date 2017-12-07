#include "KinectSkeleton.h"

#include <iostream>

//lookups for color tinting based on player index

static const int g_IntensityShiftByPlayerR[] = { 1, 2, 0, 2, 0, 0, 2, 0 };
static const int g_IntensityShiftByPlayerG[] = { 1, 2, 2, 0, 2, 0, 0, 1 };
static const int g_IntensityShiftByPlayerB[] = { 1, 0, 2, 2, 0, 2, 0, 2 };
CvPoint skeletonPoint[NUI_SKELETON_COUNT][NUI_SKELETON_POSITION_COUNT]={cvPoint(0,0)}; 
CvPoint colorPoint[NUI_SKELETON_COUNT][NUI_SKELETON_POSITION_COUNT]={cvPoint(0,0)}; 

#if !defined(MATRIX_H)
#define MATRIX_H
 
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <math.h>
 
class CMatrix
{
private:
    int m_rows;
    int m_cols;
    char m_name[128];
 
    CMatrix();
public:
    double **m_pData;
 
    CMatrix(const char *name, int rows, int cols) : m_rows(rows), m_cols(cols)
    {
        strcpy(m_name, name);
        m_pData = new double*[m_rows];
        for(int i = 0; i < m_rows; i++)
            m_pData[i] = new double[m_cols];
 
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m_pData[i][j] = 0.0;
            }
        }
    }
 
    CMatrix(const CMatrix &other)
    {
        strcpy(m_name, other.m_name);
        m_rows = other.m_rows;
        m_cols = other.m_cols;
 
        m_pData = new double*[m_rows];
        for(int i = 0; i < m_rows; i++)
            m_pData[i] = new double[m_cols];
 
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m_pData[i][j] = other.m_pData[i][j];
            }
        }
    }
 
    ~CMatrix()
    {
        for(int i = 0; i < m_rows; i++)
            delete [] m_pData[i];
        delete [] m_pData;
        m_rows = m_cols = 0;
    }
 
    void SetName(const char *name) { strcpy(m_name, name); }
    const char* GetName() const { return m_name; }
 
    void GetInput()
    {
        std::cin >> *this;
    }
 
    void FillSimulatedInput(CvPoint originalInd[3], CvPoint desiredInd[3])
    {
        static int factor1 = 1, factor2 = 2;
        std::cout << "\n\nEnter Input For Matrix : " << m_name << " Rows: " << m_rows << " Cols: " << m_cols << "\n";

			m_pData[0][0] = originalInd[0].x;
			m_pData[0][1] = originalInd[0].y;
			m_pData[0][2] = 1;
			m_pData[0][3] = 0;
			m_pData[0][4] = 0;
			m_pData[0][5] = 0;
			m_pData[1][0] = 0;
			m_pData[1][1] = 0;
	m_pData[1][2] = 0;
	m_pData[1][3] = originalInd[0].x;
	m_pData[1][4] = originalInd[0].y;
	m_pData[1][5] = 1;
	m_pData[2][0] = originalInd[1].x;
	m_pData[2][1] = originalInd[1].y;
	m_pData[2][2] = 1;
	m_pData[2][3] = 0;
	m_pData[2][4] = 0;
	m_pData[2][5] = 0;
	m_pData[3][0] = 0;
	m_pData[3][1] = 0;
	m_pData[3][2] = 0;
	m_pData[3][3] = originalInd[1].x;
	m_pData[3][4] = originalInd[1].y;
	m_pData[3][5] = 1;
	m_pData[4][0] = originalInd[2].x;
	m_pData[4][1] = originalInd[2].y;
	m_pData[4][2] = 1;
	m_pData[4][3] = 0;
	m_pData[4][4] = 0;
	m_pData[4][5] = 0;
	m_pData[5][0] = 0;
	m_pData[5][1] = 0;
	m_pData[5][2] = 0;
	m_pData[5][3] = originalInd[2].x;
	m_pData[5][4] = originalInd[2].y;
	m_pData[5][5] = 1;
	//cvSetData(A,Array1,A->step);

	//Array2[0] = desiredInd[0].x;
	//Array2[1] = desiredInd[0].y;
	//Array2[2] = desiredInd[1].x;
	//Array2[3] = desiredInd[1].y;
	//Array2[4] = desiredInd[2].x;
	//Array2[5] = desiredInd[2].y;
	//cvSetData(B,Array2,B->step);

		

        //for(int i = 0; i < m_rows; i++)
        //{
        //    for(int j = 0; j < m_cols; j++)
        //    {
        //        std::cout << "Input For Row: " << i + 1 << " Col: " << j + 1 << " = ";
        //        //int data = ((i + 1) * factor1) + (j + 1) * factor2;
        //        //m_pData[i][j] = data / 10.2;


        //        //std::cout << m_pData[i][j] << "\n";
 
        //        //factor1 += (rand() % 4);
        //        //factor2 += (rand() % 3);
        //    }
        //    std::cout << "\n";
        //}
 
        std::cout << "\n";
    }   
 
    double Determinant()
    {
        double det = 0;
        double **pd = m_pData;
        switch(m_rows)
        {
       
        case 2:
        {
            det = pd[0][0] * pd[1][1] - pd[0][1] * pd[1][0];
            return det;
        }
        break;
 
        case 3:
        {
            /***
            a b c
            d e f
            g h i
 
            a b c a b c
            d e f d e f
            g h i g h i
 
            // det (A) = aei + bfg + cdh - afh - bdi - ceg.
            ***/
 
            double a = pd[0][0];
            double b = pd[0][1];
            double c = pd[0][2];
 
            double d = pd[1][0];
            double e = pd[1][1];
            double f = pd[1][2];
 
            double g = pd[2][0];
            double h = pd[2][1];
            double i = pd[2][2];
 
            double det = (a*e*i + b*f*g + c*d*h);
            det = det - a*f*h;
            det = det - b*d*i;
            det = det - c*e*g;
 
            return det;
        }
        break;
 
        case 4:
        {
            CMatrix *temp[4];
            for(int i = 0; i < 4; i++)
                temp[i] = new CMatrix("", 3,3);
 
            for(int k = 0; k < 4; k++)
            {
               
                for(int i = 1; i < 4; i++)
                {
                    int j1 = 0;
                    for(int j = 0; j < 4; j++)
                    {
                        if(k == j)
                            continue;
                        temp[k]->m_pData[i-1][j1++] = this->m_pData[i][j];
                    }
                }
            }
            double det = this->m_pData[0][0] * temp[0]->Determinant() -
            this->m_pData[0][1] * temp[1]->Determinant() +
            this->m_pData[0][2] * temp[2]->Determinant() -
            this->m_pData[0][3] * temp[3]->Determinant();
            return det;
        }
        break;
 
        case 5:
        {
            CMatrix *temp[5];
            for(int i = 0; i < 5; i++)
                temp[i] = new CMatrix("", 4,4);
 
            for(int k = 0; k < 5; k++)
            {
               
                for(int i = 1; i < 5; i++)
                {
                    int j1 = 0;
                    for(int j = 0; j < 5; j++)
                    {
                        if(k == j)
                            continue;
                        temp[k]->m_pData[i-1][j1++] = this->m_pData[i][j];
                    }
                }
            }
            double det = this->m_pData[0][0] * temp[0]->Determinant() -
            this->m_pData[0][1] * temp[1]->Determinant() +
            this->m_pData[0][2] * temp[2]->Determinant() -
            this->m_pData[0][3] * temp[3]->Determinant() +
            this->m_pData[0][4] * temp[4]->Determinant();
            return det;
        }
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        default:
        {
            int DIM = m_rows;
            CMatrix **temp = new CMatrix*[DIM];
            for(int i = 0; i < DIM; i++)
                temp[i] = new CMatrix("", DIM - 1,DIM - 1);
 
            for(int k = 0; k < DIM; k++)
            {
               
                for(int i = 1; i < DIM; i++)
                {
                    int j1 = 0;
                    for(int j = 0; j < DIM; j++)
                    {
                        if(k == j)
                            continue;
                        temp[k]->m_pData[i-1][j1++] = this->m_pData[i][j];
                    }
                }
            }
 
            double det = 0;
            for(int k = 0; k < DIM; k++)
            {
                if( (k %2) == 0)
                    det = det + (this->m_pData[0][k] * temp[k]->Determinant());
                else
                    det = det - (this->m_pData[0][k] * temp[k]->Determinant());
            }
 
            for(int i = 0; i < DIM; i++)
                delete temp[i];
            delete [] temp;
 
            return det;
        }
        break;
        }
    }
 
    CMatrix& operator = (const CMatrix &other)
    {
        if( this->m_rows != other.m_rows ||
            this->m_cols != other.m_cols)
        {
            std::cout << "WARNING: Assignment is taking place with by changing the number of rows and columns of the matrix";
        }
        for(int i = 0; i < m_rows; i++)
            delete [] m_pData[i];
        delete [] m_pData;
        m_rows = m_cols = 0;
 
        strcpy(m_name, other.m_name);
        m_rows = other.m_rows;
        m_cols = other.m_cols;
 
        m_pData = new double*[m_rows];
        for(int i = 0; i < m_rows; i++)
            m_pData[i] = new double[m_cols];
 
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m_pData[i][j] = other.m_pData[i][j];
            }
        }
 
        return *this;
    }
 
    CMatrix CoFactor()
    {
        CMatrix cofactor("COF", m_rows, m_cols);
        if(m_rows != m_cols)
            return cofactor;
 
        if(m_rows < 2)
            return cofactor;
        else if(m_rows == 2)
        {
            cofactor.m_pData[0][0] = m_pData[1][1];
            cofactor.m_pData[0][1] = -m_pData[1][0];
            cofactor.m_pData[1][0] = -m_pData[0][1];
            cofactor.m_pData[1][1] = m_pData[0][0];
            return cofactor;
        }
        else if(m_rows >= 3)
        {
            int DIM = m_rows;
            CMatrix ***temp = new CMatrix**[DIM];
            for(int i = 0; i < DIM; i++)
                temp[i] = new CMatrix*[DIM];
            for(int i = 0; i < DIM; i++)
                for(int j = 0; j < DIM; j++)
                    temp[i][j] = new CMatrix("", DIM - 1,DIM - 1);
 
            for(int k1 = 0; k1 < DIM; k1++)
            {  
                for(int k2 = 0; k2 < DIM; k2++)
                {
                    int i1 = 0;
                    for(int i = 0; i < DIM; i++)
                    {
                        int j1 = 0;
                        for(int j = 0; j < DIM; j++)
                        {
                            if(k1 == i || k2 == j)
                                continue;
                            temp[k1][k2]->m_pData[i1][j1++] = this->m_pData[i][j];
                        }
                        if(k1 != i)
                            i1++;
                    }
                }
            }
 
            bool flagPositive = true;
            for(int k1 = 0; k1 < DIM; k1++)
            {  
                flagPositive = ( (k1 % 2) == 0);
 
                for(int k2 = 0; k2 < DIM; k2++)
                {
                    if(flagPositive == true)
                    {
                        cofactor.m_pData[k1][k2] = temp[k1][k2]->Determinant();
                        flagPositive = false;
                    }
                    else
                    {
                        cofactor.m_pData[k1][k2] = -temp[k1][k2]->Determinant();
                        flagPositive = true;
                    }
                }
               
            }
 
            for(int i = 0; i < DIM; i++)
                for(int j = 0; j < DIM; j++)
                    delete temp[i][j];
 
            for(int i = 0; i < DIM; i++)
                delete [] temp[i];
 
            delete [] temp;
        }
        return cofactor;
    }
 
    CMatrix Adjoint()
    {
        CMatrix cofactor("COF", m_rows, m_cols);
        CMatrix adj("ADJ", m_rows, m_cols);
        if(m_rows != m_cols)
            return adj;
 
        cofactor = this->CoFactor();
           
        // adjoint is transpose of a cofactor of a matrix
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                adj.m_pData[j][i] = cofactor.m_pData[i][j];
            }
        }
        return adj;
    }
 
    CMatrix Transpose()
    {
        CMatrix trans("TR", m_cols, m_rows);
 
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                trans.m_pData[j][i] = m_pData[i][j];
            }
        }
        return trans;
    }
 
    CMatrix Inverse()
    {
        CMatrix cofactor("COF", m_rows, m_cols);
        CMatrix inv("INV", m_rows, m_cols);
        if(m_rows != m_cols)
            return inv;
 
        // to find out Determinant
        double det = Determinant();
 
        cofactor = this->CoFactor();
           
        // inv = transpose of cofactor / Determinant
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                inv.m_pData[j][i] = cofactor.m_pData[i][j] / det;
            }
        }
        return inv;
    }
 
    CMatrix operator + (const CMatrix &other)
    {
        if( this->m_rows != other.m_rows ||
            this->m_cols != other.m_cols)
        {
            std::cout << "Addition could not take place because number of rows and columns are different between the two matrices";
            return *this;
        }
 
        CMatrix result("", m_rows, m_cols);
 
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                result.m_pData[i][j] = this->m_pData[i][j] + other.m_pData[i][j];
            }
        }
        return result;
    }
 
    CMatrix operator - (const CMatrix &other)
    {
        if( this->m_rows != other.m_rows ||
            this->m_cols != other.m_cols)
        {
            std::cout << "Subtraction could not take place because number of rows and columns are different between the two matrices";
            return *this;
        }
 
        CMatrix result("", m_rows, m_cols);
 
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                result.m_pData[i][j] = this->m_pData[i][j] - other.m_pData[i][j];
            }
        }
        return result;
    }
 
 
 
    CMatrix operator * (const CMatrix &other)
    {
        if( this->m_cols != other.m_rows)
        {
            std::cout << "Multiplication could not take place because number of columns of 1st Matrix and number of rows in 2nd Matrix are different";
            return *this;
        }
 
        CMatrix result("", this->m_rows, other.m_cols);
 
        for(int i = 0; i < this->m_rows; i++)
        {
            for(int j = 0; j < other.m_cols; j++)
            {
                for(int k = 0; k < this->m_cols; k++)
                {
                    result.m_pData[i][j] += this->m_pData[i][k] * other.m_pData[k][j];
                }
            }
        }
        return result;
    }
 
    bool operator == (const CMatrix &other)
    {
        if( this->m_rows != other.m_rows ||
            this->m_cols != other.m_cols)
        {
            std::cout << "Comparision could not take place because number of rows and columns are different between the two matrices";
            return false;
        }
 
        CMatrix result("", m_rows, m_cols);
 
        bool bEqual = true;
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                if(this->m_pData[i][j] != other.m_pData[i][j])
                    bEqual = false;
            }
        }
        return bEqual;
    }
 
 
    friend std::istream& operator >> (std::istream &is, CMatrix &m);
    friend std::ostream& operator << (std::ostream &os, const CMatrix &m);   
};
 
std::istream& operator >> (std::istream &is, CMatrix &m)
{
    std::cout << "\n\nEnter Input For Matrix : " << m.m_name << " Rows: " << m.m_rows << " Cols: " << m.m_cols << "\n";
    for(int i = 0; i < m.m_rows; i++)
    {
        for(int j = 0; j < m.m_cols; j++)
        {
            std::cout << "Input For Row: " << i + 1 << " Col: " << j + 1 << " = ";
            is >> m.m_pData[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    return is;
}
 
std::ostream& operator << (std::ostream &os,const CMatrix &m)
{
    os << "\n\nMatrix : " << m.m_name << " Rows: " << m.m_rows << " Cols: " << m.m_cols << "\n\n";
    for(int i = 0; i < m.m_rows; i++)
    {
        os << " | ";
        for(int j = 0; j < m.m_cols; j++)
        {
            char buf[32];
            double data = m.m_pData[i][j];
            if( m.m_pData[i][j] > -0.00001 &&
                m.m_pData[i][j] < 0.00001)
                data = 0;
            sprintf(buf, "%10.2lf ", data);
            os <<  buf;
        }
        os << "|\n";
    }
    os << "\n\n";
    return os;
}
 
 
#endif







static const COLORREF g_SkeletonColors[NUI_SKELETON_COUNT] =
{
    RGB( 255, 0, 0),
    RGB( 0, 255, 0 ),
    RGB( 64, 255, 255 ),
    RGB( 255, 255, 64 ),
    RGB( 255, 64, 255 ),
    RGB( 128, 128, 255 )
};


CKinectSkeleton::CKinectSkeleton()
{
	
}

CKinectSkeleton::~CKinectSkeleton()
{

	Nui_Zero();
}

void CKinectSkeleton::Nui_Zero()
{
  	if (m_pNuiSensor)
    {
        m_pNuiSensor->Release();
        m_pNuiSensor = NULL;
    }
	//IplImage * temp = cvLoadImage("frontm.jpg",1);
	//CvSize LoadSize;
	//LoadSize = cvSize(temp->width,temp->height);
 //   
	////need to change the size
	//uchar imageData1[695][640*3];
	//ClothesImg = cvCreateImageHeader( LoadSize,IPL_DEPTH_8U,3 );

	//
 //   cvSetImageData(ClothesImg,imageData1,ClothesImg->widthStep);
	//for( int i=0; i< LoadSize.height; i++ )
	//	for( int j=0; j< LoadSize.width; j++ )
	//		cvSet2D( ClothesImg, j, i, CV_RGB() );
    //cvSet(ClothesImg,cvScalar(24.4,15.7,100.1));
	ClothesImg = cvLoadImage("frontm.jpg",1);

	//right_shoulder
	ClothesJ[0].x = 118;
	ClothesJ[0].y = 46;
	//left_shoulder
	ClothesJ[1].x = 523;
	ClothesJ[1].y = 47;
	//spine
	ClothesJ[2].x = 320;
	ClothesJ[2].y = 500;

	//Rotation = cvCreateMat(3,3,CV_32FC1);
	RotationArray = new float[6];
	//temp = cvCreateMat(3,1,CV_32FC1);
	//cvSetData( temp, ClothesPixel, temp->step );

	//Result = cvCreateMat(3,1,CV_32FC1);
	A = cvCreateMat(6,6,CV_32FC1);
	B = cvCreateMat(6,1,CV_32FC1);
	ResultMatrix = cvCreateMat(6,1,CV_32FC1);
	InvA=cvCreateMat(6,6,CV_32FC1);



    m_hNextDepthFrameEvent = NULL;
    m_hNextColorFrameEvent = NULL;
    m_hNextSkeletonEvent = NULL;
    m_pDepthStreamHandle = NULL;
    m_pVideoStreamHandle = NULL;
    m_hThNuiProcess = NULL;
    m_hEvNuiProcessStop = NULL;
    ZeroMemory(m_Pen,sizeof(m_Pen));
    m_SkeletonDC = NULL;
    m_PensTotal = 6;
    ZeroMemory(m_Points,sizeof(m_Points));
    m_LastSkeletonFoundTime = 0;
    m_bScreenBlanked = false;
    m_DepthFramesTotal = 0;
    m_LastDepthFPStime = 0;
    m_LastDepthFramesTotal = 0;
    ZeroMemory(m_SkeletonIds,sizeof(m_SkeletonIds));
	//PtrDepthX = new float[10];
	//PtrDepthY = new float[10];
	//Cpos.x = new long[1];
	//Cpos.y = new long[1];


	cvNamedWindow( "image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow( "depthimg", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow( "depthcol", CV_WINDOW_AUTOSIZE);
	image = cvCreateImage( cvSize(640,480), IPL_DEPTH_8U, 4 );
	depthimg = cvCreateImage( cvSize(320,240), IPL_DEPTH_8U, 3 );
	small_img = cvCreateImage( cvSize(320,240), IPL_DEPTH_8U, 4);
	//depthcol = cvCreateImage( cvSize(320,240), IPL_DEPTH_8U, 3 );
	bdep = false;
	bcol = false;
	for(int i=0;i<6;i++)
		prepedeindex[i] = 0;
}

void CKinectSkeleton::Nui_UnInit( )
{
    DeleteDC( m_SkeletonDC );

    if ( NULL != m_Pen[0] )
    {
        for ( int i = 0; i < NUI_SKELETON_COUNT; i++ )
        {
            DeleteObject( m_Pen[i] );
        }
        ZeroMemory( m_Pen, sizeof(m_Pen) );
    }


    // Stop the Nui processing thread
    if ( NULL != m_hEvNuiProcessStop )
    {
        // Signal the thread
        SetEvent(m_hEvNuiProcessStop);

        // Wait for thread to stop
        if ( NULL != m_hThNuiProcess )
        {
            WaitForSingleObject( m_hThNuiProcess, INFINITE );
            CloseHandle( m_hThNuiProcess );
        }
        CloseHandle( m_hEvNuiProcessStop );
    }

    if ( m_pNuiSensor )
    {
        m_pNuiSensor->NuiShutdown( );
    }
    if ( m_hNextSkeletonEvent && ( m_hNextSkeletonEvent != INVALID_HANDLE_VALUE ) )
    {
        CloseHandle( m_hNextSkeletonEvent );
        m_hNextSkeletonEvent = NULL;
    }
    if ( m_hNextDepthFrameEvent && ( m_hNextDepthFrameEvent != INVALID_HANDLE_VALUE ) )
    {
        CloseHandle( m_hNextDepthFrameEvent );
        m_hNextDepthFrameEvent = NULL;
    }
    if ( m_hNextColorFrameEvent && ( m_hNextColorFrameEvent != INVALID_HANDLE_VALUE ) )
    {
        CloseHandle( m_hNextColorFrameEvent );
        m_hNextColorFrameEvent = NULL;
    }

    if ( m_pNuiSensor )
    {
        m_pNuiSensor->Release();
        m_pNuiSensor = NULL;
    }

	//cvReleaseMat(&Rotation);
	delete []RotationArray;
	//cvReleaseMat(&temp);
	//cvReleaseMat(&Result);
	cvReleaseMat(&A);
	cvReleaseMat(&B);
	cvReleaseMat(&InvA);
	cvReleaseMat(&ResultMatrix);

	//cvDestroyWindow( "image");
	//cvDestroyWindow( "depthimg");
	//cvReleaseImage( &image);
	//cvReleaseImage( &depthimg);
	printf("Delete KinectThread...\n");
}

HRESULT CKinectSkeleton::GetKinectSkeleton()
{
	Nui_Zero();

	HRESULT  hr;
    RECT     rc;
    bool     result;

    if ( !m_pNuiSensor )
    {
        HRESULT hr = NuiCreateSensorByIndex(0, &m_pNuiSensor);

        if ( FAILED(hr) )
        {
            return hr;
        }

        SysFreeString(m_instanceId);

        m_instanceId = m_pNuiSensor->NuiDeviceConnectionId();
    }

    m_hNextDepthFrameEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
    m_hNextColorFrameEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
    m_hNextSkeletonEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
    
    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;
    
    DWORD nuiFlags = NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_SKELETON |  NUI_INITIALIZE_FLAG_USES_COLOR;
    hr = m_pNuiSensor->NuiInitialize( nuiFlags );
    if ( E_NUI_SKELETAL_ENGINE_BUSY == hr )
    {
        nuiFlags = NUI_INITIALIZE_FLAG_USES_DEPTH |  NUI_INITIALIZE_FLAG_USES_COLOR;
        hr = m_pNuiSensor->NuiInitialize( nuiFlags) ;
    }
  
    if ( FAILED( hr ) )
        return hr;

    if ( HasSkeletalEngine( m_pNuiSensor ) )
    {
        hr = m_pNuiSensor->NuiSkeletonTrackingEnable( m_hNextSkeletonEvent, 0 );
        if( FAILED( hr ) )
            return hr;
    }

    hr = m_pNuiSensor->NuiImageStreamOpen(
        NUI_IMAGE_TYPE_COLOR,
        NUI_IMAGE_RESOLUTION_640x480,
        0,
        2,
        m_hNextColorFrameEvent,
        &m_pVideoStreamHandle );

    if ( FAILED( hr ) )
        return hr;

    hr = m_pNuiSensor->NuiImageStreamOpen(
        HasSkeletalEngine(m_pNuiSensor) ? NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX : NUI_IMAGE_TYPE_DEPTH,
        NUI_IMAGE_RESOLUTION_320x240,
        0,
        2,
        m_hNextDepthFrameEvent,
        &m_pDepthStreamHandle );

    if ( FAILED( hr ) )
        return hr;

    // Start the Nui processing thread
    m_hEvNuiProcessStop = CreateEvent( NULL, FALSE, FALSE, NULL );
    m_hThNuiProcess = CreateThread( NULL, 0, Nui_ProcessThread, this, 0, NULL );

    return hr;
}




DWORD WINAPI CKinectSkeleton::Nui_ProcessThread(LPVOID pParam)
{
    CKinectSkeleton *pthis = (CKinectSkeleton *) pParam;
    return pthis->Nui_ProcessThread();
}

//-------------------------------------------------------------------
// Nui_ProcessThread
//
// Thread to handle Kinect processing
//-------------------------------------------------------------------
DWORD WINAPI CKinectSkeleton::Nui_ProcessThread()
{
    const int numEvents = 4;
    HANDLE hEvents[numEvents] = { m_hEvNuiProcessStop, m_hNextDepthFrameEvent, m_hNextColorFrameEvent, m_hNextSkeletonEvent };
    int    nEventIdx;
    //DWORD  t;

    //m_LastDepthFPStime = timeGetTime( );

    //blank the skeleton display on startup
    //m_LastSkeletonFoundTime = 0;
	printf("CreateKinectThread...\n");
    // Main thread loop
    bool continueProcessing = true;
    while ( continueProcessing )
    {
		//m_LastDepthFPStime = timeGetTime( );
        // Wait for any of the events to be signalled
        nEventIdx = WaitForMultipleObjects( numEvents, hEvents, FALSE, 100 );

        // Process signal events
        switch ( nEventIdx )
        {
            case WAIT_TIMEOUT:
                continue;

            // If the stop event, stop looping and exit
            case WAIT_OBJECT_0:
                continueProcessing = false;
                continue;

            case WAIT_OBJECT_0 + 1:
                Nui_GotDepthAlert();
                 ++m_DepthFramesTotal;
                break;

            case WAIT_OBJECT_0 + 2:
                Nui_GotVideoAlert();
                break;

            case WAIT_OBJECT_0 + 3:
                Nui_GotSkeletonAlert( );
                break;
        }

        // Once per second, display the depth FPS
        //t = timeGetTime( );
        //if ( (t - m_LastDepthFPStime) > 1000 )
        //{
   //         int fps = ((m_DepthFramesTotal - m_LastDepthFramesTotal) * 1000 + 500) / (t - m_LastDepthFPStime);
   //         m_LastDepthFramesTotal = m_DepthFramesTotal;
   //         m_LastDepthFPStime = t;
			//printf("fps: %d\n",fps);
        //}

    }

    return 0;
}



void CKinectSkeleton::Nui_GotVideoAlert( )
{
    NUI_IMAGE_FRAME imageFrame;

    HRESULT hr = m_pNuiSensor->NuiImageStreamGetNextFrame(
        m_pVideoStreamHandle,
        0,
        &imageFrame );

    INuiFrameTexture * pTexture = imageFrame.pFrameTexture;
    NUI_LOCKED_RECT LockedRect;
    pTexture->LockRect( 0, &LockedRect, NULL, 0 );
    if( LockedRect.Pitch != 0 )
    {
        BYTE * pBuffer = (BYTE*) LockedRect.pBits;

		cvSetData( image, (BYTE*) pBuffer, image->widthStep);

		
		if (bFoundSkeleton)
		{
			for (int k = 0; k < NUI_SKELETON_COUNT; k++){
				if ( pedeindex[k]==1 ){

					for (int j = 0; j < NUI_SKELETON_POSITION_HIP_LEFT; j++)
						cvCircle( image, cvPoint(m_Points[k][j].x,m_Points[k][j].y), 7, g_JointColorTable[j], -1);
					
					bodyJ[0].x = m_Points[k][4].x;
					bodyJ[0].y = m_Points[k][4].y;
					bodyJ[1].x = m_Points[k][8].x;
					bodyJ[1].y = m_Points[k][8].y;
					bodyJ[2].x = m_Points[k][1].x;
					bodyJ[2].y = m_Points[k][1].y;

					//printf("right shoulder:%d %d\nleft shoulder:%d %d\nspine:%d %d\n\n\n",bodyJ[0].x,bodyJ[0].y,bodyJ[1].x,bodyJ[1].y,bodyJ[2].x,bodyJ[2].y);

					warpedmatrix( ClothesJ, bodyJ, RotationArray );
										
					for(int i=44;i<ClothesImg->height;i++){
						for(int j=0;j<ClothesImg->widthStep;j=j+3){
							PixelSum =(int)(uchar)ClothesImg->imageData[ i*ClothesImg->widthStep + j ] +  (int)(uchar)ClothesImg->imageData[ i*ClothesImg->widthStep + j + 1 ] + (int)(uchar) ClothesImg->imageData[ i*ClothesImg->widthStep + j + 2 ];
							if( PixelSum < 700 ){//not white pixel
								ClothesPixel[0] = (int)(j/3);  //x
								ClothesPixel[1] = i; //y
								ClothesPixel[2] = 1;
								
								result[0] = ClothesPixel[0]*RotationArray[0] + ClothesPixel[1]*RotationArray[1] + RotationArray[2];
								result[1] = ClothesPixel[0]*RotationArray[3] + ClothesPixel[1]*RotationArray[4] + RotationArray[5];

								////in the boundary of video image
								position[0] = (int)(result[0]+0.5);
								position[1] = (int)(result[1]+0.5);
								if( position[0]>=0 && position[0]<image->width && position[1]>=0 && position[1]<image->height){
								//bool k = position[0]>=0 && position[0]<640 && position[1]>=0 && position[1]<695;
								//if(k){
										cvSet2D( image, position[1], position[0], CV_RGB((int)ClothesImg->imageData[ i*ClothesImg->widthStep + j + 0 ], (int)ClothesImg->imageData[ i*ClothesImg->widthStep + j + 1 ],  (int)ClothesImg->imageData[ i*ClothesImg->widthStep + j + 2 ]) );

										//printf("DataOrder:%d\n",image->dataOrder);
										//image->imageData[ position[1]*ClothesImg->widthStep + position[0] + 2 ] = ClothesImg->imageData[ i*ClothesImg->widthStep + j + 2 ];
										//image->imageData[ position[1]*ClothesImg->widthStep + position[0] + 1 ] = ClothesImg->imageData[ i*ClothesImg->widthStep + j + 1 ];
										//image->imageData[ position[1]*ClothesImg->widthStep + position[0] ] = ClothesImg->imageData[ i*ClothesImg->widthStep + j ];
										
										/*ClothesImg->imageData[ 0*ClothesImg->widthStep + 0 + 2 ] = 0;
										ClothesImg->imageData[ 0*ClothesImg->widthStep + 0 + 1 ] = 0;
										ClothesImg->imageData[ 0*ClothesImg->widthStep + 0 ] = 0;	*/									
									
								//if ( i==ClothesJ[0].x && j==ClothesJ[0].y )
								//	printf("\nclothes right shoulder transform:%d %d\n  ",position[0],position[1]);
								//if ( i==ClothesJ[1].x && j==ClothesJ[1].y )
								//	printf("\nclothes left shoulder transform:%d %d\n  ",position[0],position[1]);
								//if ( i==ClothesJ[2].x && j==ClothesJ[2].y )
								//	printf("\nclothes spine transform:%d %d\n  ",position[0],position[1]);

								}						
							}
							
						}
					}

					//cvLine( image, cvPoint(m_Points[i][NUI_SKELETON_POSITION_HEAD].x,m_Points[i][NUI_SKELETON_POSITION_HEAD].y), cvPoint(m_Points[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].x,m_Points[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].y), CV_RGB(0,255,0), 3);
					//cvLine( image, cvPoint(m_Points[i][NUI_SKELETON_POSITION_HIP_CENTER].x,m_Points[i][NUI_SKELETON_POSITION_HIP_CENTER].y), cvPoint(m_Points[i][NUI_SKELETON_POSITION_SPINE].x,m_Points[i][NUI_SKELETON_POSITION_SPINE].y), CV_RGB(0,255,0), 3);
					//cvLine( image, cvPoint(m_Points[i][NUI_SKELETON_POSITION_SPINE].x,m_Points[i][NUI_SKELETON_POSITION_SPINE].y), cvPoint(m_Points[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].x,m_Points[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].y), CV_RGB(0,255,0), 3);
					//cvLine( image, cvPoint(m_Points[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].x,m_Points[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].y), cvPoint(m_Points[i][NUI_SKELETON_POSITION_SHOULDER_LEFT].x,m_Points[i][NUI_SKELETON_POSITION_SHOULDER_LEFT].y), CV_RGB(0,255,0), 3);
					//cvLine( image, cvPoint(m_Points[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].x,m_Points[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].y), cvPoint(m_Points[i][NUI_SKELETON_POSITION_SHOULDER_RIGHT].x,m_Points[i][NUI_SKELETON_POSITION_SHOULDER_RIGHT].y), CV_RGB(0,255,0), 3);
					//cvLine( image, cvPoint(m_Points[i][NUI_SKELETON_POSITION_SHOULDER_RIGHT].x,m_Points[i][NUI_SKELETON_POSITION_SHOULDER_RIGHT].y), cvPoint(m_Points[i][NUI_SKELETON_POSITION_ELBOW_RIGHT].x,m_Points[i][NUI_SKELETON_POSITION_ELBOW_RIGHT].y), CV_RGB(0,255,0), 3);
					//cvLine( image, cvPoint(m_Points[i][NUI_SKELETON_POSITION_ELBOW_RIGHT].x,m_Points[i][NUI_SKELETON_POSITION_ELBOW_RIGHT].y), cvPoint(m_Points[i][NUI_SKELETON_POSITION_WRIST_RIGHT].x,m_Points[i][NUI_SKELETON_POSITION_WRIST_RIGHT].y), CV_RGB(0,255,0), 3);
					//cvLine( image, cvPoint(m_Points[i][NUI_SKELETON_POSITION_WRIST_RIGHT].x,m_Points[i][NUI_SKELETON_POSITION_WRIST_RIGHT].y), cvPoint(m_Points[i][NUI_SKELETON_POSITION_HAND_RIGHT].x,m_Points[i][NUI_SKELETON_POSITION_HAND_RIGHT].y), CV_RGB(0,255,0), 3);
					//cvLine( image, cvPoint(m_Points[i][NUI_SKELETON_POSITION_SHOULDER_LEFT].x,m_Points[i][NUI_SKELETON_POSITION_SHOULDER_LEFT].y), cvPoint(m_Points[i][NUI_SKELETON_POSITION_ELBOW_LEFT].x,m_Points[i][NUI_SKELETON_POSITION_ELBOW_LEFT].y), CV_RGB(0,255,0), 3);
					//cvLine( image, cvPoint(m_Points[i][NUI_SKELETON_POSITION_ELBOW_LEFT].x,m_Points[i][NUI_SKELETON_POSITION_ELBOW_LEFT].y), cvPoint(m_Points[i][NUI_SKELETON_POSITION_WRIST_LEFT].x,m_Points[i][NUI_SKELETON_POSITION_WRIST_LEFT].y), CV_RGB(0,255,0), 3);
					//cvLine( image, cvPoint(m_Points[i][NUI_SKELETON_POSITION_WRIST_LEFT].x,m_Points[i][NUI_SKELETON_POSITION_WRIST_LEFT].y), cvPoint(m_Points[i][NUI_SKELETON_POSITION_HAND_LEFT].x,m_Points[i][NUI_SKELETON_POSITION_HAND_LEFT].y), CV_RGB(0,255,0), 3);
				}
			}
		}

		
		cvResize( image, small_img);
		bcol = true;
		cvShowImage( "image", small_img);
		cvWaitKey(1);
    }

    hr= m_pNuiSensor->NuiImageStreamReleaseFrame( m_pVideoStreamHandle, &imageFrame );
}


void CKinectSkeleton::Nui_GotDepthAlert( )
{
    NUI_IMAGE_FRAME imageFrame;

    HRESULT hr = m_pNuiSensor->NuiImageStreamGetNextFrame(
        m_pDepthStreamHandle,
        0,
        &imageFrame );

    INuiFrameTexture * pTexture = imageFrame.pFrameTexture;
    NUI_LOCKED_RECT LockedRect;
    pTexture->LockRect( 0, &LockedRect, NULL, 0 );

    if( LockedRect.Pitch != 0 )
    {
        //BYTE * pBuffer = (BYTE*) LockedRect.pBits;
		//USHORT * pBuff = (USHORT*) LockedRect.pBits;
		pBuff = (USHORT*) LockedRect.pBits;
		bdep = true;
		int ind = 0;
		 for(int i=0;i<240;i++)
		 {
			 for(int j=0;j<320;j++)
			 {
				 ind = i*320+j;
				 BYTE index = pBuff[ind]&0x07;
				 USHORT realDepth = (pBuff[ind]&0xFFF8)>>3;

				 BYTE scale = 255 - (BYTE)(256*realDepth/0x0fff);
				 buf[3*ind] = 0; 
				 buf[3*ind+1] = 0;
				 buf[3*ind+2] = 0;
				 switch( index )
				 {
				 case 0:
					 buf[3*ind]=scale/2;
					 buf[3*ind+1]=scale/2;
					 buf[3*ind+2]=scale/2;
					 break;
				 case 1:
					 buf[3*ind]=scale;
					 break;
				 case 2:
					 buf[3*ind+1]=scale;
					 break;
				 case 3:
					 buf[3*ind+2]=scale;
					 break;
				 case 4:
					 buf[3*ind]=scale;
					 buf[3*ind+1]=scale;
					 break;
				 case 5:
					 buf[3*ind]=scale;
					 buf[3*ind+2]=scale;
					 break;
				 case 6:
					 buf[3*ind+1]=scale;
					 buf[3*ind+2]=scale;
					 break;
				 case 7:
					 buf[3*ind]=255-scale/2;
					 buf[3*ind+1]=255-scale/2;
					 buf[3*ind+2]=255-scale/2;
					 break;
				}
			 }
		 }
		// cvSetData( depthimg, buf, 320*3);


		//if (bFoundSkeleton)
		//{
		//	for (int i = 0; i < NUI_SKELETON_COUNT; i++){
		//		//if ( pedeindex[i]==1 ){
		//			for (int j = 0; j < NUI_SKELETON_POSITION_HIP_LEFT; j++)
		//				cvCircle( depthimg, cvPoint(m_Points_dep[i][j].x,m_Points_dep[i][j].y), 7, g_JointColorTable[j], -1);

		//			cvLine( depthimg, cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_HEAD].x,m_Points_dep[i][NUI_SKELETON_POSITION_HEAD].y), cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].x,m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].y), CV_RGB(0,255,0), 3);
		//			cvLine( depthimg, cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_HIP_CENTER].x,m_Points_dep[i][NUI_SKELETON_POSITION_HIP_CENTER].y), cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_SPINE].x,m_Points_dep[i][NUI_SKELETON_POSITION_SPINE].y), CV_RGB(0,255,0), 3);
		//			cvLine( depthimg, cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_SPINE].x,m_Points_dep[i][NUI_SKELETON_POSITION_SPINE].y), cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].x,m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].y), CV_RGB(0,255,0), 3);
		//			cvLine( depthimg, cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].x,m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].y), cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_LEFT].x,m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_LEFT].y), CV_RGB(0,255,0), 3);
		//			cvLine( depthimg, cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].x,m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_CENTER].y), cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_RIGHT].x,m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_RIGHT].y), CV_RGB(0,255,0), 3);
		//			cvLine( depthimg, cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_RIGHT].x,m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_RIGHT].y), cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_ELBOW_RIGHT].x,m_Points_dep[i][NUI_SKELETON_POSITION_ELBOW_RIGHT].y), CV_RGB(0,255,0), 3);
		//			cvLine( depthimg, cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_ELBOW_RIGHT].x,m_Points_dep[i][NUI_SKELETON_POSITION_ELBOW_RIGHT].y), cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_WRIST_RIGHT].x,m_Points_dep[i][NUI_SKELETON_POSITION_WRIST_RIGHT].y), CV_RGB(0,255,0), 3);
		//			cvLine( depthimg, cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_WRIST_RIGHT].x,m_Points_dep[i][NUI_SKELETON_POSITION_WRIST_RIGHT].y), cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_HAND_RIGHT].x,m_Points_dep[i][NUI_SKELETON_POSITION_HAND_RIGHT].y), CV_RGB(0,255,0), 3);
		//			cvLine( depthimg, cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_LEFT].x,m_Points_dep[i][NUI_SKELETON_POSITION_SHOULDER_LEFT].y), cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_ELBOW_LEFT].x,m_Points_dep[i][NUI_SKELETON_POSITION_ELBOW_LEFT].y), CV_RGB(0,255,0), 3);
		//			cvLine( depthimg, cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_ELBOW_LEFT].x,m_Points_dep[i][NUI_SKELETON_POSITION_ELBOW_LEFT].y), cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_WRIST_LEFT].x,m_Points_dep[i][NUI_SKELETON_POSITION_WRIST_LEFT].y), CV_RGB(0,255,0), 3);
		//			cvLine( depthimg, cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_WRIST_LEFT].x,m_Points_dep[i][NUI_SKELETON_POSITION_WRIST_LEFT].y), cvPoint(m_Points_dep[i][NUI_SKELETON_POSITION_HAND_LEFT].x,m_Points_dep[i][NUI_SKELETON_POSITION_HAND_LEFT].y), CV_RGB(0,255,0), 3);
		//		//}
		//	}
		//}


		//cvShowImage( "depthimg", depthimg);
		//cvWaitKey(1);

    }

    hr = m_pNuiSensor->NuiImageStreamReleaseFrame( m_pDepthStreamHandle, &imageFrame );
}


RGBQUAD CKinectSkeleton::Nui_ShortToQuad_Depth( USHORT s )
{
    USHORT RealDepth = NuiDepthPixelToDepth(s);
    USHORT Player    = NuiDepthPixelToPlayerIndex(s);

    // transform 13-bit depth information into an 8-bit intensity appropriate
    // for display (we disregard information in most significant bit)
    BYTE intensity = (BYTE)~(RealDepth >> 4);

    // tint the intensity by dividing by per-player values
    RGBQUAD color;
    color.rgbRed   = intensity >> g_IntensityShiftByPlayerR[Player];
    color.rgbGreen = intensity >> g_IntensityShiftByPlayerG[Player];
    color.rgbBlue  = intensity >> g_IntensityShiftByPlayerB[Player];

    return color;
}

void CKinectSkeleton::Nui_GotSkeletonAlert( )
{
    //NUI_SKELETON_FRAME SkeletonFrame = {0};

    bFoundSkeleton = false;
	/*pos_3d InitialBasisx, InitialBasisy, InitialBasisz;*/

    if( SUCCEEDED(m_pNuiSensor->NuiSkeletonGetNextFrame( 0, &SkeletonFrame )) )
    {
		for( int i = 0 ; i < NUI_SKELETON_COUNT ; i++ )
		{
			pedeindex[i]=0;
			if( SkeletonFrame.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED ) /*|| 
			(SkeletonFrame.SkeletonData[i].eTrackingState == NUI_SKELETON_POSITION_ONLY && m_bAppTracking))*/
			{
				bFoundSkeleton = true;
				pedeindex[i] = 1;
			}
		}
		for(int j=0;j<6;j++)
			prepedeindex[j] = pedeindex[j];		
	}



	// no skeletons!
    if( !bFoundSkeleton ){
        return;
    }
	// smooth out the skeleton data
	HRESULT hr = m_pNuiSensor->NuiTransformSmooth(&SkeletonFrame,NULL);
    if ( FAILED(hr) ){
        return;
    }



	bool bSkeletonIdsChanged = false;
    for ( int i = 0 ; i < NUI_SKELETON_COUNT; i++ ){
        if ( m_SkeletonIds[i] != SkeletonFrame.SkeletonData[i].dwTrackingID ){
            m_SkeletonIds[i] = SkeletonFrame.SkeletonData[i].dwTrackingID;
            bSkeletonIdsChanged = true;
        }
	}	


	if (bFoundSkeleton){
		USHORT depthq;
		POINT depxy;
		for( int i = 0 ; i < NUI_SKELETON_COUNT ; i++ ){
			for (int j = 0; j < NUI_SKELETON_POSITION_HIP_LEFT; j++){
			
				NuiTransformSkeletonToDepthImage( SkeletonFrame.SkeletonData[i].SkeletonPositions[j], &m_Points_dep[i][j].x, &m_Points_dep[i][j].y, &depthq );
				hr = NuiImageGetColorPixelCoordinatesFromDepthPixel( NUI_IMAGE_RESOLUTION_640x480, 0, m_Points_dep[i][j].x, m_Points_dep[i][j].y, depthq, &m_Points[i][j].x, &m_Points[i][j].y);

				//m_Points_dep[i][j].x *= 2;
				//m_Points_dep[i][j].y *= 2;
			}
		}
	}

}

void CKinectSkeleton::warpedmatrix( CvPoint originalInd[3], CvPoint desiredInd[3],float *Array3){
	int i;
	//Array1[0] = originalInd[0].x;
	//Array1[1] = originalInd[0].y;
	//Array1[2] = 1;
	//Array1[3] = 0;
	//Array1[4] = 0;
	//Array1[5] = 0;
	//Array1[6] = 0;
	//Array1[7] = 0;
	//Array1[8] = 0;
	//Array1[9] = originalInd[0].x;
	//Array1[10] = originalInd[0].y;
	//Array1[11] = 1;
	//Array1[12] = originalInd[1].x;
	//Array1[13] = originalInd[1].y;
	//Array1[14] = 1;
	//Array1[15] = 0;
	//Array1[16] = 0;
	//Array1[17] = 0;
	//Array1[18] = 0;
	//Array1[19] = 0;
	//Array1[20] = 0;
	//Array1[21] = originalInd[1].x;
	//Array1[22] = originalInd[1].y;
	//Array1[23] = 1;
	//Array1[24] = originalInd[2].x;
	//Array1[25] = originalInd[2].y;
	//Array1[26] = 1;
	//Array1[27] = 0;
	//Array1[28] = 0;
	//Array1[29] = 0;
	//Array1[30] = 0;
	//Array1[31] = 0;
	//Array1[32] = 0;
	//Array1[33] = originalInd[2].x;
	//Array1[34] = originalInd[2].y;
	//Array1[35] = 1;
	//cvSetData(A,Array1,A->step);

	//Array2[0] = desiredInd[0].x;
	//Array2[1] = desiredInd[0].y;
	//Array2[2] = desiredInd[1].x;
	//Array2[3] = desiredInd[1].y;
	//Array2[4] = desiredInd[2].x;
	//Array2[5] = desiredInd[2].y;
	//cvSetData(B,Array2,B->step);

	//cvInvert(A,InvA,CV_LU);
	//cvmMul(InvA,B,ResultMatrix);

	CMatrix a("A", 6,6);
    //std::cin >> a;
    a.FillSimulatedInput(originalInd, desiredInd);
 
    CMatrix aadj = a.Inverse();
	int array_count=0;
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++){
		Array3[array_count]=aadj.m_pData[0][0];
		array_count++;
		}
	}//到此似乎inverse A寫好了 剩下還沒寫的是AB乘法~
			

	   // std::cout << a;
    //std::cout << aadj;




	//for(i=0;i<6;i++)
	//	Array3[i] = cvGet2D(ResultMatrix,i,0).val[0];
	//Array3[6] = 0;
	//Array3[7] = 0;
	//Array3[8] = 1;
}







void CKinectSkeleton::PrintMatrix(CvMat *Matrix,int Rows,int Cols,int Channels)
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


