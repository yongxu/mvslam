#include "FrameAnalyzer.h"


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
	feature->detectAndCompute(*f, noArray(), frame->keypoints, frame->descriptors);
	return frame;
}


std::vector< DMatch > FrameAnalyzer::match2Frames(Frame* f1, Frame* f2){
	std::vector< DMatch > matches;
	matcher->match(f1->descriptors, f2->descriptors, matches);
	return matches;
}


std::vector< DMatch > FrameAnalyzer::removeOutliersFromMatch(std::vector< DMatch >& m, double distance){
	std::vector< DMatch > nm;
	for (auto i = m.begin(); i != m.end();++i){
		if (i->distance < distance)
			nm.push_back(*i);
	}
	return nm;
}