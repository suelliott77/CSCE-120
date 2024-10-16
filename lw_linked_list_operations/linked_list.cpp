# include "linked_list.h"
# include <iostream>
# include <string>

using std::cout, std::endl, std::string, std::ostream;

void MyList::add(const std::string& name, int score) {
    // TODO
    //create the node from parameters
    //create object node of type MyNode
    MyNode* node = new MyNode(name, score);
    //if linked list is empty then make node the head
    if (empty()) {
        _head = node;
        //since the node is the only thing in the list it will also be the tail
        _tail = node;
        //node previous and node next to null ptr
        node->prev = nullptr;
        node->next = nullptr;
        }
        //else have tail point to node
        else {
            // make the next tail point to node
            _tail->next = node;
            //update all other pointers as well
            node->prev = _tail;
            node->next = nullptr;
            //update tail to be node
            _tail = node;
        }
        //increase list size
        _size++;
}


void MyList::clear() {
    // TODO
    /*_tail = nullptr;
    //create helper 
    MyNode* marker = nullptr;
    //traverse through linked list while head is not null
    while(!empty()) {
        //update the head node
        marker = _head;
        _head = _head->next;
        //remove prior head nodedelete marker;
    }
    //set all used pointers to null
    _head = nullptr;
    _tail = nullptr;
    marker = nullptr;
    //set size to zero
    _size = 0;*/
    
    MyNode* currNode = _head;
    while(_head != NULL) {
        currNode = _head;
        _head = _head->next;
        //currNode->next = NULL;
        delete currNode;
        --_size;
    }
    currNode = NULL;
    _head = NULL;
    _tail = NULL;
    _size = 0;
}

bool MyList::remove(const std::string& name) {
    // TODO

    return false;
}

bool MyList::insert(const std::string& name, int score, size_t index) {
    // TODO

    return false;
}

MyList::MyList() : _size(0), _head(nullptr), _tail(nullptr) {}

MyList::~MyList() {
    clear();
}

size_t MyList::size() const {
    return _size;
}

bool MyList::empty() const {
    return _head == nullptr;
}

MyNode* MyList::head() const {
    return _head;
}

ostream& operator<<(ostream& os, const MyList& myList) {
    MyNode* _current = myList.head();
    if (_current == nullptr) {
        os << "<empty>" << endl;
        return os;
    }

    os << "[ " << _current->name << ", " << _current->score << " ]";
    _current = _current->next;
    while (_current != nullptr) {
        os << " --> [ " << _current->name << ", " << _current->score << " ]";
        _current = _current->next;
    }
    
    return os;
}

MyNode::MyNode(const std::string& name, int score) : name{name}, score{score}, next{nullptr}, prev{nullptr} {}
