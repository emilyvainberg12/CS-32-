//
//  LinkedList.cpp
//  Homework1
//
//  Created by Emily Vainberg on 7/2/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//

#include "LinkedList.h"
#include <string>
#include <iostream>
using namespace std;

// default constructor
LinkedList::LinkedList()
{
    head = nullptr;
}

// copy constructor LinkedList(const LinkedList& rhs);
LinkedList::LinkedList(const LinkedList& rhs)
{
	head = nullptr;
	
	if (rhs.head == nullptr) // make sure that if the new list is empty, it returns empty
		return;

// process of replicating the information from rhs to the new linked list

	Node* temp = rhs.head;  // Create a temp variable since rhs.head is a constant
	Node *current = nullptr; // create another temp variable to store the location

	// creates the inital pointers and values that will then go into the while loop to traverse through the list
	head = new Node; // Allocate a new node in memory
	head->value = temp->value; // Copy over the value
	head->next = nullptr; // Set the 'next' value to null
	current = head; // Point 'current' to 'head'.
	temp = temp->next; // Move to next item in the rhs list.

	while (temp != nullptr)
	{
		current->next = new Node; // Allocate new memory for a new 'node'
		current = current->next; // Point to this new 'node'
		current->value = temp->value; // copies the values
		current->next = nullptr;
		temp = temp->next; // traverse through the list
	}
}

// Destroys all the dynamically allocated memory in the list.
LinkedList::~LinkedList()
{
	Node* p = head;

	while (p != nullptr) {
		Node *temp = p->next; // creates a pointer that stores the next locaiton so no nodes are lost
		delete p;
		p = temp; // traverses through nodes by setting p to next value previously assigned to temp
	}
}

// assignment operator, overaloaded assignment returns reference to linkedList object/ chains multiple linked list objects together with assignment operator
const LinkedList& LinkedList::operator=(const LinkedList& rhs)
{
	// checks for self assignment
	if (&rhs == this)
		return *this;
	
	//delete all the nodes in the linked list (copied the destructor)
	Node* h = head;
	while (h != nullptr) {
		Node *temp = h->next;
		delete h;
		h = temp;
	}

	// make sure that if you are copying an empty list, return an empty list
	if (rhs.head == nullptr){
		head = nullptr;
		return *this;
	}

	// copy the copy constructor here

	Node* temp = rhs.head; // Create a temp variable since rhs.head is a constant
	Node *current = nullptr;

	// creates the inital pointers and values that will then go into the while loop to traverse through the list
	head = new Node;
	head->value = temp->value;
	head->next = nullptr;
	current = head;
	temp = temp->next;

	while (temp != nullptr)
	{
		current->next = new Node; // Allocate new memory for a new node
		current = current->next;
		current->value = temp->value; // Copy the values
		current->next = nullptr;
		temp = temp->next;
	}

	return *this;
}

void LinkedList::insertToFront(const ItemType &val)
{
	Node *newNode = new Node;

	newNode->value= val;
	newNode->next= nullptr;

	if (head == nullptr){ //if linkedlist is empty, have the head point to the newNode
		head = newNode; //copy the info from newNode to next
		newNode = nullptr;
	}

	else {
		newNode->next = head; // have the new Node point to the original head node
		head = newNode; // make head point to the new node
		newNode = nullptr;
	}
}
	

void LinkedList::printList() const
{
	Node *p; // since head is constant, create a new pointer that points to head
	p = head;
    while (p != nullptr){
        cout << p->value << " ";
		p = p->next; // increment though the linked list
    }
	cout << endl;
}

bool LinkedList::get(int i, ItemType &item) const
{
	Node *p;
	p = head; // since head is constant set a temp pointer to it

	int count = 0;
	while (p != nullptr ){
		if (count == i){
			item = p->value; // sets item to value at position i 
			return true;
		}
		count++;
		p = p->next;
	}
	return false; // if it hasn't already returned true, it means there are less than 'i' elements
}

void LinkedList::reverseList()
{
	Node *previous = nullptr;
	Node *current = head;
	Node *after = head;

	while(current != nullptr) {
		after = after->next; // set the 'after' node to the one that comes next
		current->next = previous;// set the new previosu pointer to the node
		previous = current; // this copies the current information to the previous
		current = after; // this copies the after to the the current, this way no informatiojn or pointers get lost during the swaps
	  } // now traverse through the list and slowly
	head = previous;
}

void LinkedList::printReverse() const {
	
	Node *previous = nullptr;
	Node *current = head; // create temporary pointer at the head
	Node *after = head;  // create temporary pointer at the head

	// copy the same code from the reverse list function
	while (current != nullptr) {
		after = after->next;
		current->next = previous;
		previous = current;
		current = after;
	  }
	
	//copy the syntax for printing the list
	Node *p = previous;
	while (p != nullptr){
		cout << p->value <<" ";
		p = p->next;
	}
	cout << endl;
}

void LinkedList::append(const LinkedList &other) {
	LinkedList copy = other;
	Node *temp = head;
	Node *secondHead = copy.head;
	
	// if you are appending an empty linked list, just return the function
	if (copy.head == nullptr){
		return;
	}
	
	// If I am appending to an empty node, I need to run a special code to make sure the string doesn't go out of range
	else if (temp == nullptr){
		Node* temp = copy.head;  // Create a temp variable since rhs.head is a constant
		Node *current = nullptr; // create another temp variable to store the location

		// creates the inital pointers and values that will then go into the while loop to traverse through the list
		head = new Node; // Allocate a new node in memory
		head->value = temp->value; // Copy over the value
		head->next = nullptr; // Set the 'next' value to null
		current = head; // Point 'current' to 'head'.
		temp = temp->next; // Move to next item in the rhs list.

		while (temp != nullptr)
		{
			current->next = new Node; // Allocate new memory for a new 'node'
			current = current->next; // Point to this new 'node'
			current->value = temp->value; // copies the values
			current->next = nullptr;
			temp = temp->next; // traverse through the list
		}
		return;
	}
	
	while (temp->next != nullptr){
		temp = temp->next; // traverse to the find the last node of the first linked list
	}
		// other.head is how I access the second LinkedList
		
	while (secondHead != nullptr){
			Node *add = new Node; // create a new node to the original linked list every time there is still a node in the second linked list
			add->value = secondHead->value; // add the value to the first linked list
			temp->next = add; // add the pointer to the next node
			temp = temp->next; // go to the next pointer
			secondHead = secondHead->next; // move the head of the second linked list to the next pointer
		}
		temp->next = nullptr; // make sure to set the temp to null since it is no longer being used
}

void LinkedList::swap(LinkedList &other)
{
	// basic syntax for swapping two elements
	Node *temp = head;
	head = other.head;
	other.head = temp;
}

int LinkedList::size() const
{
	Node *s;
	s = head; // since head is a const variable pointer, assign a temporary pointer to it
    
	int count = 0;
	while (s != nullptr ){ // loops stops when pointer points to empty node
		count++; // count every time there is a node with values inside
		s = s->next;
    }
return count;
}




