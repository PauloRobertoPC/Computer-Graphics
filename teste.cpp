#include <iostream>
#include <cstdarg>

using namespace std;

double average(int num,...) {
    va_list valist;
    double sum = 0.0;
    int i;
    va_start(valist, num); //initialize valist for num number of arguments
    for (i = 0; i < num; i++) { //access all the arguments assigned to valist
        sum += va_arg(valist, int);
    }
    va_end(valist); //clean memory reserved for valist
    return sum/num;
}

int main() {
    cout << average(5, 10, 10, 10, 10, 10) << "\n";
}
