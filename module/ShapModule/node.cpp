#include "node.h"

Node::Node(Canva *canva, qreal w, qreal h)
    : graph(canva),defaultWidth(w),defaultHeight(h)
{
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QVector<Edge *> Node::edges() const
{
    return edgeList;
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-adjust,-adjust, defaultWidth + adjust, defaultHeight + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(0, 0, defaultWidth, defaultHeight);
    return path;
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        for (Edge *edge : qAsConst(edgeList))
            edge->adjust();
        break;
    default:
        break;
    };
    //if(!graph->itemCollides(this))
    oldPos = scenePos();
    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{   if(this->flags().testFlag(ItemIsMovable))
    {
        if(graph->itemCollides(this))
            setPos(oldPos);
    }
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

