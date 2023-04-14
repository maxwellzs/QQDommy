/**
 * @file Tlv.h
 * @author maxwellzs
 * @brief this file defines the tlv packets that was used in oicq
 * @version 0.1
 * @date 2023-04-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "utils/ByteBuffer.h"

#ifndef Tlv_h
#define Tlv_h

namespace QQDommy
{

    /// @brief test whether visitor can work
    class TestTlvPack : public BufferVisitor
    {
    public:
        void visit(ByteBuffer &ref) const override;
    };

};

#endif