#include "FrameAnalyzer.h"
#include <math.h>


FrameAnalyzer::FrameAnalyzer()
{
	int nfeatures = 500;
	float scaleFactor = 1.2f;
	int nlevels = 8;
	int edgeThreshold = 31;
	int firstLevel = 0;
	int WTA_K = 2;
	int scoreType = ORB::HARRIS_SCORE;
	int patchSize = 31;
	int fastThreshold = 20;
	feature = ORB::create(
		nfeatures,
		scaleFactor,
		nlevels,
		edgeThreshold,
		firstLevel,
		WTA_K,
		scoreType,
		patchSize,
		fastThreshold);

	matcher = new BFMatcher(NORM_L2);
}


FrameAnalyzer::~FrameAnalyzer()
{
}

Frame* FrameAnalyzer::processFrame(Ptr<Mat> f){
	Frame* frame = new Frame(0,f,0);
	return frame;
}


void FrameAnalyzer::match2Frames(Frame* f1, Frame* f2){
	std::vector< DMatch > matches;
	std::vector<KeyPoint> kp1,kp2;
	Mat descriptors1, descriptors2;
	feature->detectAndCompute(*f1->img, noArray(), kp1, descriptors1);
	feature->detectAndCompute(*f1->img, noArray(), kp2, descriptors2);
	matcher->match(descriptors1, descriptors2, matches);
	auto ms=removeOutliersFromMatch(matches, 100);

	static Point2f k1[1024];
	static Point2f k2[1024];
	int i;//size of ms
	for (i=0; i < fmin(ms.size(),1024); i++){
		k1[i] = kp1.at(ms.at(i).queryIdx).pt;
		k2[i] = kp2.at(ms.at(i).trainIdx).pt;
	}


}


std::vector< DMatch > FrameAnalyzer::removeOutliersFromMatch(const std::vector< DMatch >& m, double distance){
	std::vector< DMatch > nm;
	for (auto i = m.begin(); i != m.end();++i){
		if (i->distance < distance)
			nm.push_back(*i);
	}
	return nm;
}

