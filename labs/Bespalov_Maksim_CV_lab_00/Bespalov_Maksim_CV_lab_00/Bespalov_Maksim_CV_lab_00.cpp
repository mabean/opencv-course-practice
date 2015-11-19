// Bespalov_Maksim_CV_lab_00.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <math.h>


int main(int argc, char* argv[])
{
	cv::Mat src, clone, canny,blur,hist;
	
	src = cv::imread("cimg.jpg",1); 

	clone = src.clone();

	cv::Canny(clone,canny,20,150);
	cv::blur(clone,blur,cv::Size(5,5));
	
	cv::namedWindow( "Source", CV_WINDOW_AUTOSIZE ); 
	cv::namedWindow( "Canny", CV_WINDOW_AUTOSIZE ); 
	cv::namedWindow( "Blur", CV_WINDOW_AUTOSIZE ); 
	cv::imshow("Source", src);
	cv::imshow("Canny", canny);
	cv::imshow("Blur", blur);
	cv::waitKey();
	src = cv::imread("himg.jpg",1);
	clone = src.clone();
	cv::cvtColor(clone, clone, CV_BGR2GRAY); 
	cv::equalizeHist(clone,hist);
	cv::imshow("Source", src);
	cv::namedWindow( "Histigram Equalization", CV_WINDOW_AUTOSIZE ); 
	cv::imshow("Histigram Equalization", hist);

	cv::waitKey();
	
	return 0;
}





