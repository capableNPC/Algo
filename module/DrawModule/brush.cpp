#include "brush.h"
#include <QDebug>

Brush::Brush(QObject *parent,Canva *cnv, Config* cfg):QThread(parent),canva(cnv),config(cfg)
{
    shapeFactory = new ShapeFactory(cnv);
    scene = cnv->getScene();

    items = new QVector<Node*>;
}

void Brush::run()
{
    while (keepRun) {
        QMutexLocker locker(&lock);
        //wait command
    }
    qDebug() << "Brush exit " << endl;
}

void Brush::stopImmediately()
{
    QMutexLocker locker(&lock);
    keepRun = false;
    deleteLater();
}

void Brush::initCanva(QVector<DataOfLinear> data)
{
    qreal y = 10;
    if(!data.isEmpty())
    {
        foreach(DataOfLinear linearData , data)
        {
            Node* item = shapeFactory->getShape(linearData.type,linearData.value);
            items->append(item);
            scene->addItem(item);
            qreal itemWidth = item->shape().boundingRect().width();
            //qDebug() << "item->x()" << item->x() << "item->x()/2"  << item->x()/2 << endl;
            //qDebug() << "canva->width()" << canva->width() << "canva->width()/2" << canva->width()/2 << endl;
            qreal x = (canva->width() - itemWidth)/2;
            //qDebug() << "x" << x << endl;
            y += 30;
            item->setPos(x,y);
        }
    }
    else
    {
        QString value(tr("无数据"));
        for(int i = 0; i < 10; i++)
        {
            Node* item = shapeFactory->getShape(ShapeType::Rectangle,value);
            items->append(item);
            scene->addItem(item);
            qreal itemWidth = item->shape().boundingRect().width();
            //qDebug() << "item->x()" << item->x() << "item->x()/2"  << item->x()/2 << endl;
            //qDebug() << "canva->width()" << canva->width() << "canva->width()/2" << canva->width()/2 << endl;
            qreal x = (canva->width() - itemWidth)/2;
            //qDebug() << "x" << x << endl;
            y += 30;
            item->setPos(x,y);
        }
    }

    emit Brush2Canva(items);
    if(config->hasArrow)
    {
        for(int i = 0; i < (items->length() - 1); i++)
        {
            scene->addItem(new Edge(items->at(i), items->at(i+1)));
        }
    }
}

void Brush::initCanva(QVector<DataOfTree> data)
{

}

void Brush::updateCanva()
{

}

void Brush::updateCanva(QVector<DataOfAnimation> animation)
{

}

void Brush::updateCanva(QVector<DataOfLinear> data,QVector<DataOfAnimation> animation)
{

}

void Brush::updateCanva(QVector<DataOfTree> data,QVector<DataOfAnimation> animation)
{

}
