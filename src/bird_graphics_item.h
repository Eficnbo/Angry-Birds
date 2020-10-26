#pragma once

#include <string>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QColor>

class BirdGraphicsItem : public QGraphicsItem {
public:
    BirdGraphicsItem(const std::string& color, float x, float y);

    void SetPosition(float x, float y);
    void SetRotation(float radians);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget) override;

private:
    QColor color_;
};
