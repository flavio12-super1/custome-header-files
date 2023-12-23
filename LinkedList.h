#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <ostream>
#include <stdexcept>

// link struct for linked list class
template <class T>
struct Link {
    // struct variables
    T data;
    Link<T> *next;
    Link<T> *prev;

    // default link constructor
    Link() {
        data = 0;
        next = nullptr;
        prev = nullptr;
    }

    // link constructor that takes in a paramter value of T
    Link(T value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

// lineked list class
template <class T>
class LinkedList {
   private:
   public:
    // class variables
    Link<T> *front;
    Link<T> *back;
    int size;

    // default linkedlist constructor
    LinkedList() {
        front = nullptr;
        back = nullptr;
        size = 0;
    }

    // deconstructor
    ~LinkedList() {
        while (front) {
            Link<T> *temp = front;
            front = front->next;

            delete temp;
        }
        back = nullptr;
        size = 0;
    }

    // copy constructor
    LinkedList(const LinkedList<T> &other) {
        front = nullptr;

        // if the other list is empty, return immediately
        if (other.front == nullptr) {
            std::cout << "nothing to copy" << std::endl;
            return;
        }

        Link<T> *curr = other.front;
        while (curr) {
            append(curr->data);
            curr = curr->next;
        }
    }

    // overloaded operator for =
    LinkedList &operator=(const LinkedList<T> &other) {
        if (this == &other) {
            std::cout << "user attempted to make a copy of self" << std::endl;
            return *this;
        }

        if (other.front == nullptr) {
            std::cout << "nothing to copy for overloaded operator ="
                      << std::endl;
            return *this;
        }

        Link<T> *curr = other.front;
        while (curr) {
            append(curr->data);
            curr = curr->next;
        }
        return *this;
    }

    // inserts value at the end of the linked list
    void append(T value) {
        Link<T> *temp = new Link<T>(value);
        if (front == nullptr) {
            front = temp;
        } else {
            back->next = temp;
            temp->prev = back;
        }
        back = temp;
        size++;
    }

    // inserts value at the front of the linked list
    void prepend(T value) {
        Link<T> *temp = new Link<T>(value);

        temp->next = front;
        if (front) front->prev = temp;
        if (!back) back = temp;
        front = temp;
        size++;
    }

    // removes the first node in the linked list
    T removeFirst() {
        if (!front) throw std::logic_error("nothing to remove");
        T x = front->data;
        Link<T> *temp = front;
        front = front->next;

        if (front) front->prev = nullptr;

        delete temp;
        size--;
        return x;
    }

    // returns the value of the first link of the linked list
    // T peak()
    // {
    //     return front->data;
    // }
    T peek() const {
        if (isEmpty()) {
            // Handle empty list case
            // For example, throw an exception or return a default value
            // Throw an exception
            throw std::out_of_range("List is empty");
        }
        return front->data;
    }

    // checks if the linked list is empty
    bool isEmpty() { return front == nullptr; }

    // returns the size of the linked list
    int sizeOf() const { return size; }
};

// overloaed overator for << to cout the values of the linked list
template <class T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list) {
    Link<T> *curr = list.front;
    while (curr) {
        os << curr->data;
        if (curr != list.back) {
            os << ", ";
        }
        curr = curr->next;
    }

    // couts backwards, just to make sure all the pointers are correctly set and
    // upated

    // Link<T> *curr = list.back;
    // while (curr)
    // {
    //     os << curr->data;
    //     if (curr != list.front)
    //     {
    //         os << ", ";
    //     }
    //     curr = curr->prev;
    // }

    return os;
}

#endif