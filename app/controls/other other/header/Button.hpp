#include "Control.hpp"

class Button : public Control<void (*)()>
{
public:
    std::thread button_thread;
    // void (*onClick)();
    Button(const std::string &text, int size);

    void setPosition(float x, float y);

    void click();
    void setOnClick(void (*func)());

private:
    void run();
};