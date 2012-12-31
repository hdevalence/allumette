#ifndef SOURCEFRAME_H
#define SOURCEFRAME_H

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

	void setTransform(const Eigen::Matrix3f& transform);

	/**
	 * @brief Get pixel under transformation.
	 * @param i the x coordinate
	 * @param j the y coordinate
	 * @return the pixel value
	 */
	inline const Eigen::Array4f& getTransformed(int i, int j) const;

	inline const Eigen::Array4f& get(int i, int j) const;
private:
	FrameType m_type;
	QString m_filename;
	EImage* m_image;
	Eigen::Matrix3f m_transform = Eigen::Matrix3f::Identity();
	mutable Eigen::Vector3f m_coordInBuf  = Eigen::Vector3f(0,0,1);
	mutable Eigen::Vector3f m_coordOutBuf = Eigen::Vector3f(0,0,1);
	static const Eigen::Array4f OUT_OF_BOUNDS_PX = Eigen::Array4f::Zero();
};

#endif // SOURCEFRAME_H
