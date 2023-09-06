#include <iostream>
#include <string.h>
using namespace std;

string get_Tags(string s) {
    int len = s.length();
    string tags = "";
    for (int i = 0; i <= len-2; i++) {
        tags += "#";
    }
    return tags;
}

char get_Character_Increment(char* c){
    char incChar = *c;
	if (isalpha(incChar)) {
		incChar++;
		if(!isalpha(incChar)) {
			incChar -= 26;
		}
	}
	return incChar;
}

int main (void) {
    string name = "";
    string name2 = "";

    cout << "1. ";
    cin >> name;

    cout << "2. " << name << endl;

    cout << "3. " << name[0] << get_Tags(name) << endl;

    for (int i = 0; i <= name.length(); i++) {
       name2 += get_Character_Increment(&name[i]);
	}

    cout << "4. " << name2 << endl;
}