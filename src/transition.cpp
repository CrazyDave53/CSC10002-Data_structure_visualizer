#include "transition.h"

transition::transition() :
    isFading(),
    opacity(),
    speed(),
    isAppearing()
{
}

void transition::startFading(float duration) {
    opacity = 255;
    isFading = true;
    speed = 255.0/duration*1000/60;
}

void transition::updateOpacity() {
    if(!isFading && !isAppearing)
        return;
    if(isFading){
        opacity -= speed;
        if(opacity<=0){
            opacity = 0;
            isFading = false;
        }
    }
    if(isAppearing){
        opacity += speed;
        if(opacity>=255){
            opacity = 255;
            isAppearing = false;
        }
    }
}

void transition::startAppearing(float duration) {
    opacity = 0;
    isAppearing = true;
    speed = 255.0/duration*1000/60;
}
