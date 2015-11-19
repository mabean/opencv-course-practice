#include <opencv2\opencv.hpp>
#include <math.h>

int main(int argc, char* argv[])
{
	cv::Mat src,dst,canny,dist,integr;
	cv::Mat chan[3], res[3];
	src = cv::imread("road.png",1);
	cv::Canny(src,canny,50,120,3);
	cv::distanceTransform(cv::Scalar::all(255) - canny,dist, CV_DIST_L2,3);
	//normalize(dist, dist);
	cv::split(src,chan);
	res[0] = chan[0].clone();
	res[1] = chan[1].clone();
    res[2] = chan[2].clone();

	int bval = 0;
	int ker = 0;
	int minI,maxI,minJ,maxJ;
	float rad = 0;
	for (int ch = 0; ch <3; ch++)
	{
		cv::integral(chan[ch],integr);
		for(int i = 0; i < chan[ch].rows; i++)
			for(int j = 0; j < chan[ch].cols; j++)
			{
				minI = 0;
				minJ = 0;
				maxI = chan[ch].rows - 1;
				maxJ = chan[ch].cols - 1;
				//rad = floor( smth + 0.5);
				rad = dist.at<float>(i,j);
				/*if (i + 1 >= rad && j + 1 >= rad)
				{
				}*/
				ker = rad/2;
				if (i - ker > 0)
					minI = i - ker;

				if (j - ker > 0)
					minJ = j - ker;

				if (i + ker < chan[ch].rows)
					maxI = i + ker;

				if (j + ker < chan[ch].cols)
					maxJ = j + ker;
				if (ker > 0)
				{
					bval = integr.at<int>(maxI + 1,maxJ + 1) - integr.at<int>(maxI + 1,minJ) - integr.at<int>(minI,maxJ + 1) + integr.at<int>(minI,minJ);
					bval /= (maxI - minI + 1) * (maxJ - minJ + 1);
				}
				else
					bval = chan[ch].at<unsigned char>(i,j);
				res[ch].at<unsigned char>(i,j) = (unsigned char) bval; 

			}
	}
	cv::merge(res, 3 ,dst);




	cv::namedWindow( "Source", CV_WINDOW_AUTOSIZE ); 
	cv::namedWindow( "canny", CV_WINDOW_AUTOSIZE ); 
	cv::namedWindow( "distance transform", CV_WINDOW_AUTOSIZE ); 
	cv::namedWindow( "result", CV_WINDOW_AUTOSIZE ); 
	cv::imshow("distance transform",dist);
	cv::imshow("Source",src);
	cv::imshow("canny",canny);
	cv::imshow("result",dst);
	cv::waitKey();


	return 0;
}