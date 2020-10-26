#pragma once

#include "QGraphicsSceneMouseEvent"
#include "button.h"
#include "graphics_scene.h"
#include <string>

class Menu : public GraphicsScene {
    Q_OBJECT

public:
    Menu(int x, int y, int width, int height, QObject *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Button *a;
    Button *b;
    Button *c;
    Button *d;
    Button *e;
    Button *f;
    Button *g;
    std::string username_;

signals:
    void setName(std::string user);
    void startLevel(int levelNumber);
    void editLevel(int levelNumber);
    void changeScene(int sceneNumber);
};
