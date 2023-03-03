#include<iostream>
#include<cstdlib>
using namespace std;


int main(int argc , char* argv[] ) {
    float sum = 0;
    int N = argc;
    if(argc <= 1) {
        cout << "Please input numbers to find average.\n";
    }else{
        cout << "---------------------------------\n";
        for(int i = 0;i < N;i++) {
            sum += atof(argv[i]);
        }
        sum = sum/(argc-1);
        cout << "Average of " << argc-1 << " numbers = " << sum << endl;
        cout << "---------------------------------\n";
    }
}
