//
//  SetButton.cpp
//  Filter Goggles
//
//  Created by Abhay Singhal on 5/28/17.
//
//

#include "setButton.hpp"

SetButton::SetButton()
{
    
}

SetButton::SetButton(float x, float y, float s, string i, int n, string Name)
{
    pos = initPos = ofVec2f(x, y);
    size = s;
    
    ofLoadImage(img, i);
    
    img.resize(size, size);
    
    stateButton = false;
    num = n;
    name = Name;
}

SetButton::SetButton(float x, float y, float s, string i, string l, string Name)
{
    pos = ofVec2f(x, y);
    size = s;
    
    ofLoadImage(img, i);
    
    img.resize(size, size);
    
    stateButton = false;
    loc = l;
    name = Name;
}


void SetButton::display2()
{
    display();
    
    ofDrawBitmapString(name, pos.x-size/1.5, pos.y + 1.75*size + (num % 2)*size/1.5);
}
