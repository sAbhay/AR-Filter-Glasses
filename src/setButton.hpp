//
//  SetButton.hpp
//  Filter Goggles
//
//  Created by Abhay Singhal on 5/28/17.
//
//

#ifndef SetButton_hpp
#define SetButton_hpp

#include <stdio.h>
#include "button.hpp"

class SetButton: public Button
{
    private:
        int num;
        string name;
        bool c;
    
        ofVec2f initPos;
    
    public:
        SetButton();
        SetButton(float x, float y, float s, string i, int n, string Name);
        SetButton(float x, float y, float s, string i, bool l, string Name);
    
        int getNumber(){return num;}
        bool change(){return c;}
    
        void display2();
        void resetPos(){pos = initPos;};
};

#endif /* SetButton_hpp */
