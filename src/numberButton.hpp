//
//  numberButton.hpp
//  Filter Goggles
//
//  Created by Abhay Singhal on 5/28/17.
//
//

#ifndef numberButton_hpp
#define numberButton_hpp

#include <stdio.h>
#include "button.hpp"

class NumberButton: public Button
{
    private:
        int num;
        string name;
    
    public:
        NumberButton();
        NumberButton(float x, float y, float s, string i, int n, string Name);
    
        int getNumber(){return num;}
    
        void display2();
};

#endif /* numberButton_hpp */
