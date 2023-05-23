#ifndef NOTEPRINTER_H
#define NOTEPRINTER_H
#include <QWidget>

#define LOG_PRINTER LogPrinter::instance()

class LogPrinter
{
public:
    enum LogLevel {
        LogNormal= 0,
        LogWarn,
        LogError
    };
    static LogPrinter* instance();
    static void deleteInstance();
    
    void packLog(LogLevel level, const QString &msg, QString *log);

private:
    LogPrinter();
    LogPrinter(const LogPrinter&)=delete;
    LogPrinter& operator = (const LogPrinter&)=delete;
    LogPrinter(LogPrinter&&)=delete;
    LogPrinter& operator = (LogPrinter&&)=delete;

    static LogPrinter* uniqueInstance;
    LogLevel m_logLevel;
};

#endif // NOTEPRINTER_H
