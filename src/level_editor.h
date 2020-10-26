#pragma once

#include <string>
#include <vector>
#include <QObject>
#include <QPainter>
#include <QRectF>
#include <QGraphicsSceneMouseEvent>
#include "graphics_scene.h"
#include "bird_graphics_item.h"
#include "pig_graphics_item.h"
#include "blockgraphicsitem.h"
#include "button.h"
#include "file.h"
#include "slingshot.h"

class LevelEditor : public GraphicsScene {
    Q_OBJECT

public:
    LevelEditor(int x, int y, int width, int height, QObject *parent = nullptr);
    ~LevelEditor();

    void AddButtons();
    void ResetButtonColors();
    void RemoveItems();
    void Save();

public slots:
    void OpenEditor(int levelNumber);

protected:
    void drawForeground(QPainter *painter, const QRectF &rect) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    std::string action_;
    std::vector<Button*> buttons_;
    std::vector<File> itemInfos_;
    std::string levelName_;
    int nofBirds_;
    int nofPigs_;
    bool saved_;
    Slingshot* slingshot_;

signals:
    void levelEdited();
    void changeScene(int sceneNumber);
};


