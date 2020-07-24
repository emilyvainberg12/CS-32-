//
//  recursion.cpp
//
//  Created by Emily Vainberg on 7/20/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.

#include <iostream>
#include <string>
using namespace std;

// Returns the product of two non-negative integers, m and n, using only repeated addition.
int product(unsigned int m, unsigned int n){
    if (n == 0)
        return 0;
    return (m + product(m, n-1));
}

// Returns the number of occurrences of digit in the decimal representation of num. digit is an int between 0 and 9  inclusive.
int digitCount(int num, int digit) {

    if (num / 10 == 0){
        if (num == digit)
            return 1;
        else
            return 0;
    }
    
    else if (num % 10 == digit)
        return 1 + digitCount(num/10, digit);
    
    return digitCount(num/10, digit);
}

// Returns a string where the same characters next each other in string n are separated by "333"
string terribleTriplets(string n)
{
    if (n.size() == 0) // base case: when I have checked all my letters
        return n;
    string temp;
    temp = n[0];
    
    if (n[0] == n[1]){
        temp += "333";
        return temp +terribleTriplets(n.substr(1)); // calls the
    }
    return temp + terribleTriplets(n.substr(1));
}

// str contains a single pair of square brackets, return a new string made of the square brackets and what they contain
string hipToBeSquare(string str){
    
    if (str[0] != '['){ // deletes all the char before the opening bracket
        return hipToBeSquare(str.substr(1));
    }
    
    if (str[str.size()-1] != ']'){ // deletes all the char after the closing brackets
        return hipToBeSquare(str.substr(0,str.size()-1));
    }
    
    else if (str[0] == '[' && str[str.size()-1]== ']') // base case - when first and last index are the brackets
        return str;
        
    return str;
}

// int ar2[7] = {2, 3, 9, 8, 9, 6, 7};
// Return true if the total of any combination of elements in array a equals the value of the target.
bool summerSolstice(const int a[], int size, int target){
    
    if (target == 0)
        return true;
     
    if (size == 0 && target != 0)
        return false;
    
    int val = target - a[0]; // have a new value equal the target subtracted by the pointer value

    if (summerSolstice(a+1, size-1, val) == true)
        return true;
    
    if (summerSolstice(a+1, size-1, target) == true)
        return true;
    
    return false;
}

bool isThisTheEnd(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
// Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise
    
    if (er == sr && ec == sc) // current location is the end location
        return true;
    
    maze[sr][sc] = '#'; // mark the current location with an #
    
    if (sr+1 <= nRows && maze[sr+1][sc] == '.'){ // if the current position can move DOWN & stil be in bounds
        if (isThisTheEnd(maze, nRows, nCols, sr+1, sc, er, ec) == true){
            return true;
        }
    }
    
    if (sr-1 >= 0 && maze[sr-1][sc] == '.'){ // if the current position can move UP & stil be in bounds
        if (isThisTheEnd(maze, nRows, nCols, sr-1, sc, er, ec) == true){
            return true;
        }
    }
    
    if (sr+1 <= nCols && maze[sr][sc+1] == '.'){ // if the current position can move RIGHT & stil be in bounds
        if (isThisTheEnd(maze, nRows, nCols, sr, sc+1, er, ec) == true){
            return true;
        }
    }
    
    if (sc-1 >= 0 && maze[sr][sc-1] == '.'){ // if the current position can move LEFT & stil be in bounds
        if (isThisTheEnd(maze, nRows, nCols, sr, sc-1, er, ec) == true){
            return true;
        }
    }
 
    return false;
}

int main () {
    
}
