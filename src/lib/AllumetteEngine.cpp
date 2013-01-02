#include "AllumetteEngine.h"

AllumetteEngine::AllumetteEngine(const QJsonArray& params, QObject *parent)
	: QObject(parent)
{
	setParams(params);
}

void AllumetteEngine::setParams(const QJsonArray& params)
{
	m_params = params;
	updateFrames();
	updateMethod();
}

EImage AllumetteEngine::stack()
{
	// Create master dark, bias, flat frames

	// Subtract master offset

	// Multiply by master flat

	// Align images

	// Stack
	Stacker stacker(m_lightFrames);
	// TODO set method properly
	stacker.setMethod(Stacker::MeanStacking);

	return stacker.stack();
}

void AllumetteEngine::updateFrames()
{
	QJsonArray lightFrames = m_params.value("light_frames").toArray();
	m_lightFrames = addFrames(lightFrames,SourceFrame::LightFrame);
}

SourceFrameList AllumetteEngine::addFrames(const QJsonArray& a,
										   SourceFrame::FrameType t)
{
	SourceFrameList s;
	for(int i = 0; i < a.size(); ++i) {
		// TODO provide image loader
		SourceFrame *f = new SourceFrame(a[i]);
		f->setFrameType(t);
		s.push_back(f);
	}
	return s;
}

