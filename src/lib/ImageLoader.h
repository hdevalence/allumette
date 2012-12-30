#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QtCore/QString>

#include <libraw/libraw.h>

#include "EImage.h"

/**
 * @brief The ImageLoader class handles loading RAW files
 * into image data. We need to have this in an object since
 * LibRaw has some state.
 *
 * This is reentrant as long as we link to the reentrant
 * version of LibRaw.
 */
class ImageLoader
{
public:
	ImageLoader();
	/**
	 * @brief load an image into memory
	 * @param filename
	 * @return A pointer to a newly-allocated array.
	 *
	 * Note: Ownership of the EImage is handed to the callee.
	 */
	EImage* load(const QString& filename);
private:
	LibRaw mRaw;
};

#endif // IMAGELOADER_H
