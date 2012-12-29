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
