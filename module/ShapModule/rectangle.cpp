#include "rectangle.h"

Rectangle::Rectangle(Canva *canva, qreal w, qreal h):Node(canva,w,h)
{
    setFlag(ItemIsSelectable);
    //setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    //defaultWidth = 50;
    //defaultHeight = 30;
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (option->state & QStyle::State_Sunken)
        painter->setBrush(Qt::yellow);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawRect(0, 0, defaultWidth, defaultHeight);
// Text

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);


    QFontMetrics metrics(font);
    QString text = this->data(0).toString();
    //metrics.width(text);//获取显示文本的宽度metrics.horizontalAdvance(text)
    //metrics.height();//获取显示文本的高度

    QRectF textRect((defaultWidth - metrics.horizontalAdvance(text))/2, (defaultHeight - metrics.height()),
                    defaultWidth, defaultHeight);


    painter->setFont(font);
    //painter->setPen(Qt::lightGray);
    //painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, text);
}
