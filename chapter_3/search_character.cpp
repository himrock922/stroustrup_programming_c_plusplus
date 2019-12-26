#include "std_lib_facilities.h"

int main()
{
  int number_of_words = 0;
  string previous = " ";
  string current;
  while(cin >> current) {
    ++number_of_words;
    if(previous == current)
      cout << "word nunmber " << number_of_words << " repeated: " << current << endl;
    previous = current;
  }
}