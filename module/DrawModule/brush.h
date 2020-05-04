#ifndef BRUSH_H
#define BRUSH_H

#include <QThread>
#include <QMutex>
#include <QPushButton>
#include <QGridLayout>
#include "module/CanvaModule/canva.h"
#include "module/ShapModule/shapefactory.h"
#include "datapackage.h"
#include "module/ShapModule/node.h"

using namespace data;

class Brush : public QThread
{
    Q_OBJECT
public:
    Brush(QObject *parent = 0,Canva *cnv = 0, Config* cfg = 0);
    void run() override;
    void stopImmediately();

private:
    Canva *canva = nullptr;
    Config* config = nullptr;
    QGraphicsScene* scene;
    ShapeFactory* shapeFactory;
    QVector<Node*>* items;
    QMutex lock;
    bool keepRun = true;

signals:
    void Brush2Canva(QVector<Node*>*);

public slots:
    void initCanva(QVector<DataOfLinear> data);
    void initCanva(QVector<DataOfTree> data);
    void updateCanva();
    void updateCanva(QVector<DataOfAnimation> animation);
    void updateCanva(QVector<DataOfLinear> data,QVector<DataOfAnimation> animation);
    void updateCanva(QVector<DataOfTree> data,QVector<DataOfAnimation> animation);
};

#endif // BRUSH_H
