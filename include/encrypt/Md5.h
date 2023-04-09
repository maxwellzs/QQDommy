/**
 * @file Md5.h
 * @author maxwellzs
 * @brief this file defines the md5 digest methods
 * @version 0.1
 * @date 2023-04-08
 *
 * @copyright GNU
 *
 */

#include <vector>
#include <string>
#include <cstdint>
#include "utils/ByteBuffer.h"

#ifndef Md5_h
#define Md5_h

namespace QQDommy
{

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define ROTATE(x, n) (((x) << (n)) | ((x) >> (32-(n))))

    inline static void FF(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s,uint32_t ac);
    inline static void GG(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s,uint32_t ac);
    inline static void HH(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s,uint32_t ac);
    inline static void II(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t s,uint32_t ac);

    /// @brief A,B,C,D
    const static std::vector<uint32_t> MD5_STATES = {
        0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};

    class Md5Processor
    {
    private:
        /// @brief the original data
        std::vector<uint8_t> raw;
        std::vector<uint32_t> magicNumber = {MD5_STATES[0],MD5_STATES[1],MD5_STATES[2],MD5_STATES[3]};
        void transform(size_t startIndex);
        void padding();
        /**
         * @brief decode the given bytes into vector of vec<int32>
         * 64byte will be decoded into 16 integer
         * 
         * @param index the start of the decode prossess
         * @return std::vector<uint32_t> 
         */
        std::vector<uint32_t> decodeBytes(size_t index);
    public:
        /**
         * @brief Construct a new Md 5 Processor object, holding a string
         * calling the method "digest" will return the md5 result of this string
         *
         * @param rawString the raw data
         */
        Md5Processor(const std::string &rawString);
        /**
         * @brief digest the raw and return the 32 bit digest result
         * 
         * @param output the output buffer that will hold the result
         * @return ByteBuffer the buffer holding the result
         */
        void digest32(ByteBuffer &output);
    };

};

#endif