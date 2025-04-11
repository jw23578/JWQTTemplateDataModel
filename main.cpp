#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "exampleImplementations/stringandintobject.h"
#include "jwqttemplatemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    JWQTTemplateModel<StringAndIntObject> StringAndIntObjectModel(engine, "StringAndIntObjectModel", "sai");
    StringAndIntObjectModel.append(new StringAndIntObject("Jens", 13));
    StringAndIntObjectModel.append(new StringAndIntObject("Daniel", 14));
    StringAndIntObjectModel.append(new StringAndIntObject("Kay", 15));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("JWQTTemplateDataModel", "Main");

    return app.exec();
}
