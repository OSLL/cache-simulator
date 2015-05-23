#include "TraceFileEntry.h"
#include "defines.h"


#include <tgmath.h>
#include <QStringList>
#include <QDebug>

#define ADDRESS_KEY "LLBA"
#define LENGTH_KEY "LEN"
#define CDB_KEY "CDB"



TraceFileEntry::TraceFileEntry()
{
}

TraceFileEntry::TraceFileEntry(const QMap<QString, QVariant> &map): m_map(map)
{
}

TraceFileEntry::TraceFileEntry(const QString &string)
{
    QStringList keyValuePairs = string.split(" ", QString::SkipEmptyParts);

    foreach (QString s, keyValuePairs){


        QStringList list = s.split("=", QString::SkipEmptyParts);
        if (list.size() != 2) continue;

        QString key = list[0];
        QString value = list[1];

        m_map.insert(key, QVariant(value));
    }
}

QVariant TraceFileEntry::getElement(const QString &element) const
{
    return m_map.value(element);
}

qulonglong TraceFileEntry::getAddress() const
{
    qulonglong address = m_map.value(ADDRESS_KEY).toULongLong();
    return address;
}

qulonglong TraceFileEntry::getOffset() const
{
    qulonglong length = m_map.value(LENGTH_KEY).toULongLong();

    qulonglong offset = (length) / ((qulonglong)STRIPE_SIZE_KB);

    return offset;

}

int TraceFileEntry::getOpcode() const
{
    bool ok;
    QString cdbStr = m_map.value(CDB_KEY).toString();
    int result = cdbStr.mid(8,2).toInt(&ok, 16);
    if (!ok){
        qDebug() << "Problems during retriving opcode for CDB = " + cdbStr;
        return 0;
    }
    qDebug() << "CDB = " + cdbStr + ", opcode = " + QString::number(result,16);
    return result;
}

bool TraceFileEntry::isReadRequest() const
{
    int opcode = getOpcode();
    int readOpcodes[] = {0x08, 0x25, 0x3e, 0x52, 0x88, 0x9e, 0x11, 0xa8};

    int length = sizeof(readOpcodes)/sizeof(int);

    for (int i=0; i< length; i++){
        if (opcode == readOpcodes[i])
            return true;
    }

    return false;
}
