// QRrecognize.cpp : 定义控制台应用程序的入口点。
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
#include <ctime> //计时用的头文件
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
		//这是图片本身的问题，有一道白色边框
		//先清理周边的点,这是为了防止区域截取时候矩形区域大于图像造成无效
		for (int y=0;y<src->height;y++)
		{
			uchar *ptr=(uchar*)(src->imageData+y*src->widthStep);
			for (int x=0;x<src->width;x++)
			{
				if(x>3&&x<(src->width-3)&&y>3&&y<(src->height-3)){
					//范围内
				}else{
					ptr[src->nChannels*x]=0;
					ptr[src->nChannels*x+1]=0;
					ptr[src->nChannels*x+2]=0;

				}

			}
		}
		if(src->width<360){
			int scale =3; //缩放倍数为3倍 
			CvSize dst_cvsize; //目标图像尺寸 
			dst_cvsize.width =scale*src->width;  //目标图像的宽为源图象宽的scale倍
			dst_cvsize.height = scale*src->height; //目标图像的高为源图象高的scale倍
			dst = cvCreateImage(dst_cvsize, src->depth, src->nChannels); //构造目标图象
		}
		else dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels); //构造目标图象
		cvResize(src, dst); //缩放源图像到目标图像
	IplImage *img0=cvCreateImage(cvGetSize(dst),dst->depth,1);//灰度
	cvSetImageCOI(dst,1);//B色
	cvCopy(dst,img0);  //提取B色
	cvSetImageCOI(dst,0);//恢复
	//RecDect *rd=new RecDect(dst);	//声明对象
	//time_t start,end,time; /*注意计时所用的变量名称*/
	//start=clock();
	cvShowImage("34",dst);
	cvSaveImage("D:\\34.bmp",dst);
		//IplImage *	img0=cvCreateImage(cvGetSize(dst),dst->depth,1);//灰度
		IplImage *	img1=cvCreateImage(cvGetSize(dst),dst->depth,1);//灰度
		IplImage *	img2=cvCreateImage(cvGetSize(dst),dst->depth,1);//灰度
		IplImage *	pingjun=cvCreateImage(cvGetSize(dst),dst->depth,1);//灰度
		time_t start,end,time; /*注意计时所用的变量名称*/

    /*程序开始执行，开始计时*/

    start=clock();
		cvSplit(dst,img0,img1,img2,NULL);
		
      cvSaveImage("D:\\34B.bmp",img0);
	cvSaveImage("D:\\34R.bmp",img1);
	cvSaveImage("D:\\34G.bmp",img2);
	//int  th=rd->otsu(img0);
 //  cvThreshold(img0,img0,th,255,1);
	cvAdaptiveThreshold(img0,img0,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV,51,-3);//-数越大，细节保存越不清楚
    end=clock();

    time=end-start;//这里的时间是计算机内部时间

    cout<<"time"<<time<<endl;
  // printf("%d",th);

	cvShowImage("222",img0);
	cvSaveImage("D:\\adapt101.bmp",img0);
		//IplImage  *rr=cvCreateImage(cvGetSize(dst),dst->depth,1);//灰度;
		//cvMahalanobis(img0,img0,rr);
		//RecDect *rd=new RecDect(dst);	//声明对象
		////cvShowImage("原始图像",rd->img0);
		//cvReleaseImage( &src );
		//cvReleaseImage( &dst );
		//rd->RfindSquaresRect(0.01f,0.81f);//第一次调用，获取图像轮廓定点坐标:此步获取图像大概位置，然后进行区域选择
		///*此时已经获得pt,进行区域截取并对歪掉图像进行旋转*/
		//rd->AreaRotate();
		//int angle=rd->recognVersion(rd->findSquares4() );//位置探测图形提取并计算版本号,angle为矫正正确位置的角度
		//if(angle!=0){//这是为旋转不到位的图像准备的
		//	rd->FitRotate(rd->img,angle);
		//	rd->FitRotate(rd->img0,angle);
		//	angle=rd->recognVersion(rd->findSquares4() );//位置探测图形提取并计算版本号
		//}
		////
		//rd->drawSquares();
		//rd->drawGrid();cvWaitKey(0);
		//delete rd;
		////
		//// 等待.
		cvWaitKey(0);
		////释放图像


	}

	return 0;

}

