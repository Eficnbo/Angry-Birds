#include <QtMath>
#include <QPainter>
#include "slingshot.h"
#include "graphics_scene.h"

Slingshot::Slingshot(QGraphicsScene* scene) {
    //(x0_, y0_) is the birds's starting position in the slingshot
    x0_ = 200;
    y0_ = 505;

    //(x_, y_) is the bird's current position in the slingshot
    x_ = x0_;
    y_ = y0_;

    birdRadius_ = 12;
    maxBandLength_ = 60;
    mousePressedOnBird_ = false;
    birdInSlingshot_ = false;

    //(x, y) is the upper left corner of the slingshot
    int a = 10;
    int x = x0_ - 1.5*a;
    int y = y0_ - 0.5*a;
    line1x_ = x + 0.5*a;
    line1y_ = y + 0.5*a;
    line2x_ = x + 2.5*a;
    line2y_ = y + a/2;

    rect1_ = new QGraphicsRectItem(x+a, y+4*a, a, 4*a);
    rect2_ = new QGraphicsRectItem(x+2*a, y, a, 4*a);
    rect3_ = new QGraphicsRectItem(x, y+3*a, 3*a, a);
    rect4_ = new QGraphicsRectItem(x, y, a, 4*a);
    line1_ = new QGraphicsLineItem(line1x_, line1y_, line1x_, line1y_);
    line2_ = new QGraphicsLineItem(line2x_, line2y_, line2x_, line2y_);

    QBrush brush(QColor(190, 80, 20));
    rect1_->setBrush(brush);
    rect2_->setBrush(brush);
    rect3_->setBrush(brush);
    rect4_->setBrush(brush);
    QPen pen(QColor(0, 0, 0));
    pen.setWidth(6);
    line1_->setPen(pen);
    line2_->setPen(pen);

    //The Z value decides the stacking order of items
    rect1_->setZValue(1);
    rect2_->setZValue(2);
    rect3_->setZValue(3);
    rect4_->setZValue(6);
    line1_->setZValue(7);
    line2_->setZValue(4);

    scene->addItem(rect1_);
    scene->addItem(rect2_);
    scene->addItem(rect3_);
    scene->addItem(rect4_);
    scene->addItem(line1_);
    scene->addItem(line2_);
}

Slingshot::~Slingshot() {
    delete rect1_;
    delete rect2_;
    delete rect3_;
    delete rect4_;
    delete line1_;
    delete line2_;
}

void Slingshot::SetBird(Bird* bird) {
    bird_ = bird;
    x_ = x0_;
    y_ = y0_;
    bird_->GetGraphicsItem()->setZValue(5);
    bird_->SetToSlingshot();
    mousePressedOnBird_ = false;
    birdInSlingshot_ = true;
}

float Slingshot::Distance(int x1, int y1, int x2, int y2) {
    return qSqrt(qPow((x2-x1), 2) + qPow((y2-y1), 2));
}

float Slingshot::GetAngle() {
    int dx = x0_ - x_;
    int dy = y_ - y0_;

    //To avoid division by zero
    if(dx == 0)
        dx = 1;

    float angle = qAtan((float)dy / (float)dx);
    return angle;
}

void Slingshot::UpdateGraphics() {
    bird_->GetGraphicsItem()->setPos(x_, y_);

    if(Distance(x0_, y0_, x_, y_) > 0) {
        //Extend lines (slingshot bands) by birdRadius
        int x = x_ + (x_ - x0_) / Distance(x0_, y0_, x_, y_) * (0.9*birdRadius_);
        int y = y_ + (y_ - y0_) / Distance(x0_, y0_, x_, y_) * (0.9*birdRadius_);

        line1_->setLine(line1x_, line1y_, x, y);
        line2_->setLine(line2x_, line2y_, x, y);
    }
}

void Slingshot::MousePress(int x, int y) {
    if(Distance(x, y, x0_, y0_) <= birdRadius_) {
        mousePressedOnBird_ = true;
    }
}

void Slingshot::MouseMove(int x, int y) {
    if(mousePressedOnBird_) {

        if(y < y0_)
            y = y0_;
        if(x > x0_)
            x = x0_;

        if(Distance(x, y, x0_, y0_) <= maxBandLength_) {
            x_ = x;
            y_ = y;
        }
        else {
            /*Find position for bird when mouse is too far from slingshot.
            Solution:
            https://math.stackexchange.com/questions/127613
            /closest-point-on-circle-edge-from-point-outside-inside-the-circle*/
            int Ax = x0_;
            int Ay = y0_;
            int Bx = x;
            int By = y;
            int r = maxBandLength_;
            x_ = Ax+r*(Bx-Ax)/qSqrt(qPow((Bx-Ax),2)+qPow((By-Ay),2));
            y_ = Ay+r*(By-Ay)/qSqrt(qPow((Bx-Ax),2)+qPow((By-Ay),2));
        }
    }
}

void Slingshot::MouseRelease() {
    if(mousePressedOnBird_) {
        float x = GraphicsScene::ToWorldX((float)x_);
        float y = GraphicsScene::ToWorldY((float)y_);
        bird_->SetPosition(x, y);

        float speed = Distance(x_, y_, x0_, y0_) / maxBandLength_;
        float angle = GetAngle();
        bird_->Throw(speed, angle);

        line1_->setLine(line1x_, line1y_, line1x_, line1y_);
        line2_->setLine(line2x_, line2y_, line2x_, line2y_);
    }
}

