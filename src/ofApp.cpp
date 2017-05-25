#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup()
{
    ofDisableArbTex();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    cam.initGrabber(1280, 720);
    
    ofBackground(0);
	tracker.setup();
    tracker.reset();
    _currentFilter = 0;
    
    // here's a simple filter chain
    
    FilterChain * charcoal = new FilterChain(cam.getWidth(), cam.getHeight(), "Charcoal");
    charcoal->addFilter(new BilateralFilter(cam.getWidth(), cam.getHeight(), 4, 4));
    charcoal->addFilter(new GaussianBlurFilter(cam.getWidth(), cam.getHeight(), 2.f ));
    charcoal->addFilter(new DoGFilter(cam.getWidth(), cam.getHeight(), 12, 1.2, 8, 0.99, 4));
    _filters.push_back(charcoal);
    
    // Basic filter examples
    
    _filters.push_back(new HalftoneFilter(cam.getWidth(), cam.getHeight(), 0.01));
    _filters.push_back(new CrosshatchFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new KuwaharaFilter(6));
    _filters.push_back(new SobelEdgeDetectionFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new BilateralFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new SketchFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new DilationFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new PerlinPixellationFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new XYDerivativeFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new ZoomBlurFilter());
    _filters.push_back(new EmbossFilter(cam.getWidth(), cam.getHeight(), 2.f));
    _filters.push_back(new SmoothToonFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new TiltShiftFilter(cam.getTexture()));
    _filters.push_back(new VoronoiFilter(cam.getTexture()));
    _filters.push_back(new CGAColorspaceFilter());
    _filters.push_back(new ErosionFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new LookupFilter(cam.getWidth(), cam.getHeight(), "img/lookup_amatorka.png"));
    _filters.push_back(new LookupFilter(cam.getWidth(), cam.getHeight(), "img/lookup_miss_etikate.png"));
    _filters.push_back(new LookupFilter(cam.getWidth(), cam.getHeight(), "img/lookup_soft_elegance_1.png"));
    _filters.push_back(new VignetteFilter());
    _filters.push_back(new PosterizeFilter(8));
    _filters.push_back(new LaplacianFilter(cam.getWidth(), cam.getHeight(), ofVec2f(1, 1)));
    _filters.push_back(new PixelateFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new HarrisCornerDetectionFilter(cam.getTexture()));
    _filters.push_back(new MotionDetectionFilter(cam.getTexture()));
    _filters.push_back(new LowPassFilter(cam.getWidth(), cam.getHeight(), 0.9));
    
    // blending examples
    
    ofImage wes = ofImage("img/wes.jpg");
    ChromaKeyBlendFilter * chroma = new ChromaKeyBlendFilter(ofVec3f(0.f, 1.f, 0.f), 0.4);
    chroma->setSecondTexture(wes.getTexture());
    _filters.push_back(chroma);
    
    _filters.push_back(new DisplacementFilter("img/mandel.jpg", cam.getWidth(), cam.getHeight(), 25.f));
    _filters.push_back(new PoissonBlendFilter(wes.getTexture(), cam.getWidth(), cam.getHeight(), 2.0));
    _filters.push_back(new DisplacementFilter("img/glass/3.jpg", cam.getWidth(), cam.getHeight(), 200.0));
    _filters.push_back(new DisplacementFilter("img/mesh.png", cam.getWidth(), cam.getHeight(), 100.0));
    _filters.push_back(new ExclusionBlendFilter(wes.getTexture()));
    
    
    
    // here's how you use Convolution filters
    
    Abstract3x3ConvolutionFilter * convolutionFilter1 = new Abstract3x3ConvolutionFilter(cam.getWidth(), cam.getHeight());
    convolutionFilter1->setMatrix(-1, 0, 1, -2, 0, 2, -1, 0, 1);
    _filters.push_back(convolutionFilter1);
    
    Abstract3x3ConvolutionFilter * convolutionFilter2 = new Abstract3x3ConvolutionFilter(cam.getWidth(), cam.getHeight());
    convolutionFilter2->setMatrix(4, 4, 4, 4, -32, 4, 4,  4, 4);
    _filters.push_back(convolutionFilter2);
    
    Abstract3x3ConvolutionFilter * convolutionFilter3 = new Abstract3x3ConvolutionFilter(cam.getWidth(), cam.getHeight());
    convolutionFilter3->setMatrix(1.2,  1.2, 1.2, 1.2, -9.0, 1.2, 1.2,  1.2, 1.2);
    _filters.push_back(convolutionFilter3);
    
    
    // and here's how you might daisy-chain a bunch of filters
    
    FilterChain * foggyTexturedGlassChain = new FilterChain(cam.getWidth(), cam.getHeight(), "Weird Glass");
    foggyTexturedGlassChain->addFilter(new PerlinPixellationFilter(cam.getWidth(), cam.getHeight(), 13.f));
    foggyTexturedGlassChain->addFilter(new EmbossFilter(cam.getWidth(), cam.getHeight(), 0.5));
    foggyTexturedGlassChain->addFilter(new GaussianBlurFilter(cam.getWidth(), cam.getHeight(), 3.f));
    _filters.push_back(foggyTexturedGlassChain);
    
    
    // here's another unimaginative filter chain
    
    FilterChain * watercolorChain = new FilterChain(cam.getWidth(), cam.getHeight(), "Monet");
    watercolorChain->addFilter(new KuwaharaFilter(9));
    watercolorChain->addFilter(new LookupFilter(cam.getWidth(), cam.getHeight(), "img/lookup_miss_etikate.png"));
    watercolorChain->addFilter(new BilateralFilter(cam.getWidth(), cam.getHeight()));
    watercolorChain->addFilter(new PoissonBlendFilter("img/canvas_texture.jpg", cam.getWidth(), cam.getHeight(), 2.0));
    watercolorChain->addFilter(new VignetteFilter());
    _filters.push_back(watercolorChain);
    
    
    // and here's a random gradient map for posterity
    
    vector<GradientMapColorPoint> colors;
    for (float percent=0.0; percent<=1.0; percent+= 0.1)
        colors.push_back( GradientMapColorPoint(ofRandomuf(),ofRandomuf(),ofRandomuf(),percent) );
    _filters.push_back(new GradientMapFilter(colors));
}

void ofApp::update() {
	
    cam.update();
    
    if(!filtersOn)
    {
        if(cam.isFrameNew())
        {
            tracker.update(toCv(cam));
        }
    }
}

void ofApp::draw() {
    ofBackground(0, 0, 0);
    ofSetColor(255);
    ofPushMatrix();
    ofScale(-1, 1);
    ofTranslate(-cam.getWidth(), 0);
    
    if(filtersOn)
    {
        _filters[_currentFilter]->begin();
        cam.draw(0,0);
        _filters[_currentFilter]->end();
        ofPopMatrix();
        ofSetColor(255);
        ofDrawBitmapString( _filters[_currentFilter]->getName() + " Filter\n(Press SPACE to change filters)", ofPoint(40, 20));
    }
    else
    {
        cam.draw(0, 0);
        
        ofPopMatrix();
        ofSetColor(255);
        ofDrawBitmapString("Press 'f' to turn on filters", ofPoint(40, 20));
        
        ofPushStyle();
        ofNoFill();
        ofSetColor(255);
        ofSetLineWidth(1);
        //    tracker.getImageMesh().drawWireframe();
        ofSetLineWidth(2);
        overlay.draw(tracker);
//        tracker.draw(true);
        ofPopStyle();
    }
    
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
}

void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
    
    if (key == OF_KEY_RIGHT) {
        if(filtersOn)
        {
            _currentFilter++;
            if (_currentFilter >= _filters.size()) _currentFilter = 0;
        }
    }
    else if(key == OF_KEY_LEFT)
    {
        if(filtersOn)
        {
            _currentFilter--;
            if (_currentFilter <= 0) _currentFilter = _filters.size() - 1;
        }
    }
    
    else if (key=='f')
    {
        filtersOn = !filtersOn;
    }
}
