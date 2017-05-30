#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "ofxFaceTracker.h"
#include "FaceOverlay.hpp"

#include "ofxFilterLibrary.h"

#include "button.hpp"
#include "SetButton.hpp"

#include "faceFeature.hpp"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
    void mouseReleased(int x, int y, int button);
    
private:
    int _currentFilter;
    vector<AbstractFilter*> _filters;
    
    ofVideoGrabber cam;
    ofxFaceTracker tracker;
    FaceOverlay overlay;
    
    bool filtersOn = false;
    bool trackerOn = false;
    bool drawVideo = true;
    
    ofImage img;
    Button b[4]; //to active/deactive filters, face filters, camera, and take a picture
    vector<SetButton> fb; //filter buttons
    
    float scrollX;
    bool picture;
    
    void takeScreenshot();
    
    FaceFeature ff[8]; // 0 outline, 1-2 right and left eye, 3 - outer mouth, 4 - inner mouth, 5 - nose, 6-7 right and left eyebrow
    
    bool ffSelect[8];
    bool fffSelect;
    void console(int i);
    
    Button ffButton[8];
    SetButton ffb[8];
    
    Button done;

    int fffindex;
    int index = -10;
    
    bool consoleDrawing = false;
};
