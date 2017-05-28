#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "ofxTiming.h"

class FaceOverlay {
private:
    static void drawCurve(const ofPolyline& polyline) {
        if(polyline.size() == 0) {
            return;
        }
        ofBeginShape();
        const vector<ofVec3f>& vertices = polyline.getVertices();
        ofCurveVertex(vertices.front().x, vertices.front().y);
        for(int i = 0; i < vertices.size(); i++) {
            ofCurveVertex(vertices[i].x, vertices[i].y);
        }
        ofCurveVertex(vertices.back().x, vertices.back().y);
        ofEndShape();
    }
    
public:
    FaceOverlay()
    {
        
    }
    void draw(ofxFaceTracker& tracker) {
        
        ofFill();
        ofSetColor(255, 0, 0);
        
//        vector<ofVec3f> points[2];
//        points[0] = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE).getVertices();
//        points[1] = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE).getVertices();
//        
//        for(int i = 0; i < 2; i++)
//        {
//            ofBeginShape();
//        
//            for(int j = 0; j < points[i].size(); j++)
//            {
//                ofVertex(points[i].at(j));
//            }
//            
//            ofEndShape();
//        }
        
//        ofSetColor(0);
        drawCurve(tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE));
        drawCurve(tracker.getImageFeature(ofxFaceTracker::LEFT_EYE));
    }
};
