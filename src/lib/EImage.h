#ifndef EIMAGE_H
#define EIMAGE_H

#include <Eigen/Core>

/**
 * @brief The EImage class holds an image as an Eigen array.
 *
 * It acts as a glorified struct, with direct read/write access.
 * We need it only because our pixel data is an Eigen array and
 * Eigen does not support multidimensional arrays.
 */
class EImage
{
public:
	/**
	 * @brief i holds the image data
	 *
	 * Pixels are RGBA float arrays.
	 * i has w*h columns, with pixels set out in
	 * column-major order, i.e., like Eigen or Fortran.
	 */
	Eigen::Array4Xf* i;
	int w;
	int h;
	/**
	 * @brief Constructs an image from existing data.
	 */
	EImage(Eigen::Array4Xf* image, int width, int height)
	{
		i = image;
		w = width;
		h = height;
	}
};

#endif // EIMAGE_H
