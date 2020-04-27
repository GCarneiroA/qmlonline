#include <QApplication>
#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>
#include "util.h"

#include <QtPlugin>

#include "3rdparty/kirigami/src/kirigamiplugin.h"

//Q_IMPORT_PLUGIN(KirigamiPlugin);

int main(int argc, char *argv[])
{
    qmlRegisterSingletonType<Util>("Util", 1, 0, "Util", Util::qmlSingletonRegister);

    QGuiApplication app(argc, argv);
    KirigamiPlugin::getInstance().registerTypes();
    QQmlEngine engine;
    QQmlComponent component(&engine);
    QObject::connect(Util::self(), &Util::codeChanged, [&component]() {
        qDebug() << "LOAD DATA!";
        component.setData(Util::self()->code().toLatin1(), {});
        component.create();
        qDebug() << "LOADED DATA!";
    });

    while(true) {
        app.exec();
        qDebug() << "spin!";
    }
    return 0;
}
