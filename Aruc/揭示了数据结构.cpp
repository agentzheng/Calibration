#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/aruco.hpp>

using namespace std;
using namespace cv;

int main(){
	for (int i = 0; i < 5; i++) {
		string a = "a";
		a = a + to_string(i);
		cout << a + ".jpg" << endl;
		Mat inputImage = imread(a + ".jpg");
		if (!inputImage.data) {
			cout << "can't find image" << endl;
			return -1;
		}
		std::vector<int> markerIds;
		vector<vector<Point2f>> markerCorners, rejectedCandidates;
		Ptr<aruco::DetectorParameters> parameters = aruco::DetectorParameters::create();
		Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
		aruco::detectMarkers(inputImage, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
		
		for (vector<vector<Point2f>>::iterator it=markerCorners.begin(); it!=markerCorners.end(); it++)
		{
			for (vector<Point2f>::iterator it2 = it->begin(); it2 != it->end(); it2++)
			{
				Point2f& point = *it2;
				cout << "(" << point.x << "," << point.y << ")";
			}
			cout << endl;
		}
		for (vector<int>::iterator it = markerIds.begin(); it != markerIds.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}