#ifndef EIMAGE_H
#define EIMAGE_H

#include <Eigen/Core>

/**
 * @brief The EImage class holds an image as an Eigen array.
 *
 * This class is basically acting as a glorified struct,
 * rather than a real OO class.
 */
class EImage
{
public:
	/**
	 * @brief i holds the image data
	 *
	 * Pixels are RGBA float arrays.
	 * @p i has rows * cols columns, with pixels set out in
	 * column-major order, i.e., like Eigen or Fortran.
	 */
	Eigen::Array4Xf i;
	int width;
	int height;
	bool valid;

	/**
	 * @brief Constructs an image from existing data
	 * @param image The image data
	 * @param w The width of the image
	 * @param h The height of the image
	 */
	EImage(Eigen::Array4Xf image, int w, int h);

	/**
	 * @brief Constructs an invalid image.
	 */
	EImage();
};

#endif // EIMAGE_H
