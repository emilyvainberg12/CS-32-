//
//  BirthdayParty.h
//  cs 32- proj 2
//
//  Created by Emily Vainberg on 7/8/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//

#ifndef BIRTHDAYPARTY_H
#define BIRTHDAYPARTY_H

#include <string>

typedef std::string BirthdayType;

class BirthdayParty{
    private:
        struct Node {   // since its a doubly-linked list, I want both a next and a previous node to create two directions
            Node *next;
            Node *previous;
            std::string LastName;
            std::string firstName;
            BirthdayType value;
        };
        Node* head;
        Node* tail;

    public:
        BirthdayParty(); // Create an empty BirthdayParty list
    
        ~BirthdayParty(); // Destructor
    
        BirthdayParty(const BirthdayParty& other); // copy constructor
        // When a brand new BirthdayParty is created as a copy of an existing BirthdayParty, a deep copy should be made.
    
        BirthdayParty& operator=(const BirthdayParty& rhs); //assignment operator
        
        bool noInvitees() const; // Return true if the BirthdayParty list is empty, otherwise false.
    
        int whosOnTheGuestList() const; // Return the number of players in the BirthdayParty list.

        bool addInvitee(const std::string& firstName, const std::string& lastName, const BirthdayType& value);
// If the full name (both the first and last name) is not equal to any full name currently in the list then add it and return true. Elements should be added according to their last name. Elements with the same last name should be added according to their first names. Otherwise, make no change to the list and return false (indicating that the name is already in the list).
       
        bool modifyInvitee(const std::string& firstName, const std::string& lastName, const BirthdayType& value);
// If the full name is equal to a full name currently in the list, then make that full name no longer map to the value it currently maps to, but instead map to the value of the third parameter; return true in this case. Otherwise, make no change to the list and return false.
        
        bool addOrModify(const std::string& firstName, const std::string& lastName, const BirthdayType& value);
// If full name is equal to a name currently in the list, then make that full name no longer map to the value it currently maps to, but instead map to the value of the third parameter. If the full name is not equal to any full name currently in the list then add it this function always returns true.
        
        bool dropFromGuestList(const std::string& firstName, const std::string& lastName);
// If the full name is equal to a full name currently in the list, remove the full name and value from the list and return true. Otherwise, make no change to the list and return false.
        
        bool personOnGuestList(const std::string& firstName, const std::string& lastName) const;
      // Return true if the full name is equal to a full name currently in the list, otherwise false.
        
        bool checkGuestList(const std::string& firstName, const std::string& lastName, BirthdayType& value) const;
// If the full name is equal to a full name currently in the list, set value to the value in the list that that full name maps to, and return true. Otherwise, make no change to the value parameter of this function and return false.
        
        bool selectInvitee(int i, std::string& firstName, std::string& lastName, BirthdayType& value) const;
// If 0 <= i < size(), copy into firstName, lastName and value parameters the corresponding information of the element at position i in the list and return true. Otherwise, leave the parameters unchanged and return false. 
        
        void changeGuestList(BirthdayParty& other);
// Exchange the contents of this list with the other one.
    
};

// not member functions

bool combineGuestLists(const BirthdayParty & bpOne, const BirthdayParty & bpTwo, BirthdayParty & bpJoined);
   //When this function returns, bpJoined must consist of pairs determined by these rules:
   //If a full name appears in exactly one of bpOne and bpTwo, then bpJoined must contain an element consisting of that full name and its corresponding value.
    
   //If a full name appears in both bpOne and bpTwo, with the same corresponding value in both, then bpJoined must contain an element with that full name and value.
   //When this function returns, bpJoined must contain no elements other than those required by these rules. (You must not assume bpJoined is empty when it is passed in to this function; it might not be.)
   //If there exists a full name that appears in both bpOne and bpTwo, but with different corresponding values, then this function returns false; if there is no full name like this, the function returns true. Even if the function returns false, result must be constituted as defined by the above rules.
   
  void verifyGuestList (const std::string& fsearch, const std::string& lsearch, const BirthdayParty& bpOne, BirthdayParty& bpResult);
 //When this function returns, bpResult must contain a copy of all the elements in bpOne that match the search terms; it must not contain any other elements. You can wildcard the first name, last name or both by supplying "*". (You must not assume result is empty when it is passed in to this function; it may not be.)

#endif /* BirthdayParty_h */
