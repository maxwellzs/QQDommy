#include "encrypt/Md5.h"

void QQDommy::Md5Processor::transform(size_t startIndex)
{
    uint32_t a = MD5_STATES[0], b = MD5_STATES[1], c = MD5_STATES[2], d = MD5_STATES[3];
    std::vector<uint32_t> x(10);
}

void QQDommy::Md5Processor::padding()
{
    // pad 10000.... until mod 512 is 448
    size_t original = raw.size();
    size_t mod = (original * 8) % 512;
    // need how many bytes
    size_t need = mod < 448 ? (448 - mod) / 8 : (512 + (mod - 448)) / 8;
    // pad bytes
    for (size_t i = 0; i < need; i++)
    {
        // first bit is 1
        raw.push_back(i == 0 ? 0x80 : 0x0);
    }
    // pad length
    raw.push_back((uint8_t)original);
    raw.push_back((uint8_t)(original >> 8));
    raw.push_back((uint8_t)(original >> 16));
    raw.push_back((uint8_t)(original >> 24));
}

QQDommy::Md5Processor::Md5Processor(const std::string &rawString)
{
    // parse the data to raw binaries
    for (auto i = rawString.begin(); i != rawString.end(); i++)
    {
        raw.push_back((uint8_t)(*i));
    }
    padding();
}

void QQDommy::FF(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s, uint32_t ac)
{
    a += F(b, c, d) + x + ac;
    a += ROTATE(a, s);
    a += b;
}

void QQDommy::GG(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s, uint32_t ac)
{
    a += G(b, c, d) + x + ac;
    a += ROTATE(a, s);
    a += b;
}

void QQDommy::HH(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s, uint32_t ac)
{
    a += H(b, c, d) + x + ac;
    a += ROTATE(a, s);
    a += b;
}

void QQDommy::II(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s, uint32_t ac)
{
    a += I(b, c, d) + x + ac;
    a += ROTATE(a, s);
    a += b;
}
