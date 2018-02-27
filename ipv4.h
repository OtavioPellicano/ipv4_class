#ifndef IPV4_H
#define IPV4_H

#include <iostream>
#include <climits>
#include <cmath>
#include <stdexcept>


using namespace std;
namespace opmm {

class Ipv4
{
public:
    Ipv4(const unsigned char& oct_1, const unsigned char& oct_2, const unsigned char& oct_3, const unsigned char& oct_4, const unsigned char &mask = 0) throw(std::domain_error);

private:

    friend ostream &operator<<(ostream &out, const Ipv4 &ipv4);

    unsigned long mUlIpv4;
    unsigned long mUlBroadCast;
    unsigned long mUlNetwork;

    unsigned char mBit;

    const unsigned char desloc_1 = 24;
    const unsigned char desloc_2 = 16;
    const unsigned char desloc_3 = 8;



};



}


#endif // IPV4_H
