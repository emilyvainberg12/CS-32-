//
//  main.cpp
//  cs 32- proj 2
//
//  Created by Emily Vainberg on 7/10/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//


#include <string>
#include <iostream>
#include <cassert>
#include "BirthdayParty.h"

using namespace std;

int main (){

BirthdayParty One;
    One.addInvitee("Kobe", "Bryant" , "emily");
    One.addInvitee("Emily", "Vainberg" , "large");
    One.addInvitee("Adam", "Bryant" , "small");
    One.addInvitee("Zack", "Bryant" , "baby");
    
    One.addOrModify("Barb", "Lexie" ,"final");
    
    
    for (int n = 0; n < One.whosOnTheGuestList(); n++){
                string first;
                string last;
                string val;
                One.selectInvitee (n, first, last, val);
                cout << first << " " << last << " " << val << endl;
            }

    One.dropFromGuestList("Emily", "Vainberg");
    One.dropFromGuestList("Barb", "Lexie");
    
    cout << "List One: " <<endl;
           for (int n = 0; n < One.whosOnTheGuestList(); n++){
                  string first;
                  string last;
                  string val;
                  One.selectInvitee (n, first, last, val);
                  cout << first << " " << last << " " << val << endl;
              }
    cout << "all tests passed" <<endl;
    }
