#include "nativebehavior.h"

NativeBehavior::NativeBehavior(QObject *parent)
    :Behavior(parent)
{
}

void NativeBehavior::update(const int &delta)
{
    if(update_func){
        update_func(delta);
    }
}
