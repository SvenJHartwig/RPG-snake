#include "dialog.h"

void Dialog::show() {}
void Dialog::close() {}
void Dialog::setText(std::string text) {}
Dialog::Dialog(SEngine::IRenderEngine *engine, std::string text)
{
    this->engine = engine;
}
Dialog::~Dialog() {}