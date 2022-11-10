#include "randomizer.h"
#include <QQmlContext>
#include <QDebug>
#include <QRegularExpression>
#include <QUuid>
Randomizer::Randomizer(QObject *parent)
    : QObject{parent}
{




}

QString Randomizer::randomCode(){
           QString str = QUuid::createUuid().toString();
            str.remove(QRegularExpression("{|}|-"));// if you want only hex numbers
            str.resize(4);
            qDebug()<<str;
            return str;
}
