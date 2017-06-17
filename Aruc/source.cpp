#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/aruco.hpp>

using namespace std;
using namespace cv;

int main(){
	for (int i = 0; i < 5; i++){
		string a = "a";
		a = a + to_string(i);
		cout << a +".jpg"<< endl;
		Mat inputImage = imread(a+".jpg");
		if (!inputImage.data){
			cout << "can't find image" << endl;
			return -1;
		}
		std::vector<int> markerIds;
		std::vector<std::vector<Point2f>> markerCorners, rejectedCandidates;
		Ptr<aruco::DetectorParameters> parameters = aruco::DetectorParameters::create();
		Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
		aruco::detectMarkers(inputImage, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
		aruco::drawDetectedMarkers(inputImage, markerCorners, markerIds);
		imwrite(a+".png", inputImage);
	}
	cvWaitKey(0);
}