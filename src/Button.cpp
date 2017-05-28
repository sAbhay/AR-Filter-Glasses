//
//  button.cpp
//  Blackjack
//
//  Created by Abhay Singhal on 5/5/17.
//
//

#include "button.hpp"

Button::Button()
{

}

Button::Button(float x, float y, float s, string i, bool stateB, bool startState)
{
    pos = ofVec2f(x, y);
    size = s;

    ofLoadImage(img, i);
    
    img.resize(size, size);
    
    stateButton = stateB;
    on = startState;
}

Button::~Button()
{
    
}

void Button::display()
{
    if(!hidden)
    {
        ofFill();
        ofSetColor(255);
        ofDrawCircle(pos.x, pos.y, size * 1.1);
    
        ofSetColor(175);
        ofDrawCircle(pos.x, pos.y, size);

        img.draw(pos.x-size/2, pos.y-size/2);
    
        if(!on && stateButton)
        {
            ofPushMatrix();
            ofTranslate(pos.x, pos.y);
            ofRotate(45);
            ofSetLineWidth(3);
            ofSetColor(255);
            ofDrawLine(0, -size, 0, size);
            ofPopMatrix();
        }
    }
}

bool Button::isPressed(int x, int y)
{
    if(ofDist(x, y, pos.x, pos.y) < size)
    {
        return true;
    }
    
    return false;
}
