#pragma once

#include "opencv2/opencv.hpp"
#include <opencv2/features2d/features2d.hpp>
#include "Frame.h"


using namespace cv;

class FrameAnalyzer
{
public:
	FrameAnalyzer();
	~FrameAnalyzer();

	Frame* processFrame(Ptr<Mat> f);

	void match2Frames(Frame* f1, Frame* f2);
	std::vector< DMatch > removeOutliersFromMatch(const std::vector< DMatch >& m, double distance);
private:
	Ptr<Feature2D> feature;
	Ptr<DescriptorMatcher> matcher;
};

