#include "iostream"
#include "stdexcept"

// declare classes
template <typename T>
class SingleLinkedNode;
template <typename T>
class SingleLinkedList;

// declare methods is in class
template <typename T>
class SingleLinkedNode {
private:
  friend class SingleLinkedList<T>;
  T val;
  SingleLinkedNode<T>* next;
  SingleLinkedNode(T);
};

template <typename T>
class SingleLinkedList {
private:
  SingleLinkedNode<T>* head;
  SingleLinkedNode<T>* tail;
  int size;
public:
  SingleLinkedList();
  void addFirst(T); // add an element at the head of the structure
  void addLast(T); // add an element at the last of the structure
  void add(int, T); // add an element at an arbitrary point of the structure
  T peekFirst(); // see the first element of the structure
  T peekLast(); // see the last element of the structure
  T peek(int); // see the element at the given index
  T removeFirst(); // remove first element from the structure
  T removeLast(); // remove last element from the structure
  T remove(int); // remove the element at the given index from the strucutre
  int length(); // number of element that this structure contain
  friend std::ostream& operator<<(std::ostream& os, SingleLinkedList<T>& lst){
    /* the dumb architecture does not allow me to write this one as out side of
    the class so i include it here. do not ask why i don't to it like the other
    methods. it will trigger my PTHD */
    SingleLinkedNode<T>* currentNode = lst.head;
    os << "[ ";
    while (currentNode != nullptr){
      os << currentNode -> val << " ";
      currentNode = currentNode -> next;
    }
    os << "]\n";
    return os;
  } // technically the "toString" method to print out things within the structure
};

// declare the implementation of class
// constructor of SingleLinkedNode
template <typename T>
SingleLinkedNode<T>::SingleLinkedNode(T val){
  this -> val = val;
  this -> next = 0;
}

// constructor of SingleLinkedList
template <typename T>
SingleLinkedList<T>::SingleLinkedList(){
  this -> size = 0;
  this -> head = 0;
  this -> tail = 0;
}

// add to the head of the list
template <typename T>
void SingleLinkedList<T>::addFirst(T val){
  SingleLinkedNode<T>* newNode = new SingleLinkedNode<T>(val);
  if (size == 0){
    this -> head = newNode;
    this -> tail = newNode;
  } else {
    newNode -> next = this -> head;
    this -> head = newNode;
  }
  this -> size++;
}

// add to the end of the list
template <typename T>
void SingleLinkedList<T>::addLast(T val){
  SingleLinkedNode<T>* newNode = new SingleLinkedNode<T>(val);
  if (this -> size == 0){
    this -> head = newNode;
    this -> tail = newNode;
  } else {
    this -> tail -> next = newNode;
    this -> tail = newNode;
  }
  this -> size++;
}

// peek an item at the front of the list
template <typename T>
void SingleLinkedList<T>::add(int index, T val){
  if (index < 0 || index > this -> size) throw std::runtime_error("index out of bound");
  else if (index == this -> size) this -> addLast(val);
  else if (index == 0) this -> addFirst(val);
  else {
    SingleLinkedNode<T>* currentNode = this -> head;
    SingleLinkedNode<T>* newNode = new SingleLinkedNode<T>(val);
    for(int i = 0; i != index - 1; i++) currentNode = currentNode -> next;
    newNode -> next = currentNode -> next;
    currentNode -> next  = newNode;
    this -> size++;
  }
}

// peek the item at the front of the list
template <typename T>
T SingleLinkedList<T>::peekFirst() {
  if (size == 0) throw std::runtime_error("list is empty");
  return this -> head -> val;
}

// peek an item at the end of the list
template <typename T>
T SingleLinkedList<T>::peekLast() {
  if (size == 0) throw std::runtime_error("list is empty");
  return this -> tail -> val;
}

// peek at the element with the given index of the list
template <typename T>
T SingleLinkedList<T>::peek(int index) {
  if (index < 0 || index >= this -> size) throw std::runtime_error("index out of bound");
  else if (index == 0) return this -> peekFirst();
  else if (index == this -> size - 1) return this -> peekLast();
  else {
    SingleLinkedNode<T>* currentNode = this -> head;
    for (int i = 0; i < index; i++) currentNode = currentNode -> next;
    return currentNode -> val;
  }
}


// remove the first item from the list
template <typename T>
T SingleLinkedList<T>::removeFirst() {
  SingleLinkedNode<T>* newHead = this -> head -> next;
  this -> head -> next = nullptr;
  this -> head = newHead;
  this -> size--;
}

// remove the last item from the list
template <typename T>
T SinglelinkedList<T>::removeLast() {
  return this -> remove(this -> size - 1);
}

// remove an arbitrary item with given index from the list
template <typename T>
T SingleLinkedList<T>:: remove(int index) {
  if (index < 0 || index >= this -> size) thow std::runtime_error("index out of bound");
  else {
    SingleLinkedNode<T>* currentNode = this -> head;
    for (int i = 0; i < index - 1; i++) currentNode = currentNode -> next;
    SingleLinkedNode<T>* deleteNode = currentNode -> next;
    currentNode -> next = deleteNode -> next;
    deleteNode -> next = nullptr;
    this -> size--;
    return deleteNode.val;
  }
}

// get the size of the list
template <typename T>
int SingleLinkedList<T>::length(){
  return this -> size;
}
