// QRrecognize.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "RecDetect.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui.hpp"
#include<math.h>
#include <ctime> //��ʱ�õ�ͷ�ļ�
#include <iostream>

using namespace std;
#include<conio.h>
char* names[] = { "34.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp","8.bmp","9.bmp","10.bmp","11.bmp","1.bmp",0 };
//char* names[] = { "3.bmp",0 };
double f(int i,int j,double v,double r){
	
	double ff=1.0/(2*CV_PI*r*r)*exp(-(i*i+j*j)/(2*r*r));
	return ff;
}
int _tmain(int argc, _TCHAR* argv[])
{

	for(int i = 0; i<1; i++ )
	{	
		char t1='0'+i/10,t2='0'+i%10;
		char name[7];
		name[0]= t1;
		name[1]=t2;
		name[2]='.';
		name[3]='b';
		name[4]='m';
		name[5]='p';
		name[6]='\0';
		IplImage *src=0, *dst=0; 
		// load i-th image	
		//src = cvLoadImage( name, 1);
		src = cvLoadImage("34.bmp", 1);
		printf("Cload %s\n", name );
		if( !src )
		{
			printf("Couldn't load %s\n", name );
			continue;
		}
		//����ͼƬ��������⣬��һ����ɫ�߿�
		//�������ܱߵĵ�,����Ϊ�˷�ֹ�����ȡʱ������������ͼ�������Ч
		for (int y=0;y<src->height;y++)
		{
			uchar *ptr=(uchar*)(src->imageData+y*src->widthStep);
			for (int x=0;x<src->width;x++)
			{
				if(x>3&&x<(src->width-3)&&y>3&&y<(src->height-3)){
					//��Χ��
				}else{
					ptr[src->nChannels*x]=0;
					ptr[src->nChannels*x+1]=0;
					ptr[src->nChannels*x+2]=0;

				}

			}
		}
		if(src->width<360){
			int scale =3; //���ű���Ϊ3�� 
			CvSize dst_cvsize; //Ŀ��ͼ��ߴ� 
			dst_cvsize.width =scale*src->width;  //Ŀ��ͼ��Ŀ�ΪԴͼ����scale��
			dst_cvsize.height = scale*src->height; //Ŀ��ͼ��ĸ�ΪԴͼ��ߵ�scale��
			dst = cvCreateImage(dst_cvsize, src->depth, src->nChannels); //����Ŀ��ͼ��
		}
		else dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels); //����Ŀ��ͼ��
		cvResize(src, dst); //����Դͼ��Ŀ��ͼ��
	IplImage *img0=cvCreateImage(cvGetSize(dst),dst->depth,1);//�Ҷ�
	cvSetImageCOI(dst,1);//Bɫ
	cvCopy(dst,img0);  //��ȡBɫ
	cvSetImageCOI(dst,0);//�ָ�
	//RecDect *rd=new RecDect(dst);	//��������
	//time_t start,end,time; /*ע���ʱ���õı�������*/
	//start=clock();
	cvShowImage("34",dst);
	cvSaveImage("D:\\34.bmp",dst);
		//IplImage *	img0=cvCreateImage(cvGetSize(dst),dst->depth,1);//�Ҷ�
		IplImage *	img1=cvCreateImage(cvGetSize(dst),dst->depth,1);//�Ҷ�
		IplImage *	img2=cvCreateImage(cvGetSize(dst),dst->depth,1);//�Ҷ�
		IplImage *	pingjun=cvCreateImage(cvGetSize(dst),dst->depth,1);//�Ҷ�
		time_t start,end,time; /*ע���ʱ���õı�������*/

    /*����ʼִ�У���ʼ��ʱ*/

    start=clock();
		cvSplit(dst,img0,img1,img2,NULL);
		
      cvSaveImage("D:\\34B.bmp",img0);
	cvSaveImage("D:\\34R.bmp",img1);
	cvSaveImage("D:\\34G.bmp",img2);
	//int  th=rd->otsu(img0);
 //  cvThreshold(img0,img0,th,255,1);
	cvAdaptiveThreshold(img0,img0,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,51,-3);//-��Խ��ϸ�ڱ���Խ�����
    end=clock();

    time=end-start;//�����ʱ���Ǽ�����ڲ�ʱ��

    cout<<"time"<<time<<endl;
  // printf("%d",th);

	cvShowImage("222",img0);
	cvSaveImage("D:\\adapt101.bmp",img0);
		//IplImage  *rr=cvCreateImage(cvGetSize(dst),dst->depth,1);//�Ҷ�;
		//cvMahalanobis(img0,img0,rr);
		//RecDect *rd=new RecDect(dst);	//��������
		////cvShowImage("ԭʼͼ��",rd->img0);
		//cvReleaseImage( &src );
		//cvReleaseImage( &dst );
		//rd->RfindSquaresRect(0.01f,0.81f);//��һ�ε��ã���ȡͼ��������������:�˲���ȡͼ����λ�ã�Ȼ���������ѡ��
		///*��ʱ�Ѿ����pt,���������ȡ�������ͼ�������ת*/
		//rd->AreaRotate();
		//int angle=rd->recognVersion(rd->findSquares4() );//λ��̽��ͼ����ȡ������汾��,angleΪ������ȷλ�õĽǶ�
		//if(angle!=0){//����Ϊ��ת����λ��ͼ��׼����
		//	rd->FitRotate(rd->img,angle);
		//	rd->FitRotate(rd->img0,angle);
		//	angle=rd->recognVersion(rd->findSquares4() );//λ��̽��ͼ����ȡ������汾��
		//}
		////
		//rd->drawSquares();
		//rd->drawGrid();cvWaitKey(0);
		//delete rd;
		////
		//// �ȴ�.
		cvWaitKey(0);
		////�ͷ�ͼ��


	}

	return 0;

}

