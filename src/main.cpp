#include <iostream>
#include "Global.h"
#include "utils/ByteBuffer.h"

void test_buffer();

int main(int args, char **argv)
{
    DEBUG_ASYN("test started");
    test_buffer();

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
