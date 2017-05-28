#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "ofxFaceTracker.h"
#include "FaceOverlay.h"

#include "ofxFilterLibrary.h"

#include "button.hpp"
#include "numberButton.hpp"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    
private:
    int                         _currentFilter;
    vector<AbstractFilter *>    _filters;
    
    ofVideoGrabber cam;
    ofxFaceTracker tracker;
    FaceOverlay overlay;
    
    bool filtersOn = false;
    bool trackerOn = false;
    bool drawVideo = true;
    
    ofImage img;
    Button b[4]; //to active/deactive filters, face filters, camera, and take a picture
    vector<NumberButton> fb; //filter buttons
    
    float scrollX[2];
};
