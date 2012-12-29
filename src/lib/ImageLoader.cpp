#include "ImageLoader.h"

ImageLoader::ImageLoader()
	: mRaw()
{
}

EImage ImageLoader::load(const QString &filename)
{
	const char * fn = filename.toLocal8Bit().constData();
	int err = mRaw.open_file(fn);
	if( err != LIBRAW_SUCCESS )
		abort(); //TODO: error handling
	// unpack() loads the raw data but does not debayer it.
	err = mRaw.unpack();
	if( err != LIBRAW_SUCCESS )
		abort(); //TODO: error handling
	// now we debayer
	err = mRaw.raw2image();
	if( err != LIBRAW_SUCCESS )
		abort(); //TODO: error handling
	int height = mRaw.imgdata.sizes.iheight;
	int width = mRaw.imgdata.sizes.iwidth;
	int size = height * width;
	// then convert to array of float
	Eigen::Array4Xf image(4, size);
	unsigned short (*ptr)[4] = mRaw.imgdata.image;
	for(int i = 0; i < size; ++i) {
		for(int j = 0; j < 4; ++j) {
			// NB. Eigen uses column-major order by default.
			image(j,i) = (*(ptr + i))[j];
		}
	}
	return EImage(image, width, height);
}