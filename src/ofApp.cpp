#include "ofApp.h"
#include "cstdlib"
#include "ctime"

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

		void insertAtHead(int value);
		void insertAtTail(int value);
		void deleteHead();
		void deleteTail();
};

linkedList llist;

//--------------------------------------------------------------
void ofApp::setup() {
}

//--------------------------------------------------------------
void ofApp::update(){


}

//--------------------------------------------------------------
void ofApp::draw(){
	node* newNode = llist.head;
	float xPos = 100.f;

	while (newNode) {
		
		//Pour imprimer les Nodes
		ofSetColor(255);
		ofDrawCircle(xPos, 200, newNode->data);
		
		//Pour imprime le nombre des Nodes
		ofSetColor(0);
		ofDrawBitmapString(newNode->data, xPos, 200);

		//Changer de Node et agmenter le xPos
		newNode = newNode->next;
		xPos += 200.f;
	}	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	std::srand(time(0));

	if (key == 'q') {
		llist.insertAtHead(10 + std::rand() % 91 );
	}

	if (key == 'w') {
		llist.insertAtTail(10 + std::rand() % 91);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
//Pour inserer un nombre a la head de la linkedList
void linkedList::insertAtHead(int value) {
	node* newNode = new node(value);

	if (head == nullptr) {
		head = newNode;
		return;
	}

	newNode->next = head;
	head = newNode;
	
}
//----------------------------------------------------------------
//Pour inserer un nombre a la Tail de la linkedList
void linkedList::insertAtTail(int value) {
	
	node* newNode = new node(value);
	if (head == nullptr) {
		head = newNode;
		return;
	}

	node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}

	temp->next = newNode;
}