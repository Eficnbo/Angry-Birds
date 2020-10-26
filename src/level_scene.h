#pragma once

#include <string>
#include <vector>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QGraphicsTextItem>
#include "graphics_scene.h"
#include "level.hpp"
#include "bird.hpp"
#include "slingshot.h"

class LevelScene : public GraphicsScene {
    Q_OBJECT

public:
    LevelScene(int x, int y, int width, int height, QObject *parent = nullptr);
    ~LevelScene();

    void UpdateTexts();
    void EndLevel();
    void delay(int seconds);

public slots:
    void setName(std::string user);
    void StartLevel(int levelNumber);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private slots:
    void TimeStep();

signals:
    void levelPlayed(int score);
    void changeScene(int sceneNumber);

private:
    Level *level_;
    QTimer *timer_;
    Slingshot *slingshot_;
    std::shared_ptr<Bird> activeBird_;
    QGraphicsTextItem* text1_;
    QGraphicsTextItem* text2_;
    QGraphicsTextItem* text3_;
    bool viewFollowingBird_;
    std::string user_;
};


