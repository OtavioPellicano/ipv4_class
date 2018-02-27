#include "ipv4.h"

namespace opmm {

Ipv4::Ipv4(const unsigned char &oct_1, const unsigned char &oct_2, const unsigned char &oct_3, const unsigned char &oct_4, const unsigned char &mask) throw(std::domain_error)
{

    mUlIpv4 = (oct_1<<desloc_1)|(oct_2<<desloc_2)|(oct_3<<desloc_3)|oct_4;

    mBit = mask;

    if(mask != 0)
    {

        if(mask >=8 && mask <= 32)
        {
            mUlNetwork = (ULONG_MAX<<(32-mask))&(mUlIpv4);  //Definindo o limite inferior
            mUlBroadCast = (~(ULONG_MAX<<(32-mask)))|(mUlIpv4);
        }
        else
        {
            throw std::domain_error("mask should be between 8 and 32");
        }
    }
    else
    {
        mUlBroadCast = mUlIpv4;
        mUlNetwork = mUlIpv4;
    }

}

ostream &operator<<(ostream &out, const Ipv4 &ipv4)
{
    unsigned long oct;
    unsigned long mask = 255;

    if(ipv4.mBit != 0)
    {
        oct = ipv4.mUlNetwork;
        out <<"cidr/bit: " << (oct>>ipv4.desloc_1) << "."
            << ((oct>>ipv4.desloc_2)&(mask)) << "."
            << ((oct>>ipv4.desloc_3)&(mask)) << "."
            << ((oct)&(mask)) << "/" << int(ipv4.mBit) << endl;
    }

    oct = ipv4.mUlIpv4;
    out <<"ipv4: " << (oct>>ipv4.desloc_1) << "."
        << ((oct>>ipv4.desloc_2)&(mask)) << "."
        << ((oct>>ipv4.desloc_3)&(mask)) << "."
        << ((oct)&(mask)) << endl;

    if(ipv4.mBit != 0)
    {
        oct = ipv4.mUlNetwork;
        out <<"network: " << (oct>>ipv4.desloc_1) << "."
            << ((oct>>ipv4.desloc_2)&(mask)) << "."
            << ((oct>>ipv4.desloc_3)&(mask)) << "."
            << ((oct)&(mask)) << endl;

        oct = ipv4.mUlBroadCast;
        out <<"broadcast: " << (oct>>ipv4.desloc_1) << "."
            << ((oct>>ipv4.desloc_2)&(mask)) << "."
            << ((oct>>ipv4.desloc_3)&(mask)) << "."
            << ((oct)&(mask)) << endl;
    }




    return out;
}

}

