#include "classes.h"

#include <iostream>

// Node

template<class TItem>
LinkedList<TItem>::ListNode::ListNode(TItem value) :
        value(std::move(value)),
        next(nullptr) {}

template<class TItem>
LinkedList<TItem>::ListNode::~ListNode() {
    delete next;
}

// Iterator

template<class TItem>
LinkedList<TItem>::Iterator::Iterator() :
    current(nullptr) {}

template<class TItem>
LinkedList<TItem>::Iterator::Iterator(LinkedList::ListNode *current) :
    current(current) {}

template<class TItem>
TItem LinkedList<TItem>::Iterator::operator*() const {
    throwIfNull();

    return current->value;
}

template<class TItem>
typename LinkedList<TItem>::Iterator& LinkedList<TItem>::Iterator::operator ++() {
    throwIfNull();

    current = current->next;
    return *this;
}

template<class TItem>
typename LinkedList<TItem>::Iterator LinkedList<TItem>::Iterator::operator ++(int) {
    throwIfNull();

    const Iterator temp(current);
    current = current->next;
    return temp;
}

template<class TItem>
bool LinkedList<TItem>::Iterator::operator ==(const Iterator& r) const {
    return current == r.current;
}

template<class TItem>
bool LinkedList<TItem>::Iterator::operator !=(const Iterator& r) const {
    return current != r.current;
}

template<class TItem>
void LinkedList<TItem>::Iterator::throwIfNull() const {
    if(current == nullptr)
        throw std::out_of_range("Iterator error");
}

// List

template<class TItem>
LinkedList<TItem>::LinkedList() :
        head(nullptr),
        tail(nullptr) {}

template<class TItem>
LinkedList<TItem>::~LinkedList() {
    delete head;
}

template<class TItem>
void LinkedList<TItem>::push_back(const TItem &item) {
    auto newNode = new ListNode(item);

    if(tail == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}


template<class TItem>
void LinkedList<TItem>::clear() {
    delete head;

    head = tail = nullptr;
}

template<class TItem>
typename LinkedList<TItem>::Iterator LinkedList<TItem>::begin() const {
    return Iterator(head);
}

template<class TItem>
typename LinkedList<TItem>::Iterator LinkedList<TItem>::end() const {
    return Iterator();
}

template<class TItem>
std::istream &operator >>(std::istream& stream, LinkedList<TItem>& list) {
    TItem item;

    while (stream >> item)
        list.push_back(item);

    return stream;
}

template<class TItem>
std::ostream& operator <<(std::ostream& stream, const LinkedList<TItem>& list) {
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
