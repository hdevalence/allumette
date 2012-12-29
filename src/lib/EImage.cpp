#include "EImage.h"

EImage::EImage(Eigen::Array4Xf image, int w, int h)
{
	i = image;
	width = w;
	height = h;
	valid = (width * height == image.cols());
}

EImage::EImage()
{
	valid = false;
}

void EImage::setTransform(const Eigen::Matrix3f &transform)
{
	mTransform = transform;
}

Eigen::Array4f EImage::get(int i, int j)
{
	// FIXME: We're assuming that 1*1*.....*1 = 1.
	// Is this true, or do we need to worry about float error?
	mCoordInBuf[0] = i;
	mCoordInBuf[1] = j;
	mCoordOutBuf = mTransform * mCoordInBuf;
	i = static_cast<int>(mCoordOutBuf[0]);
	j = static_cast<int>(mCoordOutBuf[1]);
	if( i < 0 || i >= width || j < 0 || j >= height ) {
		return OUT_OF_BOUNDS_PX;
	} else {
		int idx = width * i + j;
		return image.col(idx);
	}
}
