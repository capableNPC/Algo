#include "structcompute.h"
#include <QDebug>

void StructCompute::array()
{
    lock.lock();
    qDebug() << "arrayCompute" << endl;
    int i = 0;
    if(!config->data.isEmpty())
    {
        foreach(QString str , config->data)
        {
            DataOfLinear item;
            item.value = str;
            item.id = i++;
            item.type = ShapeType::Rectangle;
            item.ImmediatePrecursor = i-1;
            item.ImmediateSuccessors = i+1;
            data.append(item);
        }
        data.end()->ImmediateSuccessors = -2;
    }
    config->hasArrow = false;
    qDebug() << "emit initCanva(data);" << endl;
    emit initCanva(data);
    lock.unlock();
}

StructCompute::StructCompute(QObject *parent,Config *cfg, AlgoTypes algoType):QThread(parent)
{
    this->config = cfg;
    qDebug() << algoType << endl;
    switch (algoType) {
    case AlgoType::Array:
        algo = &StructCompute::array;
        break;
    default:
        algo = &StructCompute::error;
        break;
    }
}

void StructCompute::run()
{
    (this->*algo)();
    while (keepRun) {
        QMutexLocker locker(&lock);
        //wait command
    }
}

void StructCompute::command(CommandType command)
{
    QMutexLocker locker(&lock);
    qDebug() << command.Nop << endl;
}

void StructCompute::stopImmediately()
{
    QMutexLocker locker(&lock);
    keepRun = false;
    deleteLater();
}

void StructCompute::error()
{

}




