#include "logger.h"

logger::logger()
{

}

///
///  Método -> logMessage
///  Parámetro -> type
///  Determina el tipo de mensaje que se va a escribir
///  Parametro -> message
///  Se especifica a fondo el mensaje, permite adicionar contenido al orginal
///

QString logger::logMessage(int type, QString message)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString messageLog;
    switch (type) {
    case LOG_INFO:
        messageLog = QString("[" + timestamp + "] [INFO]: " + message);
        break;
    case LOG_WARNING:
        messageLog = QString("[" + timestamp + "] [WARNING]: " + message);
        break;
    case LOG_ERROR:
        messageLog = QString("[" + timestamp + "] [ERROR]: " + message);
        break;
    case LOG_DEBUG:
        messageLog = QString("[" + timestamp + "] [DEBUG]: " + message);
        break;
    case LOG_TRACE:
        messageLog = QString("[" + timestamp + "] [TRACE]: " + message);
        break;
    default:
        messageLog = QString("[" + timestamp + "] [ERROR]: Something want wrong");
        break;
    }
    return messageLog;
}
