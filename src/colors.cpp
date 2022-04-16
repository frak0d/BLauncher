#pragma once

#include <QtCore/QString>

QString operator ""_bld (const char* str, size_t)
{
    return "<b>" + QString(str) + "</b>";
}

QString operator ""_red (const char* str, size_t)
{
    return "<font color=red>" + QString(str) + "</font>";
}

QString operator ""_bldred (const char* str, size_t)
{
    return "<font color=red><b>" + QString(str) + "</b></font>";
}

QString operator ""_grn (const char* str, size_t)
{
    return "<font color=green>" + QString(str) + "</font>";
}

QString operator ""_bldgrn (const char* str, size_t)
{
    return "<font color=green><b>" + QString(str) + "</b></font>";
}

QString operator ""_cyn (const char* str, size_t)
{
    return "<font color=cyan>" + QString(str) + "</font>";
}

QString operator ""_bldcyn (const char* str, size_t)
{
    return "<font color=cyan><b>" + QString(str) + "</b></font>";
}
