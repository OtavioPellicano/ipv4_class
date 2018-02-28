#ifndef IPV4_H
#define IPV4_H

#include <iostream>
#include <climits>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
namespace opmm {

class Ipv4
{
public:
    Ipv4();
    Ipv4(const unsigned char& oct_1, const unsigned char& oct_2, const unsigned char& oct_3, const unsigned char& oct_4, const unsigned char &mask = 0) throw(std::domain_error);
    Ipv4(string &cidr) throw(exception, out_of_range, invalid_argument, domain_error);

    ~Ipv4();

    unsigned long ulBroadCast() const;
    unsigned long ulNetwork() const;

    void setup(const unsigned char& oct_1, const unsigned char& oct_2, const unsigned char& oct_3, const unsigned char& oct_4, const unsigned char &mask = 0) throw(std::domain_error);

    void setup(string &cidr) throw(exception, out_of_range, invalid_argument, domain_error);

private:

    friend ostream &operator<<(ostream &out, const Ipv4 &ipv4);

    unsigned long mUlIpv4;
    unsigned long mUlBroadCast;
    unsigned long mUlNetwork;

    unsigned char mBit;

    const unsigned char mDesloc_1 = 24;
    const unsigned char mDesloc_2 = 16;
    const unsigned char mDesloc_3 = 8;

    vector<unsigned int> mVecIpCidr;


};



}


#endif // IPV4_H
