#pragma once
#include <utility>
#include <stdexcept> 
#include <initializer_list>
using namespace std;

template <typename DataType>
class Vector{
private:
    DataType *data;
    long capacity;
    long size;
    void resize();

public:
    Vector(long capacity = 100);
    Vector(const Vector &vector);
    Vector(initializer_list<DataType> list);
    ~Vector();

    Vector& operator = (const Vector & other);
    DataType& operator [] (int position);

    bool isEmpty();
    bool isFull();
    void pushback(DataType value);
    void pushfront(DataType value);
    void popback();
    void popfront();
    void remove(int position);

    long getSize();
    long getCapacity();

    
};
