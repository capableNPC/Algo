#ifndef ABSTRACTCOMPUTE_H
#define ABSTRACTCOMPUTE_H

#include <QObject>
#include "datapackage.h"

using namespace data;

class AbstractCompute : public QObject
{
    Q_OBJECT
public:
    AbstractCompute();

public:

public slots:
    //void command(CommandType command);

};

#endif // ABSTRACTCOMPUTE_H
