//
//  button.hpp
//  Blackjack
//
//  Created by Abhay Singhal on 5/5/17.
//
//

#ifndef button_hpp
#define button_hpp

#include <stdio.h>
#include "ofMain.h"

class Button
{
protected:
    ofVec2f pos;
    float size;
    ofImage img;
    bool hidden = false;
    bool on;
    bool stateButton;
    
public:
    Button();
    Button(float x, float y, float s, string i, bool stateB, bool startState);
    ~Button();
    
    void display();
    
    bool isPressed(int x, int y);
    void setState(bool s){ on = s;}
    
    void setHidden(bool h) {hidden = h;}
    void setPos(ofVec2f p){pos = p;};
    ofVec2f getPos(){return pos;}
};

#endif /* button_hpp */
