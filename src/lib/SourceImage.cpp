#include "SourceFrame.h"

SourceFrame::SourceFrame()
{
}

SourceFrame::SourceFrame(const QString &filename, ImageLoader *loader)
{
	bool newLoader = !loader;
	if(newLoader) {
		loader = new ImageLoader();
	}

	// We'll need to think of some nice way to pass on libraw errors.
	m_image = loader->load(filename);

	if(newLoader) {
		delete loader;
	}
}

SourceFrame::~SourceFrame()
{
	delete m_image->i;
	delete m_image;
}

SourceFrame::FrameType SourceFrame::frameType() const
{
	return m_frameType;
}

void SourceFrame::setFrameType(SourceFrame::FrameType type)
{
	m_frameType = type;
}

const EImage &SourceFrame::imageData() const
{
	return *m_image;
}

const Eigen::Array4f &SourceFrame::getTransformed(int i, int j) const
{
	// FIXME: We're assuming that 1*1*.....*1 = 1.
	// Is this true, or do we need to worry about float error?
	m_coordInBuf[0] = i;
	m_coordInBuf[1] = j;
	m_coordOutBuf = m_transform * m_coordInBuf;
	i = static_cast<int>(m_coordOutBuf[0]);
	j = static_cast<int>(m_coordOutBuf[1]);
	return this->get(i,j);
}

const Eigen::Array4f &SourceFrame::get(int i, int j) const
{
	if( i < 0 || i >= w || j < 0 || j >= h ) {
		return OUT_OF_BOUNDS_PX;
	} else {
		int idx = width * i + j;
		return m_image->i.col(idx);
	}
}


SourceFrame::SourceImage &SourceFrame::operator =(const SourceFrame::SourceImage &s)
{
}


SourceFrame::SourceImage(const SourceFrame::SourceImage &s)
{
}

int SourceFrame::width() const
{
	return m_image->w;
}

int SourceFrame::height() const
{
	return m_image->h;
}

int SourceFrame::numPixels() const
{
	return m_image->cols();
}
