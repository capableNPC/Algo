#include "canva.h"
#include <QDebug>

Canva::Canva(QWidget *parent) : QGraphicsView(parent)
{
    Scene = new QGraphicsScene(this);
    Scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    oldSize = this->size();
    Scene->setSceneRect(0, 0, this->width(), this->height());
    setScene(Scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setStyleSheet("padding:0px;border:0px;background:green;");
    //setMinimumSize(400, 400);
    //repaint();
}

void Canva::setSize(QSize size)
{
    oldSize = size;
    this->resize(size);
}

void Canva::DataOfBrush(QVector<Node *>* vector)
{
    items = vector;
}
/*
void Canva::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QVector<Node *> nodes;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    for (Node *node : qAsConst(nodes))
        node->calculateForces();

    bool itemsMoved = false;
    for (Node *node : qAsConst(nodes)) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}
*/
#if QT_CONFIG(wheelevent)
void Canva::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2., -event->angleDelta().y() / 240.0));
}
#endif

void Canva::drawBackground(QPainter *painter, const QRectF &rect)
{
    //painter->setBrush(Qt::darkGray);
    //painter->drawRect(rect);
    //Q_UNUSED(rect);
/*
    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);
*/    /*
    // Fill
    QLinearGradient gradient(rect.topLeft(), rect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(rect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(rect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys"));
    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
*/
}

void Canva::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

bool Canva::itemCollides(Node* selectedNode)
{
    //qDebug() << "caaaaaaaaaaaaaaaalllllldddddddddd " << endl;
    /*
    QVector<Node *> nodes;
    const QList<QGraphicsItem *> items = scene()->items();
    foreach(QGraphicsItem *item , items)
    {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }
    */
    for(Node* node : *items)
    {
        if(selectedNode == node)
            continue;
        if(selectedNode->collidesWithItem(node))
            return true;
    }
    return false;
}

QGraphicsScene *Canva::getScene()
{
    return Scene;
}

void Canva::clearCanva()
{

    Scene->clear();
    items->clear();
    centerNode = nullptr;
    //this->viewport()->update();
}

void Canva::restore()
{
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void Canva::zoomIn()
{
    scaleView(qreal(1.2));
}

void Canva::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void Canva::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
        restore();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void Canva::resizeEvent(QResizeEvent *event)
{
    Scene->setSceneRect(0, 0, this->width(), this->height());
    //qreal widthRate = this->width()/(oldSize.width()*1.0);
    //qreal heightRate = this->height()/(oldSize.height()*1.0);
    qreal y = 10;
//qDebug() << "widthRate " << widthRate << "heightRate " << heightRate << endl;
    //qreal extraX,extraY;
    QVector<Node *> nodes;
    const QList<QGraphicsItem *> items = scene()->items();
    //extraY = (heightRate-1) * items.at(0)->y();
    //extraX = (widthRate-1) * items.at(0)->x();
    if(!items.isEmpty())
    {
        qreal itemWidth = items.at(0)->shape().boundingRect().width();
        qreal x = (this->width() - itemWidth)/2;
        foreach(QGraphicsItem *item , items)
        {
            if (Node *node = qgraphicsitem_cast<Node *>(item))
            {
                node->setPos(x, y);
                //node->setPos(node->x() + extraX, node->y() + extraY);
                node->update();
                y += 30;
            }
        }
    }
    this->repaint();
    oldSize = this->size();
    return;
    //return QGraphicsView::resizeEvent(event);
}
/*



void Canva::paintEvent(QPaintEvent *event)
{
    QString path = "./qss/cr.svg";
    QSvgRenderer* svgRender = new QSvgRenderer();
    svgRender->load(path);
    svgRender->animated();
    svgRender->framesPerSecond();
    QPainter p(this);
    svgRender->render(&p);
    event->accept();
}
*/
