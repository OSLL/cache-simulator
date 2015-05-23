#ifndef STORAGEPROCESSORMODEL_H
#define STORAGEPROCESSORMODEL_H

#include "IStorageElement.h"
#include "Cache.h"



class LimitedThroughput;
class RedirectDecisionMaker;

class StorageProcessorModel : public IStorageElement
{
private:
    Cache * m_cache;
    LimitedThroughput* m_icThroughput;

    // Amount of waiting data blocks to be transfered among IC
    qulonglong m_icQueue;

    RedirectDecisionMaker * m_decisionMaker;

    void processDataExistingInCache(GlobalState &currentState);
    void processDataNotExistingInCache(GlobalState &currentState);
    void sendDataToApplication(GlobalState &currentState);
    void requestDataFromRaid(GlobalState &currentState);
    void requestDataFromOtherStorageProcessor(GlobalState &currentState);
    void sendDataToOtherStorageProcessor(GlobalState &currentState);

    bool makeRedirectDecision();
public:
    StorageProcessorModel();


    virtual QString getElementName() const ;
    virtual void calculateNextState(GlobalState& currentState);

    bool doesExistInCache(GlobalState &currentState);

    ~StorageProcessorModel();
    void setCache(Cache *cache);

    qulonglong getIcQueue() const;
    void setIcQueueToZero();
    void incrementIcQueue();
    static void printIcQueueStatistics();
};

#endif // STORAGEPROCESSORMODEL_H
