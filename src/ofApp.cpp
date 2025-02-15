#include "ofApp.h"
#include "cstdlib"
#include "ctime"

//--------------------------------------------------------------
void ofApp::setup() {
	std::srand(time(0));

	//Utilisation d'internet pour les aspects de camera pour la faire bouger de gauche à droit
	//https://openframeworks.cc///documentation/3d/ofCamera/
	cam.setPosition(cameraX, 0, 0);
	cam.lookAt(glm::vec3(0, 0, 0));
}
//--------------------------------------------------------------
void ofApp::update(){
	cam.setPosition(cameraX, 0, 500);
}
//--------------------------------------------------------------
void ofApp::draw() {
	Node* newNode = llist.head;
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

		//Aller à la prochaine Node et agmenter xPos
		xPos += 200.f;
		newNode = newNode->next;
	}

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {

		//Insérer à la tête
		case 'q':
			llist.insertAtHead(10 + std::rand() % 91);
			break;

		//Insérer à la queue
		case 'w':
			llist.insertAtTail(10 + std::rand() % 91);
			break;
		
		//Enlever la tête
		case 'a':
			llist.deleteHead();
			break;

		//Enlever la queue
		case 's':
			llist.deleteTail();
			break;

		//Augmenter l'oscillation
		case 'z':
			increaseOscillation();
			break;

		//Diminuer l'oscillation
		case 'x':
			decreaseOscillation();
			break;

		//Trier la linkedList
		case 'e':
			llist.head = mergeSort(llist.head);
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
//Pour insérer un nombre à la tête de la linkedList
void LinkedList::insertAtHead(int value) {
	Node* newNode = new Node(value);

	if (head == nullptr) {
		head = newNode;
		return;
	}

	newNode->next = head;
	head = newNode;
	
}
//----------------------------------------------------------------
//Pour insérer un nombre a la queue de la linkedList
void LinkedList::insertAtTail(int value) {
	
	Node* newNode = new Node(value);
	if (head == nullptr) {
		head = newNode;
		return;
	}

	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}

	temp->next = newNode;
}
//----------------------------------------------------------------
//Pour supprimer la tête de la linkedList 
void LinkedList::deleteHead() {

	if (head == nullptr) {
		return;
	}

	Node* temp = head;
	head = head->next;
	delete temp;
}
//---------------------------------------------------------------
//Pour surpprimer la queue de la linkedList
void LinkedList::deleteTail() {

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

	Node* temp = head;
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
//Trier la linkedList en ordre croissant 
//Puis utilisation: https://www.geeksforgeeks.org/merge-sort-for-linked-list/
Node* ofApp::split(Node* head) {
	Node* fast = head;
	Node* slow = head;

	while (fast != nullptr && fast->next != nullptr) {
		fast = fast->next->next;
		
		if (fast != nullptr) {
			slow = slow->next;
		}
	}

	Node* temp = slow->next;
	slow->next = nullptr;
	return temp;
}

Node* ofApp::merge(Node* first, Node* second) {
	if(first == nullptr) {
		return second;
	}

	if (second == nullptr) {
		return first;
	}

	if (first->data < second->data) {
		first->next = merge(first->next, second);
		return first;
	}
	else {
		second->next = merge(first, second->next);
		return second;
	}
}

Node* ofApp::mergeSort(Node* head) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	Node* second = split(head);

	head = mergeSort(head);
	second = mergeSort(second);

	return merge(head, second);
}