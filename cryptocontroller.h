#ifndef CRYPTOCONTROLLER_H
#define CRYPTOCONTROLLER_H

#include <QObject>
#include <QObject>
#include <QString>

class CryptoController : public QObject
{
    Q_OBJECT
public:
    explicit CryptoController(QObject *parent = nullptr);
    ~CryptoController() {};

public slots:
    bool check_password(QString password);
    void encrypt_login_or_password(QString password);

private:
    unsigned char * iv = (unsigned char *)("77411230141456889873614547987324");

signals:

};

#endif // CRYPTOCONTROLLER_H
