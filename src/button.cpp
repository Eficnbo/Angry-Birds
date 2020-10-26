#include <QFont>
#include "button.h"

Button::Button() : QGraphicsTextItem()
{
    color_ = QColor(255, 130, 0);
    QFont font;
    font.setPixelSize(15);
    this->setFont(font);
}

void Button::ResetColor() {
    color_ = QColor(255, 130, 0);
    update();
}

void Button::Darken() {
    color_ = QColor(200, 100, 0);
    update();
}

QRectF Button::boundingRect() const {
   return QGraphicsTextItem::boundingRect().adjusted(-2,-2,+2,+2);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(color_);
    painter->drawRect(Button::boundingRect());
    QGraphicsTextItem::paint(painter,option,widget);
}
