#include "FrameQueue.h"


FrameQueue::FrameQueue(int size) :max_size(size), Q(size)
{
}


FrameQueue::~FrameQueue()
{
}

void FrameQueue::add(Ptr<Frame> f){
	Q[currentPos++]=f;
	if (currentPos == max_size)
		currentPos = 0;
	if (currentSize != max_size)
		currentSize++;
}