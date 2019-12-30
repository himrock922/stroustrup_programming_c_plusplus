#include "std_lib_facilities.h"

void bubblesort(string *array, int size){
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if(array[i].at(0) > array[j].at(0)){
                string number = array[i];
                array[i] = array[j];
                array[j] = number;
            }
        }
    }
}

int main()
{
    cout << "Please enter a two names: " << endl;
    unique_ptr<string[]> values = make_unique<string[]>(3);

    for(int i = 0; i < 3; i++) {
        cin >> values[i];
    }
    bubblesort(values.get(), 3);

    for(int i = 0; i < 3; i++) {
        cout  << values[i] << endl;
    }
}