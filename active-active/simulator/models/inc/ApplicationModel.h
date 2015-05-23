#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H
#include "IStorageElement.h"
#include "GlobalState.h"

#include <QMultiMap>

class IReadTrace;
class ReadRequest;

class ApplicationModel : public IStorageElement
{

    IReadTrace * m_readTrace;
public:
    ApplicationModel();


    virtual QString getElementName() const;
    virtual void calculateNextState(GlobalState& currentState);
    void createNewReadRequest(qulonglong step, QMultiMap<ReadRequest *, GlobalState> &states);

    bool isModelingFinished(qulonglong step) const;

    ~ApplicationModel();
};

#endif // APPLICATIONMODEL_H
