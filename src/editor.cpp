#include "editor/controller/editorController.h"
#include "editor/view/editorView.h"

int main()
{
    EditorController *controller = new EditorController(new EditorView());
    controller->mainLoop();

    return 0;
}
