#include "algoexplain.h"
#include <QtDebug>

AlgoExplain::AlgoExplain(QToolBox* wgt)
{
    this->explainBox = wgt;
}

void AlgoExplain::init(AlgoTypes type)
{
    explain = new QString("None");
    code = new QString("None");
    complexity = new QString("None");
    QMetaEnum t = QMetaEnum::fromType<AlgoTypes>();
    QString filePath = basePath + t.valueToKey((int)type) + ".xml";
    QFile file(filePath);
    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        parsingXML(reader);
        file.close();
    }
    explainBox->widget(0)->findChild<QTextBrowser*>("explainBrowser")->setHtml(*explain);
    explainBox->widget(1)->findChild<QTextBrowser*>("codeBrowser")->setHtml(*code);
    explainBox->widget(2)->findChild<QTextBrowser*>("complexityBrowser")->setHtml(*complexity);

}

void AlgoExplain::parsingXML(QXmlStreamReader &reader)
{
    QString* value = nullptr;
    while (!reader.atEnd()) {
        if (reader.readNextStartElement() == false)
            return;
        QString nodeName = reader.name().toString();
        QXmlStreamAttributes attributes = reader.attributes();
        if("explain" == nodeName)
        {
            value = explain;
            if("true" == attributes.value("empty").toString())
                continue;
        }
        else
        {
            if("code" == nodeName)
            {
                value = code;
                if("true" == attributes.value("empty").toString())
                    continue;
            }
            else
            {
                if("complexity" == nodeName)
                {
                    value = complexity;
                    if("true" == attributes.value("empty").toString())
                        continue;
                }
                else
                    continue;
            }
        }
        *value =  reader.readElementText();
    }
}
