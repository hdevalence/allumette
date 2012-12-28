#ifndef ALLUMETTESTACKER_H
#define ALLUMETTESTACKER_H

#include <QObject>

class AllumetteStacker : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief AllumetteStacker does the work of image stacking.
     * @param params A JSON object containing the stacking parameters.
     * @param parent The parent QObject
     */
    explicit AllumetteStacker(QJsonObject params, QObject *parent = 0);

    void stack();
    
signals:
    
public slots:
    
private:
    QJsonObject m_params;
};

#endif // ALLUMETTESTACKER_H
