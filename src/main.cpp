#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "chartdatamodel.h"
#include "chartrenderer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ChartDataModel>("BoatPerformanceChart", 1, 0, "ChartDataModel");
    qmlRegisterType<ChartRenderer>("BoatPerformanceChart", 1, 0, "ChartRenderer");

    QQmlApplicationEngine engine;
    
    // Create and initialize the data model
    ChartDataModel dataModel;
    dataModel.generateSampleData();
    
    engine.rootContext()->setContextProperty("chartDataModel", &dataModel);
    
    const QUrl url(QStringLiteral("qrc:/BoatPerformanceChart/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    
    engine.load(url);

    return app.exec();
}
