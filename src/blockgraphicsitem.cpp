#include "blockgraphicsitem.h"
#include "graphics_scene.h"
#include <iostream>
#include <QPainter>
#include <QtMath>
BlockGraphicsItem::BlockGraphicsItem(const std::string &color,float x, float y) {
  this->SetPosition(x,y);
  rect = QRectF(-20,-20,40,40);
  if(color == "blue") {
    color_ = QColor(0,200,230);
  }
  if(color == "lightBrown") {
    color_ = QColor(255,160,45);
  }
  if(color == "gray") {
      color_ = QColor(130,130,130);
  }
  if(color == "darkBrown") {
      color_ = QColor(190,80,0);
  }
}

void BlockGraphicsItem::SetPosition(float x, float y) {
    x = GraphicsScene::ToSceneX(x);
    y = GraphicsScene::ToSceneY(y);
    this->setPos(x,y);
}
void BlockGraphicsItem::SetRotation(float radians) {
    this->setRotation(-qRadiansToDegrees(radians));
}

QRectF BlockGraphicsItem::boundingRect() const {
    return QRectF(-20,-20,40,40);
}
void BlockGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color_);
    painter->drawRect(rect);
}
