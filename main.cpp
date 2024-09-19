#include "controller/gameController.h"
#include "view/glView.h"
// #include <GL/glew.h>

int main()
{
    GameController gameController;
    gameController.setView(new GlView());
    gameController.mainLoop();

    return 0;
}
