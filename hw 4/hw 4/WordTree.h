//
//  WordTree.hpp
//  hw 4
//
//  Created by Emily Vainberg on 8/6/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//

#ifndef WORDTREE_H
#define WORDTREE_H

#include <iostream>
#include <string>
typedef std::string WordType;

struct WordNode {
   WordType m_data;
   WordNode *m_left = nullptr;
   WordNode *m_right = nullptr;
   int m_count;
   // You may add additional data members and member functions in WordNode
};

class WordTree {
   private: // add all helper functions to private
       WordNode *root;
       int InOrderCounter(WordNode *cur) const;
       int totalWordsHelper(WordNode *cur) const;
       void DeleteNodes(WordNode *current);
       void PrintNodes(WordNode* current) const;
       void CopyNodes(WordNode* &current, WordNode* &rhs) const;
   public:
      // default constructor
      WordTree():root(nullptr) {};
      
    // copy constructor
      WordTree(const WordTree& rhs);
      
    // assignment operator
      const WordTree& operator=(const WordTree& rhs);
      
    // Inserts v into the WordTree
      void add(WordType v);
      
    // Returns the number of distinct words / nodes
      int distinctWords() const;
      
    // Returns the total number of words inserted, including duplicate values
        int totalWords() const;
        
    // Prints the LinkedList
    friend std::ostream& operator<<(std::ostream &out, const WordTree& rhs);
        
    // Destroys all the dynamically allocated memory in the tree
          ~WordTree();
    
};


#endif /* WordTree_H */
