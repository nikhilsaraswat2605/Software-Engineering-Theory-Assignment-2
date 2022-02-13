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
            if (this->primes[i] * this->primes[i] > n)
            {
                cout << n << " is a prime number!"
                     << "\n";
                return;
            }
            if (n % this->primes[i] == 0)
            {
                cout << n << " is a composite number"
                     << "\n";
                return;
            }
        }

        int startindex = this->nStored;
        int startval;
        if (this->nStored == 0)
            startval = 2;
        else
            startval = this->primes[this->nStored - 1] + 1;
        for (int i = startval; i * i <= n; i++)
        {
            if (this->nStored == this->bufsize)
            {
                cout << "error in calculation of primality test of " << n << ", buffer-size is not sufficient"
                     << "\n";
                return;
            }
            bool flag = 0;
            for (int j = 0; j < this->nStored; j++)
            {
                if (i % this->primes[j] == 0)
                {
                    flag = 1;
                    break;
                }
                else if (this->primes[j] * this->primes[j] > i)
                {
                    break;
                }
            }
            if (flag)
                continue;
            this->primes[nStored++] = i;
        }
        for (int i = startindex; i < this->nStored; i++)
        {
            if (n % this->primes[i] == 0)
            {
                cout << n << " is a composite number"
                     << "\n";
                return;
            }
        }

        cout << n << " is a prime number!"
             << "\n";
    } // Implement
    void printprime()
    {
        for (int i = 0; i < nStored; i++)
        {
            cout << primes[i] << endl;
        }
    }
};
PrimalityTest *PrimalityTest::_myTest = NULL;
int main()
{
    PrimalityTest::newTest().test(2958);
    PrimalityTest::newTest().test(823);
    PrimalityTest::newTest().test(10000007);

    return 0;
}