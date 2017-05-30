//
//  feature.hpp
//  Filter Goggles
//
//  Created by Abhay Singhal on 5/30/17.
//
//

#ifndef faceFeature_hpp
#define faceFeature_hpp

#include <stdio.h>

#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "ofxTiming.h"
#include "ofxFilterLibrary.h"

class FaceFeature {
private:
    
    AbstractFilter* filter;
    ofColor colour;
    ofxFaceTracker::Feature feature;
    
    static void drawCurve(const ofPolyline& polyline);
    
    int index;
    
public:
    FaceFeature();
    FaceFeature(ofxFaceTracker::Feature f, int i);
    ~FaceFeature();
    
    void draw(ofxFaceTracker& tracker);
    
    ofColor getColor(){return colour;}
    void setColor(ofColor c){colour = c;}
    
    void setFilter(AbstractFilter* f){filter = f;}
    AbstractFilter* getFilter(){return filter;}
    
    ofxFaceTracker::Feature getFeature(){return feature;}
    
    int getIndex(){return index;}
};


#endif /* faceFeature_hpp */
