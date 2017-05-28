//
//  numberButton.cpp
//  Filter Goggles
//
//  Created by Abhay Singhal on 5/28/17.
//
//

#include "numberButton.hpp"

NumberButton::NumberButton()
{
    
}

NumberButton::NumberButton(float x, float y, float s, string i, int n, string Name)
{
    pos = ofVec2f(x, y);
    size = s;
    
    ofLoadImage(img, i);
    
    img.resize(size, size);
    
    stateButton = false;
    num = n;
    name = Name;
}

void NumberButton::display2()
{
    display();
    
    ofDrawBitmapString(name, pos.x-size/1.5, pos.y + 1.75*size + (num % 2)*size/1.5);
}
