#include "StackerBuffer.h"

StackerBuffer::StackerBuffer(const SourceFrameList &images, int offset)
{
	m_numImages = images.size();
	int sourcePixels = images[0]->numPixels();
	int m_numPixels = 0;
	int stop  = offset + MAX_BUFFER_SIZE;

	if(stop < sourcePixels) {
		m_numPixels = MAX_BUFFER_SIZE;
	} else {
		stop = sourcePixels;
		m_numPixels = sourcePixels-offset;
	}

	m_buf = Eigen::Array4Xf(4,m_numImages*m_numPixels);
	int width = images[0]->width();
	for(int i = 0; i < m_numImages; ++i) {
		SourceFrame* image = images[i];
		for(int j = offset; j < stop; ++j) {
			int x = j % width;
			int y = j / width;
			m_buf.col(j*m_numImages + i) = image->getTransformed(x,y);
		}
	}
}

int StackerBuffer::numImages() const
{
	return m_numImages;
}

int StackerBuffer::numPixels() const
{
	return m_numPixels;
}

Eigen::Array4Xf& StackerBuffer::buffer()
{
	return m_buf;
}

const Eigen::Array4Xf& StackerBuffer::buffer() const
{
	return m_buf;
}
