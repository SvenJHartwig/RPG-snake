#include "soundController.h"
#include <string>

SoundController::SoundController()
{
    music = new sf::Music();
}
SoundController::~SoundController() {}

int SoundController::playBackgroundMusic()
{
    if (!music->openFromFile(static_cast<std::string>(RESOURCE_DIR).append("/music/background.mp3")))
        return -1; // error

    music->setVolume(20.0f);
    music->setLooping(true);
    music->setLoopPoints({sf::milliseconds(500), sf::seconds(4)});
    music->play();

    return 0;
}