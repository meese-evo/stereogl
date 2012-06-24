/*
* Folgende Libs dem Linker hinzufügen
* - sfml-system
 */

#include <SFML/System.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
    Clock Clock;
    while (Clock.GetElapsedTime() < 5.f)
    {
     cout << Clock.GetElapsedTime() << endl;
        Sleep(0.5f);
    }

    return 0;
}
