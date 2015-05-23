#include "RandomReadTraceGeneratorSelector.h"
#include "NoneLocalityGenerator.h"
#include "SpacialLocalityGenerator.h"
#include "TimeLocalityGenerator.h"
#include "SettingsReader.h"
#include "defines.h"
#include <QDebug>

IRandomReadTraceAddressGenerator* RandomReadTraceGeneratorSelector::getGenerator(){
    QString localityType = SettingsReader::getValue(RANDOM_LOCALITY_TYPE,
                                                    RANDOM_LOCALITY_NONE).toString();

    IRandomReadTraceAddressGenerator* result = NULL;

    qulonglong readSize = SettingsReader::getValue(READ_BLOCK_SIZE).toULongLong();
    qulonglong raidSize = SettingsReader::getValue(RAID_SIZE).toULongLong() - readSize;

    qDebug() << "Locality type" << localityType;

    // Create and setup objects for the given type
    if (localityType == RANDOM_LOCALITY_NONE){
        result = new NoneLocalityGenerator(raidSize);
    }else if (localityType == RANDOM_LOCALITY_SPACIAL){
        result = new SpacialLocalityGenerator(raidSize);
        qulonglong leftAddress = SettingsReader::getValue(SPACIAL_LOCALITY_LEFT_ADDRESS, 0).toULongLong();
        qulonglong rightAddress =
                SettingsReader::getValue(SPACIAL_LOCALITY_RIGHT_ADDRESS, 0).toULongLong();
        int probability =
                SettingsReader::getValue(SPACIAL_LOCALITY_PROBABILITY, 0).toInt();

        ((SpacialLocalityGenerator*)result)->setParameters(leftAddress, rightAddress, probability);
    }else if (localityType == RANDOM_LOCALITY_TIME){
        result = new TimeLocalityGenerator(raidSize);
        qulonglong memorizedQueueLength =
                SettingsReader::getValue(TIME_LOCALITY_MEMORIZED_QUEUE_LENGTH, 0).toULongLong();
        int probability =
                SettingsReader::getValue(TIME_LOCALITY_PROBABILITY, 0).toInt();

        ((TimeLocalityGenerator*)result)->setParameters(memorizedQueueLength, probability);
    }

    return result;
}
