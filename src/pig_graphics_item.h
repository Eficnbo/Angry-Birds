#pragma once

#include <string>
#include <QGraphicsItem>
#include <string>
class PigGraphicsItem : public QGraphicsItem {
public:
    PigGraphicsItem(const std::string &color,float x,float y);
    void SetPosition(float x,float y);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) override;
    void SetRotation(float radians);

private:
    QColor color_;
};
