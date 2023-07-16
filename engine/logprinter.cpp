#include "logprinter.h"

LogPrinter *LogPrinter::uniqueInstance = nullptr;
QString LogString[3] = {"[正常]", "[警告]", "[错误]"};

LogPrinter *LogPrinter::instance()
{
    if(!uniqueInstance) {
        uniqueInstance = new LogPrinter;
    }
    return uniqueInstance;
}

void LogPrinter::deleteInstance()
{
    if (uniqueInstance) {
        delete uniqueInstance;
    }
}

void LogPrinter::packLog(LogLevel level, const QString &msg, QString *log)
{
    QString time;
    *log = LogString[level] + "" + time + ":" + msg;
    
}

LogPrinter::LogPrinter()
{
    m_logLevel = LogNormal;
}
