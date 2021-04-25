#ifndef LAB_2_4_CLASSES_H
#define LAB_2_4_CLASSES_H

#include <iostream>

template<class TItem>
class LinkedList {
private:
    struct ListNode {
        TItem value;
        ListNode* next;

        explicit ListNode(TItem value);
        ~ListNode();
    };

    ListNode* head;
    ListNode* tail;

public:
    // Create empty list
    LinkedList();

    ~LinkedList();

    // Add element to end of the list
    void push_back(const TItem& item);

    // Remove all items from the list
    void clear();

    class Iterator {
    public:
        Iterator();
        explicit Iterator(ListNode* current);
        TItem operator *() const;
        Iterator& operator ++();
        Iterator operator ++(int);
        bool operator ==(const Iterator& r) const;
        bool operator !=(const Iterator& r) const;

    private:
        ListNode* current;

        void throwIfNull() const;
    };

    [[nodiscard]] Iterator begin() const;
    [[nodiscard]] Iterator end() const;
};

template<class TItem>
std::istream& operator >>(std::istream& stream, LinkedList<TItem>& list);

template<class TItem>
std::ostream& operator <<(std::ostream& stream, const LinkedList<TItem>& list);

#endif //LAB_2_4_CLASSES_H
