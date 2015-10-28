// Implementation of the templated Vector class
// ECE4893/8893 lab 3
// YOUR NAME HERE

#include <iostream> // debugging
#include "Vector.h"

// Your implementation here
// Fill in all the necessary functions below
using namespace std;

// Default constructor
template <typename T>
Vector<T>::Vector()
{
  count = 0;
  reserved = 0;
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& rhs)
{
  count = rhs.count;
  reserved = rhs.reserved;
  elements = (T*) malloc(reserved * sizeof(T));
  for (size_t i = 0; i < count; i++){
    T* temp = new(&elements[i]) T((rhs.elements[i]));
  }
}

// Assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
  Vector<T> temp = Vector<T>(rhs);
  return temp;
}

#ifdef GRAD_STUDENT
// Other constructors
template <typename T>
Vector<T>::Vector(size_t nReserved)
{ // Initialize with reserved memory
  elements = (T*) malloc(nReserved * sizeof(T));
  reserved = nReserved;
}

template <typename T>
Vector<T>::Vector(size_t n, const T& t)
{ // Initialize with "n" copies of "t"
  elements = (T*) malloc(n * sizeof(T));
  for (size_t i = 0; i < n; i++){
    T* temp = new(&elements[i]) T(t);
  }
}
#endif

// Destructor
template <typename T>
Vector<T>::~Vector()
{
  for (size_t i = 0; i < count; i++){
    elements[i].~T();
  }
  free(elements);
}

// Add and access front and back
template <typename T>
void Vector<T>::Push_Back(const T& rhs)
{
}

template <typename T>
void Vector<T>::Push_Front(const T& rhs)
{
}

template <typename T>
void Vector<T>::Pop_Back()
{ // Remove last element
}

template <typename T>
void Vector<T>::Pop_Front()
{ // Remove first element
}

// Element Access
template <typename T>
T& Vector<T>::Front() const
{
}

// Element Access
template <typename T>
T& Vector<T>::Back() const
{
}

template <typename T>
const T& Vector<T>::operator[](size_t i) const
{
}

template <typename T>
T& Vector<T>::operator[](size_t i)
{
}

template <typename T>
size_t Vector<T>::Size() const
{
}

template <typename T>
bool Vector<T>::Empty() const
{
}

// Implement clear
template <typename T>
void Vector<T>::Clear()
{
}

// Iterator access functions
template <typename T>
VectorIterator<T> Vector<T>::Begin() const
{
  return VectorIterator<T>(elements);
}

template <typename T>
VectorIterator<T> Vector<T>::End() const
{
}

#ifdef GRAD_STUDENT
// Erase and insert
template <typename T>
void Vector<T>::Erase(const VectorIterator<T>& it)
{
}

template <typename T>
void Vector<T>::Insert(const T& rhs, const VectorIterator<T>& it)
{
}
#endif

// Implement the iterators

// Constructors
template <typename T>
VectorIterator<T>::VectorIterator()
{
}

template <typename T>
VectorIterator<T>::VectorIterator(T* c)
{
}

// Copy constructor
template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator<T>& rhs)
{
}

// Iterator defeferencing operator
template <typename T>
T& VectorIterator<T>::operator*() const
{
}

// Prefix increment
template <typename T>
VectorIterator<T>  VectorIterator<T>::operator++()
{
}

// Postfix increment
template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int)
{;
}

// Comparison operators
template <typename T>
bool VectorIterator<T>::operator !=(const VectorIterator<T>& rhs) const
{
}

template <typename T>
bool VectorIterator<T>::operator ==(const VectorIterator<T>& rhs) const
{
}




