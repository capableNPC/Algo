#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "node.h"

class Rectangle : public Node
{
public:
    Rectangle(Canva* canva, qreal w, qreal h);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:

};

#endif // RECTANGLE_H
