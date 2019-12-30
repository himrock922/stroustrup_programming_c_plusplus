#include "std_lib_facilities.h"

int square(int x);

int main()
{
    int result = 0;
    cin >> result;
    cout << square(result) << endl;
}

int square(int x) {
    return x * x;
}