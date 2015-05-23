#ifndef ISTORAGEELEMENT_H
#define ISTORAGEELEMENT_H

#include <GlobalState.h>
#include "StorageModel.h"

class IStorageElement{

public:

    virtual QString getElementName() const =0;
    virtual void calculateNextState(GlobalState& currentState) =0;
};

#endif // ISTORAGEELEMENT_H
