//
//  main.cpp
//  project 3
//
//  Created by Emily Vainberg on 7/23/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <istream>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


int BasicCounter(string array []){
    if (array[0] == "")
        return 0;
    return 1 + BasicCounter(array +1);
}

// helper function to count words in the results array
int DictCounter(istream &dictfile, string dict[], int count) {
    string line;
    
    if (!getline(dictfile,line)){ // means its empty or we ran out of lines to imput
          return 0;
      }
    
    if (count == MAXDICTWORDS)
        return 0;
    
    *dict = line;
    return 1 + DictCounter(dictfile,dict+1, count+1); // adds the numbers of strings in the results array
}

int createDict(istream &dictfile, string dict[]){
    return DictCounter(dictfile, dict, 0);
}

bool Search(string word, const string dict[], int counter, int size){
    
    if (word == *dict) // if it finds the word in dictionary it should return true
        return true;
    
    if (*dict == "") // since we add one at a time, if it encounters an empty string- it means there are no more words
        return false;
    
    if (counter == size || counter == MAXDICTWORDS) // make sure that the counter does not exceed the maxDict
        return false;

    return Search(word, dict+1, counter+1, size);
}

void printPermutations(string prefix, string rest, string results[], const string dict[], int size);

void Loop(int init, int max, string prefix, string rest, string results[], const string dict [], int size){
    
    if (init >= max) // this is the code to keep iterating through the loop until rest runs out
        return;
    
    string next = prefix + rest[init];
    string remaining = rest.substr(0,init)+ rest.substr(init+1);

    printPermutations(next, remaining, results, dict, size);
    Loop(init+1, max, prefix, rest, results, dict, size);
}


// helper function that finds all the permutations of the word- and puts it correctlty into results
void printPermutations(string prefix, string rest, string results[], const string dict[], int size) {
    
    if (rest == ""){
        // start by checking if the word is in the dictionary & not in the results
        if (Search(prefix, dict,0, size) == true && Search(prefix, results,0, size) == false){
            int count = BasicCounter(results); // should check that the results is also less than MAXRESULTS
                if (count < MAXRESULTS){  // Check results has less than 20 words
                    results[count] = prefix;
                }
        }
    }
    Loop(0, rest.size(), prefix, rest, results, dict, size);
}

//Puts all the possibilities of word which are found in dict into results.
//The size is the number of words inside the dict array
int characterMixer(string word, const string dict[], int size, string results[]){
    
    printPermutations("", word, results, dict, size);
    return BasicCounter(results); //Returns the number of matched words found.
}

void ViewHelper (const string results[], int size, int count){
    
    if (count == MAXRESULTS) // if the count reaches the max- just return
        return;
    
    if (size!= 0){
           cout << results[0] <<endl;
           ViewHelper(results+1, size-1, count+1);
    }
}

//Displays 'size' number of strings from results. The results can be printed in any order.
void viewAnswers(const string results[], int size){
    ViewHelper(results, size, 0);
}


int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    nwords = createDict(dictfile, dict);
    
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = characterMixer(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        viewAnswers(results, numMatches);

    return 0;
}


   
