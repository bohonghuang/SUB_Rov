#ifndef OILVALVE_H
#define OILVALVE_H

#include <QObject>

class Oilvalve{
    public:
        int index;
        quint16 *oils;

    public:
        Oilvalve();
        bool ResetOils(quint16*);
        quint16 GetOilAddLevelAndOfIndex();
        quint16 GetOilSubOilAndOfIndex();
        quint16 GetOil();
};
#endif // OILVALVE_H
