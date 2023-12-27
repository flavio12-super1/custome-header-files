#ifndef ARRAY_LIST
#define ARRAY_LIST

#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

// here
struct Success {
    bool state;
    int index;
    std::string response;
    Success() {
        state = false;
        index = 0;
        response = "not found";
    }

    Success(bool state, std::string response) {
        this->state = state;
        this->response = response;
    }

    Success(bool state, int index, std::string response) {
        this->state = state;
        this->index = index;
        this->response = response;
    }
};

template <class T>
class ArrayList;

template <class T>
std::ostream &operator<<(std::ostream &os, const ArrayList<T> &container);

template <class T>
class ArrayList {
   public:
    T *arr;
    int count;
    int capacity;

    void inflate() {
        if (count == capacity) {
            int oldCapacity = capacity;
            capacity *= 2;

            T *temp = new T[capacity];

            for (int i = 0; i < oldCapacity; i++) {
                temp[i] = arr[i];
            }

            T *old = arr;

            arr = temp;

            delete[] old;
        }
    }

    void deflate() {
        if (count * 2 < capacity) {
            capacity = capacity / 2;
            T *temp = new T[capacity];
            for (int i = 0; i < count; i++) {
                temp[i] = arr[i];
            }

            T *old = arr;
            arr = temp;
            delete[] old;
        }
    }

    ArrayList() {
        capacity = 1;
        arr = new T[capacity];
        count = 0;
    }

    ArrayList(const ArrayList &other) {
        arr = new T[capacity];
        count = other.count;
        for (int i = 0; i < count; i++) {
            arr[i] = other.arr[i];
        }
    }

    ArrayList &operator=(const ArrayList &other) {
        count = other.count;
        for (int i = 0; i < count; i++) {
            arr[i] = other.arr[i];
        }
        return *this;
    }

    T &operator[](int index) const {
        if (index < 0 || index >= count) {
            throw std::logic_error("Array index out of bounds.");
        }
        return arr[index];
    }

    void append(T value) {
        arr[count] = value;
        count++;

        inflate();
    }

    void prepend(T value) {
        for (int i = count; i > 0; i--) {
            arr[i] = arr[i - 1];
        }
        arr[0] = value;
        count++;

        inflate();
    }

    // find object by property
    template <typename PropertyType>
    Success find(PropertyType value, PropertyType T::*property) {
                for (int i = 0; i < count; i++) {
            if (arr[i].*property == value) {
                std::string response = "found: " + value;
                Success message(true, i, response);
                return message;
            }
        }
        Success message(false, -1, "not found");
        return message;
    }

    bool search(T value) const {
        for (int i = 0; i < count; i++) {
            if (value == arr[i]) {
                return true;
            }
        }
        return false;
    }

    T remove(int index) {
        if (count == 0) {
            throw std::logic_error("Can not remove from an empty list.");
        }
        if (index < 0 || index >= count) {
            throw std::logic_error("Array index out of bounds.");
        }
        T result = arr[index];

        for (int i = index; i < count - 1; i++) {
            arr[i] = arr[i + 1];
        }
        count--;
        deflate();

        return result;
    }

    T removeFirst() {
        if (count == 0) {
            throw std::logic_error("Can not remove from an empty list.");
        }
        T result = arr[0];
        for (int i = 0; i < count - 1; i++) {
            arr[i] = arr[i + 1];
        }
        count--;
        deflate();
        return result;
    }

    T removeLast() {
        if (count == 0) {
            throw std::logic_error("Can not remove from an empty list.");
        }
        T result = arr[--count];
        deflate();
        return result;
    }

    void insert(T value, int index) {
        append(value);
        for (int i = count - 1; i > index; i--) {
            T temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;
        }
    }

    void reverse() {
        int start = 0;
        int end = size() - 1;

        while (start < end) {
            T temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }

    int size() const { return count; }

    void stats() const {
        std::cout << "Count:     " << count << std::endl;
        std::cout << "Capacity:  " << capacity << std::endl;
        std::cout << std::endl;
    }

    ~ArrayList() { delete[] arr; }

    friend std::ostream &operator<< <>(std::ostream &os,
                                       const ArrayList<T> &container);
    friend struct TestArrayList;
};

template <class T>
std::ostream &operator<<(std::ostream &os, const ArrayList<T> &container) {
    for (int i = 0; i < container.count; i++) {
        os << container.arr[i];
        if (i < container.count - 1) {
            os << ", ";
        }
    }
    return os;
}

#endif