#pragma once

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include "box2d/b2_world.h"
#include "box2d/b2_math.h"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include "bird.hpp"
#include "block.hpp"
#include "pig.hpp"
#include "contact_listener.hpp"

class Level{
public:
    Level();

    void LoadLevel(std::string filename);

    std::vector<std::shared_ptr<Bird>> GetBirds();

    std::vector<std::shared_ptr<Pig>> GetPigs();

    std::vector<std::shared_ptr<Block>>  GetBlocks();

    void TimeStep();

    int GetNumberOfBirds();

    int GetNumberOfPigs();

    bool IsFinished();

    bool NextBirdAvailable();

    std::shared_ptr<Bird> GetNextBird();

    int GetScore();

    int GetFinalScore();

    int GetStars();

    bool IsPassed();

    void SetName(std::string user);
    
    int GetBestScore();

    std::string GetBestUser();
private:
    std::vector<std::shared_ptr<Bird>>  birds_;
    std::vector<std::shared_ptr<Pig>>  pigs_;
    std::vector<std::shared_ptr<Block>>  blocks_;
    int i;
    int j;
    std::unique_ptr<b2World> world_;
    std::unique_ptr<ContactListener> contactListener_;
    int og_birds_;
    int og_pigs_;
    int og_blocks_;
    int bestscore_;
    std::string bestuser_;
    std::string username_;
    std::string levelname_;
    
};
