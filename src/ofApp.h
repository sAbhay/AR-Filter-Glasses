#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "ofxFaceTracker.h"
#include "FaceOverlay.h"

#include "ofxFilterLibrary.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
    
private:
    int                         _currentFilter;
    vector<AbstractFilter *>    _filters;
    
    ofVideoGrabber cam;
    ofxFaceTracker tracker;
    FaceOverlay overlay;
    
    bool filtersOn = true;
    
    ofImage img;
};
