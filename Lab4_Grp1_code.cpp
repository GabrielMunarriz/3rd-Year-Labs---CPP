#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

struct Node {
    string value;
    Node* nextNode;

    Node(){
        value = "";
        nextNode = NULL;
    };
};

class StringStack {
    private:
        Node* stackPtr;
    public:

        void Push(string value){
            
            Node* push = new Node;

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
                cout << "There is nothing on the stack" << endl;
            } else {
                Node* pop = stackPtr;
                // ReadPopValue(pop);
                stackPtr = stackPtr->nextNode;
                pop->nextNode = NULL;
                delete pop;
            }
        };

        string Peek() {

            if (stackPtr == NULL) {
                cout << "There is nothing on the stack" << endl;
            }

            return stackPtr->value;
        }

        // void ReadPopValue(Node* r){  
        //     cout << "The value " << r->value <<" has been popped." << endl;
        // };

        void ReadValue(Node* r){
            cout << r->value << endl;
        };

        void PrintAll(){
            Node* print = stackPtr;

            while(print != NULL){
                ReadValue(print);
                print = print->nextNode;
            }
        };

        // string ReturnValueOfNode(int nodeNumber){

        //     int iterator = 0;
        //     Node* current = stackPtr;

        //     while(current != NULL && iterator != nodeNumber){
        //         current = current->nextNode;
        //         iterator += 1;
        //     }

        //     return current->value;
        // };

        int NumberOfNodes(){
            int total = 0;
            Node* counter = stackPtr;
            
            while(counter != NULL){
                total += 1;
                counter = counter->nextNode;
            }

            return total;
        }

        StringStack(){
            stackPtr = NULL;
        }

        //deconstructor
        ~StringStack(){
            
            Node* pointer1;
            Node* pointer2;

            pointer1 = stackPtr;

            while(pointer1 != NULL){
                pointer2 = pointer1;
                pointer1 = pointer1->nextNode;
                pointer2->nextNode = NULL;
                delete pointer2;

            }
        
        };

};

int main() {
    
    int firstNumber;
    int secondNumber;
    int product;

    int base = 2;
    int exponent = 1;
    int powerOfTwo = pow(base,exponent);

    StringStack* Instructions = new StringStack();
    int numberOfInstructions;
    
    cout << "Enter a number" << endl;
    cin >> firstNumber;
    product = firstNumber;
    cout << "Enter another number" << endl;
    cin >> secondNumber;

    while (true) {

        if (secondNumber == 0){ // if second number is 0, manually set the product to 0 and break the loop

            product = 0;
            break;

        } else if (secondNumber == 1) { // if second number is 1, break the loop

            // cout << "Else 1" << endl;
            // Instructions->PrintAll();
            break;

        } else if (secondNumber == -1) { // if second number is -1, manually set the product to -firstNumber and break the loop.

            product = 0 - firstNumber;
            break;
        
        } else if (secondNumber < -1) { // if second number is less than -1, negate the first number and make secondNumber positive. Make sure product is updated based on value of first number.

            firstNumber = 0 - firstNumber;
            secondNumber = abs(secondNumber);
            product = firstNumber;

            //cout << firstNumber << endl;
            //cout << secondNumber << endl;

        } else if (secondNumber > 1) { // if the second number is greater than 1...

            // cout << "If 1" << endl;

            if (secondNumber % 2 > 0) { // ...check if the number is odd. If it is, subtract 1 from secondNumber and add an "A" instruction to the stack. ...

                // cout << "If 2" << endl;
                secondNumber -= 1;
                Instructions->Push("A");
                // cout << secondNumber << endl;

            } else { // ...if the number is even...

                // cout << "Else 2" << endl;

                if (secondNumber % powerOfTwo == 0) { // ...check if it is divisible by 2^n. If it is, increase the exponent and update 2^n. ...

                    // cout << "If 3" << endl;
                    exponent += 1;
                    powerOfTwo = pow(base,exponent);     
                    // cout << secondNumber << endl;  

                } else { //... if it is no longer divisible by a power of two, subtract the exponent, update 2^n, divide secondNumber by the updated 2^n, and add an "MX" instruction to the stack where X is equal to the current value of the exponent.
                    // cout << "Else 3" << endl;

                    exponent -=1;
                    powerOfTwo = pow(base,exponent);
                    secondNumber = secondNumber / powerOfTwo;
                    Instructions->Push("S" + to_string(exponent));
                    // cout << secondNumber << endl;

                }
            }
        } 
    }

    numberOfInstructions = Instructions->NumberOfNodes();

    for (int i = 0; i < numberOfInstructions; i++){

        // cout << "enter for loop" << endl;

        char forLoopExponentChar;
        int forLoopBase = 2;
        int forLoopExponent;
        int forLoopPowerOfTwo = pow(forLoopBase, forLoopExponent);

        if (Instructions->Peek()[0] == 'A'){ // Mimics the "Add" command

            // cout << "For Loop If 1" << endl;
            product = product + firstNumber;
            //cout << product << endl;
            Instructions->Pop();

        } else if (Instructions->Peek()[0] == 'S'){ // Mimics the shift command where you multiply by powers of 2. This is essentially an arithmetic shift to the left done as much times as the value of the exponent.
            
            // cout << "For Loop If 2" << endl;
            forLoopExponentChar = Instructions->Peek()[1];
            forLoopExponent = forLoopExponentChar - '0'; // Char conversion from ASCII equivalent to the actual integer
            forLoopPowerOfTwo = pow(forLoopBase, forLoopExponent);
            product = product * forLoopPowerOfTwo;
            //cout << product << endl;
            Instructions->Pop();
        }
    
    }

    cout << "The product is " << product << endl;

    delete Instructions;

    return 0;
}