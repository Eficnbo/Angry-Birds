#include <QtMath>
#include <QMessageBox>
#include "level_editor.h"

LevelEditor::LevelEditor(int x, int y, int width, int height, QObject *parent) :
    GraphicsScene(x, y, width, height, parent)
{
    slingshot_ = new Slingshot(this);
}

LevelEditor::~LevelEditor() {
    delete slingshot_;
}

void LevelEditor::drawForeground(QPainter *painter, const QRectF &) {
    painter->setPen(Qt::SolidLine);
    int x1, y1, x2, y2;

    //draw vertical lines
    for(unsigned int i = 10; ToSceneX(i) < this->width(); i++) {
        x1 = ToSceneX(i);
        y1 = ToSceneY(0);
        y2 = 0;
        painter->drawLine(x1, y1, x1, y2);
    }

    //draw horizontal lines
    for(unsigned int i = 0; ToSceneY(i) > 0; i++) {
        y1 = ToSceneY(i);
        x1 = ToSceneX(10);
        x2 = this->width();
        painter->drawLine(x1, y1, x2, y1);
    }
}

void LevelEditor::OpenEditor(int levelNumber) {
    levelName_ = "level" + std::to_string(levelNumber);
    action_ = "None";
    saved_ = false;
    RemoveItems();
    AddButtons();
    slingshot_ = new Slingshot(this);
}

void LevelEditor::AddButtons() {
    Button *b0 = new Button();
    b0->setPlainText("Add Red Bird");
    buttons_.push_back(b0);

    Button *b1 = new Button();
    b1->setPlainText("Add Yellow Bird");
    buttons_.push_back(b1);

    Button *b2 = new Button();
    b2->setPlainText("Add Pigs");
    buttons_.push_back(b2);

    Button *b3 = new Button();
    b3->setPlainText("Add Glass Blocks");
    buttons_.push_back(b3);

    Button *b4 = new Button();
    b4->setPlainText("Add Wood Blocks");
    buttons_.push_back(b4);

    Button *b5 = new Button();
    b5->setPlainText("Add Stone Blocks");
    buttons_.push_back(b5);

    Button *b6 = new Button();
    b6->setPlainText("Add Ground Blocks");
    buttons_.push_back(b6);

    Button *b7 = new Button();
    b7->setPlainText("Remove All Items");
    buttons_.push_back(b7);

    Button *b8 = new Button();
    b8->setPlainText("Save Level To File");
    buttons_.push_back(b8);

    Button *b9 = new Button();
    b9->setPlainText("Quit Editor");
    buttons_.push_back(b9);

    for(unsigned int i = 0; i < buttons_.size(); i++) {
        buttons_[i]->setPos(50 + i*180, 620);
        this->addItem(buttons_[i]);
    }
}

void LevelEditor::ResetButtonColors() {
    for(unsigned int i = 0; i < buttons_.size(); i++) {
        buttons_[i]->ResetColor();
    }
}

void LevelEditor::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem* clickedItem = itemAt(event->scenePos().x(), event->scenePos().y(), QTransform());

    if(clickedItem == buttons_[0] && nofBirds_ < 5) {
        float posX = 4 - nofBirds_ * 0.8;
        float posY = 0.33f;
        BirdGraphicsItem* graphicsItem = new BirdGraphicsItem("red", posX, posY);
        this->addItem(graphicsItem);
        struct File info = { "bird", "red", posX, posY };
        itemInfos_.push_back(info);
        nofBirds_ += 1;
        ResetButtonColors();
        action_ = "None";
    }
    else if(clickedItem == buttons_[1] && nofBirds_ < 5) {
        float posX = 4 - nofBirds_ * 0.8;
        float posY = 0.33f;
        BirdGraphicsItem* graphicsItem = new BirdGraphicsItem("yellow", posX, posY);
        this->addItem(graphicsItem);
        struct File info = { "bird", "yellow", posX, posY };
        itemInfos_.push_back(info);
        nofBirds_ += 1;
        ResetButtonColors();
        action_ = "None";
    }
    else if(clickedItem == buttons_[2]) {
        action_ = "Add Pigs";
        ResetButtonColors();
        buttons_[2]->Darken();
    }
    else if(clickedItem == buttons_[3]){
        action_ = "Add Glass Blocks";
        ResetButtonColors();
        buttons_[3]->Darken();
    }
    else if(clickedItem == buttons_[4]){
        action_ = "Add Wood Blocks";
        ResetButtonColors();
        buttons_[4]->Darken();
    }
    else if(clickedItem == buttons_[5]){
        action_ = "Add Stone Blocks";
        ResetButtonColors();
        buttons_[5]->Darken();
    }
    else if(clickedItem == buttons_[6]){
        action_ = "Add Ground Blocks";
        ResetButtonColors();
        buttons_[6]->Darken();
    }
    else if(clickedItem == buttons_[7]){
        RemoveItems();
        AddButtons();
        slingshot_ = new Slingshot(this);
        action_ = "None";
    }
    else if(clickedItem == buttons_[8]){
        Save();
        action_ = "None";
    }
    else if(clickedItem == buttons_[9]){
        emit changeScene(0);
        if(saved_) {
            emit levelEdited();
        }
    }
    else {
        int x = qFloor(ToWorldX(event->scenePos().x()));
        int y = qFloor(ToWorldY(event->scenePos().y()));
        if(x >= 10 && y >= 0 && clickedItem == nullptr) {
            float posX = x + 0.5;
            float posY = y + 0.5;
            if(action_ == "Add Glass Blocks") {
                BlockGraphicsItem* graphicsItem = new BlockGraphicsItem("blue", posX, posY);
                this->addItem(graphicsItem);
                struct File info = { "block", "blue", posX, posY };
                itemInfos_.push_back(info);
            }
            else if(action_ == "Add Wood Blocks") {
                BlockGraphicsItem* graphicsItem = new BlockGraphicsItem("lightBrown", x+0.5, y+0.5);
                this->addItem(graphicsItem);
                struct File info = { "block", "lightBrown", posX, posY };
                itemInfos_.push_back(info);
            }
            else if(action_ == "Add Stone Blocks") {
                BlockGraphicsItem* graphicsItem = new BlockGraphicsItem("gray", x+0.5, y+0.5);
                this->addItem(graphicsItem);
                struct File info = { "block", "gray", posX, posY };
                itemInfos_.push_back(info);
            }
            else if(action_ == "Add Ground Blocks") {
                BlockGraphicsItem* graphicsItem = new BlockGraphicsItem("darkBrown", x+0.5, y+0.5);
                this->addItem(graphicsItem);
                struct File info = { "block", "darkBrown", posX, posY };
                itemInfos_.push_back(info);
            }
            else if(action_ == "Add Pigs") {
                PigGraphicsItem* graphicsItem = new PigGraphicsItem("green", x+0.5, y+0.5);
                this->addItem(graphicsItem);
                struct File info = { "pig", "green", posX, posY };
                itemInfos_.push_back(info);
                nofPigs_ += 1;
            }
        }
    }
}

void LevelEditor::RemoveItems() {
    //clear removes and deletes all graphicsitems
    delete slingshot_;
    clear();

    update();
    buttons_.clear();
    itemInfos_.clear();
    nofBirds_ = 0;
    nofPigs_ = 0;
}

void LevelEditor::Save() {
    if(nofBirds_ > 0 && nofPigs_ > 0) {
        bool success = fileread::write(itemInfos_, levelName_);
        if(success) {
            saved_ = true;
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Saving to file failed");
            msgBox.exec();
        }
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Add at least 1 bird and 1 pig");
        msgBox.exec();
    }
}

