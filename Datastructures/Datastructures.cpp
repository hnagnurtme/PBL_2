#include "Datastructures/DataStructures.h"
template <typename DataType>
Vector<DataType> :: Vector(long capacity) : capacity(capacity) , size(0) {
    data = new DataType[capacity];
}

template <typename DataType>
Vector<DataType> :: Vector(const Vector &vector) : capacity(vector.capacity) ,size(vector.size) {
    data = new DataType[capacity];

    for( int i = 0; i < size ; i++){
        data[i] = vector.data[i];
    }
}

template <typename DataType>
Vector<DataType>::Vector(std::initializer_list<DataType> list) : capacity(list.size()), size(list.size()) {
    data = new DataType[capacity];
    int i = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        data[i++] = *it;
    }
}

template <typename DataType>
Vector<DataType>& Vector<DataType> :: operator = (const Vector & other){
    if( &other != this){
        delete[] data;
        capacity = other.capacity;
        size = other.size;

        data = new DataType[capacity];
        for( int i = 0; i < size ; i++){
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename DataType>
DataType& Vector<DataType> :: operator [] (int position){
    if (position < 0 || position >= size) {
        throw out_of_range("Index out of range");
    }
    return data[position];
}
template <typename DataType>
bool Vector<DataType> :: isEmpty(){
    return size == 0;
}
template <typename DataType>
bool Vector<DataType> :: isFull(){
    return size == capacity ;
}

template <typename DataType>
void Vector<DataType> :: pushback(DataType value){
    if(isFull()){
        resize();
    }
    data[size++] = value;
}

template <typename DataType>
void Vector<DataType> ::pushfront(DataType value){
    if(isFull()){
        resize();
    }
    for (int i = size; i > 0; i--) {
        data[i] = data[i - 1];
    }
    data[0] = value;  
    size++;
}

template <typename DataType>
void Vector<DataType> ::popback(){
    if(!isEmpty()){
        size --;
    }

};

template <typename DataType>
void Vector<DataType> ::popfront(){
    if (!isEmpty()) {
        for (int i = 0; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--; 
    }
}

template <typename DataType>
void Vector<DataType> ::remove(int position){
    if (position < 0 || position >= size) {
        throw out_of_range("Index out of range");
    }

    for (int i = position; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}
template <typename DataType>
Vector<DataType> :: ~Vector(){
    delete[] data;

}

template <typename DataType>
long Vector<DataType> :: getSize(){
    return size;
}

template <typename DataType>
long Vector<DataType> :: getCapacity(){
    return capacity;
}

template <typename DataType>
void Vector<DataType> :: resize(){
    capacity = (capacity == 0) ? 1 : capacity * 2; 
    DataType* newData = new DataType[capacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;

}