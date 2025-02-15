#include "ofApp.h"
#include "cstdlib"
#include "ctime"

//--------------------------------------------------------------
void ofApp::setup() {
	std::srand(time(0));

	//Utilisation de internet pour les aspect de camera pour la faire bouger de gauche à droit
	//https://openframeworks.cc///documentation/3d/ofCamera/
	cam.setPosition(cameraX, 0, 0);
	cam.lookAt(glm::vec3(0, 0, 0));
}
//--------------------------------------------------------------
void ofApp::update(){
	cam.setPosition(cameraX, 0, 500);
}
// Implement the linked list sorting function
//--------------------------------------------------------------
void ofApp::draw() {
	node* newNode = llist.head;
	float xPos = 100.f;

	cam.begin();

	while (newNode) {

		//Pour Dessiner la circumference du nombre de la linkedList
		ofSetColor(255);
		ofDrawCircle(xPos, 100, newNode->data);

		//Pour Dessiner le nombre de la linkedList
		ofSetColor(0);
		ofDrawBitmapString(newNode->data, xPos, 100);

		if (newNode->next) {
			
			//Ai pour cette section (oscillation)
			//---------------------------------------------------//
			float time = ofGetElapsedTimef();
			float oscillation = sin(time * 2.0) * speedOscillation;  
			//---------------------------------------------------//

			ofDrawArrow(glm::vec3(xPos + newNode->data, oscillation + 100, 0),
				glm::vec3((xPos + 200) - newNode->next->data, 100, 0));
		}

		//Changer de Node et agmenter xPos
		xPos += 200.f;
		newNode = newNode->next;
	}

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {

		case 'q': 
			llist.insertAtHead(10 + std::rand() % 91);
			break;

		case 'w':
			llist.insertAtTail(10 + std::rand() % 91);
			break;
		
		case 'a':
			llist.deleteHead();
			break;

		case 's':
			llist.deleteTail();
			break;

		case 'z':
			increaseOscillation();
			break;

		case 'x':
			decreaseOscillation();
			break;

		case OF_KEY_LEFT:
			cameraX -= 20;
			break;

		case OF_KEY_RIGHT:
			cameraX += 20;
			break;

		default:
			break;
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
//----------------------------------------------------------------
//Pour supprimer la head de la linkedList 
void linkedList::deleteHead() {

	if (head == nullptr) {
		return;
	}

	node* temp = head;
	head = head->next;
	delete temp;
}
//---------------------------------------------------------------
//Pour surpprimer la Tail de la linkedList
void linkedList::deleteTail() {

	//s'il n'y pas de head encore 
	if (head == nullptr) {
		return;
	}

	//si le prochain est nullptr supprimer la head
	if (head->next == nullptr) {
		delete head;
		head = nullptr;
		return;
	}

	node* temp = head;
	while (temp->next->next != nullptr) {
		temp = temp->next;
	}

	temp->next = temp->next->next;
}
//--------------------------------------------------------------
//Pour augmenter l'ocsillation
void ofApp::increaseOscillation() {
	speedOscillation += 20;
}
//-------------------------------------------------------------
//Pour diminuer l'oscillation
void ofApp::decreaseOscillation() {

	if (speedOscillation == 10) {
		speedOscillation == 10;
	}
	else {
		speedOscillation -= 20;
	}
}
//-------------------------------------------------------------
