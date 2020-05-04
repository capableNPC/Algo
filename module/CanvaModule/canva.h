#ifndef CANVA_H
#define CANVA_H

//#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QSize>
//#include <QtSvg/QSvgRenderer>
#include <QGraphicsView>
#include <math.h>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include "module/ShapModule/node.h"
#include "module/ShapModule/edge.h"

class Canva : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Canva(QWidget *parent = nullptr);
    void setSize(QSize size);
    QGraphicsScene* getScene();
    void clearCanva();
    bool itemCollides(Node* selectedNode);

private:
    QVector<Node *>*  items = nullptr;
    QGraphicsScene* Scene = nullptr;
    Node* centerNode = nullptr;//QFrame 有一个Shape枚举
    QSize oldSize;
protected:
    void resizeEvent(QResizeEvent *event) override;
    //void paintEvent(QPaintEvent *event);

public slots:
    void DataOfBrush(QVector<Node *>* vector);
    void restore();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    //void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

signals:

};

#endif // CANVA_H
