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
    test_md5();

    CLEAN_UP
    return 0;
}

void test_buffer()
{
    using namespace QQDommy;
    ByteBuffer b,c;
    b.writeHexString("1A 2B 3C 4D");
    c.writeBuffer(b);
    DEBUG_ASYN(c.toHexString());
}

void test_md5() {
    using namespace QQDommy;
    ByteBuffer b = Md5Processor("admin").digest32();
    DEBUG_ASYN(b.toHexString());
}

void test_vistor()
{
    using namespace QQDommy;
    ByteBuffer b;
    TestTlvPack p;
    b.doVisit(p).doVisit(p);
    DEBUG_ASYN(b.toHexString());
}
