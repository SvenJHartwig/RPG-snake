#include "controller/gameController.h"
#include "view/glView.h"
#include "controller/soundController.h"
#include "services/gameControllerService.h"
#include "services/gameModeService.h"

int main()
{
    GameControllerService::setInstance(std::make_shared<GameController>());
    GameModeService::setInstance(std::make_shared<RPGGameMode>());
    GameController *gameController = GameControllerService::get().get();
    gameController->setView(new GlView());
    gameController->setSoundController(new SoundController());
    gameController->mainLoop();

    return 0;
}
