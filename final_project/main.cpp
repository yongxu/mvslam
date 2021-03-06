#include "opencv2/opencv.hpp"
#include <opencv2/features2d/features2d.hpp>
#include "FrameAnalyzer.h"
#include "FrameQueue.h"

using namespace cv;

int main(int, char)
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened()) // check if we succeeded
		return -1;
	namedWindow("t", 1);
	namedWindow("t2", 2);

	FrameAnalyzer fa;
	FrameQueue Q(5);

	for (;;)
	{
		Mat* img=new Mat;
		cap >> *img;


		Ptr<Frame> f=fa.processFrame(img);
		Q.add(f);


		
		if (Q.size() > 1
			&& Q.getLastFrame()->getRawKeypoints().size()>0
			&& Q.getCurrentFrame()->getRawKeypoints().size()>0){
			fa.match2Frames(Q.getLastFrame(), Q.getCurrentFrame());
			//Mat fundamental = findFundamentalMat(Q.getLastFrame()->getRawKeypoints(), Q.getCurrentFrame()->getRawKeypoints(), FM_RANSAC, 3.0, 0.99);
			//std::cout << "Fundamental Matrix " << fundamental << std::endl;
		}

		waitKey(10);
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}