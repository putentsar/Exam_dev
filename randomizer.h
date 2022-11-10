#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <QObject>

class Randomizer : public QObject
{
    Q_OBJECT
public:
    explicit Randomizer(QObject *parent = nullptr);

public slots:
 QString randomCode();

signals:

};

#endif // RANDOMIZER_H
