#include "file.h"
#include "level.hpp"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <QString>
#include <QInputDialog>
Level::Level()
    : i(1), j(0), og_birds_(0), og_blocks_(0), og_pigs_(0) {
    b2Vec2 gravity(0, -9.81f);
    world_ = std::make_unique<b2World>(gravity);
    contactListener_ = std::make_unique<ContactListener>();
    world_->SetContactListener(contactListener_.get());

    struct b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world_->CreateBody(&groundBodyDef);
    groundBody->SetUserData(nullptr);


    b2PolygonShape groundBox;
    groundBox.SetAsBox(1000.0f, 10.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.0f;
    fixtureDef.friction = 100.0f;
    groundBody->CreateFixture(&groundBox, 0.0f);
    // Ask for birth date as a string.
}

void Level::SetName(std::string user) {
	username_ = user;
}

void Level::LoadLevel(std::string levelname){
    std::vector<File*> file_vec = fileread::read(levelname);
    levelname_ = levelname;
   
    for(auto it : file_vec) {
	if(it->name == "highscore") {
		bestuser_ = it->color;
		bestscore_ = it->x;
	}

        if(it->name == "block"){
            float x = it->x;
            float y = it->y;
            std::string color = it->color;
            std::shared_ptr<Block> block(new Block(x,y,color,world_.get()));
            blocks_.push_back(block);
        }

        else if(it->name == "pig"){
            float x = it->x;
            float y = it->y;
            std::shared_ptr<Pig> pig(new Pig(x,y,world_.get()));
            pigs_.push_back(pig);
        }

        if(it->name == "bird"){
            float x = it->x;
            float y = it->y;
            std::string color = it->color;
            if(color == "red"){
                std::shared_ptr<Bird> bird(new Bird(x,y,color,false,world_.get()));
                birds_.push_back(bird);
            }
            else if(color == "yellow"){
                std::shared_ptr<Bird> bird(new Bird(x,y,color,true,world_.get()));
                birds_.push_back(bird);
            }
        }
    }
    og_birds_ = birds_.size();
    og_pigs_ = pigs_.size();
    og_blocks_ = blocks_.size();
    for(auto k : file_vec) {
    	delete k;
    }
}

std::vector<std::shared_ptr<Bird>> Level::GetBirds(){
    return birds_;
}

std::vector<std::shared_ptr<Pig>> Level::GetPigs(){
    return pigs_;
}

std::vector<std::shared_ptr<Block>> Level::GetBlocks(){
    return blocks_;
}

void Level::TimeStep(){
    float timeStep = 1.0f / 25.0f;

   int32 velocityIterations = 6;
   int32 positionIterations = 2;

    world_->Step(timeStep, velocityIterations, positionIterations);


    for (std::vector<std::shared_ptr<Block>> ::iterator it = blocks_.begin(); it != blocks_.end(); ++it) {
        (*it)->UpdateGraphics();
    }
    for (std::vector<std::shared_ptr<Pig>> ::iterator it = pigs_.begin(); it != pigs_.end(); ++it) {
        (*it)->UpdateGraphics();

    }
    for (std::vector<std::shared_ptr<Bird>> ::iterator it = birds_.begin(); it != birds_.end(); ++it) {
        (*it)->UpdateGraphics();
    }

    for (std::vector<std::shared_ptr<Block>> ::iterator it = blocks_.begin(); it != blocks_.end(); ++it) {
        if((*it)->GetHitpoints() <= 0){
            world_->DestroyBody(((*it).get())->GetBody());
            blocks_.erase(std::remove(blocks_.begin(), blocks_.end(), *it), blocks_.end());
            break;
        }
    }

    for (std::vector<std::shared_ptr<Pig>> ::iterator it = pigs_.begin(); it != pigs_.end(); ++it) {
        if((*it)->GetHitpoints() <= 0){
            world_->DestroyBody(((*it).get())->GetBody());
            pigs_.erase(std::remove(pigs_.begin(), pigs_.end(), *it), pigs_.end());
            break;
        }
    }
}

int Level::GetNumberOfBirds(){
    int k = 0;
    for (std::vector<std::shared_ptr<Bird>> ::iterator it = birds_.begin(); it != birds_.end(); ++it) {
        if(((*it)->IsThrown()) == false){k++;}
    }
    return k;
}

int Level::GetNumberOfPigs(){
    return pigs_.size();
}

bool Level::IsFinished(){
    if(pigs_.empty()){
         if(GetFinalScore() > bestscore_) {
     	    std::vector<File*> a = fileread::read(levelname_);
                a.pop_back();
                File *hs = new File();
                hs->name = "highscore";
                hs->color = username_;
                hs->x = GetFinalScore();
                hs->y = 0.0;
                a.push_back(hs);
                fileread::write(a,levelname_);
	 }

	 return true;
    }
    else if(birds_.back()->IsThrown()){
        if(birds_.back()->GetBody()->GetLinearVelocity().Length() == 0){
	    if(GetFinalScore() > bestscore_) {
	    	std::vector<File*> a = fileread::read(levelname_);
		a.pop_back();
		File *hs = new File();
		hs->name = "highscore";
		hs->color = username_;
		hs->x = GetFinalScore();
		hs->y = 0.0;
		a.push_back(hs);
		fileread::write(a,levelname_);
	    }
	    return true;
	}
	return false;
    }
    else{return false;}
}

bool Level::NextBirdAvailable(){
    if(i < birds_.size()) {
        return true;}
    else {return false;}
}

std::shared_ptr<Bird> Level::GetNextBird(){
    std::shared_ptr<Bird> next_bird = birds_[i];
    i++;
    return next_bird;
}

int Level::GetScore(){
    int destroyed_pigs = og_pigs_ - pigs_.size();
    int destroyed_blocks = og_blocks_ - blocks_.size();
    int score = destroyed_pigs * 5000 + destroyed_blocks * 1000;
    return score;
}

int Level::GetFinalScore() {
    return GetScore() + 10000 * GetNumberOfBirds();
}

int Level::GetStars(){
    int max_score = og_birds_ * 10000 + og_pigs_ * 5000 + og_blocks_ * 1000;
    int score = GetFinalScore();
    if (score == 0){return 0;}
    else if (score > 0 && score < max_score*0.5){return 1;}
    else if (score >= max_score*0.5 && score < max_score*0.8){return 2;}
    else {return 3;}
}

int Level::GetBestScore() {
	return bestscore_;
}

std::string Level::GetBestUser() {
	return bestuser_;
}

bool Level::IsPassed() {
    if(pigs_.empty()){return true;}
    else{return false;}
}
