#include "ImageLoader.h"

ImageLoader::ImageLoader()
	: mRaw()
{
}

EImage* ImageLoader::load(const QString &filename)
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
	// Todo: implement our own raw processing
	err = mRaw.dcraw_process();
	if( err != LIBRAW_SUCCESS )
		abort(); //TODO: error handling
	int height = mRaw.imgdata.sizes.iheight;
	int width = mRaw.imgdata.sizes.iwidth;
	int size = height * width;
	// then convert to array of float
	Eigen::Array4Xf* image = new Eigen::Array4Xf(4, size);
	unsigned short (*ptr)[4] = mRaw.imgdata.image;
	for(int i = 0; i < size; ++i) {
		// Saturate alpha channel
		(*(ptr + i))[3] = (1 << 16) -1;
		for(int j = 0; j < 4; ++j) {
			// NB. Eigen uses column-major order by default.
			(*image)(j,i) = (*(ptr + i))[j];
		}
	}
	return new EImage(image, width, height);
}
