#include "Stacker.h"

#include <Eigen/Core>

#include "StackerBuffer.h"
#include "EImage.h"

Stacker::Stacker(const SourceFrameList &frames) {
	m_frames = frames;
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
	void (*stackFunction)(const StackerBuffer&, Eigen::Array4Xf*, int) = 0;
	switch(m_method) {
		case Stacker::MeanStacking:
			stackFunction = &Mean::stack;
			break;
		default:
			abort();
	}

	int width = m_images[0].width();
	Eigen::Array4Xf* output = new Eigen::Array4Xf(4, numPixels);
	for(int block = 0; block < numPixels;
		block += StackerBuffer::MAX_BUFFER_SIZE)
	{
		StackerBuffer buf(m_images, block);
		stackFunction(buf,output,block);
	}

	return EImage(output,m_images[0].width(),m_images[0].height());
}

// Stacking Methods

namespace Mean {
void stack(const StackerBuffer& buf,
		   Eigen::Array4Xf* dest,
		   int destIndex)
{
	// s is the part of the pixel stack
	// corresponding to pixel i
	Eigen::Block<const Eigen::Array4Xf> s;
	int numImages = buf.numImages();
	int numPixels = buf.numPixels();
	for(int i = 0; i < numPixels; ++i) {
		s = stack.block(0,i*numImages,4,numImages);
		// Mean of columns
		dest->col(destIndex + i) = s.rowwise().mean();
	}
}
} // NS Mean


