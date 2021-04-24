#include "classes.h"

#include <iostream>

// Node

LinkedList::ListNode::ListNode(TItem value) :
        value(std::move(value)),
        next(nullptr) {}

LinkedList::ListNode::~ListNode() {
    delete next;
}

// Iterator
typedef LinkedList::Iterator Iterator;

LinkedList::Iterator::Iterator() :
    current(nullptr) {}

LinkedList::Iterator::Iterator(LinkedList::ListNode *current) :
    current(current) {}

TItem Iterator::operator*() const {
    throwIfNull();

    return current->value;
}

Iterator& Iterator::operator ++() {
    throwIfNull();

    current = current->next;
    return *this;
}

Iterator Iterator::operator ++(int) {
    throwIfNull();

    const Iterator temp(current);
    current = current->next;
    return temp;
}

bool Iterator::operator ==(const Iterator& r) const {
    return current == r.current;
}

bool Iterator::operator !=(const Iterator& r) const {
    return current != r.current;
}

void Iterator::throwIfNull() const {
    if(current == nullptr)
        throw std::out_of_range("Iterator error");
}

// List

LinkedList::LinkedList() :
        head(nullptr),
        tail(nullptr) {}

LinkedList::~LinkedList() {
    delete head;
}

void LinkedList::push_back(const TItem &item) {
    auto newNode = new ListNode(item);

    if(tail == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

void LinkedList::clear() {
    delete head;

    head = tail = nullptr;
}

Iterator LinkedList::begin() const {
    return Iterator(head);
}

Iterator LinkedList::end() const {
    return Iterator();
}

std::istream &operator >>(std::istream& stream, LinkedList& list) {
    TItem item;

    while (stream >> item)
        list.push_back(item);

    return stream;
}

std::ostream& operator <<(std::ostream& stream, const LinkedList& list) {
    if(&stream == &std::cout) {
        stream << '<';

        auto iter = list.begin();
        if(iter != list.end()) {
            stream << *iter;
            ++iter;
        }

        for(; iter != list.end(); ++iter) {
            stream << ", " << *iter;
        }

        stream << '>';

        return stream;
    }

    for(auto item : list)
        stream << item << ' ';

    return stream;
}
