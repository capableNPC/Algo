#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <QVariant>
#include "node.h"
#include "datapackage.h"
#include "module/CanvaModule/canva.h"
#include "rectangle.h"


class ShapeFactory
{
public:
    ShapeFactory(Canva *parent = 0);
    Node* getShape(data::ShapeType type,QString data);

private:
    Node* rectangle(QString data);
    Canva *canva = nullptr;
};

#endif // SHAPEFACTORY_H
