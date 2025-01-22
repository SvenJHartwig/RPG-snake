#pragma once
#include "SFML/Audio.hpp"

class ISoundController
{
public:
    virtual int playBackgroundMusic() = 0;
};