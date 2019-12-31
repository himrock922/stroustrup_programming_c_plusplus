#include "std_lib_facilities.h"
#include "float.h"

bool IsPrime(int num);

int main()
{
    vector<int> checking_primes;
    vector<int> checked_primes;
    for(int i = 1; i <= 100; ++i) {
        checking_primes.push_back(i);
    }
    for(int i = 0; i < checking_primes.size(); ++i) {
        if(IsPrime(checking_primes[i])) {
            checked_primes.push_back(checking_primes[i]);
        }
    }
    cout << "Primes List" << endl;
    for(int i = 0; i < checked_primes.size(); ++i) {
        cout << checked_primes[i] << " ";
    }
    cout << endl;
}

bool IsPrime(int num) {
    if(num < 2) return false;
    if(num == 2) return true;
    if(num %2 == 0) return false;

    double sqrtNum = sqrt(num);
    for (int i = 3; i <= sqrtNum; i += 2)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}


