#include "sj_math.h"
#include <iostream>
#include <cstdio>
#include <assert.h>
using namespace std;
int main() {
    int a = 240, b = 46;
    int x, y, g;
    g = sj::xgcd(a, b, &x, &y);
    printf("a=%d b=%d, x=%d, y=%d, g=%d\n", a, b, x, y, g);

    const int p = 8191;
    const int p2 = 8197;
    for(int i = 1; i < p; i++) {
        int j = sj::mod_inverse(i, p);
        if(i*j%p != 1) {
            printf("error\n");
        }
        
    }

    using sj::ModNumber;
    ModNumber<p> n1 = 13;
    auto n2 = n1.inv();
    auto n3 = n1 + 10000;
    auto n4 = n1 - 10000;
    auto n5 = n1  * 12345;
    auto n6 = 1 / n1;
    cout << n2 << endl;
    cout << n3 << endl;
    cout << n4 << endl;
    cout << n5 << endl;
    cout << n6 << endl;

    ModNumber<p2> m1 = 17;
    auto m2 = 3 / m1;
    cout << (m2 * m1) << endl;
    return 0;
}
