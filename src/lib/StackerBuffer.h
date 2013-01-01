#ifndef STACKERBUFFER_H
#define STACKERBUFFER_H

/** The buffer is held as an Array4Xf, with the pixels from the
	same location but different images next to each other, and then in
	rows with regard to the output order:

	[ px 0,0 ][ px 1,0 ]........[ 127,0 ][ 0,1 ]........
	RRRRRRRRRRRRRRRRRRRR........RRRRRRRRRRRRRRRR........
	GGGGGGGGGGGGGGGGGGGG........GGGGGGGGGGGGGGGG........
	BBBBBBBBBBBBBBBBBBBB........BBBBBBBBBBBBBBBB........
	AAAAAAAAAAAAAAAAAAAA........AAAAAAAAAAAAAAAA........

	Each call to stack() creates a new buffer.
	2^16 pixels * 4 bpp * 4 channels = 1 MB per image.
 */


class StackerBuffer
{
public:
	static const int BUFFER_SIZE = 1 << 16;
	StackerBuffer(const SourceFrameList& images, int offset);
	int numImages() const;
	int numPixels() const;
	Eigen::Array4Xf& buffer();
	const Eigen::Array4Xf& buffer() const;
private:
	int m_numImages;
	int m_numPixels;
	Eigen::Array4Xf m_buf;
};


#endif // STACKERBUFFER_H
