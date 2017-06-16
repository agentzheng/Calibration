#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/aruco.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat markerImage;
	Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
	for (int i = 0; i < 20; i++) {
		aruco::drawMarker(dictionary, i, 1000, markerImage, 1);
		imwrite(to_string(i)+".jpg", markerImage);
	}
	
	cvWaitKey(0);
}