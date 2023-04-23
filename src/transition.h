#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_TRANSITION_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_TRANSITION_H

class transition{
public:
   transition();
   void startFading(float duration);
   void startAppearing(float duration);
   void startDisappearing(float duration);
   void updateOpacity();
   bool isFading;
   bool isAppearing;
   bool isDisappearing;
   float opacity;
   float speed;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_TRANSITION_H
