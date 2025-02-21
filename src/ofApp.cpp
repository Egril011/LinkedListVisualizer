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

	ofSetBackgroundColor(0);
}
//--------------------------------------------------------------
void ofApp::update(){
	
//Pour pas que la camera va trop à gauche pour rien
	if (cameraX < 0) {
		cam.setPosition(0, 0, 500);
		cameraX = 0;
	}
	else {
		cam.setPosition(cameraX, 0, 500);
	}

	oscillationTime = ofGetElapsedTimef();
}
//--------------------------------------------------------------
void ofApp::draw() {
	Node* newNode = llist.head;
	float xPos = 100.f;
	
	cam.begin();

	while (newNode) {
		
		//Aide du cours 
		oscillation = sin(oscillationTime * 2 + xPos) * oscillationSpeed;

		//Pour Dessiner la circumference du nombre de la linkedList
		ofSetColor(255);
		ofDrawCircle(xPos, 100 + oscillation, newNode->data);

		//Pour Dessiner le nombre de la linkedList
		ofSetColor(0);
		ofDrawBitmapString(newNode->data, xPos, 100 + oscillation);

		if (newNode->next) {
			
			//Pour dessiner les lignes qui oscille
			ofSetColor(255);
			
			float nextOscillation = sin(oscillationTime * 2 + (xPos + 200)) * oscillationSpeed;
			ofDrawArrow(glm::vec3(xPos, 100 + oscillation, 0), 
				glm::vec3((xPos + 200), 100 + nextOscillation, 0));

			//Agmenter xPos
			xPos += 200.f;
		}

		//Aller à la prochaine Node
		newNode = newNode->next;
	}

	//Informations du programme 
	ofSetColor(255);
	string text = "Informations:\n"
		"\"q\" Pour pour insérer un noeud au début\n"
		"\"w\" Pour insérer un noeud à la fin\n"
		"\"a\" Pour supprimer le noeud en tete\n"
		"\"s\" Pour supprimer le noeud en queue\n"
		"\"e\" Pour trier la linkedList\n"
		"\"z\" Pour augmenter l'oscillation\n"
		"\"x\" Pour diminuer l'oscillation\n"
		"\"->\" Pour bouger la caméra à gauche\n"
		"\"<-\" Pour bouger la caméra à droite\n"
		"\t Le programme à exécuté: " + executed;
	ofDrawBitmapString(text, cameraX - 300, -150);

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {

		//Insérer à la tête
		case 'q':
			executed = "Insérer un noeud au début";
			llist.insertAtHead(10 + std::rand() % 91);
			break;

		//Insérer à la queue
		case 'w':
			executed = "Insérer un noeud à la fin";
			llist.insertAtTail(10 + std::rand() % 91);
			break;
		
		//Enlever la tête
		case 'a':
			executed = "Supprimer le noeud en tete";
			llist.deleteHead();
			break;

		//Enlever la queue
		case 's':
			executed = "Supprimer le noeud à la fin";
			llist.deleteTail();
			break;

		//Augmenter l'oscillation
		case 'z':
			executed = "Augmenter l'oscillation";
			increaseOscillation();
			break;

		//Diminuer l'oscillation
		case 'x':
			executed = "Diminuer l'oscillation";
			decreaseOscillation();
			break;

		//Trier la linkedList
		case 'e':
			executed = "Trier la linkedList";
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
	oscillationSpeed += 20;
}
//-------------------------------------------------------------
//Pour diminuer l'oscillation
void ofApp::decreaseOscillation() {

	if (oscillationSpeed == 0) {
		oscillationSpeed == 0;
	}
	else {
		oscillationSpeed -= 20;
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