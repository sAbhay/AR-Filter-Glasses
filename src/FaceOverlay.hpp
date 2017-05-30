//
//  FaceOverlay.hpp
//  Filter Goggles
//
//  Created by Abhay Singhal on 5/29/17.
//
//

#ifndef FaceOverlay_hpp
#define FaceOverlay_hpp

#include <stdio.h>

#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "ofxTiming.h"
#include "ofxFilterLibrary.h"

class FaceOverlay {
private:
    
    vector<ofImage> img;
    
    static void drawCurve(const ofPolyline& polyline);
    
public:
    FaceOverlay();
    ~FaceOverlay();
    
    void draw(ofxFaceTracker& tracker);
    void drawFeature(ofxFaceTracker& tracker, ofxFaceTracker::Feature feature, ofColor c);
    void drawFeature(ofxFaceTracker& tracker, ofxFaceTracker::Feature feature, ofColor c, AbstractFilter* filter);
};


#endif /* FaceOverlay_hpp */
