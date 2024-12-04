#include "controller/gameController.h"
#include "view/glView.h"

int main()
{
    GameController gameController;
    gameController.setView(new GlView());
    gameController.mainLoop();

    return 0;
}
