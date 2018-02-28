#include "ipv4.h"

namespace opmm {

Ipv4::Ipv4(const unsigned char &oct_1, const unsigned char &oct_2, const unsigned char &oct_3, const unsigned char &oct_4, const unsigned char &mask) throw(std::domain_error)
{
    try {
        this->setup(oct_1, oct_2, oct_3, oct_4, mask);
    } catch (...) {
        throw;
    }

}

Ipv4::Ipv4(string &cidr) throw(exception, out_of_range, invalid_argument, domain_error)
{
    mVecIpCidr.resize(5);
    unsigned char pos = 0;
    unsigned char qntPontos = 0;
    unsigned char qntBarras = 0;
    string::iterator itInicio = cidr.begin();
    for(string::iterator itStr = cidr.begin(); itStr != cidr.end(); ++itStr)
    {
        try {
            if(*itStr == '.')
            {
                mVecIpCidr[pos++] = stoul((string(itInicio, itStr)));
                itInicio = itStr + 1;
                if(++qntPontos > 3)
                    throw out_of_range("acceptable values: cidr/bit or ipv4");

            }
            if(*itStr == '/')
            {
                mVecIpCidr[pos++] = stoul(string(itInicio, itStr));
                itInicio = itStr + 1;

                mVecIpCidr[pos] = stoul(string(itInicio, cidr.end()));
                if(++qntBarras > 1)
                    throw out_of_range("acceptable values: cidr/bit or ipv4");
            }
        } catch(invalid_argument)
        {
            throw invalid_argument("acceptable values: cidr/bit or ipv4");
        }
        catch (exception) {
            throw;
        }
    }

    try {
        if((qntBarras == 0))
            mVecIpCidr[pos] = stoul(string(itInicio, cidr.end()));
    } catch (invalid_argument) {
        throw invalid_argument("acceptable values: cidr/bit or ipv4");
    } catch(exception)
    {
        throw;
    }


    if((qntPontos == 0))
        throw out_of_range("acceptable values: cidr/bit or ipv4");

    if(mVecIpCidr[0] > 255 || mVecIpCidr[1] > 255 || mVecIpCidr[2] > 255 || mVecIpCidr[3] > 255 || mVecIpCidr[4] > 32)
        throw domain_error("octet domain_error");

    this->setup(mVecIpCidr[0], mVecIpCidr[1], mVecIpCidr[2], mVecIpCidr[3], mVecIpCidr[4]);

}

unsigned long Ipv4::ulBroadCast() const
{
    return mUlBroadCast;
}

unsigned long Ipv4::ulNetwork() const
{
    return mUlNetwork;
}

void Ipv4::setup(const unsigned char &oct_1, const unsigned char &oct_2, const unsigned char &oct_3, const unsigned char &oct_4, const unsigned char &cidr_bit) throw(std::domain_error)
{
    mUlIpv4 = (oct_1<<mDesloc_1)|(oct_2<<mDesloc_2)|(oct_3<<mDesloc_3)|oct_4;

    mBit = cidr_bit;

    if(cidr_bit != 0)
    {

        if(cidr_bit >=8 && cidr_bit <= 32)
        {
            mUlNetwork = (ULONG_MAX<<(32-cidr_bit))&(mUlIpv4);  //Definindo o limite inferior
            mUlBroadCast = (~(ULONG_MAX<<(32-cidr_bit)))|(mUlIpv4);
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
        oct = ipv4.mUlIpv4;
        out <<"cidr/bit: " << (oct>>ipv4.mDesloc_1) << "."
            << ((oct>>ipv4.mDesloc_2)&(mask)) << "."
            << ((oct>>ipv4.mDesloc_3)&(mask)) << "."
            << ((oct)&(mask)) << "/" << int(ipv4.mBit) << endl;
    }

    oct = ipv4.mUlIpv4;
    out <<"ipv4: " << (oct>>ipv4.mDesloc_1) << "."
        << ((oct>>ipv4.mDesloc_2)&(mask)) << "."
        << ((oct>>ipv4.mDesloc_3)&(mask)) << "."
        << ((oct)&(mask)) << endl;

    if(ipv4.mBit != 0)
    {
        oct = ipv4.mUlNetwork;
        out <<"network: " << (oct>>ipv4.mDesloc_1) << "."
            << ((oct>>ipv4.mDesloc_2)&(mask)) << "."
            << ((oct>>ipv4.mDesloc_3)&(mask)) << "."
            << ((oct)&(mask)) << endl;

        oct = ipv4.mUlBroadCast;
        out <<"broadcast: " << (oct>>ipv4.mDesloc_1) << "."
            << ((oct>>ipv4.mDesloc_2)&(mask)) << "."
            << ((oct>>ipv4.mDesloc_3)&(mask)) << "."
            << ((oct)&(mask)) << endl;
    }

    return out;
}

}

