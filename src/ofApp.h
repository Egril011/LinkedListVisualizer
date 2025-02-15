#pragma once
#include "ofMain.h"

//--------------------------------------------------------------
class node {
public:
	int data;
	node* next;

	node(int value) {
		data = value;
		next = nullptr;
	}
};
//--------------------------------------------------------------
class linkedList {
public:
	node* head;

	linkedList() {
		head = nullptr;
	}

	void insertAtHead(int value);
	void insertAtTail(int value);
	void deleteHead();
	void deleteTail();
};
//----------------------------------------------------------------
class ofApp : public ofBaseApp{

	public:

		int speedOscillation = 10;
		float cameraX = 0.f;
		linkedList llist;
		ofCamera cam;


		void setup();
		void update();
		void draw();


		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void increaseOscillation();
		void decreaseOscillation();
};
