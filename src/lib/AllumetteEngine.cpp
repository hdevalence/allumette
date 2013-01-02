#include "AllumetteEngine.h"

#include <QtCore/QJsonArray>
#include <QtCore/QDebug>

#include "Stacker.h"

AllumetteEngine::AllumetteEngine(const QJsonObject& params, QObject *parent)
	: QObject(parent)
{
	setParams(params);
}

void AllumetteEngine::setParams(const QJsonObject& params)
{
	m_params = params;
	updateFrames();
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
	for(int i = 0; i < m_lightFrames.size(); ++i) {
		delete m_lightFrames[i];
	}
	qDebug() << m_params;
	QJsonArray lightFrames = m_params.value("light_frames").toArray();
	qDebug() << lightFrames;
	m_lightFrames = addFrames(lightFrames,SourceFrame::LightFrame);
}

SourceFrameList AllumetteEngine::addFrames(const QJsonArray& a,
                                           SourceFrame::FrameType t)
{
	SourceFrameList s;
	for(int i = 0; i < a.size(); ++i) {
		// TODO provide image loader
		SourceFrame *f = new SourceFrame(a[i].toString());
		f->setFrameType(t);
		s.push_back(f);
	}
	return s;
}

