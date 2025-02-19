#pragma once
#include <string>

class IEditorView
{
public:
    virtual std::string showOutput(std::string out) = 0;
};

class EditorView : public IEditorView
{
public:
    std::string showOutput(std::string out);
};