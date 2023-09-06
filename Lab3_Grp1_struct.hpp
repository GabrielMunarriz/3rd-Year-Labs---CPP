#include <iostream>
using namespace std;

struct IntNode {
    int value;
    IntNode* nextNode;

    IntNode(){
        value = 0;
        nextNode = NULL;
    };
};

class IntLinkedList {
    private:
        IntNode* headNode;
        IntNode* currentNode;
        IntNode* tempNode;
    public:
        IntLinkedList(){ //constructor
            headNode = NULL;
            currentNode = NULL;
            tempNode = NULL;
        };

        void AddNode(int newValue){
            IntNode* newNode = new IntNode();
            newNode->value = newValue;
            newNode->nextNode = NULL;

            if (headNode != NULL) { //add node to the very end of the list if a list already exists
                currentNode = headNode;

                while(currentNode->nextNode != NULL){ // traverse list until we reach the very end
                    currentNode = currentNode->nextNode;
                }

                currentNode->nextNode = newNode; 
            } else { //if a list does not exist yet, the new node becomes the head.
                headNode = newNode;
            }
        };

        void DeleteNodeWithValue(int deletedValue){
            IntNode* deleteNode = NULL;
            tempNode = headNode;
            currentNode = headNode;

            while(currentNode != NULL && currentNode->value != deletedValue){ //traverse list until we reach the very end or once we find the value we want to delete.
                tempNode = currentNode;
                currentNode = currentNode->nextNode;
            }

            if(currentNode == NULL){
                cout << deletedValue << " was not in the list." << endl;
                delete deleteNode;
            } else if (currentNode == headNode) {
                deleteNode = currentNode; 
                headNode = headNode->nextNode;
                currentNode = NULL;
                tempNode = NULL;
                delete deleteNode;
                cout << "The value " << deletedValue << " was deleted." << endl;
            } else {
                deleteNode = currentNode;
                currentNode = currentNode->nextNode; // we move current node after the node that's about to get deleted
                tempNode->nextNode = currentNode; // we connect temp node (located right before the node about to be deleted) to the new current node, essentially isolating the node that's about to be deleted.
                delete deleteNode;
                cout << "The value " << deletedValue << " was deleted." << endl;
            }
        }

        void PrintList(){
            currentNode = headNode;

            while(currentNode != NULL){
                cout << currentNode->value << endl;
                currentNode = currentNode->nextNode;
            }

        };
};

class IntStack {
    private:
        IntNode* stackPtr;
    public:
        void Push(int value){
            
            IntNode* push = new IntNode;

            push->value = value;

            if(stackPtr == NULL){               
                stackPtr = push;
                stackPtr->nextNode = NULL;

            }else{               
                push->nextNode = stackPtr;
                stackPtr = push;

            }
        };
        void Pop(){            
            if(stackPtr == NULL){
                cout << "There is nothing on the stack\n";
            }else{
                IntNode* pop = stackPtr;
                ReadPopValue(pop);
                stackPtr = stackPtr->nextNode;
                pop->nextNode = NULL;
                delete pop;
            }
        };

        void ReadPopValue(IntNode* r){  
            cout << "The value " << r->value <<" has been popped." << endl;
        };

        void ReadValue(IntNode* r){
            cout << r->value << endl;
        };
        void Print(){
            IntNode* print = stackPtr;

            while(print != NULL){
                ReadValue(print);
                print = print->nextNode;
            }
        };

        IntStack(){
            stackPtr = NULL;
        }

        //deconstructor
        ~IntStack(){
            
            IntNode* pointer1;
            IntNode* pointer2;

            pointer1 = stackPtr;

            while(pointer1 != NULL){
                pointer2 = pointer1;
                pointer1 = pointer1->nextNode;
                pointer2->nextNode = NULL;
                delete pointer2;

            }
        
        };

};