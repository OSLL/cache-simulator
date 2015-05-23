#include "DataType.h"

QString dataTypeToString(DataType dt){
    switch(dt){
    case REQUEST:
        return "REQUEST";
    case RESPONSE:
        return "RESPONSE";
    default:
        return "unknown state";
    }

}
