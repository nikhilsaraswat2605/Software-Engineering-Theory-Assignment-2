#include <iostream>
using namespace std;
class PrimalityTest
{
    static PrimalityTest *_myTest;
    int nStored; // Number of Stored Primes
    int *primes; // Pointer to Buffer
    int bufsize; // Size of the buffer
    PrimalityTest(int bufsize)
    {
        this->nStored = 0;
        this->bufsize = bufsize;
        this->primes = new int[100];
    } // Implement
    ~PrimalityTest()
    {
        delete[] primes;
    } // Implement
public:
    static PrimalityTest &newTest(int bufsize = 100)
    {
        if (!_myTest)
        {
            _myTest = new PrimalityTest(bufsize);
        }
        return *_myTest;
    } // Implement
    void test(int n)
    {
        for (int i = 0; i < this->nStored; i++)
        {
            if (n % this->primes[i] == 0)
            {
                cout << n << " is a composite number"
                     << "\n";
                return;
            }
        }
        if (nStored == 0)
        {
            int startindex = nStored;
            int startval;
            if (nStored == 0)
                startval = 2;
            else
                startval = primes[nStored - 1] + 1;
            for (int i = startval; i * i <= n; i++)
            {
                if (nStored == bufsize)
                {
                    cout << "error in calculation, buffersize is not sufficient"
                         << "\n";
                    return;
                }
                for (int j = 0; j < this->nStored; j++)
                {
                    if (primes[j] * primes[j] > i)
                    {
                        break;
                    }
                    if (i % primes[j] == 0)
                    {
                        break;
                    }
                }
                primes[nStored++] = i;
            }
            for (int i = startindex; i < nStored; i++)
            {
                if (n % primes[i] == 0)
                {
                    cout << n << " is a composite number"
                         << "\n";
                    // this->primes[this->nStored++] = n;
                    return;
                }
            }
        }

        cout << n << " is a prime number!"
             << "\n";
    } // Implement
};
PrimalityTest *PrimalityTest::_myTest = NULL;
int main()
{
    PrimalityTest::newTest().test(2958);
    PrimalityTest::newTest().test(823);
    PrimalityTest::newTest().test(83479);
    return 0;
}