#include <QGuiApplication>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>

#include "../header/bleclient.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);     // Enable high dpi in order to scale with all device types
    QGuiApplication app(argc, argv);

    bleClient ble_client;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("c_ble_client", &ble_client);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
