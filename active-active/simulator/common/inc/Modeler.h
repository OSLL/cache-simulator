#ifndef MODELER_H
#define MODELER_H

#include "StorageModel.h"
#include "ReadRequest.h"

class Modeler
{
    static qulonglong m_step;
public:
    Modeler();

    static qulonglong getStep();
    static void increaseStep();

    void doModeling();
    ~Modeler();

};

#endif // MODELER_H
