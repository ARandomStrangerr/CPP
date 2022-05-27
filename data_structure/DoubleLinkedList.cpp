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
};
template <typename T>
class DoubleLinkedList{
private:
  int size;
  DoubleLinkedNode<T>* dummy;
public:
  DoubleLinkedList(); // constructor
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
DoubleLinkedList<T>::DoubleLinkedList(){ // constructor of DoubleLinkedList
  this -> size = 0;
  this -> dummy = new DoubleLinkedNode<T>(0);
  this -> dummy -> next = this -> dummy;
  this -> dummy -> prev = this -> dummy;
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
