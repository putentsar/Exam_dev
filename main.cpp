#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "randomizer.h"
#include <QQmlContext>
#include <QDebug>
#include <QRegularExpression>
#include <QUuid>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/191_331_Revyakin/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    Randomizer rnd;
    QQmlContext *context1 = engine.rootContext();
    context1->setContextProperty("Randomizer", &rnd);

    engine.load(url);
    return app.exec();
}
