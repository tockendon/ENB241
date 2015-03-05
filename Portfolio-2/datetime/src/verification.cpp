/* verification.cpp
 * ENB241 Portfolio 2
 *
 * Linking verification app
 *
 * 08/04/2014 - D. Chen
 *
 *     DO NOT MODIFY
 */

#include <iostream>
#include <time1.h>
#include <datetime.h>


// Execute every function so link is attempted
int main(int argc, char *argv[])
{
    Time t1;
    Time t2(1, 1, 1);
    Time t3("01:01:01");
    
    t1.toString();
    t1.toString12();
    t1.compare(t2);
    t1.calcSeconds(t2);
    t1.increment();
    
    Date d;
    DateTime d1;
    DateTime d2(d, t1);
    DateTime d3("1000/10/10 10:10:10");
    
    d1.toString();
    d1.toString12();
    d1.compare(d2);
    d1.calcSeconds(d2);
    d1.calcDays(d2);
    d1.increment();
    d1.incrementDays();

    std::cout << "\033[32mAll functions successfully linked\033[0m" << std::endl;
    return 0;
}
