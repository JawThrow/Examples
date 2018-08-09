#pragma warning(disable:4996)
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "CamCalibDefine.h"

using namespace std;
using namespace cv;

void harrisCorner(int, void* boardimg);
vector<Point2f> findGridPoints(Mat eimg, const int gridRows, const int gridCols);

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
	int gridRows = 7;
	int gridCols = 5;
	vector<Point2f> GridPoints = findGridPoints(boardimg, gridRows, gridCols);
		
	
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

/** findGridPoints
* this function extracts grid point using harrison corner detection
* 
*/
vector<Point2f> findGridPoints(Mat eimg, const int gridRows, const int gridCols)
{
	Mat boardimg = eimg.clone();
	int rows = eimg.rows;
	int cols = eimg.cols;
	
	vector<Point2f> CornerPoints;
	Mat himg;
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
	int thresh = 150;
	int max_thresh = 255;

	char ch = 0;
	while (ch != 'q')
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
			CornerPoints = pnts;
		}
	}
	cout << "Extracted Corner Points: " << CornerPoints.size() << endl;
	
	// averaging neighborhood points
	vector<Point2f> GridPoints;
	vector<bool> visited(CornerPoints.size(), true);

	uchar cprev = 0;
	uchar cnext = 0;
	uchar rprev = 0;
	uchar rnext = 0;
	float ptRange = 5;
	int ptidx = 0;
	int idx = 0;
	Mat temp;
	Mat cimg(boardimg.size(), CV_8UC3);

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			cimg.at<Vec3b>(y, x)[0] = boardimg.at<uchar>(y, x);
			cimg.at<Vec3b>(y, x)[1] = boardimg.at<uchar>(y, x);
			cimg.at<Vec3b>(y, x)[2] = boardimg.at<uchar>(y, x);
		}
	}

	for (vector<Point2f>::iterator it = CornerPoints.begin(); it != CornerPoints.end(); it++)
	{		
		if (!visited[idx++])
			continue;

		Point2f CurrPt = *it;
		int ptCnt = 0;
		float avgX = 0;
		float avgY = 0;	
		temp = cimg.clone();
		circle(temp, CurrPt, 1, CV_RGB(0, 255, 0));

		int nPt = 0;
		for (vector<Point2f>::iterator in = CornerPoints.begin(); in != CornerPoints.end(); in++)
		{	
			
			Point2f tempPt = *in;
			
			if (visited[nPt])
			{
				if (tempPt.x > CurrPt.x - ptRange && tempPt.x < CurrPt.x + ptRange)
				{
					if (tempPt.y > CurrPt.y - ptRange && tempPt.y < CurrPt.y + ptRange)
					{						
						avgX += tempPt.x;
						avgY += tempPt.y;
						ptCnt++;
						visited[nPt] = false;

						circle(temp, tempPt, 1, CV_RGB(255, 0, 0));
						imshow("point test", temp);
						waitKey();
					}
				}
			}
			nPt++;
		}
		avgX /= static_cast<float>(ptCnt);
		avgY /= static_cast<float>(ptCnt);
		GridPoints.push_back(Point2f(avgX, avgY));
	}
	cout << "Grid points : " << GridPoints.size() << endl;
	temp = boardimg.clone();
	for (vector<Point2f>::iterator it = GridPoints.begin(); it != GridPoints.end(); it++)
	{
		Point2f pt = *it;
		circle(temp, pt, 1, CV_RGB(255, 255, 255), 3);
	}
	imshow("Merging grid points test", temp);
	waitKey();

	return GridPoints;
}

