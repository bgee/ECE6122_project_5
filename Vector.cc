// Implementation of the templated Vector class
// ECE4893/8893 lab 3
// Bi Ge

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
  //elements = NULL;
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
  count = 0;
}

template <typename T>
Vector<T>::Vector(size_t n, const T& t)
{ // Initialize with "n" copies of "t"
  elements = (T*) malloc(n * sizeof(T));
  for (size_t i = 0; i < n; i++){
    T* temp = new(&elements[i]) T(t);
  }
  count = n;
  reserved = n;
  //T::PrintCounts();
}
#endif

// Destructor
template <typename T>
Vector<T>::~Vector()
{
  for (size_t i = 0; i < count; i++){
    elements[i].~T();
  }
  if (reserved >= 0){
    free(elements);
  }
}

template <typename T>
T* Vector<T>::Get_New_Block(size_t newSize)
{
  T* new_elements = (T*) malloc((newSize) * sizeof(T));
  for (size_t i = 0; i < count; i++){
    T* temp = new(&new_elements[i]) T(elements[i]);
    elements[i].~T();
  }
  return new_elements;
}

// Add and access front and back
template <typename T>
void Vector<T>::Push_Back(const T& rhs)
{
  // if have enough space for one extra object
  if (reserved - count >= 1){
    new (&elements[count]) T(rhs);
    count++;
  }
  // if not, need to find another space and copy over all the element
  // and push to the back
  else {
    T* new_elements = Get_New_Block(count+1);
    T* temp = new (&new_elements[count]) T(rhs);
    if (count != 0){
      free(elements);
    }
    elements = new_elements;
    count++;
    reserved = count;
  }

}

template <typename T>
void Vector<T>::Reserve(size_t nReserved)
{
  // if current reserved size is less than nReserved
  if (reserved < nReserved){
    if (count > 0){
      free(elements);
    }
    elements = Get_New_Block(nReserved);
    reserved = nReserved;
  }
}

template <typename T>
void Vector<T>::Push_Front(const T& rhs)
{
  // if have one extra space left, shift everything and
  // insert at front
  if (reserved - count >= 1){
    // start shifting from back to front to avoid overwriting
    for (size_t i = count; i > 0; i--){
      elements[i] = T(elements[i-1]);
    }
    elements[0] = T(rhs);
    count++;
  }
  // else find new block and copy over then insert at front
  else {
    T* new_elements = (T*) malloc((count + 1) * sizeof(T));
    for (int i = 0; i < count; i++){
      new (&new_elements[i+1]) T(elements[i]);
      elements[i].~T();
    }
    // new pushed object
    new (&new_elements[0]) T(rhs);
    if (count >= 0){
      free(elements);
    }
    elements = new_elements;
    count++;
    reserved = count;
  }
}

template <typename T>
void Vector<T>::Pop_Back()
{ // Remove last element
  if (count > 0){
    elements[count-1].~T();
    count--;
  }
}

template <typename T>
void Vector<T>::Pop_Front()
{ // Remove first element
  if (count > 0){
    // free first and advance elements
    size_t count_backup = count-1;
    // we should keep reserved the same
    T* new_elements = (T*) malloc(reserved * sizeof(T));
    for(int i = 0; i < count-1; i++){
      new (&new_elements[i]) T(elements[i+1]);
      elements[i+1].~T();
    }
    elements[0].~T();
    free(elements);
    elements = new_elements;
    count = count_backup;
  }
}

// Element Access
template <typename T>
T& Vector<T>::Front() const
{
  return (elements[0]);
}

// Element Access
template <typename T>
T& Vector<T>::Back() const
{
  return (elements[count - 1]);
}

template <typename T>
const T& Vector<T>::operator[](size_t i) const
{
  return elements[i];
}

template <typename T>
T& Vector<T>::operator[](size_t i)
{
  return elements[i];
}

template <typename T>
size_t Vector<T>::Size() const
{
  return count;
}

template <typename T>
bool Vector<T>::Empty() const
{
  // appearently not supposed to use count
  return count == 0;
}

// Implement clear
template <typename T>
void Vector<T>::Clear()
{
  while (count > 0){
    Pop_Back();
  }
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
  return VectorIterator<T>(elements+count);
}

#ifdef GRAD_STUDENT
// Erase and insert
template <typename T>
void Vector<T>::Erase(const VectorIterator<T>& it)
{
  size_t erasePos = 0;
  for (VectorIterator<T> i = Begin(); i != it; i++){
    erasePos++;
  }
  // if erase on the end, no need to relocate
  if (erasePos == count -1){
    elements[erasePos].~T();
    count--;
  }
  // if non-end erasing, need to find new space
  else {


    // this shouldn't alter reserved, so get a space with size reserved
    T* new_elements = (T*) malloc(reserved * sizeof(T));
    for (size_t i = 0; i < erasePos; i++){
      new (&new_elements[i]) T(elements[i]);
      //elements[i].~T();
    }
    for (size_t i = erasePos + 1; i < count; i++){
      new (&new_elements[i-1]) T(elements[i]);
      //elements[i].~T();
    }
    for (size_t i = 0; i < count; i++){
      elements[i].~T();
      }
    //elements[erasePos].~T();
    free(elements);
    elements = new_elements;
    count--;
  }
}

template <typename T>
void Vector<T>::Insert(const T& rhs, const VectorIterator<T>& it)
{
  // shift everthing in Vector one element backwards, then insert
  // first need to see if theres enough space
  if (reserved - count >= 1){
    count++;
  }
  else {
    reserved = count + 1;
    count = reserved;
  }
  T* new_elements = (T*) malloc(reserved * sizeof(T));
  size_t insertPos = 0;
  // copy everything before it
  for (VectorIterator<T> i = Begin(); i != it; i++){
    insertPos++;
  }
  for (size_t i = 0; i < insertPos; i++){
    new (&new_elements[i]) T(elements[i]);
    elements[i].~T();
  }
  // insert at it
  new (&new_elements[insertPos]) T(rhs);
  for (size_t i = insertPos; i < count-1; i++){
    new (&new_elements[i+1]) T(elements[i]);
    elements[i].~T();
  }
  free(elements);
  elements = new_elements;
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
  current = c;
}


// Copy constructor
template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator<T>& rhs)
{
  current = rhs.current;
}

// Iterator defeferencing operator
template <typename T>
T& VectorIterator<T>::operator*() const
{
  return *current;
}

/*// debug helper
template <typename T>
void VectorIterator<T>::printCurrent()
{
  }*/

// Prefix increment
template <typename T>
VectorIterator<T>  VectorIterator<T>::operator++()
{
  return VectorIterator<T>(++current);
}

// Postfix increment
template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int)
{
  //current++;
  return VectorIterator<T>(current++);
}

// Comparison operators
template <typename T>
bool VectorIterator<T>::operator !=(const VectorIterator<T>& rhs) const
{
  return current!=rhs.current;
}

template <typename T>
bool VectorIterator<T>::operator ==(const VectorIterator<T>& rhs) const
{
  return current==rhs.current;
}




