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
    
    static ofPolyline buildCircle(const ofVec2f& center, float radius, int resolution = 32) {
        ofPolyline polyline;
        ofVec2f base(radius, 0);
        for(int i = 0; i < resolution; i++) {
            float angle = 360 * (float) i / resolution;
            ofVec2f cur = center + base.getRotated(angle);
            polyline.addVertex(cur);
        }
        polyline.close();
        return polyline;
    }
    
    static float determinant(const ofVec2f& start, const ofVec2f& end, const ofVec2f& point) {
        return (end.x - start.x) * (point.y - start.y) - (end.y - start.y) * (point.x - start.x);
    }
    
    static void divide(const ofVec2f& a, const ofVec2f& b,
                const ofVec2f& left, const ofVec2f& right,
                ofMesh& top, ofMesh& bottom) {
        ofVec2f avg = a.getInterpolated(b, 0.5);
        if(determinant(left, right, avg) < 0) {
            top.addVertex(a);
            top.addVertex(b);
        } else {
            bottom.addVertex(a);
            bottom.addVertex(b);
        }
    }
    
    static void divide(const ofPolyline& poly,
                const ofVec2f& left, const ofVec2f& right,
                ofMesh& top, ofMesh& bottom) {
        top.setMode(OF_PRIMITIVE_LINES);
        bottom.setMode(OF_PRIMITIVE_LINES);
        const vector<ofVec3f>& vertices = poly.getVertices();
        for(int i = 0; i + 1 < vertices.size(); i++) {
            divide(vertices[i], vertices[i + 1], left, right, top, bottom);
        }
        if(poly.isClosed()) {
            divide(vertices.back(), vertices.front(), left, right, top, bottom);
        }
    }
    
public:
    Hysteresis noseHysteresis, mouthHysteresis;
    float noseAngle = 15;
    float nostrilWidth = .06;
    float lipWidth = .7;
    
    FaceOverlay() {
        noseHysteresis.setDelay(1000);
        mouthHysteresis.setDelay(1000);
    }
    void draw(ofxFaceTracker& tracker) {
        
        ofFill();
        ofSetColor(255, 0, 0);
        
        ofBeginShape();
        
        vector<ofVec3f> points = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE).getVertices();
        
        for(int i = 0; i < points.size(); i++)
        {
            ofVertex(points.at(i));
        }
        
        ofEndShape();
        
//        ofSetColor(0);
        drawCurve(tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE));
    }
};
