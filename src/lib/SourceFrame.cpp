#include "SourceFrame.h"

#include "ImageLoader.h"

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
    //FIXME: memory ownership semantics on images?
	delete m_image->img;
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

SourceFrame& SourceFrame::operator=(const SourceFrame &s)
{
	// NOOP
}


SourceFrame::SourceFrame(const SourceFrame &s)
{
	// NOOP
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
	return width()*height();
}
