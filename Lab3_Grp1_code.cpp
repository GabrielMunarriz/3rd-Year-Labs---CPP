#include <iostream>
#include "Lab3_Grp1_struct.hpp"
using namespace std;

int main() {
    while (true){

        int linkedListOrStackChoice;

        cout << endl;
        cout << "Program will only accept integers." << endl;
        cout << "MAIN MENU: Press 1 to create a Linked List. Press 2 to create a Stack. Press 3 to Exit: ";
        cin >> linkedListOrStackChoice;
        cout << endl;

        if (linkedListOrStackChoice == 1) {
            int firstNode;
            int linkedListOptionsChoice;
            int newNodeValue;
            int deleteNodeValue;
            IntLinkedList* LinkedList = new IntLinkedList();

            cout << "Let's create a Linked List." << endl;
            cout << "Please specify the value of your first node: ";
            cin >> firstNode;
            cout << endl;
            LinkedList->AddNode(firstNode);

            while (true) {
                cout << "Press 1 to add a new node. Press 2 to delete a node. Press 3 to print your linked list. Press 4 to return to Main Menu: ";
                cin >> linkedListOptionsChoice;
                cout << endl;

                if (linkedListOptionsChoice == 1) {
                    cout << "Please specify the value of your new node: ";
                    cin >> newNodeValue;
                    cout << endl;
                    LinkedList->AddNode(newNodeValue);
                } else if (linkedListOptionsChoice == 2) {
                    cout << "Please specify the value you want to delete: ";
                    cin >> deleteNodeValue;
                    cout << endl;
                    LinkedList->DeleteNodeWithValue(deleteNodeValue);
                } else if (linkedListOptionsChoice == 3) {
                    cout << "The linked list contains:" << endl;
                    LinkedList->PrintList();
                } else if (linkedListOptionsChoice == 4) {
                    delete LinkedList;
                    break;
                } else {
                    cout << "Invalid Input" << endl;
                }
            }
        }
        else if (linkedListOrStackChoice == 2) {
            cout << "Let's create a Stack." << endl;

            IntStack* Stack = new IntStack();
            
            int stackChoice;
            int stackValue;

            while(true){
                cout << "Press 1 to push. Press 2 to pop. Press 3 to print your stack. Press 4 to return to main menu: ";
                cin >> stackChoice;
                cout << endl;

                if(stackChoice == 1){
                    cout << "Please specify value to push: ";
                    cin >> stackValue;
                    cout << endl;
                    Stack->Push(stackValue);
                }
                else if(stackChoice == 2){
                    Stack->Pop();
                }
                else if(stackChoice == 3){
                    cout << "The stack contains:" << endl;
                    Stack->Print();
                }
                else if(stackChoice == 4){
                    delete Stack;
                    break;
                } else{
                    cout << "Invalid input" << endl;
                }
            }
        }
        else if (linkedListOrStackChoice == 3) {
            break;
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }

    return 0;
}