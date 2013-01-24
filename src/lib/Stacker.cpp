#include "Stacker.h"

#include <Eigen/Core>

#include "StackerBuffer.h"
#include "EImage.h"


// Stacking Methods

namespace Mean {
void stack(const StackerBuffer& buf,
           StackerBuffer* dest)
{
	int numImages = buf.numImages();
	const Eigen::Array4Xf src = buf.buffer();
	for(int x = 0; x < StackerBuffer::BUFFER_SIZE; ++x) {
		for(int y = 0; y < StackerBuffer::BUFFER_SIZE; ++y) {
		// s is the part of the pixel stack
		// corresponding to pixel x,y
		auto s = src.block(0, numImages*StackerBuffer::bufIdx(0,x,y),
		                   4, numImages);
		// Mean of columns
		dest->col(StackerBuffer::bufIdx(0,x,y)) = s.rowwise().mean();
	}
}
} // NS Mean

// Stacker class

Stacker::Stacker(const SourceFrameList &frames) 
    : m_frames(frames)
{
	
}

Stacker::Method Stacker::method() const
{
	return m_method;
}

void Stacker::setMethod(Stacker::Method method)
{
	m_method = method;
}

EImage Stacker::stack()
{
	void (*stackFunction)(const StackerBuffer&, StackerBuffer*, int) = 0;
	switch(m_method) {
		case Stacker::MeanStacking:
			stackFunction = &Mean::stack;
			break;
		default:
			abort();
	}

	int w = m_frames[0]->width();
	int h = m_frames[0]->height();
	Eigen::Array4Xf* i = new Eigen::Array4Xf(4,w*h);
	EImage img(i,w,h);

	for(int x = 0; x < w; x += StackerBuffer::BUFFER_SIZE) {
		for(int y = 0; y < h; y += StackerBuffer::BUFFER_SIZE) {
			StackerBuffer buf(m_frames,x,y);
			StackerBuffer out(1);
			stackFunction(buf, &out);
		}
	}

	// TODO: copy stacked data into output.
	return img;
}

