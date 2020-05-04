#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include "edge.h"
#include "module/CanvaModule/canva.h"

class Canva;

class Node : public QGraphicsItem
{
public:
    Node(Canva* canva, qreal w, qreal h);
    void addEdge(Edge *edge);
    QVector<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QVector<Edge *> edgeList;
    QPointF oldPos;
    Canva *graph;
    bool initFlag = true;
protected:
    qreal defaultWidth = 50;
    qreal defaultHeight = 50;
};


#endif // NODE_H
