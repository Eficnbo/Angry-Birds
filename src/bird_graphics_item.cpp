#include <QtMath>
#include "bird_graphics_item.h"
#include "graphics_scene.h"

BirdGraphicsItem::BirdGraphicsItem(const std::string& color, float x, float y) {
    if(color == "red")
        color_ = QColor(255, 0, 0);
    if(color == "yellow")
        color_ = QColor(255, 255, 0);
    this->SetPosition(x, y);
};

QRectF BirdGraphicsItem::boundingRect() const {
    return QRectF(-30, -30, 60, 60);
}

void BirdGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    //draw body
    painter->setPen(Qt::NoPen);
    painter->setBrush(color_);
    painter->drawEllipse(QPointF(0, 0), 12, 12);

    //draw eyes
    painter->setBrush(QColor(255, 255, 255));
    painter->drawEllipse(QPointF(-4, -2), 3, 3);
    painter->drawEllipse(QPointF(4, -2), 3, 3);
    painter->setBrush(QColor(0, 0, 0));
    painter->drawEllipse(QPointF(-4, -2), 1, 1);
    painter->drawEllipse(QPointF(4, -2), 1, 1);

    //draw eyebrows
    painter->setPen(QPen(Qt::black, 3));
    painter->drawLine(QLineF(-5, -6, -3, -4));
    painter->drawLine(QLineF(5, -6, 3, -4));

    //draw beak
    QPainterPath path;
    path.moveTo(-2, 1);
    path.lineTo(7, 4);
    path.lineTo(-2, 9);
    path.lineTo(-2, 1);
    painter->setPen(Qt::NoPen);
    painter->fillPath(path, QBrush(QColor(255, 130, 0)));
}

void BirdGraphicsItem::SetPosition(float x, float y) {
    x = GraphicsScene::ToSceneX(x);
    y = GraphicsScene::ToSceneY(y);
    this->setPos(x, y);
}

void BirdGraphicsItem::SetRotation(float radians) {
    this->setRotation(-qRadiansToDegrees(radians));
}
