#include "Frame.h"


Frame::Frame(int id, Ptr<Mat> img, double timestamp) :id(id), img(img), timestamp(timestamp)
{
}


Frame::~Frame()
{
}
