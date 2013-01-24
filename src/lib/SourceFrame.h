#ifndef SOURCEFRAME_H
#define SOURCEFRAME_H

#include <vector>

#include <Eigen/Core>

#include <QtCore/QString>

#include "EImage.h"

class ImageLoader;
class SourceFrame;

typedef std::vector<SourceFrame*> SourceFrameList;

class SourceFrame
{
public:
	/**
	 * @brief SourceFrame represents a single source frame,
	 * be it light, dark, flat, or bias.
	 * @param filename The source file
	 * @param loader Used if nonnull
	 */
	SourceFrame(const QString& filename, ImageLoader* loader = 0);
	~SourceFrame();

	enum FrameType {
		LightFrame,
		DarkFrame,
		BiasFrame,
		FlatFrame
	};

	FrameType frameType() const;
	void setFrameType(FrameType type);

	const EImage& imageData() const;

	int width() const;
	int height() const;
	int numPixels() const;

	void setTransform(const Eigen::Matrix3f& transform);

	inline Eigen::Array4f getTransformed(int i, int j) const
	{
		// FIXME: We're assuming that 1*1*.....*1 = 1.
		// Is this true, or do we need to worry about float error?
		m_coordInBuf[0] = i;
		m_coordInBuf[1] = j;
		m_coordOutBuf = m_transform * m_coordInBuf;
		i = static_cast<int>(m_coordOutBuf[0]);
		j = static_cast<int>(m_coordOutBuf[1]);
		return m_image->get(i,j);
	}
private:
	// Disallow copying
	SourceFrame(const SourceFrame& s);
	SourceFrame& operator=(const SourceFrame& s);
	FrameType m_frameType;
	QString m_filename;
	EImage* m_image;
	Eigen::Matrix3f m_transform = Eigen::Matrix3f::Identity();
	mutable Eigen::Vector3f m_coordInBuf  = Eigen::Vector3f(0,0,1);
	mutable Eigen::Vector3f m_coordOutBuf = Eigen::Vector3f(0,0,1);
};

#endif // SOURCEFRAME_H
