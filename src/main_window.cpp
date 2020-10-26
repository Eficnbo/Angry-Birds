#include "main_window.h"

MainWindow::MainWindow() {
    setGeometry(50, 50, 1000, 700);
    setWindowTitle("Angry Birds");
    menuScene_ = new Menu(0, 0, 1000, 700);
    levelScene_ = new LevelScene(0, 0, 1800, 700);
    editorScene_ = new LevelEditor(0, 0, 1800, 700);

    menuView_ = new QGraphicsView(menuScene_);
    levelView_ = new QGraphicsView(levelScene_);
    editorView_ = new QGraphicsView(editorScene_);

    stackedScenes_ = new QStackedWidget;
    stackedScenes_->addWidget(menuView_);
    stackedScenes_->addWidget(levelView_);
    stackedScenes_->addWidget(editorView_);
    setCentralWidget(stackedScenes_);

    menuView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    menuView_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    levelView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    levelView_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    editorView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    editorView_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(menuScene_, SIGNAL(changeScene(int)), this, SLOT(ChangeScene(int)));
    connect(menuScene_, SIGNAL(startLevel(int)), levelScene_, SLOT(StartLevel(int)));
    connect(menuScene_, SIGNAL(editLevel(int)), editorScene_, SLOT(OpenEditor(int)));

    connect(menuScene_, SIGNAL(setName(std::string)), levelScene_, SLOT(setName(std::string)));
    connect(levelScene_, SIGNAL(changeScene(int)), this, SLOT(ChangeScene(int)));
    connect(levelScene_, SIGNAL(levelPlayed(int)), menuScene_, SLOT(LevelPlayed(int)));

    connect(editorScene_, SIGNAL(changeScene(int)), this, SLOT(ChangeScene(int)));
    connect(editorScene_, SIGNAL(levelEdited()), menuScene_, SLOT(LevelEdited()));
}

MainWindow::~MainWindow() {
    delete menuScene_;
    delete levelScene_;
    delete editorScene_;
    delete menuView_;
    delete levelView_;
    delete editorView_;
    delete stackedScenes_;
}

void MainWindow::ChangeScene(int sceneNumber) {
    stackedScenes_->setCurrentIndex(sceneNumber);
}

