#include <iostream>
#include <cstdlib>
#include <sys/unistd.h>
#include <sys/types.h>


int main(int argc, char* argv[])
{

    using namespace std;
    char c;
    while ((c = getchar()) != 'q')
    {
        sleep(1);
        cout << "input character:";
        getchar();
    }
    exit(EXIT_SUCCESS);
}