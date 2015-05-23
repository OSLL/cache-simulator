#ifndef DATATYPE_H
#define DATATYPE_H

#include <QString>

enum DataType{
    REQUEST, RESPONSE
};

QString dataTypeToString(DataType dt);

#endif // DATATYPE_H
