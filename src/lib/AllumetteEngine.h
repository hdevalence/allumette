#ifndef ALLUMETTEENGINE_H
#define ALLUMETTEENGINE_H

#include <QtCore/QObject>
#include <QtCore/QJsonArray>

class AllumetteEngine : public QObject
{
	Q_OBJECT
public:

	/**
	 * @brief AllumetteEngine does the work of image stacking.
	 * @param params A JSON array containing the stacking parameters.
	 * @param parent The parent QObject
	 */
	explicit AllumetteEngine(const QJsonArray& params, QObject *parent = 0);

	void stack();
	
signals:
	
public slots:
	
private:
	QJsonArray m_params;
};

#endif // ALLUMETTEENGINE_H
