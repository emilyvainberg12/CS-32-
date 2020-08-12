//
//  WordTree.cpp
//  hw 4
//
//  Created by Emily Vainberg on 8/6/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//

#include "WordTree.h"

using namespace std;


void WordTree::CopyNodes(WordNode* &current, WordNode* &rhs) const{
    
    if (rhs == nullptr)
        current = nullptr;
    
    else{
        current = new WordNode;
        current->m_count = rhs->m_count;
        current->m_data = rhs->m_data;
        CopyNodes(current->m_left, rhs->m_left);
        CopyNodes(current->m_right,rhs->m_right);
    }
}

   // copy constructor
WordTree::WordTree(const WordTree& rhs){ //PREORDER trsversal
    
    WordNode *temp = rhs.root;
    
    if (temp == nullptr)
        root = nullptr;
    
    else
        CopyNodes(this->root, temp);
}
     
   // assignment operator
const WordTree& WordTree::operator=(const WordTree& rhs){
   
    //check for aliasing
    if (&rhs == this)
        return *this;
       
    //delete all the nodes in the current list
    
    WordNode* temp = rhs.root;
    
    DeleteNodes(this->root);
        
    // if rhs is empty, return the emopty list
    if (temp == nullptr){
        root = nullptr;
        return *this;
    }
    
    CopyNodes(this->root, temp);
    return  *this;
    
}
     
   // Inserts v into the WordTree
void WordTree::add(WordType v){
    
//    If the tree is empty
    if (root == nullptr){
        root = new WordNode;
        root->m_data = v;
        root->m_count = 1;
        return;
    }
    
    WordNode *current = root;
    
    for (;;){ // begin the traversal
        
        if (v == current->m_data){
            current->m_count++;
            return; //don't add the same word into the tree
        }
        
        if (v < current->m_data){ // if the word is smaller than the first word, since its a loop the 'current' changes
            if (current->m_left != nullptr){
                current = current->m_left; // keep traversing though the nodes
            }
            else{ // once we reach an empty node thats where it can be added
                current->m_left = new WordNode;
                current->m_left->m_data = v;
                current->m_left->m_count = 1;
                return;
            }
        }
        else if (v > current->m_data){ // if the value is greater, we move to the right until we get to the nullptr and add
            if (current->m_right != nullptr)
                current = current->m_right;
            else {
                current->m_right = new WordNode; // this would become the new largest word
                current->m_right->m_data = v;
                current->m_right->m_count = 1;
                return;
            }
        }
    }
}


int WordTree::InOrderCounter(WordNode *cur) const { // INORDER TRAVERSAL
    if (cur == nullptr)
        return 0;
    
    return 1 + InOrderCounter(cur->m_left);
    return 1 + InOrderCounter(cur->m_right);
}
     
   // Returns the number of distinct words / nodes
int WordTree::distinctWords() const{
    
    WordNode *current = root;
    return InOrderCounter(current);
}


int WordTree::totalWordsHelper(WordNode *current) const {
    if (current == nullptr)
         return 0;
    
    return current->m_count + totalWordsHelper(current->m_left);     // Process nodes in left sub-tree
return current-> m_count + totalWordsHelper(current-> m_right);  // Process nodes in right sub-tree
}

     
   // Returns the total number of words inserted, including duplicate values
int WordTree::totalWords() const{ //PREORDER TRAVERSAL
    
    WordNode *current = root;
    return totalWordsHelper(current);
}
       
   // Prints the LinkedList

void WordTree::PrintNodes(WordNode* current) const{
    if (current == nullptr)
        return;
    
    PrintNodes(current->m_left);
    cout << current->m_data << " " << current->m_count <<endl;
    PrintNodes(current->m_right);
}

ostream& operator<<(std::ostream &out, const WordTree& rhs){ //INORDER TRAVERSAL
    
    rhs.PrintNodes(rhs.root);
    return out;
}


void WordTree::DeleteNodes(WordNode *current){ //POST ORDER
    if (current == nullptr)
        return;
    
    DeleteNodes(current->m_left);
    DeleteNodes(current->m_right);
    
    delete current;
}
       
   // Destroys all the dynamically allocated memory in the tree
WordTree::~WordTree(){
    WordNode* current = root;
    DeleteNodes(current);
}
   



