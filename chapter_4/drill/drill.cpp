#include "std_lib_facilities.h"
#include "float.h"

void two_print(string val);

int main()
{
    string val = "";
    two_print(val);
}

void two_print(string val) {
    vector<double> sort_table;
    double target = 0.0;
    double max_value = DBL_MIN, min_value = DBL_MAX;
    while(true) {
        cin >> val;
        if(val == "|") {
            break;
        } else {
            try {
                target = stoi(val);
                cout << "input value: " << target << endl;
                if(max_value < target) {
                    max_value = target;
                    cout << "the largest so far" << endl;
                }
                if(min_value > target) {
                    min_value = target;
                    cout << "the smallest so far" << endl;
                }
                sort_table.push_back(target);
            } catch(const invalid_argument& e){
                cout << val <<  " " << e.what() << endl;
                exit(1);
            }
        }
    }
    sort(sort_table.begin(), sort_table.end());
    for(int i = 0; i < sort_table.size(); ++i) {
        cout << sort_table[i] << endl;
    }
}