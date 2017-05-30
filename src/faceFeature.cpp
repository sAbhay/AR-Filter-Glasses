//
//  feature.cpp
//  Filter Goggles
//
//  Created by Abhay Singhal on 5/30/17.
//
//

#include "faceFeature.hpp"

FaceFeature::FaceFeature()
{
    
}

FaceFeature::FaceFeature(ofxFaceTracker::Feature f, int i)
{
    feature = f;
    colour = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(255));
    filter = NULL;
    
    index = i;
}

FaceFeature::~FaceFeature()
{
    
}

void FaceFeature::drawCurve(const ofPolyline& polyline)
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

void FaceFeature::draw(ofxFaceTracker& tracker)
{
    if(filter != NULL) filter -> begin();
    
    ofFill();
    ofSetColor(colour);
    
    drawCurve(tracker.getImageFeature(feature));

    
    if(feature == ofxFaceTracker::NOSE_BRIDGE)
    {
        ofPolyline line = tracker.getImageFeature(ofxFaceTracker::NOSE_BASE);
        line.addVertex(tracker.getImagePoint(27));
        
        drawCurve(line);
    }
        
    if(filter != NULL) filter -> end();
}
