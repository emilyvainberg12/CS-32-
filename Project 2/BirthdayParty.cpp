//
//  main.cpp
//  cs 32- proj 2
//
//  Created by Emily Vainberg on 7/8/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//


#include <iostream>
#include <string>
#include "BirthdayParty.h"

using namespace std;

BirthdayParty::BirthdayParty() { // default constructor
    head = nullptr;
    tail = nullptr;
};


BirthdayParty::~BirthdayParty(){ //destructor
    
    Node* p = head;
    while (p != nullptr) {
        Node *temp = p->next; // creates a pointer that stores the next locaiton so no nodes are lost
        delete p;
        p = temp; // traverses through nodes by setting p to next value previously assigned to temp
    }
    head = nullptr;
    tail = nullptr; 
}

BirthdayParty::BirthdayParty(const BirthdayParty& other){ //copy constructor, when making a new
  //  cout << "copy constructor" <<endl;
    head = nullptr;
    tail = nullptr;
    
   // creating the first node for the new list
    Node *add = new Node;
    Node *temp = other.head;
    add->value = temp->value;
    add->firstName = temp->firstName;
    add->LastName = temp->LastName;
    head = add;
    tail = add;
    add->next = nullptr;
    add->previous = nullptr;
    
    temp = temp->next;
    while (temp != nullptr){
        addInvitee(temp->firstName, temp->LastName, temp->value);
        temp = temp->next;
    }
}

BirthdayParty& BirthdayParty::operator=(const BirthdayParty& rhs){ //assignment operator
    
    //check for aliasing
    if (&rhs == this)
        return *this;
    
    // if you are copying an empty list, return an empty list
    if (rhs.head == nullptr){
        head = nullptr;
        return *this;
    }
    
    BirthdayParty temp = rhs;
    changeGuestList(temp); // call the swap function to copy the rhs into the current linkedlist
    return  *this;
}

bool BirthdayParty::noInvitees() const{
    if (head == nullptr){ // if the list is empty then head will be a nullptr
        return true; // returns true if empty
    }
    return false; // if head is not a nullptr then list is not empty
}

int BirthdayParty::whosOnTheGuestList() const{ // Return the number of players in the BirthdayParty list.
    int count = 0;
    Node* temp = head; // since we don't want to change the location of head, make a temp pointer to it
    while (temp != nullptr){
        count++;
        temp = temp->next;
    }
    return count;
}

bool BirthdayParty::addInvitee(const std::string& firstName, const std::string& lastName, const BirthdayType& value){
    
    Node* temp = head;
    while (temp != nullptr) { // once this loop quits, temp-> next = nullptr, which means temp is at the last node
        if (firstName == temp->firstName && lastName == temp->LastName){
            return false;
        }
        temp = temp->next;
    }
    
    // create a new node for the given values- do this once each time add Invite is called
    Node *add = new Node;
    add->next = nullptr;
    add->previous = nullptr;
    add->firstName = firstName;
    add->LastName = lastName;
    add->value = value;
    
    //if the list is empty, simply add a new node with the information
    if (noInvitees()){
        head = add;
        tail = add;
        return true;
    }
  
    if (lastName < head->LastName ){ // add to very front of list
        Node *temp = head;
        add->next = temp;
        temp->previous = add;
        add->previous = nullptr;
        head = add;
        return true;
    }
    
    else if (lastName > tail->LastName){ // add to very back of list
        tail->next = add;
        add->previous = tail;
        add->next = nullptr;
        tail = add;
        return true;
    }
    
    Node *same = head;
    while (same != nullptr){ // create a loop to go though the list and check if there are any names with the same last name
        if (lastName == same->LastName) {
            if (firstName < head->firstName && lastName == head->LastName){ // same last name but should become the very front of the list
                Node *temp = head;
                add->next = temp;
                temp->previous = add;
                add->previous = nullptr;
                head = add;
                return true;
        }
        
            else if (firstName > tail->firstName && lastName == tail->LastName){ // same last name as another but should be at the bottom of the list
                Node *temp = tail;
                temp->next = add;
                add->previous = temp;
                add->next = nullptr;
                tail = add;
            return true;
            }
       
        else { // if it reaches here- the linked list must go in the middle of last names //
        Node* ptr = same;
        while (ptr->LastName == lastName && ptr->next != nullptr){
            if (firstName < ptr->firstName){ // it should eventually reach the node where it
               // should be placed above the ptr
                Node *temp = ptr->previous;
                add->previous = temp;
                temp->next = add;
                add->next = ptr;
                ptr->previous = add;
                return true;
            }
            ptr = ptr->next;
        }
        
            // add after the last name
            Node *temp = ptr->previous;
            add->previous = temp;
            temp->next = add;
            add->next = ptr;
            ptr->previous = add;
            return true;
        }
    return true;
    }
        
        else if (lastName < same->LastName){ // it should eventually reach the node where it should be placed above
            Node *temp = same->previous;
            add->previous = temp;
            temp->next = add;
            add->next = same;
            same->previous = add;
            return true;
        }
        same = same->next;
    }
    return true;
}

bool BirthdayParty::modifyInvitee(const std::string& firstName, const std::string& lastName, const BirthdayType& value){
    // first check if the full name is equal to a full name in the list
    Node *temp = head;
    
    while (temp != nullptr){
        if (firstName == temp->firstName && lastName == temp->LastName){
            temp-> value = value; //make that full name no longer map to the value it currently maps to, but instead map to the value of the third // parameter;
            return true;
        }
        temp = temp->next;
    }
    return false;   // if it reaches here- the name is not in the list and it should return false
}


bool BirthdayParty::addOrModify(const std::string& firstName, const std::string& lastName, const BirthdayType& value){

    Node *temp = head;
     
    while (temp != nullptr){
         if (firstName == temp->firstName && lastName == temp->LastName){
             temp-> value = value; //make that full name no longer map to the value it currently maps to, but instead map to the value of the third // parameter;
             return true;
         }
         temp = temp->next;
     }
    
    // if not equal to a name already in the list, add the name
    addInvitee(firstName, lastName, value);
    return true;
}


bool BirthdayParty::dropFromGuestList(const std::string& firstName, const std::string& lastName){
    
    if (head == nullptr){
        return false;
    }
    
    if (!personOnGuestList(firstName, lastName))
        return false;

    if (firstName == head->firstName && lastName == head->LastName){
        Node *temp = head;
        head = temp->next;
        head->previous = nullptr;
        delete temp;
        return true;
    }
    
    else if (firstName == tail->firstName && lastName == tail->LastName){
        Node *temp = tail;
        tail = temp->previous;
        tail->next = nullptr;
        delete temp;
        return true;
    }
    
    else {
        Node *kill = head;
        while (kill != nullptr){
            if (kill != nullptr && kill->firstName == firstName && kill->LastName == lastName){
                kill->next->previous = kill->previous;
                kill->previous->next = kill->next;
                delete kill;
                return true; 
            }
            kill = kill->next;
        }
        return true;
    }
    return true;
}


bool BirthdayParty::personOnGuestList(const std::string& firstName, const std::string& lastName) const{
    
    if (head == nullptr){
        return false;
    }
    
    Node *temp = head;
    while (temp != nullptr){
         if (firstName == temp->firstName && lastName == temp->LastName){
             return true;
         }
         temp = temp->next;
     }
    return false;
}

bool BirthdayParty::checkGuestList(const std::string& firstName, const std::string& lastName, BirthdayType& value) const{
    
    if (head == nullptr){
        return false;
    }
    
    Node *temp = head;
    while (temp != nullptr){
        if (firstName == temp->firstName && lastName == temp->LastName){
            value = temp->value; //set value to the value in the list that that full name maps to,
            return true;
     }
     temp = temp->next;
 }
    return false;
}

bool BirthdayParty::selectInvitee(int i, std::string& firstName, std::string& lastName, BirthdayType& value) const{

    if ( i< 0 || i > whosOnTheGuestList()){
        return false; //parameters unchanged and return false.
    }
    
    int count = 0 ;
    Node *temp = head;
    while (temp != nullptr){
        if (count == i){
            firstName = temp->firstName;
            lastName = temp->LastName;
            value = temp->value;
            return true;
        }
        count++;
        temp = temp->next;
    }
    
    return true; // should never be called  because returned true or false before this point
}

void BirthdayParty::changeGuestList(BirthdayParty& other){
    Node *tempH = head;
    Node *tempT = tail;
    head = other.head;
    tail = other.tail;
    other.head = tempH;
    other.tail = tempT;
}

bool combineGuestLists(const BirthdayParty & bpOne, const BirthdayParty & bpTwo, BirthdayParty & bpJoined){
    bool shouldbeTrue = true;
    
    BirthdayParty check;
    check = bpOne;

    for (int n = 0; n < bpTwo.whosOnTheGuestList(); n++){
        string first2;
        string last2;
        BirthdayType val2;
        bpTwo.selectInvitee(n, first2, last2, val2);
        
        BirthdayType var;
        
        if (bpOne.personOnGuestList(first2, last2) == true){ // this means the first and last names are the same
            bpOne.checkGuestList(first2, last2, var);
                if (var != val2){  // this means first & last names are the same && values is the same
                    check.dropFromGuestList(first2, last2); // remove item that was orignally placed in copy list from bpOne
                    shouldbeTrue = false;
                }
        }
        else // this means they have different names & values
            check.addInvitee(first2, last2, val2); // add the new
    }
    bpJoined = check; // this empties anything that might have been in BPJoined and puts in only the new values
    
    return shouldbeTrue;
}

void verifyGuestList (const std::string& fsearch, const std::string& lsearch, const BirthdayParty& bpOne, BirthdayParty& bpResult){   
    
    BirthdayParty check;
    
    // result should now be a copy of bpOne
    if (lsearch == "*" && fsearch == "*" ){
        check = bpOne;
    }
        
    // if last name is inputted to search
    else if (fsearch == "*" && lsearch != "*"){
        for (int i=0; i< bpOne.whosOnTheGuestList(); i++){
                   string first;
                   string last;
                   BirthdayType val;
                   bpOne.selectInvitee(i, first, last, val);
                    if (lsearch == last){
                        check.addInvitee(first, last, val);
                    }
        }
    }
    
    // if the first name is inputted
    else if (lsearch == "*" && fsearch != "*" ){
        for (int i=0; i< bpOne.whosOnTheGuestList(); i++){
        string first;
        string last;
        BirthdayType val;
        bpOne.selectInvitee(i, first, last, val);
            if (fsearch == first){
                check.addInvitee(first, last, val);
            }
        
        }
    }
    
    else if (lsearch != "*" && fsearch != "*" ){
        for (int i=0; i< bpOne.whosOnTheGuestList(); i++){
        string first;
        string last;
        BirthdayType val;
        bpOne.selectInvitee(i, first, last, val);
            if (fsearch == first && lsearch == last){
                check.addInvitee(first, last, val);
            }
        
        }
    }
    bpResult = check;
}


