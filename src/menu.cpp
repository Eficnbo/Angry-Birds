#include "menu.h"
#include <iostream>
#include <QString>
#include <QInputDialog>
#include <string>
Menu::Menu(int x, int y, int width, int height, QObject *parent) : GraphicsScene(x, y, width, height, parent) {

    bool ok;
    QString text = QInputDialog::getText(0, "Input dialog",
                                         "username:", QLineEdit::Normal,
                                         "", &ok);
    if(ok) {
        username_ = text.toUtf8().constData();
    }
    else {
       username_ = "anon";
    }
    a = new Button();
    a->setPlainText ("Play Level 1");
    a->setPos(400,250);
    this->addItem(a);

    b = new Button();
    b->setPlainText("Edit Level 1");
    b->setPos(600,250);
    this->addItem(b);

    c = new Button();
    c->setPlainText("Play Level 2");
    c->setPos(400,200);
    this->addItem(c);

    d = new Button();
    d->setPlainText("Edit Level 2");
    d->setPos(600,200);
    this->addItem(d);

    e = new Button();
    e->setPlainText("Play Level 3");
    e->setPos(400,150);
    this->addItem(e);

    f = new Button();
    f->setPlainText("Edit Level 3");
    f->setPos(600,150);
    this->addItem(f);

    g = new Button();
    g->setPlainText("Change username");
    g->setPos(500,100);
    this->addItem(g);

}

void Menu::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem* clickedItem = itemAt(event->scenePos().x(), event->scenePos().y(), QTransform());
    if(clickedItem != nullptr) {
        if(clickedItem == a) {
            emit setName(username_);
	    emit changeScene(1);
	    emit startLevel(1);

        }
	if(clickedItem == b) {
		emit changeScene(2);
		emit editLevel(1);
	}
	if(clickedItem == c) {
		emit setName(username_);
		emit changeScene(1);
		emit startLevel(2);
	}
	if(clickedItem == d) {
		emit changeScene(2);
		emit editLevel(2);
	}
	if(clickedItem == e) {
		emit setName(username_);
		emit changeScene(1);
		emit startLevel(3);
	}
	if(clickedItem == f) {
		emit changeScene(2);
		emit editLevel(3);
	}
	if(clickedItem == g) {
		bool ok;
		QString text = QInputDialog::getText(0, "Input dialog",
                                         "username:", QLineEdit::Normal,
                                         "", &ok);
		    if(ok) {
        		username_ = text.toUtf8().constData();
    			}
    		    else {
       			username_ = "anon";
    		    }
	}
    }
}
