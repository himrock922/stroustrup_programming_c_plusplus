#include "std_lib_facilities.h"

int main()
{
    cout << "Please enter a two names: " << endl;
    string values = "";

    while(true) {
        cin >> values;
        if( values.compare("zero") == 0) {
            cout << "0" << endl;
        } else if( values.compare("one") == 0) {
            cout << "1" << endl;
        } else if( values.compare("two") == 0) {
            cout << "2" << endl;
        } else if( values.compare("three") == 0) {
            cout << "3" << endl;
        } else if( values.compare("four") == 0) {
            cout << "4" << endl;
        } else {
            cout << "not a number I know" << endl;
            break;
        }
    }
}