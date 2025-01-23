#include "soundController.h"
#include <string>

SoundController::SoundController()
{
    music = new sf::Music();
    buffer = new sf::SoundBuffer();
    sound = new sf::Sound(*(buffer));
}
SoundController::~SoundController() {}

int SoundController::playBackgroundMusic(std::string path)
{
    music->stop();
    if (!music->openFromFile(path))
        return -1; // error

    music->setVolume(20.0f);
    music->setLooping(true);
    music->setLoopPoints({sf::milliseconds(500), sf::seconds(4)});
    music->play();

    return 0;
}

int SoundController::playSoundEffect(std::string path)
{
    if (!buffer->loadFromFile(path))
        return -1;

    sound->play();

    return 0;
}