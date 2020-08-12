//
//  main.cpp
//  hw 4
//
//  Created by Emily Vainberg on 8/6/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include "WordTree.h"
using namespace std;

int main() {
    
    WordTree w;
    w.add("Harry");
    w.add("Niall");
    w.add("Niall");
    w.add("Liam");
    w.add("Louis");
    w.add("Harry");
    w.add("Niall");
    w.add("Zayn");
   // cout << w;
    
    
    WordTree l;
    l.add("p");
    cout << l;
    
    WordTree X = w;
    
    
    WordTree E;
    WordTree M;
    M.add("Emily");
    M.add("Joe");
    
    E = M;
    
    cout << E;
    
    
    l = w;
    
    cout << l;
}
    
//    ifstream fin;
//    ofstream fout;
//    string filename;
//    cout << "Enter name of file with text to analyze: ";
//    cin >> filename;
//    fin.open(filename.c_str());
//    if (fin.fail()) {
//        cout << "Error opening file.\n";
//        exit(1);
//    }
//    cout << "\nAnalyzing " << filename << ".\n";
//
//    WordTree myTree;
//
//    // insert code here
//
//    fin.close();
//    fout.open("results.txt");
//    cout << "\nWord counts:\n\n";
//    cout << myTree;
//    fout << myTree;
//    cout << "\nTotal number of words in text: " << myTree.totalWords() << ".\n";
//    fout << "\nTotal number of words in text: " << myTree.totalWords() << ".\n";
//    cout << "Number of distinct words appearing in text: "
//         << myTree.distinctWords() << ".\n";
//    fout << "Number of distinct words appearing in text: "
//         << myTree.distinctWords() << ".\n";
//    fout.close();
//    return 0;
//}
