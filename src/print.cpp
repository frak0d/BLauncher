#pragma once

#include <iostream>
#include <QtCore/QString>

std::ostream& operator << (std::ostream& out, const QString& str)
{
    return out << str.toStdString();
}

void print(const auto& ... args)
{
    (std::cout << ... << args) << std::flush;
}
void println(const auto& ... args)
{
    (std::cout << ... << args) << std::endl;
}
