#pragma once

#include <QtGui/QColor>
#include <QtCore/QString>

QColor QString_to_Qcolor(const QString& str)
{
    uint R,G,B;
    std::sscanf(str.toStdString().c_str(), "(%u,%u,%u)", &R, &G, &B);
    return QColor(R,G,B);
}
