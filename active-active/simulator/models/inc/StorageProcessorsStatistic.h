#ifndef STORAGEPROCESSORSSTATISTIC_H
#define STORAGEPROCESSORSSTATISTIC_H

#include <QList>

class IStorageElement;

// This class stores information about storage processors curent queue element number.
class StorageProcessorsStatistic
{
    QList<int> m_statistic;
    static StorageProcessorsStatistic * m_instance;

    StorageProcessorsStatistic();

public:
    void updateStatistic(int index, int statistic);

    static StorageProcessorsStatistic * getInstance();
    int getMinimalQueueSP() const;


};

#endif // STORAGEPROCESSORSSTATISTIC_H
