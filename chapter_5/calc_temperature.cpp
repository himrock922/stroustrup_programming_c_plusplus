#include "std_lib_facilities.h"
#include "float.h"

int main()
{
  vector<double> temps;
  double temp = 0.0;
  double sum = 0.0;
  double high_temp = DBL_MIN;
  double low_temp = DBL_MAX;

  while(cin>>temp)
    temps.push_back(temp);
  for(int i = 0; i < temps.size(); ++i) {
    if(temps[i] > high_temp) high_temp = temps[i];
    if(temps[i] < low_temp) low_temp = temps[i];
    sum += temps[i];
  }

  cout << "High temperature: " << high_temp << endl;
  cout << "Low temperature: " << low_temp << endl;
  cout << "Average temperature: " << sum / temps.size() << endl;
}