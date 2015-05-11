#pragma once
#include "Frame.h"
#include "opencv2\core.hpp"
using namespace cv;

class FrameQueue
{
public:
	FrameQueue(int size);
	~FrameQueue();

	void add(Ptr<Frame> f);
	Ptr<Frame> getLastFrame(){
		return Q[(currentPos - 2 + max_size) % max_size];
	}


	Ptr<Frame> getCurrentFrame(){
		return Q[(currentPos - 1 + max_size) % max_size];
	}

	Ptr<Frame> getNLastFrame(int n){
		return Q[(currentPos -1 - n + max_size) % max_size];
	}

	int size(){
		return currentSize;
	}
private:
	int currentSize = 0;
	int currentPos = 0;
	int max_size;
	std::vector < Ptr<Frame> > Q; //circular FIFO
};

