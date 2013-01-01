#ifndef STACKER_H
#define STACKER_H

#include "SourceImage.h"

/**
 * @brief The Stacker class is responsible for stacking
 * a list of cleaned and aligned light frames.
 */
class Stacker
{
public:
	enum Method {
		MeanStacking
	};

	Stacker(const SourceFrameList& frames);

	Method method() const;
	void setMethod(Method method);

	EImage Stacker::stack();
private:
	const SourceFrameList& m_frames;
	Method m_method = MeanStacking;
};

#endif // STACKER_H
