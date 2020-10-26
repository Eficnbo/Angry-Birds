#include <QRandomGenerator>
#include "graphics_scene.h"

GraphicsScene::GraphicsScene(int x, int y, int width, int height, QObject *parent) :
    QGraphicsScene(x, y, width, height, parent) { }

void GraphicsScene::drawBackground(QPainter *painter, const QRectF &) {
    QColor skyColor = QColor(140, 255, 250);
    QColor grassColor = QColor(0, 200, 15);
    QColor grassColor2 = QColor(0, 100, 0);
    QColor groundColor = QColor(190, 80, 0);
    QColor groundColor2 = QColor(50, 25, 0);

    int skyHeight = 0.83 * this->height();
    int grassHeight = 0.02 * this->height();
    int groundHeight = 0.15 * this->height();

    painter->setPen(Qt::NoPen);

    painter->setBrush(skyColor);
    painter->drawRect(0, 0, this->width(), skyHeight);

    painter->setBrush(grassColor);
    painter->drawRect(0, skyHeight, this->width(), grassHeight);

    painter->setBrush(groundColor);
    painter->drawRect(0, skyHeight + grassHeight, this->width(), groundHeight);

    int seed = 10;
    QRandomGenerator gen(seed);
    int x, y, lowest, highest;

    //Draw ground texture
    lowest = skyHeight + grassHeight;
    highest = skyHeight + grassHeight + groundHeight;
    painter->setBrush(groundColor2);
    for(unsigned int i = 0; i < 8000; i++) {
        x = gen.bounded(0, this->width());
        y = gen.bounded(lowest, highest);
        painter->drawRect(x, y, 2, 2);
    }

    //Draw grass texture
    lowest = skyHeight;
    highest = skyHeight + grassHeight;
    painter->setBrush(grassColor2);
    for(unsigned int i = 0; i < 1000; i++) {
        x = gen.bounded(0, this->width());
        y = gen.bounded(lowest, highest);
        painter->drawRect(x, y, 2, 4);
    }
}

float GraphicsScene::ToSceneX(float x) {
    //Transform b2World x coordinate to QGraphicsScene x
    return 40*x;
}

float GraphicsScene::ToSceneY(float y) {
    //Transform b2World x coordinate to QGraphicsScene x
    return -40*y+581;
}

float GraphicsScene::ToWorldX(float x) {
    //Transform QGraphicsScene x coordinate to b2World x
    return x / 40;
}

float GraphicsScene::ToWorldY(float y) {
    //Transform QGraphicsScene y coordinate to b2World y
    return -(y - 581) / 40;
}
