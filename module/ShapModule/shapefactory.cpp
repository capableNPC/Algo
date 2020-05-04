#include "shapefactory.h"

ShapeFactory::ShapeFactory(Canva *parent): canva(parent)
{
}

Node *ShapeFactory::getShape(data::ShapeType type,QString data)
{
    switch (type) {
    case data::ShapeType::Rectangle:
        return rectangle(data);
    default:
        return rectangle(data);
    }
}

Node *ShapeFactory::rectangle(QString data)
{
    Rectangle* shape = new Rectangle(canva,200,30);//父类为 canva？？？
    //QVariant value = data;
    shape->setData(0,data);
    /*shape->setStyleSheet("QPushButton{font-size: 13px;"
                         "line-height: 18px;"
                         "padding: 3px 18px;"
                         "font-weight: bold;"
                         "border-radius: 3px;"
                         "margin: 0 8px 0 3px;"
                         "border: 1px solid #3383da;"
                         "color: #ffffff;"
                         "background-color: #3383da;}");
                         */
    return shape;
}
