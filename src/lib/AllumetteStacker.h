#ifndef ALLUMETTESTACKER_H
#define ALLUMETTESTACKER_H

#include <QtCore/QObject>
#include <QtCore/QJsonArray>

class AllumetteStacker : public QObject
{
	Q_OBJECT
public:

	/**
	 * @brief AllumetteStacker does the work of image stacking.
	 * @param params A JSON array containing the stacking parameters.
	 * @param parent The parent QObject
	 */
	explicit AllumetteStacker(const QJsonArray& params, QObject *parent = 0);

	void stack();
	
signals:
	
public slots:
	
private:
	QJsonArray m_params;
};

#endif // ALLUMETTESTACKER_H
