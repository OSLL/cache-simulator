#ifndef RAIDMODEL_H
#define RAIDMODEL_H

#include "IStorageElement.h"

#include <QMap>

class LimitedThroughput;
class StorageProcessorModel;

class RaidModel : public IStorageElement
{
    QMap<StorageProcessorModel*,LimitedThroughput*> m_spDataChannels;
public:
    RaidModel();

    virtual QString getElementName() const;
    virtual void calculateNextState(GlobalState& currentState) ;

    qulonglong getRaidQueueSize(StorageProcessorModel *sp);
};

#endif // RAIDMODEL_H
