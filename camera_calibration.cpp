#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <time.h>
#include <sstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>



using namespace cv;
using namespace std;

class CalibPIJ
{
public:
	int numOfImages;
	vector<Mat> boardImages;
	enum Pattern {NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };

	Size boardSize;            // The size of the board -> Number of items by width and height
	Pattern calibrationPattern;// One of the Chessboard, circles, or asymmetric circle pattern
	float squareSize;          // The size of a square in your defined unit (point, millimeter,etc).
	int nrFrames;              // The number of frames to use from the input for calibration
	float aspectRatio;         // The aspect ratio
	int delay;                 // In case of a video input
	bool bwritePoints;         //  Write detected feature points
	bool bwriteExtrinsics;     // Write extrinsic parameters
	bool calibZeroTangentDist; // Assume zero tangential distortion
	bool calibFixPrincipalPoint;// Fix the principal point at the center
	bool flipVertical;          // Flip the captured images around the horizontal axis
	string outputFileName;      // The name of the file where to write
	bool showUndistorsed;       // Show undistorted images after calibration
	string input;               // The input ->

	void pijInit(int nframes, float sqSize, Size bSize);
	bool readBoardImages(const string imgname, const int numOfImages);
	
	void CalibPIJ::executeCameraCalib(Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs, vector<vector<Point2f>> imagePoints,
		vector<Mat>& rvecs, vector<Mat>& tvecs, vector<float>& reprojErrs, double& totalAvgErr);
	
};

void CalibPIJ::pijInit(int nframes, float sqSize, Size bSize)
{
	numOfImages = nframes;
	squareSize = sqSize;
	boardSize = bSize;
}

int main(void)
{		

	CalibPIJ pij;	
	int nframes = 13;
	float sqareSize = 25; // or 2.5
	Size boardSize(9, 6);
	
	pij.pijInit(nframes, sqareSize, boardSize);

	if (!pij.readBoardImages("left", nframes))
		return -1;
	
	vector<vector<Point2f>> imagePoints;
	
	Size imageSize;
	//Size boardSize(7, 5);
	for (int i = 0; i < pij.numOfImages; i++)
	{
		Mat view = pij.boardImages[i].clone();
		vector<Point2f> pointBuf;

		bool found;
		found = findChessboardCorners(view, boardSize, pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
		
		if (found)
		{
			Mat viewGray;
			cvtColor(view, viewGray, COLOR_BGR2GRAY);
			cornerSubPix(viewGray, pointBuf, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

			imagePoints.push_back(pointBuf);			
			drawChessboardCorners(view, boardSize, Mat(pointBuf), found);
			

			/*char wnd[256];
			sprintf(wnd, "corner detection test%d", i+1);
			imshow(wnd, view);
			waitKey();
			destroyAllWindows();*/
		}
		
		imageSize = view.size();
		
	}

	Mat cameraMatrix;
	Mat distCoeffs;
	vector<Mat> rvec, tvec;
	vector<float> reprojError;
	double totalAvgError;
	if (imagePoints.size() > 0)
		pij.executeCameraCalib(imageSize, cameraMatrix, distCoeffs, imagePoints, rvec, tvec, reprojError, totalAvgError);
	return 0;
}

void calcBoardCornerPositions(Size boardSize, float squareSize, vector<Point3f>& corners /*, Settings::Pattern patternType /*= Settings::CHESSBOARD*/)
{
	corners.clear();

	
	// chess board or circles grid
	for (int i = 0; i < boardSize.height; ++i)
		for (int j = 0; j < boardSize.width; ++j)
			corners.push_back(Point3f(float(j*squareSize), float(i*squareSize), 0));
	

	// asymmetric circles grid
	/*for (int i = 0; i < boardSize.height; i++)
		for (int j = 0; j < boardSize.width; j++)
			corners.push_back(Point3f(float((2 * j + i % 2)*squareSize), float(i*squareSize), 0));*/
	
	
}

double computeReprojectionErrors(const vector<vector<Point3f> >& objectPoints,
	const vector<vector<Point2f> >& imagePoints,
	const vector<Mat>& rvecs, const vector<Mat>& tvecs,
	const Mat& cameraMatrix, const Mat& distCoeffs,
	vector<float>& perViewErrors)
{
	vector<Point2f> imagePoints2;
	int i, totalPoints = 0;
	double totalErr = 0, err;
	perViewErrors.resize(objectPoints.size());

	for (i = 0; i < (int)objectPoints.size(); ++i)
	{
		projectPoints(Mat(objectPoints[i]), rvecs[i], tvecs[i], cameraMatrix,
			distCoeffs, imagePoints2);
		err = norm(Mat(imagePoints[i]), Mat(imagePoints2), CV_L2);

		int n = (int)objectPoints[i].size();
		perViewErrors[i] = (float)std::sqrt(err*err / n);
		totalErr += err*err;
		totalPoints += n;
	}

	return std::sqrt(totalErr / totalPoints);
}


void CalibPIJ::executeCameraCalib(Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs, vector<vector<Point2f>> imagePoints, 
								  vector<Mat>& rvecs, vector<Mat>& tvecs, vector<float>& reprojErrs, double& totalAvgErr)
{
	cameraMatrix = Mat::eye(3, 3, CV_64F);
	
	// need to check CV_CALB_FIX_ASPECT_RATIO mode

	distCoeffs = Mat::zeros(8, 1, CV_64F);

	vector<vector<Point3f>> objectPoints(1);
	calcBoardCornerPositions(boardSize, squareSize, objectPoints[0]/*, board type check flag*/);
	objectPoints.resize(imagePoints.size(), objectPoints[0]);
	double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs/*, CV_CALIB_USE_INTRINSIC_GUESS*/);
	cout << "Re-projection error reported by calibrateCamera: " << rms << endl;
	bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);

	totalAvgErr = computeReprojectionErrors(objectPoints, imagePoints,
		rvecs, tvecs, cameraMatrix, distCoeffs, reprojErrs);
	
	cout << (ok ? "Calibration succeeded" : "Calibration failed")
		<< ". avg re projection error = " << totalAvgErr;


}
bool boardImageCapture(int frameNum)
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		printf("fail to open video\n");
		return false;
	}

	int frameCnt = 0;
	Mat curframe;
	vector<Mat> boardimgs;
	char key;
	while(frameCnt < frameNum)
	{
		Mat frame;
		cap >> frame;
		flip(frame, curframe, 1);

		imshow("test", curframe);

		key = waitKey(30);
		if (key == 'q')
		{
			break;
		}
		else if (key == 's')
		{
			printf("frame num : %d\n", ++frameCnt);
			boardimgs.push_back(curframe.clone());
			imshow("captured frame", curframe);
		}
	}

	if (frameCnt < frameNum)
		return false;

	for (int i = 0; i < frameCnt; i++)
	{
		char fname[256];
		sprintf(fname, "board%d.jpg", i + 1);
		imwrite(fname, boardimgs[i]);
	}

	return true;
}

bool CalibPIJ::readBoardImages(string imgname, const int nImgs)
{
	char fname[256];	
	
	for (int i = 0; i < numOfImages; i++)
	{
		sprintf(fname, "%s%02d.jpg", imgname.c_str(), i+1);		
		cout << fname << endl;
		Mat temp = imread(fname, IMREAD_COLOR);
		if (temp.empty())
		{
			cout << "fail to read image - "<< i << endl;
			return false;
		}
		boardImages.push_back(temp.clone());
	}

	/*for (int i = 0; i < nImgs; i++)
	{
		char wnd[256];
		sprintf(wnd, " img%d", i);
		imshow(wnd, boardImages[i]);
	}
	waitKey();
	*/

	
	return true;
}