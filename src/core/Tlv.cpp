#include "core/Tlv.h"

void QQDommy::TestTlvPack::visit(ByteBuffer &ref) const
{
    ref.writeByteVector({0xab,0xcd});
}