#include "std_lib_facilities.h"

int main()
{
  cout << "Please enter a floating-point value: ";
  int n;
  cin >> n;
  cout << "n == " << n
    << endl << "n+1 == " << n + 1
    << endl << "three times n == " << 3 * n
    << endl << "twice n == " << n * n
    << endl << "half of n == " << n / 2
    << endl << "square root of n == " << sqrt(n)
    << endl;
}