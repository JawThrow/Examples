#pragma warning(disable:4996)
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "CamCalibDefine.h"

using namespace std;
using namespace cv;

void harrisCorner(int, void* boardimg);

int main(void)
{
	/*********** load board image *************/
	char fname[256];
	//sprintf(fname, "%sboard0 1.jpg", IMG_PATH);
	sprintf(fname, "../images/board01.jpg");
	Mat boardimg = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
	if (boardimg.empty())
		cout << "fail to load image" << endl;

	imshow("input board image", boardimg);
	
	/*********** canny edge detection *************/

	Mat cannyimg;
	Canny(boardimg, cannyimg, 100, 150);
	imshow("canny edge image", cannyimg);

	/*********** harrison corner detection *************/
	vector<Point2f> GridPoints;
	Mat himg;
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
	int thresh = 150;
	int max_thresh = 255;
	
	char ch = 0;
	while(ch!='q')
	{
		Point2f PrevPnt;
		vector<Point2f> pnts;
		Mat harrisimg;
		Mat norm, norm_scaled;
		cornerHarris(boardimg, harrisimg, blockSize, apertureSize, k);
		normalize(harrisimg, norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
		convertScaleAbs(norm, norm_scaled);
		imshow("Harris image no circle", norm_scaled);
		for (int y = 0; y < norm.rows; y++)
		{
			for (int x = 0; x < norm.cols; x++)
			{
				if (norm.at<float>(y, x) > thresh)
				{
					circle(norm_scaled, Point(x, y), 5, Scalar(0), 2, 8, 0);
					pnts.push_back(Point2f(x, y));
					/*imshow("Harris image norm_scaled", norm_scaled);
					waitKey();*/
				}
			}
		}
		imshow("Harris image norm_scaled", norm_scaled);
		cout << "harris threshold: " << thresh << endl;
		ch = waitKey();
		if (ch == 'u')
		{
			thresh += 5;
		}
		else if (ch == 'd')
		{
			thresh -= 5;
		}
		else if (ch == 'q')
		{
			GridPoints = pnts;
		}
	}	
	cout << "Points: " << GridPoints.size() << endl;
	
	/*Mat temp = boardimg.clone();
	for (vector<Point2f>::iterator it = GridPoints.begin(); it != GridPoints.end(); it++)
	{
		Point2f pt = *it;
		circle(temp, pt, 1, CV_RGB(0,0,0), 2);
	}
	imshow("temp", temp);*/


	waitKey();
	return 0;
}

void harrisCorner(int , void* boardimg)
{
	double thresh = 100;
	Mat bimg = ((Mat*)boardimg)->clone();
	Mat harrisimg;
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
		
	cornerHarris(bimg, harrisimg, blockSize, apertureSize, k);
	Mat norm, norm_scaled;
	normalize(harrisimg, norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(norm, norm_scaled);

	for (int y = 0; y < norm.rows; y++)
		for (int x = 0; x < norm.cols; x++)
			if (norm.at<float>(y, x) > thresh)
				circle(norm_scaled, Point(x, y), 5, Scalar(0), 2, 8, 0);

	namedWindow("Corners detected");
	imshow("Corners detected", norm_scaled);
}
vector<Point2f> findGridPoints(Mat eimg)
{
	int rows = eimg.rows;
	int cols = eimg.cols;
	uchar cprev = 0;
	uchar cnext = 0;
	uchar rprev = 0;
	uchar rnext = 0;
	vector<Point2f> GridPoints;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 1; x < cols; x++)
		{
			;
		}
	}
	return GridPoints;
}

