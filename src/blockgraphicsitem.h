#pragma once

#include <QGraphicsItem>
#include <QImage>
#include <QRect>
#include <string>
class BlockGraphicsItem : public QGraphicsItem {

public:
    BlockGraphicsItem(const std::string &color,float x, float y);

    void SetRotation(float radians);
    void SetPosition(float x,float y);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;

private:
    QRectF rect;
    QColor color_;
};
