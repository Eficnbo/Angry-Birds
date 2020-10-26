#pragma once

#include <QGraphicsScene>
#include <QObject>
#include <QPainter>
#include <QRectF>

class GraphicsScene : public QGraphicsScene {
public:
    GraphicsScene(int x, int y, int width, int height, QObject *parent = nullptr);

    static float ToSceneX(float x);
    static float ToSceneY(float y);
    static float ToWorldX(float x);
    static float ToWorldY(float y);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};
