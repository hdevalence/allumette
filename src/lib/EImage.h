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
	Eigen::Array4Xf* img;
	int w;
	int h;
	
	/**
	 * @brief Constructs an image from existing data.
	 */
	EImage(Eigen::Array4Xf* image, int width, int height)
	{
		img = image;
		w = width;
		h = height;
	}

	inline Eigen::Array4f get(int x, int y) const
	{
		if( x < 0 || x >= w || y < 0 || y >= h ) {
			return OUT_OF_BOUNDS_PX;
		} else {
			int idx = bufIdx(x,y);
			return img->col(idx);
		}
	}

	inline int buf_idx(int x, int y)
	{
		return x*w + y;
	}

	void load_buffer(const StackerBuffer& buf, int x, int y)
	{
		auto b = buf.buffer();
		int block_width = StackerBuffer::BUFFER_SIZE;
		int block_height = StackerBuffer::BUFFER_SIZE;
		if( x + block_width > w ) {
			block_width = w - x;
		}
		if( y + block_height > h ) {
			block_height = h - y;
		}
		// TODO: implement. currently this is a noop.
	}
};

#endif // EIMAGE_H
