#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    int i;
    char text[15]="Hello World!";
    
    for (i=0; i<=4; i++){
        printf("%i. printf: %s\n",i, text);
        cout << i << ". cout: " << text << endl;
    }

    return 0;
}

