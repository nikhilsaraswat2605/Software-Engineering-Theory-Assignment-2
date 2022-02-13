#include <iostream>
using namespace std;
class PrimalityTest
{
    static PrimalityTest *_myTest; // static pointer object of the class PrimalityTest
    int nStored;                   // Number of Stored Primes
    int *primes;                   // Pointer to Buffer
    int bufsize;                   // Size of the buffer

    PrimalityTest(int bufsize) // constructor
    {
        this->nStored = 0;
        this->bufsize = bufsize;
        this->primes = new int[bufsize]; // allocating memory for buffer array
    }                                    // Implement
    ~PrimalityTest()                     // destructor
    {
        delete[] primes; // de-allocating memory for the primes arraY (buffer array)
    }                    // Implement
public:
    static PrimalityTest &newTest(int bufsize = 100)
    {
        // if _mytest pointer is 'None' type then allocate memory for new objext of class PrimalityTest
        // else return the same object
        if (!_myTest)
        {
            _myTest = new PrimalityTest(bufsize);
        }
        return *_myTest;
    } // Implement
    void test(int n)
    {
        if (n < 2)
        {
            cout << n << " is neither a prime nor a composite number!"
                 << "\n";
            return;
        }
        for (int i = 0; i < this->nStored; i++) // first try to check primality using stored primes of the buffer array
        {
            if (this->primes[i] * this->primes[i] > n) // if our buffer array has not been exhausted and any of the available primes are not able to divide the given number 'n', then declare n as a 'prime' number
            {
                cout << n << " is a prime number!"
                     << "\n";
                return;
            }
            if (n % this->primes[i] == 0) // else if any of the prime numbers of buffer array divides 'n' then declare 'n' as a 'prime' number
            {
                cout << n << " is a composite number"
                     << "\n";
                return;
            }
        }

        int startindex = this->nStored; // just for storing the starting index for appending more primes in the buffer array in available memory
        int startval;
        if (this->nStored == 0) // if we are handling the first test, then take 2 as the start value
        {
            startval = 2;
        }
        else // else take successor integer of the last stored prime number
        {
            startval = this->primes[this->nStored - 1] + 1;
        }
        for (int i = startval; i * i <= n; i++) // now we are taking all integers till sqrt(n)
        {
            if (this->nStored == this->bufsize) // if buffer size is not sufficient, so we shall not consider this test as a valid test, because the data which we are using for primality testing of 'n', that won't be saved for future usage
            {
                cout << "error in calculation of primality test of " << n << ", buffer-size is not sufficient"
                     << "\n";
                return;
            }
            bool flag = false;
            for (int j = 0; j < this->nStored; j++) // we are checking the new prime number which will be appended with the stored
            {
                if (i % this->primes[j] == 0) // if the new candidate prime number is divivsible by previously stored primes, then this is not eligible for primes, discard this prime number, so mark flag as true
                {
                    flag = true;
                    break;
                }
                else if (this->primes[j] * this->primes[j] > i) // if primes square is going more than candidate prime number, then break and store this number as new prime in buffer array
                {
                    break;
                }
            }
            if (flag)
                continue;
            this->primes[nStored++] = i;
        }
        for (int i = startindex; i < this->nStored; i++) // now since we have updated the primes array (buffer array), so we can check the primality of n, this will not affect time complexity of the code
        {
            if (n % this->primes[i] == 0) // if divisible by any of the primes stored in the buffer array, then print composite and return
            {
                cout << n << " is a composite number"
                     << "\n";
                return;
            }
        }

        // at last if n is not divisible any of the prime number numbers then print it as a prime
        cout << n << " is a prime number!"
             << "\n";
    } // Implement
};

// intitializing the _myTest pointer as NULL
PrimalityTest *PrimalityTest::_myTest = NULL;

int main()
{
    PrimalityTest::newTest().test(2958); // this time we are first calling newTest, so it will static object of the PrimalityTest class
    // now we are again calling newTest, but now this will not allocate meory for new object, but return the previously created object of the PrimalityTest class
    PrimalityTest::newTest().test(823);
    PrimalityTest::newTest().test(83479);

    return 0;
}
