#pragma once
#include "opencv2/opencv.hpp"
#include <opencv2/features2d/features2d.hpp>


using namespace cv;
class Frame
{
public:
	Frame(int id, Ptr<Mat> img, double timestamp);
	Frame(int id){};
	~Frame();

	double timestamp;

	int id;
	

	std::vector<Point2f> getRawKeypoints(){
		return keypoints;
	};

	Ptr<Mat> img;
	std::vector<Ptr<Mat>> pyramid;
	std::vector<Point2f> keypoints;

};

