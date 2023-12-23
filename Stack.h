#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <ostream>
#include <stdexcept>

#include <LinkedList.h>

// stack class, uses linked list
template <class T>
class Stack
{

private:
public:
    LinkedList<T> elements;

    // adds value to the front of the stack
    void push(T value)
    {
        elements.prepend(value);
    }

    // removes the first value of the stack
    T pop()
    {
        return elements.removeFirst();
    }

    // peaks at the first value of the stack
    T peak()
    {
        return elements.peak();
    }

    // checks if the stack is empty
    bool isEmpty()
    {
        return elements.isEmpty();
    }

    // returns the size of the stack
    int length() const
    {
        return elements.sizeOf();
    }
};

// couts the contents of the stack
template <class T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &stack)
{
    os << stack.elements;
    return os;
}

#endif