#include <iostream>
#include <string>
using namespace std;

int main()
{
    string input;
    string agentMessage;
    int agentCoordinate1;
    int agentCoordinate2;
    int numberOfAgents;

    getline(cin, input);
    numberOfAgents = stoi(input);

    for(int i = 0; i <= numberOfAgents-1; i++){
        
        getline(cin, input, ' ');
        agentCoordinate1 = stoi(input);

        getline(cin, input, ' ');
        agentCoordinate2 = stoi(input);

        cout << "Agent#" << i + 1 << " is at (" << agentCoordinate1 << ", " << agentCoordinate2 << ")" << endl;

        getline(cin, input);
        agentMessage = input;
        cout << "Says: " << agentMessage << endl;

    }
    return 0;
}