#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/aruco.hpp>

using namespace std;
using namespace cv;

int main(){
	int waitTime = 1;
	cv::VideoCapture inputVideo;
	inputVideo.open(0);
	cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
	while (inputVideo.grab()) {
		cv::Mat image, imageCopy;
		inputVideo.retrieve(image);
		image.copyTo(imageCopy);
		std::vector<int> ids;
		std::vector<std::vector<cv::Point2f> > corners;
		cv::aruco::detectMarkers(image, dictionary, corners, ids);// if at least one marker detected
		if (ids.size() > 0)
			cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
		cv::imshow("out", imageCopy);
		char key = (char)cv::waitKey(waitTime);
		if (key == 27)
			break; 
	}
	return 0;
}