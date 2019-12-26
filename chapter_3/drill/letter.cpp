#include "std_lib_facilities.h"

int main() {
  cout << "Enter the name of the person you want to write to" << endl;
  string first_name = "";
  string friend_name = "";
  char friend_gender = 0;
  cin >> first_name;
  cout << "Enter the your friend name" << endl;
  cin >> friend_name;
  cout << "What is gender that your friend?(if man, please input 'm', But if girl, please input 'f')" << endl;
  cin >> friend_gender;
  cout << "Dear " << first_name << "," << endl;
  cout << "How are you? I am fine. I miss you" << endl;
  cout << "Have you seen " << friend_name << " lately?" << endl;
  cout << "If you see " << friend_name << " plaese ask " <<
  ((friend_gender == 'm') ? "him" : "her") << " to call me" << endl;
}