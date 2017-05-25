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
private:
    ofVec2f pos;
    ofVec2f dimensions;
    string text;
    
public:
    Button();
    Button(float x, float y, float h, string t);
    ~Button();
    
    void display();
    
    bool isPressed(int x, int y);
};

#endif /* button_hpp */
