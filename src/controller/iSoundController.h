#pragma once
#include "SFML/Audio.hpp"

class ISoundController
{
public:
    virtual int playBackgroundMusic(std::string path) = 0;
    virtual int playSoundEffect(std::string path) = 0;
};