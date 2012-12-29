#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QtCore/QString>

#include <libraw/libraw.h>

#include "EImage.h"

class ImageLoader
{
public:
	ImageLoader();
	EImage load(const QString& filename);
private:
	LibRaw mRaw;
};

#endif // IMAGELOADER_H
