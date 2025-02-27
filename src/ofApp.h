#pragma once
#include "ofMain.h"

//--------------------------------------------------------------
class Node {
public:
	int data;
	Node* next;

	Node(int value) {
		data = value;
		next = nullptr;
	}
};
//--------------------------------------------------------------
class LinkedList {
public:
	Node* head;

	LinkedList() {
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
		int oscillationSpeed = 0;
		float oscillationTime = 0;
		float oscillation = 0;

		float cameraX = 0.f;
		LinkedList llist;
		ofCamera cam;
		string executed;
		


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

		Node* split(Node* head);
		Node* merge(Node* first, Node* second);
		Node* mergeSort(Node* head);
};
