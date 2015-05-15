#pragma once
#include "opencv2/opencv.hpp"

using namespace cv;

void subSampleIndexes(int sampleIndex[], int size){
	int idx_i;
	RNG rng;
	int i = 0, j;
	for (;;)
	{
		idx_i = sampleIndex[i] = rng.uniform(0, size);
		for (j = 0; j < i; j++)
			if (idx_i == sampleIndex[j])
				break;
		if (j == i)
			break;
	}

}
void ransac(Point2f* p1, Point2f* p2, int sampleSize, int subSampleSize, double confidence = 0.99, int maxIters = 1000){

	int iters = maxIters;
	int* subSampleIdx = new int[subSampleSize];
	Point2f* subSampleP1 = new Point2f[subSampleSize];
	Point2f* subSampleP2 = new Point2f[subSampleSize];
	int maxInliers = subSampleSize-1;
	for (int n = 0; n < iters; n++){
		subSampleIndexes(subSampleIdx, subSampleSize);
		for (int i = 0; i < subSampleSize; i++){
			subSampleP1[i] = p1[i];
			subSampleP2[i] = p2[i];
		}
		//run sample model and find inliers
		int goodInliers = 0;
		if (goodInliers > maxInliers)
		{
			model_i.copyTo(bestModel);
			maxInliers = goodInliers;
			niters = RANSACUpdateNumIters(confidence, (double)(count - goodCount) / count, modelPoints, niters);
		}
	}
	
	delete[] subSampleIdx;
	delete[] subSampleP1;
	delete[] subSampleP2;
}

