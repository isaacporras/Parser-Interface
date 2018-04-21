#ifndef LOGGER_H
#define LOGGER_H
#include <QString>
#include <QDebug>
#include <QDateTime>

#define LOG_INFO 0
#define LOG_WARNING 1
#define LOG_ERROR 2
#define LOG_DEBUG 3
#define LOG_TRACE 4



///
///  Clase -> logger
///  Es la que se encarga del los mensajes tipo log que se imprimen en el applicaction log
///
class logger
{
public:
    logger();
    QString logMessage(int type, QString message);
};

#endif // LOGGER_H
