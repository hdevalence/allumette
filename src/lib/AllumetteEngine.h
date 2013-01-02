#ifndef ALLUMETTEENGINE_H
#define ALLUMETTEENGINE_H

#include <QtCore/QObject>
#include <QtCore/QJsonObject>

#include "SourceFrame.h"

class AllumetteEngine : public QObject
{
	Q_OBJECT
public:

	/**
	 * @brief AllumetteEngine does the work of image stacking.
	 * @param params A JSON array containing the stacking parameters.
	 * @param parent The parent QObject
	 */
	explicit AllumetteEngine(const QJsonObject& params, QObject *parent = 0);

	EImage stack();
	
	void setParams(const QJsonObject& params);
signals:
	
public slots:
	
private:
	void updateFrames();
	SourceFrameList addFrames(const QJsonArray& a,
	                          SourceFrame::FrameType t);
	SourceFrameList m_lightFrames;
	QJsonObject m_params;
};

#endif // ALLUMETTEENGINE_H
