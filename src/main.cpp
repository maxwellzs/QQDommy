#include <iostream>
#include "Global.h"
#include "utils/ByteBuffer.h"
#include "encrypt/Md5.h"
#include "core/Tlv.h"

void test_buffer();
void test_md5();
void test_vistor();

int main(int args, char **argv)
{
    DEBUG_ASYN("test started");
    test_vistor();

    CLEAN_UP
    return 0;
}

void test_buffer()
{
    using namespace QQDommy;
    ByteBuffer b;
    b.writeByteVector({0xab,0xbc,0xab,0xcd,0x0});
    b.read_uint16Be();
    b.read_uint8();
}

void test_md5() {
    using namespace QQDommy;
    ByteBuffer out;
    Md5Processor p("abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd");
    p.digest32(out);
    DEBUG_ASYN(out.toHexString());
}

void test_vistor()
{
    using namespace QQDommy;
    ByteBuffer b;
    TestTlvPack p;
    b.doVisit(p).doVisit(p);
    DEBUG_ASYN(b.toHexString());
}
