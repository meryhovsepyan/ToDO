#include "include/filter_manager.h"
#include "include/taskmanager.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<TaskManager>("TaskManager", 1, 0, "TaskManager");
    qmlRegisterType<FilteredModel>("FilteredModel", 1, 0, "FilteredModel");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("MyToDo", "Main");


    return app.exec();
}
