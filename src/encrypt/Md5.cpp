#include "encrypt/Md5.h"

void QQDommy::Md5Processor::transform(size_t startIndex)
{
    uint32_t a = magicNumber[0], b = magicNumber[1], c = magicNumber[2], d = magicNumber[3];
    std::vector<uint32_t> x = decodeBytes(startIndex);
    // round 1
    FF(a, b, c, d, x[0], 7, 0xd76aa478);
    FF(d, a, b, c, x[1], 12, 0xe8c7b756);
    FF(c, d, a, b, x[2], 17, 0x242070db);
    FF(b, c, d, a, x[3], 22, 0xc1bdceee);
    FF(a, b, c, d, x[4], 7, 0xf57c0faf);
    FF(d, a, b, c, x[5], 12, 0x4787c62a);
    FF(c, d, a, b, x[6], 17, 0xa8304613);
    FF(b, c, d, a, x[7], 22, 0xfd469501);
    FF(a, b, c, d, x[8], 7, 0x698098d8);
    FF(d, a, b, c, x[9], 12, 0x8b44f7af);
    FF(c, d, a, b, x[10], 17, 0xffff5bb1);
    FF(b, c, d, a, x[11], 22, 0x895cd7be);
    FF(a, b, c, d, x[12], 7, 0x6b901122);
    FF(d, a, b, c, x[13], 12, 0xfd987193);
    FF(c, d, a, b, x[14], 17, 0xa679438e);
    FF(b, c, d, a, x[15], 22, 0x49b40821);

    // round 2
    GG(a, b, c, d, x[1], 5, 0xf61e2562);
    GG(d, a, b, c, x[6], 9, 0xc040b340);
    GG(c, d, a, b, x[11], 14, 0x265e5a51);
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, x[5], 5, 0xd62f105d);
    GG(d, a, b, c, x[10], 9, 0x2441453);
    GG(c, d, a, b, x[15], 14, 0xd8a1e681);
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, x[9], 5, 0x21e1cde6);
    GG(d, a, b, c, x[14], 9, 0xc33707d6);
    GG(c, d, a, b, x[3], 14, 0xf4d50d87);
    GG(b, c, d, a, x[8], 20, 0x455a14ed);
    GG(a, b, c, d, x[13], 5, 0xa9e3e905);
    GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
    GG(c, d, a, b, x[7], 14, 0x676f02d9);
    GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);

    // round 3
    HH(a, b, c, d, x[5], 4, 0xfffa3942);
    HH(d, a, b, c, x[8], 11, 0x8771f681);
    HH(c, d, a, b, x[11], 16, 0x6d9d6122);
    HH(b, c, d, a, x[14], 23, 0xfde5380c);
    HH(a, b, c, d, x[1], 4, 0xa4beea44);
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, x[10], 23, 0xbebfbc70);
    HH(a, b, c, d, x[13], 4, 0x289b7ec6);
    HH(d, a, b, c, x[0], 11, 0xeaa127fa);
    HH(c, d, a, b, x[3], 16, 0xd4ef3085);
    HH(b, c, d, a, x[6], 23, 0x4881d05);
    HH(a, b, c, d, x[9], 4, 0xd9d4d039);
    HH(d, a, b, c, x[12], 11, 0xe6db99e5);
    HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, x[2], 23, 0xc4ac5665);

    // round 4
    II(a, b, c, d, x[0], 6, 0xf4292244);
    II(d, a, b, c, x[7], 10, 0x432aff97);
    II(c, d, a, b, x[14], 15, 0xab9423a7);
    II(b, c, d, a, x[5], 21, 0xfc93a039);
    II(a, b, c, d, x[12], 6, 0x655b59c3);
    II(d, a, b, c, x[3], 10, 0x8f0ccc92);
    II(c, d, a, b, x[10], 15, 0xffeff47d);
    II(b, c, d, a, x[1], 21, 0x85845dd1);
    II(a, b, c, d, x[8], 6, 0x6fa87e4f);
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, x[6], 15, 0xa3014314);
    II(b, c, d, a, x[13], 21, 0x4e0811a1);
    II(a, b, c, d, x[4], 6, 0xf7537e82);
    II(d, a, b, c, x[11], 10, 0xbd3af235);
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, x[9], 21, 0xeb86d391);
    magicNumber[0] += a;
    magicNumber[1] += b;
    magicNumber[2] += c;
    magicNumber[3] += d;
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
    // pad length 64 bits
    raw.push_back((uint8_t)( (original * 8) & 0xff));
    raw.push_back((uint8_t)(((original * 8) >> 8) & 0xff));
    raw.push_back((uint8_t)(((original * 8) >> 16) & 0xff));
    raw.push_back((uint8_t)(((original * 8) >> 24) & 0xff));
    raw.push_back((uint8_t)(((original * 8) >> 32) & 0xff));
    raw.push_back((uint8_t)(((original * 8) >> 40) & 0xff));
    raw.push_back((uint8_t)(((original * 8) >> 48) & 0xff));
    raw.push_back((uint8_t)(((original * 8) >> 56) & 0xff));
}

std::vector<uint32_t> QQDommy::Md5Processor::decodeBytes(size_t index)
{
    std::vector<uint32_t> temp;
    // run 16 times
    for (size_t i = index; i < index + 64; i += 4)
    {
        uint32_t h1 = raw[i];
        uint32_t h2 = raw[i+1];
        uint32_t h3 = raw[i+2];
        uint32_t h4 = raw[i+3];
        temp.push_back(h1 + (h2 << 8) + (h3 << 16) + (h4 << 24));
    }
    return temp;
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

void QQDommy::Md5Processor::digest32(ByteBuffer &output)
{
    size_t block = 0;
    size_t all = (raw.size() * 8) / 512;
    while (block < all)
    {
        transform(block * 64);
        block++;
    }
    // turn magic to buffer
    output.write_uint32(magicNumber[0]);
    output.write_uint32(magicNumber[1]);
    output.write_uint32(magicNumber[2]);
    output.write_uint32(magicNumber[3]);
    // reset magic number
    magicNumber.clear();
    magicNumber = {MD5_STATES[0],MD5_STATES[1],MD5_STATES[2],MD5_STATES[3]};
}

void QQDommy::FF(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s, uint32_t ac)
{
    a += F(b, c, d) + x + ac;
    a = ROTATE(a, s);
    a += b;
}

void QQDommy::GG(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s, uint32_t ac)
{
    a += G(b, c, d) + x + ac;
    a = ROTATE(a, s);
    a += b;
}

void QQDommy::HH(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s, uint32_t ac)
{
    a += H(b, c, d) + x + ac;
    a = ROTATE(a, s);
    a += b;
}

void QQDommy::II(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s, uint32_t ac)
{
    a += I(b, c, d) + x + ac;
    a = ROTATE(a, s);
    a += b;
}
