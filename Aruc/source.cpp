#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/aruco.hpp>

using namespace std;
using namespace cv;

void Find_Match(vector<DMatch>& RR_matches, vector<KeyPoint>& RR_keypoint01, vector<KeyPoint>& RR_keypoint02, int index1, vector<vector<Point2f>>& markCorners1, int index2, vector<vector<Point2f>>& markCorners2);

int main(int argc,char** argv)
{
		Mat inputImage1 = imread(argv[1]);
		Mat inputImage2 = imread(argv[2]);
		if (!inputImage2.data||!inputImage2.data) {
			cerr << "can't find image" << endl;
			return -1;
		}
		std::vector<int> markerIds1,markerIds2;//markID
		vector<vector<Point2f>> markerCorners1, markerCorners2;//mark角点
		Ptr<aruco::DetectorParameters> parameters = aruco::DetectorParameters::create();//检测所需参数
		Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
		aruco::detectMarkers(inputImage1, dictionary, markerCorners1, markerIds1, parameters);
		aruco::detectMarkers(inputImage2, dictionary, markerCorners2, markerIds2, parameters);

		vector<KeyPoint> keypoint1, keypoint2;
		vector<DMatch> match;
		for (vector<int>::iterator it1 = markerIds1.begin(); it1 != markerIds1.end(); it1++)
		{
			bool is_find = false;
			cout << "The ID of marker is " << *it1 << endl;
			for (vector<int>::iterator it2 = markerIds2.begin(); it2 != markerIds2.end(); it2++)
			{
				if (*it1 == *it2) 
				{
					cout << "Yes,we find the match";
					int index1 = distance(markerIds1.begin(), it1);
					int index2 = distance(markerIds2.begin(), it2);
					Find_Match(match, keypoint1, keypoint2, index1, markerCorners1, index2, markerCorners2);
					cout << "generate match success" <<endl;
					is_find = true;
					break;
				}
			}
			if(!is_find)
				cout << "Sorry, The marker doesn't find any match" << endl;
			cout << endl;
		}
	Mat img_RR_matches;
	drawMatches(inputImage1, keypoint1, inputImage2, keypoint2, match, img_RR_matches);
	imshow("寻找匹配点", img_RR_matches);
	cvWaitKey(0);
	return 0;
}




void Find_Match(vector<DMatch>& RR_matches, vector<KeyPoint>& RR_keypoint01, vector<KeyPoint>& RR_keypoint02,int index1,vector<vector<Point2f>>& markCorners1, int index2, vector<vector<Point2f>>& markCorners2)
{
	vector<Point2f>::iterator it1 = markCorners1[index1].begin();//index1和index2往往是不一样的
	vector<Point2f>::iterator it2 = markCorners2[index2].begin();
	while (it1 != markCorners1[index1].end() && it2 != markCorners2[index2].end())
	{
		DMatch match;
		KeyPoint keypoint1(*it1,2);
		KeyPoint keypoint2(*it2,2);//这个2只是为了凑数而已，实际上这指的是描述子的半径，不过对我们这边应该没有影响
		RR_keypoint01.push_back(keypoint1);
		RR_keypoint02.push_back(keypoint2);
		if (RR_keypoint01.size() == RR_keypoint02.size())
		{
			match.trainIdx=match.queryIdx = RR_keypoint01.size() - 1;
			RR_matches.push_back(match);
		}
		else
		{
			cerr << "Error:the two is no the same" << endl;
		}
		it1++;
		it2++;
	}
}