#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/aruco.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat markerImage;
	Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
	aruco::drawMarker(dictionary, 0, 400, markerImage, 1);
	Mat FourMarkers(Size(1000, 1000), markerImage.type(), Scalar::all(255));
	for (int i = 0; i < 20; i++)
	{
		Mat markerImage1;
		for (int j = 0; j < 2; j++)
		{
			aruco::drawMarker(dictionary, i * 4 + 2*j, 400, markerImage1, 1);
			markerImage1.copyTo(Mat(FourMarkers, Rect(50, 50+500*j, 400, 400)));
			aruco::drawMarker(dictionary, i * 4 + 2*j + 1, 400, markerImage1, 1);
			markerImage1.copyTo(Mat(FourMarkers, Rect(550, 50 + 500 * j, 400, 400)));
			imshow(to_string(i) + ".jpg", FourMarkers);
		}
		//Mat result;
		//resize(FourMarkers, result, Size(1000, 1000));
		imwrite(to_string(i) + ".jpg", FourMarkers);
		cvWaitKey(10);
	}
}