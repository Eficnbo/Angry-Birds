#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QtMath>
#include "pig_graphics_item.h"
#include "graphics_scene.h"

PigGraphicsItem::PigGraphicsItem(const std::string &color,float x, float y) {

    if(color == "green") {
        color_ = QColor(0,200,0);
    }

    this->SetPosition(x,y);
};

QRectF PigGraphicsItem::boundingRect() const {
    return QRectF(-20, -20, 40, 40);
}

void PigGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setPen(Qt::NoPen);
    painter->setBrush(color_);
    painter->drawEllipse(QPointF(0, 0), 20, 20);

    //draw eyes
    painter->setBrush(QColor(255, 255, 255));
    painter->drawEllipse(QPointF(-9, -4), 5, 5);
    painter->drawEllipse(QPointF(9, -4), 5, 5);
    painter->setBrush(QColor(0, 0, 0));
    painter->drawEllipse(QPointF(-9, -4), 2, 2);
    painter->drawEllipse(QPointF(9, -4), 2, 2);

    //draw nose
    painter->setBrush(QColor(50, 255, 50));
    painter->drawEllipse(QPointF(0, 4), 6, 4);
    painter->setBrush(QColor(25, 50, 0));
    painter->drawEllipse(QPointF(-2, 4), 1, 2);
    painter->drawEllipse(QPointF(2, 4), 1, 2);
}

void PigGraphicsItem::SetPosition(float x,float y) {
    x = GraphicsScene::ToSceneX(x);
    y = GraphicsScene::ToSceneY(y);
    this->setPos(x,y);
}

void PigGraphicsItem::SetRotation(float radians) {
    this->setRotation(-qRadiansToDegrees(radians));
}

