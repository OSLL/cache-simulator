#include "Event.h"
#include "SettingsReader.h"

#include <QDebug>

void Event::init(const QString &parameter, const qulonglong applyStep)
{
    m_parameter = parameter;
    m_applyStep = applyStep;
}

Event::Event()
{
}

Event::Event(const QString &parameter, const qulonglong applyStep, const QVariant &newValue):
    m_type(INSTANT_EVENT), m_newValue(newValue)
{
    init(parameter, applyStep);
}

Event::Event(const QString &parameter, const qulonglong applyStep, const int valueDelta,
             const qulonglong stepsNumberToApply):
    m_type(GRADUAL_EVENT), m_valueDelta(valueDelta), m_stepsNumberToApply(stepsNumberToApply)
{
        init(parameter, applyStep);
}

bool Event::shouldBeApplied(const qulonglong step) const
{
    qDebug() << "shouldBeApplied "<< step << toString();
    bool result = false;
    switch (m_type){
    case INSTANT_EVENT:
        result = (m_applyStep == step);
        break;
    case GRADUAL_EVENT:
        result = (m_applyStep <= step) && (step <= m_applyStep+m_stepsNumberToApply);
        break;
    }

    return result;
}

QVariant Event::getValueForStep(const qulonglong step) const
{
    QVariant result = QVariant();
    if (shouldBeApplied(step)){
        switch (m_type){
        case INSTANT_EVENT:
            result = m_newValue;
            break;
        case GRADUAL_EVENT:
            qulonglong oldValue = SettingsReader::getValue(m_parameter).toULongLong();

            if (m_valueDelta < 0)
                result = QVariant(oldValue - (qulonglong)qAbs(m_valueDelta));
            else
                result = QVariant(oldValue + (qulonglong)qAbs(m_valueDelta));

            break;
        }
    }
    return result;
}

QString Event::getParameterName() const
{
    return m_parameter;
}

bool Event::isFinished(const qulonglong step) const
{
    bool result = false;
    switch (m_type){
    case INSTANT_EVENT:
        result = (step == m_applyStep);
        break;
    case GRADUAL_EVENT:
        result = (step == m_applyStep + m_stepsNumberToApply);
        break;
    }
    return result;
}

bool Event::operator <(const Event &other) const
{
    return m_applyStep < other.m_applyStep;
}

bool Event::operator ==(const Event &other) const
{
    bool result = (m_type == other.m_type);
    if (result == true){

        result = (m_applyStep == other.m_applyStep) && (m_parameter == other.m_parameter);

        if (result == true){
            switch (m_type){
            case INSTANT_EVENT:
                result = (m_newValue == other.m_newValue);
                break;
            case GRADUAL_EVENT:
                result = (m_stepsNumberToApply == other.m_stepsNumberToApply)
                        && (m_valueDelta == other.m_valueDelta);
                break;
            }
        }

    }
    return result;
}

QString Event::toString() const
{
    QString result =QString("this=%1 applyStep=%2 paramterName=%3").
            arg((qulonglong)this).arg(m_applyStep).arg(m_parameter);
    switch (m_type){
    case INSTANT_EVENT:
        result += QString(" newValue=%1").arg(m_newValue.toString());
        break;
    case GRADUAL_EVENT:
        result += QString(" valueDelta=%1 stepsNumberToApply=%2").
                arg(m_valueDelta).arg(m_stepsNumberToApply);
        break;
    }


    return result;
}
