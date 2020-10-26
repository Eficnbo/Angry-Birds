#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QStackedWidget>
#include "menu.h"
#include "level_scene.h"
#include "level_editor.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();

public slots:
    void ChangeScene(int sceneNumber);

private:
    Menu *menuScene_;
    LevelScene *levelScene_;
    LevelEditor *editorScene_;
    QGraphicsView *menuView_;
    QGraphicsView *levelView_;
    QGraphicsView *editorView_;
    QStackedWidget *stackedScenes_;
};
