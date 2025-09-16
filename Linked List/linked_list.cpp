# include "linked_list.h"
# include <iostream>
# include <string>

using std::cout, std::endl, std::string, std::ostream;

void MyList::add(const std::string& name, int score) {
    // TODO
    MyNode* node = new MyNode(name, score); // Create a new node

    if (_head == nullptr && _tail == nullptr) { // If empty
        _head = node;
        _tail = node;
        _size += 1;
        return;
    }

    _size += 1; // Update size of list

    MyNode* old_tail = _tail;
    old_tail->next = node;
    node->prev = old_tail; // Prev pointer
    _tail = node; // New tail node
    

}

void MyList::clear() {
    // TODO
    MyNode* next_node;
    while(_head) {
        next_node = _head->next; // Temp node pointing to next
        delete _head; // Delete head

        _head = next_node; // Set head
        _size -= 1; // Decrease size
        
    }
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
