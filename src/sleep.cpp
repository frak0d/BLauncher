#pragma once

#include <QtCore/QString>
#include <QtCore/QThread>

void sleep_for(float value, const QString& unit)
{
    unsigned long duration = 0;
    
    if (unit == "s")  duration = value * 1e6;
    else
    if (unit == "ms") duration = value * 1e3;
    else
    if (unit == "us") duration = value * 1e1;
    
    QThread::usleep(duration);
}
