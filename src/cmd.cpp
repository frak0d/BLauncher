#pragma once

#include <QtCore/QString>
#include <QtCore/QProcess>

bool cmd(const QString& cmd)
{
    auto args = QProcess::splitCommand(cmd);
    
    QProcess sp;
    sp.setProgram(args[0]);
    args.erase(args.begin());
    sp.setArguments(args);
    sp.start();
    
    if (sp.waitForFinished(10000))
        if (sp.exitStatus() == QProcess::NormalExit)
            return true;
    
    return false;
}

QString cmd2(const QString& cmd)
{
    auto args = QProcess::splitCommand(cmd);
    
    QProcess sp;
    sp.setProgram(args[0]);
    args.erase(args.begin());
    sp.setArguments(args);
    sp.start();
    
    if (sp.waitForFinished(10000))
        return sp.readAll();
    else
        throw sp.errorString();
}
