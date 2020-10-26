#include <QGraphicsView>
#include <iostream>
#include <QBrush>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include "level_scene.h"

LevelScene::LevelScene(int x, int y, int width, int height, QObject *parent) :
    GraphicsScene(x, y, width, height, parent)
{
    slingshot_ = new Slingshot(this);
    timer_ = new QTimer();
    connect(timer_, &QTimer::timeout, this, &LevelScene::TimeStep);

    text1_ = new QGraphicsTextItem("Score: ");
    text2_ = new QGraphicsTextItem("Birds Left: ");
    text3_ = new QGraphicsTextItem("Pigs Left: ");
    QFont font;
    font.setPixelSize(20);
    text1_->setFont(font);
    text2_->setFont(font);
    text3_->setFont(font);
    text1_->setPos(10, 10);
    text2_->setPos(10, 40);
    text3_->setPos(10, 70);
    this->addItem(text1_);
    this->addItem(text2_);
    this->addItem(text3_);
}

LevelScene::~LevelScene() {
    delete timer_;
    delete slingshot_;
}
void LevelScene::setName(std::string user) {
	user_ = user;
}

void LevelScene::StartLevel(int levelNumber) {
    level_ = new Level();
    level_->SetName(user_);
    std::string levelname = "level" + std::to_string(levelNumber);
    level_->LoadLevel(levelname);

    std::vector<std::shared_ptr<Bird>> birds = level_->GetBirds();
    for (unsigned int i = 0; i < birds.size(); i++) {
        this->addItem(birds[i]->GetGraphicsItem());
    }
    std::vector<std::shared_ptr<Pig>> pigs = level_->GetPigs();
    for (unsigned int i = 0; i < pigs.size(); i++) {
       this->addItem(pigs[i]->GetGraphicsItem());
    }
    std::vector<std::shared_ptr<Block>> blocks = level_->GetBlocks();
    for (unsigned int i = 0; i < blocks.size(); i++) {
        this->addItem(blocks[i]->GetGraphicsItem());
    }

    activeBird_ = birds[0];
    slingshot_->SetBird(activeBird_.get());
    slingshot_->UpdateGraphics();
    viewFollowingBird_ = false;
    update();

    //timer starts calling TimeStep every 40ms
    timer_->start(40);
}

void LevelScene::TimeStep() {
    level_->TimeStep();
    UpdateTexts();
    if(viewFollowingBird_) {
        this->views().first()->centerOn(activeBird_->GetGraphicsItem());
    }
    if(level_->IsFinished()) {
        timer_->stop();
        EndLevel();
    }
}

void LevelScene::UpdateTexts() {
    std::string str1 = "Score: " + std::to_string(level_->GetScore());
    const char * c1 = str1.c_str();
    text1_->setPlainText(QString(c1));

    std::string str2 = "Birds Left: " + std::to_string(level_->GetNumberOfBirds());
    const char * c2 = str2.c_str();
    text2_->setPlainText(QString(c2));

    std::string str3 = "Pigs Left: " + std::to_string(level_->GetNumberOfPigs());
    const char * c3 = str3.c_str();
    text3_->setPlainText(QString(c3));
}

void LevelScene::EndLevel() {
    QGraphicsRectItem *rect = new QGraphicsRectItem(800, 200, 450, 200);
    rect->setBrush(QBrush(Qt::white));
    QGraphicsTextItem *text1 = new QGraphicsTextItem("LEVEL");
    QGraphicsTextItem *text2 = new QGraphicsTextItem("Stars: ");
    QGraphicsTextItem *text3 = new QGraphicsTextItem("Score: ");
    text1->setPos(810, 210);
    text2->setPos(810, 235);
    text3->setPos(810, 260);

    std::string str1;
    if(level_->IsPassed()) {
        if(level_->GetFinalScore() > level_->GetBestScore()) {
	    str1 = "LEVEL COMPLETED! \nNEW HIGHSCORE \n";
	}
	else {
		str1 = "LEVEL COMPLETED! \nCURRENT HIGHSCORE: " +level_->GetBestUser() +" "+ std::to_string(level_->GetBestScore()) +" \n";
	}
    }
    else {
	if(level_->GetFinalScore() > level_->GetBestScore()) {    
        	str1 = "LEVEL FAILED! \nNEW HIGHSCORE";
	}
	else {
		str1 = "LEVEL FAILED! \nCURRENT HIGHSCORE: " + level_->GetBestUser() + " " + std::to_string(level_->GetBestScore()) + "\n";
	}
    }
    const char * c1 = str1.c_str();
    text1->setPlainText(QString(c1));

    std::string str2 = "\nStars: " + std::to_string(level_->GetStars()) + "/3";
    const char * c2 = str2.c_str();
    text2->setPlainText(QString(c2));

    std::string str3 = "\nScore: " + std::to_string(level_->GetFinalScore());
    const char * c3 = str3.c_str();
    text3->setPlainText(QString(c3));

    QFont font;
    font.setPixelSize(20);
    text1->setFont(font);
    text2->setFont(font);
    text3->setFont(font);

    this->addItem(rect);
    this->addItem(text1);
    this->addItem(text2);
    this->addItem(text3);
    this->views().first()->centerOn(rect);
    this->update();
    delay(5);

    delete rect;
    delete text1;
    delete text2;
    delete text3;
    emit levelPlayed(level_->GetFinalScore());
    delete level_;
    emit changeScene(0);
}

void LevelScene::delay(int seconds)
{
    //from stackoverflow
    QTime dieTime= QTime::currentTime().addSecs(seconds);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(!activeBird_->IsThrown()) {
        slingshot_->MousePress(event->scenePos().x(), event->scenePos().y());
        slingshot_->UpdateGraphics();
    }
    else {
        if(activeBird_->AbilityAvailable()) {
            activeBird_->ActivateAbility();
        }
        else {
            viewFollowingBird_ = false;
            if(level_->NextBirdAvailable()) {
                activeBird_ = level_->GetNextBird();
                slingshot_->SetBird(activeBird_.get());
                slingshot_->UpdateGraphics();
            }
        }
    }
}

void LevelScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(!activeBird_->IsThrown()) {
        slingshot_->MouseMove(event->scenePos().x(), event->scenePos().y());
        slingshot_->UpdateGraphics();
    }
}

void LevelScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
    if(!activeBird_->IsThrown()) {
        slingshot_->MouseRelease();
        viewFollowingBird_ = true;
    }
}


