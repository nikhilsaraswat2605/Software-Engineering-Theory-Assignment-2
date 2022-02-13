#include <iostream>
using namespace std;
class PrimalityTest
{
    static PrimalityTest *_myTest;
    int nStored;                // Number of Stored Primes
    int *primes;                // Pointer to Buffer
    int bufsize;                // Size of the buffer
    PrimalityTest(int bufsize); // Implement
    ~PrimalityTest();           // Implement
public:
    static PrimalityTest &newTest(int bufsize = 100)
    {
        if (!_myTest)
        {
            _myTest->primes = new int[100];
        }
        return
    }                 // Implement
    void test(int n); // Implement
};
PrimalityTest *PrimalityTest::_myTest = NULL;
int main()
{
    PrimalityTest::newTest().test(2958);
    PrimalityTest::newTest().test(823);
    PrimalityTest::newTest().test(83479);
    return 0;
}