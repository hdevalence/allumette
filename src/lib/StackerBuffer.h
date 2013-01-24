#ifndef STACKERBUFFER_H
#define STACKERBUFFER_H

#include <Eigen/Core>

// FIXME: We need this to prevent a circular include with EImage in
// the header files. To fix this, we should have a header with 
// typedefs and utility functions.
class SourceFrame;
typedef std::vector<SourceFrame*> SourceFrameList;

/* Each buffer holds a square of size BUFFER_SIZE from each
   image, transformed according to that image's position.
 */

class StackerBuffer
{
public:
	static const int BUFFER_SIZE = 32;
	StackerBuffer(int num_frames);
	StackerBuffer(const SourceFrameList& images, int x, int y);
	int numImages() const;
	Eigen::Array4Xf& buffer();
	const Eigen::Array4Xf& buffer() const;

	inline int bufIdx(int imageIdx, int x, int y) const 
    {
		int xoffset = x*m_numImages*BUFFER_SIZE;
		int yoffset = y*m_numImages;
		return xoffset + yoffset + imageIdx;
	}

	inline void imageIdx(int bufIdx, int* x, int* y, int* imageIdx) const
    {
		*x = bufIdx / (m_numImages*BUFFER_SIZE);
		bufIdx = bufIdx % (m_numImages*BUFFER_SIZE); 
		*y = bufIdx / m_numImages;
		*imageIdx = bufIdx % m_numImages;
	}

private:
	int m_numImages;
	Eigen::Array4Xf m_buf;
};


#endif // STACKERBUFFER_H
