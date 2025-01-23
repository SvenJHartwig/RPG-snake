#pragma once
#include "iSoundController.h"

class SoundController : public ISoundController
{
private:
    sf::Music *music;
    sf::Sound *sound;
    sf::SoundBuffer *buffer;

public:
    SoundController();
    int playBackgroundMusic(std::string path);
    int playSoundEffect(std::string path);
    ~SoundController();
};