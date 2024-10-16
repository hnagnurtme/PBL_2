#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <iostream>
#include <initializer_list>
#include <stdexcept>

using namespace std;

template <typename DataType>
class Vector {

private:
    DataType* data;
    long capacity;
    long size;
public:
    Vector(long capacity = 1000);
    Vector(const Vector &vector);
    Vector(initializer_list<DataType> list);
    Vector<DataType>& operator=(const Vector &other);

    DataType& operator[](int position);
    const DataType& operator[](int position) const;

    ~Vector();

    long getSize() const;
    long getCapacity() const;

    bool isEmpty() const;
    bool isFull() const;

    void pushback(const DataType& value);
    void pushfront(const DataType& value);
    void popback();
    void popfront();
    void remove(int position);

};

template <typename DataType>
Vector<DataType>::Vector(long capacity) : capacity(capacity), size(0) {
    data = new DataType[capacity];
}

template <typename DataType>
Vector<DataType>::Vector(const Vector &vector) : capacity(vector.capacity), size(vector.size) {
    data = new DataType[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = vector.data[i];
    }
}

template <typename DataType>
Vector<DataType>::Vector(std::initializer_list<DataType> list) : capacity(list.size()), size(list.size()) {
    data = new DataType[capacity];
    int i = 0;
    for (const auto& item : list) {
        data[i++] = item;
    }
}

template <typename DataType>
Vector<DataType>& Vector<DataType>::operator=(const Vector &other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new DataType[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename DataType>
DataType& Vector<DataType>::operator[](int position) {
    if (position < 0 || position >= size) {
        throw out_of_range("Index out of bounds");
    }
    return data[position];
}

template <typename DataType>
const DataType& Vector<DataType>::operator[](int position) const {
    if (position < 0 || position >= size) {
        throw out_of_range("Index out of bounds");
    }
    return data[position];
}

template <typename DataType>
Vector<DataType>::~Vector() {
    delete[] data;
}

template <typename DataType>
long Vector<DataType>::getSize() const {
    return size;
}

template <typename DataType>
long Vector<DataType>::getCapacity() const {
    return capacity;
}

template <typename DataType>
bool Vector<DataType>::isEmpty() const {
    return size == 0;
}

template <typename DataType>
bool Vector<DataType>::isFull() const {
    return size == capacity;
}

template <typename DataType>
void Vector<DataType>::pushback(const DataType& value) {
    if (isFull()) {
        return;
    }
    data[size++] = value;
}

template <typename DataType>
void Vector<DataType>::pushfront(const DataType& value) {
    if (isFull()) {
        return;
    }
    for (int i = size; i > 0; i--) {
        data[i] = data[i - 1];
    }
    data[0] = value;
    size++;
}

template <typename DataType>
void Vector<DataType>::popback() {
    if (!isEmpty()) {
        size--;
    }
}

template <typename DataType>
void Vector<DataType>::popfront() {
    if (!isEmpty()) {
        for (int i = 0; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
}

template <typename DataType>
void Vector<DataType>::remove(int position) {
    if (position < 0 || position >= size) {
        throw out_of_range("Index out of bounds");
    }
    for (int i = position; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}


template <typename DataType>
class Queue {
private:
    DataType* data;
    long size;
    long capacity;
    long frontIndex; 
    long rearIndex;  

public:
    Queue(long capacity = 1000);
    Queue(const Queue &queue);
    Queue(initializer_list<DataType> list);
    Queue<DataType>& operator=(const Queue &other);

    ~Queue();

    void enqueue(const DataType& value);

    DataType dequeue();
    DataType front() const; 
    DataType rear() const;  

    bool isEmpty() const;
    bool isFull() const;

    long getSize() const;
    void display() const;

private:
    void resize(long new_capacity);
};

template <typename DataType>
Queue<DataType>::Queue(long capacity) : capacity(capacity), size(0), frontIndex(0), rearIndex(-1) {
    data = new DataType[capacity];
}

template <typename DataType>
Queue<DataType>::Queue(const Queue &queue) : capacity(queue.capacity), size(queue.size), frontIndex(queue.frontIndex), rearIndex(queue.rearIndex) {
    data = new DataType[capacity];
    for (long i = 0; i < size; i++) {
        data[i] = queue.data[i];
    }
}

template <typename DataType>
Queue<DataType>::Queue(initializer_list<DataType> list) : capacity(list.size()), size(list.size()), frontIndex(0), rearIndex(list.size() - 1) {
    data = new DataType[capacity];
    int i = 0;
    for (const auto& item : list) {
        data[i++] = item;
    }
}

template <typename DataType>
Queue<DataType>& Queue<DataType>::operator=(const Queue &other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        frontIndex = other.frontIndex;
        rearIndex = other.rearIndex;
        data = new DataType[capacity];
        for (long i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename DataType>
Queue<DataType>::~Queue() {
    delete[] data;
}

template <typename DataType>
bool Queue<DataType>::isEmpty() const {
    return size == 0;
}

template <typename DataType>
bool Queue<DataType>::isFull() const {
    return size == capacity;
}

template <typename DataType>
long Queue<DataType>::getSize() const {
    return size;
}

template <typename DataType>
void Queue<DataType>::resize(long new_capacity) {
    DataType* new_data = new DataType[new_capacity];
    for (long i = 0; i < size; i++) {
        new_data[i] = data[(frontIndex + i) % capacity]; 
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
    frontIndex = 0; 
    rearIndex = size - 1; 
    }

template <typename DataType>
void Queue<DataType>::enqueue(const DataType& value) {
    if (isFull()) {
        cerr << "Queue is full, cannot enqueue" << endl;
        return;
    }
    rearIndex = (rearIndex + 1) % capacity; 
    data[rearIndex] = value;
    size++;
}

template <typename DataType>
DataType Queue<DataType>::dequeue() {
    if (isEmpty()) {
        throw out_of_range("Queue is empty, cannot dequeue");
    }
    DataType frontValue = data[frontIndex];
    frontIndex = (frontIndex + 1) % capacity; 
    size--;
    return frontValue;
}

template <typename DataType>
DataType Queue<DataType>::front() const {
    if (isEmpty()) {
        throw out_of_range("Queue is empty, no front element");
    }
    return data[frontIndex];
}

template <typename DataType>
DataType Queue<DataType>::rear() const {
    if (isEmpty()) {
        throw out_of_range("Queue is empty, no rear element");
    }
    return data[rearIndex];
}

template <typename DataType>
void Queue<DataType>::display() const {
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
        return;
    }
    cout << "Queue elements:";
    for (long i = 0; i < size; i++) {
        cout << data[(frontIndex + i) % capacity] << " "; 
    }
    cout << endl;
}


template <typename DataType>
class Stack {
private:
    DataType* data;   
    long size;        
    long capacity;    

public:
    Stack(long capacity = 1000);                   
    Stack(const Stack &stack);                      
    Stack(initializer_list<DataType> list);        
    Stack<DataType>& operator=(const Stack &other); 

    ~Stack();                                       

    void push(const DataType& value);     

    DataType pop();                                 
    DataType top() const;    

    bool isEmpty() const;                           
    bool isFull() const;  

    long getSize() const;    
    void display() const;                           

private:
    void resize(long new_capacity);                 
};

template <typename DataType>
Stack<DataType>::Stack(long capacity) : capacity(capacity), size(0) {
    data = new DataType[capacity];
}

template <typename DataType>
Stack<DataType>::Stack(const Stack &stack) : capacity(stack.capacity), size(stack.size) {
    data = new DataType[capacity];
    for (long i = 0; i < size; i++) {
        data[i] = stack.data[i];
    }
}

template <typename DataType>
Stack<DataType>::Stack(initializer_list<DataType> list) : capacity(list.size()), size(list.size()) {
    data = new DataType[capacity];
    int i = 0;
    for (const auto& item : list) {
        data[i++] = item;
    }
}

template <typename DataType>
Stack<DataType>& Stack<DataType>::operator=(const Stack &other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new DataType[capacity];
        for (long i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename DataType>
Stack<DataType>::~Stack() {
    delete[] data;
}

template <typename DataType>
bool Stack<DataType>::isEmpty() const {
    return size == 0;
}

template <typename DataType>
bool Stack<DataType>::isFull() const {
    return size == capacity;
}

template <typename DataType>
long Stack<DataType>::getSize() const {
    return size;
}

template <typename DataType>
void Stack<DataType>::resize(long new_capacity) {
    DataType* new_data = new DataType[new_capacity];
    for (long i = 0; i < size; i++) {
        new_data[i] = data[i]; 
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

template <typename DataType>
void Stack<DataType>::push(const DataType& value) {
    if (isFull()) {
        cerr << "Stack is full, cannot push" << endl;
        return;
    }
    data[size++] = value;
}

template <typename DataType>
DataType Stack<DataType>::pop() {
    if (isEmpty()) {
        throw out_of_range("Stack is empty, cannot pop ");
    }
    return data[--size];
}

template <typename DataType>
DataType Stack<DataType>::top() const {
    if (isEmpty()) {
        throw out_of_range("Stack is empty, no top element");
    }
    return data[size - 1];
}

template <typename DataType>
bool Stack<DataType>::isEmpty() const {
    return size == 0;
}

template <typename DataType>
void Stack<DataType>::display() const {
    if (isEmpty()) {
        cout << "Stack is empty" << endl;
        return;
    }
    cout << "Stack elements:";
    for (long i = 0; i < size; i++) {
        cout << data[i] << " "; 
    }
    cout << endl;
}

#endif // DATASTRUCTURES_H
