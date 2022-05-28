#include "iostream"
#include "stdexcept"

// declare classes
template <typename T>
class DoubleLinkedNode;
template <typename T>
class DoubleLinkedList;

// declare methods within class
template <typename T>
class DoubleLinkedNode {
private:
  friend class DoubleLinkedList<T>;
  DoubleLinkedNode<T>* prev;
  DoubleLinkedNode<T>* next;
  T val;
  DoubleLinkedNode(T);
  ~DoubleLinkedNode();
};
template <typename T>
class DoubleLinkedList{
private:
  int size;
  DoubleLinkedNode<T>* dummy;
public:
  DoubleLinkedList(); // constructor
  ~DoubleLinkedList(); // destructor
  void addFirst(T); // add an element to the front of the list
  void addLast(T); // add an element to the back of the list
  void add(int, T); // add an element to an arbitrary position of the list
  T peekFirst(); // see the element at the front of the list
  T peekLast(); // see the element at the back of the list
  T peek(int); // see an element at a given position in the list
  T removeFirst(); // remove the element at the front of the list
  T removeLast(); // remove the element at the back of the list
  T remove(int); // remove an element at the given position of the list
  int length(); // get the length of the list
  friend std::ostream& operator<<(std::ostream& os, const DoubleLinkedList<T>& lst){
    os << "Structure size: " << lst.size << "\n";
    os << "Traverse Forward:\n[ ";
    DoubleLinkedNode<T>* currentNode = lst.dummy -> next;
    while (currentNode != lst.dummy){
      os << currentNode -> val << " ";
      currentNode = currentNode -> next;
    }
    os << "]\n";
    os << "Traverse Backward: \n[ ";
    currentNode = lst.dummy -> prev;
    while (currentNode != lst.dummy){
      os << currentNode -> val << " ";
      currentNode = currentNode -> prev;
    }
    os << "]";
    return os;
  }
};

// implementation of method
template <typename T>
DoubleLinkedNode<T>::DoubleLinkedNode(T val){ // constructor of DoubleLinkedNode
  this -> val = val;
  this -> prev = 0;
  this -> next = 0;
}
template <typename T>
DoubleLinkedNode<T>::~DoubleLinkedNode(){ // destructor of DoubleLinkedNode
  this -> next = nullptr;
  this -> prev = nullptr;
}
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(){ // constructor of DoubleLinkedList
  this -> size = 0;
  this -> dummy = new DoubleLinkedNode<T>(0);
  this -> dummy -> next = this -> dummy;
  this -> dummy -> prev = this -> dummy;
}
template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList(){ // destructor of DoubleLinkedNode
  while (size != 0) this -> removeFirst();
  delete dummy;
}
template <typename T>
void DoubleLinkedList<T>::addFirst(T val){ // add an element to the front of the list
  DoubleLinkedNode<T>* newNode = new DoubleLinkedNode<T>(val);
  if (this -> size == 0){
    this -> dummy -> prev = newNode;
    newNode -> next = this -> dummy;
  } else {
    newNode -> next = this -> dummy -> next;
    this -> dummy -> next -> prev = newNode;
  }
  newNode -> prev = this -> dummy;
  this -> dummy -> next = newNode;
  this -> size++;
}
template <typename T>
void DoubleLinkedList<T>::addLast(T val){ // add an element to the end of the list
  DoubleLinkedNode<T>* newNode = new DoubleLinkedNode<T>(val);
  if (this -> size == 0){
    newNode -> prev = this -> dummy;
    this -> dummy -> next = newNode;
  } else {
    newNode -> prev = this -> dummy -> prev;
    this -> dummy -> prev -> next = newNode;
  }
  newNode -> next = this -> dummy;
  this -> dummy -> prev = newNode;
  this -> size++;
}
template <typename T>
void DoubleLinkedList<T>::add(int index, T val){ // add an element at the given position
  if (0 > index || index > this -> size) throw std::runtime_error("index out of range");
  else if (index == 0) this -> addFirst(val);
  else if (index == this -> size) addLast(val);
  else {
    DoubleLinkedNode<T>* currentNode = this -> dummy -> next;
    DoubleLinkedNode<T>* newNode = new DoubleLinkedNode<T>(val);
    for (int i = 0; i < index - 1; i++) currentNode = currentNode -> next;
    newNode -> prev = currentNode;
    newNode -> next = currentNode -> next;
    currentNode -> next -> prev = newNode;
    currentNode -> next = newNode;
    this -> size++;
  }
}
template <typename T>
T DoubleLinkedList<T>::peekFirst(){ // look at the first element without removing it
  if (this -> size == 0) throw std::runtime_error("list is empty");
  return this -> dummy -> next -> val;
}
template <typename T>
T DoubleLinkedList<T>::peekLast(){ // look at the last element without removing it
  if (this -> size == 0) throw std::runtime_error("list is empty");
  return this -> dummy -> prev -> val;
}
template <typename T>
T DoubleLinkedList<T>::peek(int index){ // look at the element at the given index
  if (index < 0 || index >= this -> size) std::runtime_error("index out of bound");
  DoubleLinkedNode<T>* currentNode = this -> dummy -> next;
  for (int i = 0; i < index; i++) currentNode = currentNode -> next;
  return currentNode -> val;
}
template <typename T>
T DoubleLinkedList<T>::removeFirst(){ // remove first element from the list
  if (this -> size == 0) throw std::runtime_error("list is empty");
  DoubleLinkedNode<T>* deleteNode = this -> dummy -> next;
  deleteNode -> next -> prev = this -> dummy;
  this -> dummy -> next = deleteNode -> next;
  T returnVal = deleteNode -> val;
  delete deleteNode;
  this -> size--;
  return returnVal;
}
template <typename T>
T DoubleLinkedList<T>::removeLast(){ // remove last element from the list
  if (this -> size == 0) throw std::runtime_error("list is empty");
  DoubleLinkedNode<T>* deleteNode = this -> dummy -> prev;
  deleteNode -> prev -> next = this -> dummy;
  this -> dummy -> prev = deleteNode -> prev;
  T returnVal = deleteNode -> val;
  delete deleteNode;
  this -> size--;
  return returnVal;
}
template <typename T>
T DoubleLinkedList<T>::remove(int index){ // remove the element at given index
  if (this -> size == 0) throw std::runtime_error("list is empty");
  else if (index < 0 || index >= size) throw std::runtime_error("index out of bound");
  else if (index == 0) return this -> removeFirst();
  else if (index == this -> size - 1) return this -> removeLast();
  else {
    DoubleLinkedNode<T>* deleteNode = this -> dummy -> next;
    for (int i = 0; i < index; i++) deleteNode = deleteNode -> next;
    deleteNode -> next -> prev = deleteNode -> prev;
    deleteNode -> prev -> next = deleteNode -> next;
    T returnVal = deleteNode -> val;
    delete deleteNode;
    return returnVal;
  }
}

template <typename T>
int DoubleLinkedList<T>::length(){ // return the size of the structure
  return this -> size;
}
