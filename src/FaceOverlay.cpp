//
//  FaceOverlay.cpp
//  Filter Goggles
//
//  Created by Abhay Singhal on 5/29/17.
//
//

#include "FaceOverlay.hpp"

FaceOverlay::FaceOverlay()
{
    
}

FaceOverlay::~FaceOverlay()
{
    
}

void FaceOverlay::drawCurve(const ofPolyline& polyline)
{
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

void FaceOverlay::draw(ofxFaceTracker& tracker)
{
    ofFill();
    ofSetColor(0);
    drawCurve(tracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE));

    ofFill();
    ofSetColor(255, 0, 0);
    drawCurve(tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE));
    drawCurve(tracker.getImageFeature(ofxFaceTracker::LEFT_EYE));
}

void FaceOverlay::drawFeature(ofxFaceTracker& tracker, ofxFaceTracker::Feature feature, ofColor c)
{
    ofFill();
    ofSetColor(c);
    drawCurve(tracker.getImageFeature(feature));
}

void FaceOverlay::drawFeature(ofxFaceTracker& tracker, ofxFaceTracker::Feature feature, ofColor c, AbstractFilter* filter)
{
    filter -> begin();
    
    drawFeature(tracker, feature, c);
    
    filter -> end();
}
