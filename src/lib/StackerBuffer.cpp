#include "StackerBuffer.h"
#include "SourceFrame.h"

StackerBuffer::StackerBuffer(int num_frames)
{
	m_numImages = num_frames;
	m_buf = Eigen::Array4Xf(4,m_numImages*BUFFER_SIZE*BUFFER_SIZE);
}

StackerBuffer::StackerBuffer(const SourceFrameList &images, int x, int y)
{
	m_numImages = images.size();
	m_buf = Eigen::Array4Xf(4,m_numImages*BUFFER_SIZE*BUFFER_SIZE);

	for(int i = 0; i < m_numImages; ++i) {
		SourceFrame* image = images[i];
		for(int x; x < BUFFER_SIZE; ++x) {
			for(int y; y < BUFFER_SIZE; ++y) {
				m_buf.col( bufIdx(i,x,y) ) = image->getTransformed(x,y);
			}
		}
	}
}

int StackerBuffer::numImages() const
{
	return m_numImages;
}

Eigen::Array4Xf& StackerBuffer::buffer()
{
	return m_buf;
}

const Eigen::Array4Xf& StackerBuffer::buffer() const
{
	return m_buf;
}
