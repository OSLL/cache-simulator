#include "TimeUtil.h"
#include <sys/time.h>

qulonglong getCurrentTime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec*1000000 + tv.tv_usec;
}
