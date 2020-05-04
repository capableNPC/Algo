#ifndef ALGOEXPLAIN_H
#define ALGOEXPLAIN_H

#include <QString>
#include <QMetaEnum>
#include <QFile>
#include <QXmlStreamReader>
#include <QToolBox>
#include <QTextBrowser>
#include "datapackage.h"

using namespace data;

class AlgoExplain : public QObject
{
public:
    explicit AlgoExplain(QToolBox* wgt);
    void init(AlgoTypes type);

private:
    QString basePath = "./data/algoDetails/";
    QString* explain;
    QString* code;
    QString* complexity;
    QToolBox* explainBox;

    void parsingXML(QXmlStreamReader &reader);

};

#endif // ALGOEXPLAIN_H
