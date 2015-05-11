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
	

	std::vector<KeyPoint> getRawKeypoints(){
		return keypoints;
	};
	std::vector<KeyPoint> getRawDescriptors(){
		return descriptors;
	};

	Ptr<Mat> img;
	std::vector<Ptr<Mat>> pyramid;
	std::vector<KeyPoint> keypoints;
	Mat descriptors;

};

