#ifndef EIMAGE_H
#define EIMAGE_H

#include <Eigen/Core>

/**
 * @brief The EImage class holds an image as an Eigen array.
 *
 * It allows two methods of access:
 * 1.  As a glorified struct, with direct read/write access
 * 2.  An interface to the data which handles translations, etc.
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

	void setTransform(const Eigen::Matrix3f& transform);

	/**
	 * @brief Get pixel under transformation.
	 * @param i the x coordinate
	 * @param j the y coordinate
	 * @return the pixel value
	 */
	inline Eigen::Array4f get(int i, int j);
private:
	Eigen::Matrix3f mTransform = Eigen::Matrix3f::Identity();
	Eigen::Vector3f mCoordInBuf  = Eigen::Vector3f(0,0,1);
	Eigen::Vector3f mCoordOutBuf = Eigen::Vector3f(0,0,1);
	static const Eigen::Array4f OUT_OF_BOUNDS_PX = Eigen::Array4f::Zero();
};

#endif // EIMAGE_H
