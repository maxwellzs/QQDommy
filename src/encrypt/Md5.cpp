#include "encrypt/Md5.h"

QQDommy::Md5Processor::Md5Processor(const std::string &rawString)
{
    // parse the data to raw binaries
    for(auto i = rawString.begin();i != rawString.end();i ++) {
        raw.push_back((uint8_t)(*i));
    }
}
void QQDommy::FF(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t *x, uint32_t s, uint32_t ac)
{
}

void QQDommy::GG(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t *x, uint32_t s, uint32_t ac)
{
}

void QQDommy::HH(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t *x, uint32_t s, uint32_t ac)
{
}

void QQDommy::II(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t *x, uint32_t s, uint32_t ac)
{
}
