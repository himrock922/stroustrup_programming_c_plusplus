#include "std_lib_facilities.h"

int main()
{
    const char alpha = 'a';
    for(int i = 0; i < 26; ++i) {
        cout << char(alpha + i) << " ";
    }
    cout << endl;
}