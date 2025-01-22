#pragma once
#include "iSoundController.h"

class SoundController : public ISoundController
{
private:
    sf::Music *music;

public:
    SoundController();
    int playBackgroundMusic();
    ~SoundController();
};