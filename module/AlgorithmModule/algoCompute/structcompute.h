#ifndef STRUCTCOMPUTE_H
#define STRUCTCOMPUTE_H

//typedef void (StructCompute::*algo)();

#include "datapackage.h"
#include "abstractcompute.h"
#include <QObject>
#include <QThread>
#include <QMutex>

class StructCompute : public QThread//, public AbstractCompute
{
    Q_OBJECT
public:
    StructCompute(QObject *parent,Config* cfg,AlgoTypes algoType);
    void run();
    void stopImmediately();
public slots:
    void command(CommandType command);

private:
    Config* config = nullptr;
    void (StructCompute::*algo)();
    QMutex lock;
    bool keepRun = true;
    QVector<DataOfLinear> data;

private:
    void error();
    void array();
signals:
    void initCanva(QVector<DataOfLinear> data);
    void initCanva(QVector<DataOfTree> data);
    void updateCanva();
    void updateCanva(QVector<DataOfAnimation> animation);
    void updateCanva(QVector<DataOfLinear> data,QVector<DataOfAnimation> animation);
    void updateCanva(QVector<DataOfTree> data,QVector<DataOfAnimation> animation);
};

#endif // STRUCTCOMPUTE_H
