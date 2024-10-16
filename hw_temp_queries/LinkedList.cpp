# include <iostream>
# include <string>
# include "LinkedList.h"
# include "Node.h"

using namespace std;
using std::string, std::ostream;

LinkedList::LinkedList():head(nullptr), tail(nullptr) /* TODO */ {
	// TODO: implement this function
}

LinkedList::~LinkedList() {
	// TODO: implement this function
	this -> clear();
}

LinkedList::LinkedList(const LinkedList& source):head(nullptr), tail(nullptr) /* TODO */ {
	// TODO: implement this function
	if(source.head == nullptr) {
        return;
    }
    Node* copy = source.head;
    while (copy != nullptr) {
        this->insert(copy->data.id, copy->data.year, copy->data.month, copy->data.temperature);
        copy = copy->next;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	// TODO: implement this function
    if (this != &source) {
        this->clear();
        Node* copy = source.head;
        while (copy != nullptr) {
            this->insert(copy->data.id, copy->data.year, copy->data.month, copy->data.temperature);
            copy = copy->next;
        }
    }
    return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	// TODO: implement this function

	Node* newNode = new Node(location, year, month, temperature);
    Node* cur = head;
    Node* specialNode = head;
    bool foundSpot = false;
    int stepsAwayFromHead = 0;
    while (!foundSpot) {
        if (head == nullptr && tail == nullptr) {
            foundSpot = true;
            newNode->next = nullptr;
            head = newNode;
            tail = newNode;// only node is both head and tail
        }
        else if (newNode->data.operator<(cur->data)) {
            if (cur == head) {
                newNode->next = head;
                head = newNode;
                foundSpot = true;
            }
            else {
                foundSpot = true;
                for (int i = 1; i < stepsAwayFromHead; ++i) {
                    specialNode = specialNode->next;
                }
                newNode->next = specialNode->next;
                specialNode->next = newNode;
            }
        }
        else if (cur->next == nullptr) {
            foundSpot = true;
            newNode->next = nullptr;
            cur->next = newNode;
            tail = newNode;
        }
        else {
            stepsAwayFromHead += 1;
            cur=cur->next;
        }
    }

	/*Node* newNode = new Node(location,year,month,temperature);
	if (head == NULL && tail == NULL) {
		head = newNode;tail = newNode;
	}
	else {
		Node* tempVar = head;
		Node* tempVar2 = nullptr;
		while (tempVar != nullptr) {
			if (*tempVar < *newNode) {
				tempVar2 = tempVar;
				tempVar = tempVar -> next;
			} 
			else {
				if(tempVar2 == nullptr) {
					//firsttempVar2 = newNode;
					head = newNode;
				} 
				else {
					//middletempVar2 -> next = newNode;
				}
				newNode -> next = tempVar;
				return;
			}
		}
	//last
	tempVar2 -> next = newNode;
	tail = newNode;
	}*/
}

void LinkedList::clear() {
	// TODO: implement this function
	while (head != nullptr) {
		Node* tempVar = head -> next;
		delete head;
		head = tempVar;
	}
}

Node* LinkedList::getHead() const {
	// TODO: implement this function, it will be used to help grade other functions
	return head;
}

string LinkedList::print() const {
	string outputString;
	/*ostringstream os;
	// TODO: Implement this function
	Node* curr = head;
	while(curr != nullptr) {
		os << curr -> data.id << " " << curr -> data.year << " " << curr ->
			data.month << " " << curr -> data.temperature << endl;
		curr = curr -> next;
	}

	outputString = os.str();*/
	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	os << ll.print();
	return os;
}
