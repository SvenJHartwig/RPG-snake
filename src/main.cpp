#include "controller/gameController.h"
#include "view/glView.h"
#include "controller/soundController.h"

int main()
{
    GameController gameController;
    gameController.setView(new GlView());
    gameController.setSoundController(new SoundController());
    gameController.mainLoop();

    return 0;
}
