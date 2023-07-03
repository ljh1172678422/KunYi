#ifndef SERVICEEXCEPTION_H
#define SERVICEEXCEPTION_H

#include <exception>
#include <QString>

/**
 * @brief The ServiceException class    异常处理工具类
 */
class ServiceException : public std::exception
{
public:
    ServiceException(const QString &msg):message(msg){};
    ~ServiceException() throw() {};

    virtual const char* what() const throw () {
        return "ServiceException";
    }

    QString getMessage() const {return message;};

private:
    QString message;
};

#endif // SERVICEEXCEPTION_H
