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
    pos = dimensions = ofVec2f(0, 0);
    text = "";
}

Button::Button(float x, float y, float h, string t)
{
    pos = ofVec2f(x, y);
    dimensions = ofVec2f(0, h);
    text = t;
    
    dimensions.x = text.length() * 20*ofGetWidth()/1024;
    
    pos.x -= dimensions.x/2;
    pos.y -= dimensions.y/2;
}

Button::~Button()
{
    
}

void Button::display()
{
    ofFill();
    ofSetColor(128);
    ofDrawRectangle(pos.x, pos.y, dimensions.x, dimensions.y);
    
    ofSetColor(255);
    ofDrawBitmapString(text, pos.x + dimensions.x/2 - dimensions.x/text.length()/1.5, pos.y + dimensions.y/2);
}

bool Button::isPressed(int x, int y)
{
    if(x >= pos.x && x <= pos.x + dimensions.x && y >= pos.y && y <= pos.y + dimensions.y)
    {
        return true;
    }
    
    return false;
}
