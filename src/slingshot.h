#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include "bird.hpp"

class Slingshot {
public:
    Slingshot(QGraphicsScene *scene);
    ~Slingshot();

    void SetBird(Bird *bird);
    float Distance(int x1, int y1, int x2, int y2);
    float GetAngle();
    void UpdateGraphics();
    void MousePress(int x, int y);
    void MouseMove(int x, int y);
    void MouseRelease();

private:
    int x_;
    int y_;
    int x0_;
    int y0_;
    int birdRadius_;
    float maxBandLength_;
    bool mousePressedOnBird_;
    bool birdInSlingshot_;
    Bird *bird_;
    QGraphicsRectItem* rect1_;
    QGraphicsRectItem* rect2_;
    QGraphicsRectItem* rect3_;
    QGraphicsRectItem* rect4_;
    QGraphicsLineItem* line1_;
    QGraphicsLineItem* line2_;
    int line1x_;
    int line1y_;
    int line2x_;
    int line2y_;
};
