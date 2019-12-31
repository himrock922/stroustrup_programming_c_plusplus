#include "std_lib_facilities.h"
#include "float.h"

void calc_output();

int main()
{
    calc_output();
}

void calc_output() {
    double val1 = 0.0, val2 = 0.0;
    double result = 0.0;
    char val3;
    string formula = "";
    while(true) {
        cin >> val1 >> val2 >> val3;
        if(val3 == '|') {
            exit(0);
        } else {
            switch(val3) {
            case '+':
              formula = "sum";
              result = val1 + val2;
              break;
            case '-':
              formula = "reduce";
              result = val1 - val2;
              break;
            case '*':
              formula = "multiple";
              result = val1 * val2;
              break;
            case '/':
              formula = "division";
              result = val1 / val2;
            }
            cout << "The " << formula << " of " << val1 << " and " << val2 << " is " << result << endl;
        }
    }
}//
// Created by 八木 辰弥 on 2019/12/31.
//

