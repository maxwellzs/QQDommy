/**
 * @file ByteBuffer.h
 * @author maxwellzs
 * @brief In this file a byte buffer is provided
 * a byte buffer is a util class that allows read, write and slice
 * a buffer received from the network should be read BE
 *
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright GNU
 *
 */

#include <cstdint>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <string>
#include <map>
#include <exception>
#include <sstream>

#ifndef ByteBuffer_h
#define ByteBuffer_h

namespace QQDommy
{

    /**
     * @brief thrown when passing a maleformed hex string to bytebuffer
     *
     */
    class IllegalHexExprException : public std::exception
    {
    private:
        std::string expr;

    public:
        IllegalHexExprException(const std::string &expr);
        const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override;
    };

    /**
     * @brief thrown when reading or writing of the buffer is out of bound
     *
     */
    class BufferOutOfBoundException : public std::exception
    {
    public:
        const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override;
    };

    class ReadOnlyBufferException : public std::exception
    {
    public:
        const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override;
    };

    const static std::map<int8_t, char> HEX_CHAR = {
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}};
    const static std::map<char, int8_t> HEX_VAL = {
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'A', 0xa}, {'B', 0xb}, {'C', 0xc}, {'D', 0xd}, {'E', 0xe}, {'E', 0xf}};
    const static size_t DEFAULT_BUFFER_SIZE = 64;

    class ByteBuffer
    {
    private:
        /// @brief the inner buffer
        uint8_t *data = nullptr;
        /// @brief the index used to indicate the last postion of read/write
        size_t readIndex = 0;
        size_t writeIndex = 0;
        size_t capacity = DEFAULT_BUFFER_SIZE;
        /// @brief if writing an read only buffer . throw a @ReadOnlyBufferException 
        bool isReadOnly = false;
        void resize();
        /**
         * @brief decide whether the buffer needs a resize
         *
         * @param s the number of bytes of the incoming data
         */
        void check_resize(size_t s);
        void check_readOnly();
        void check_outOfBound(size_t val);
    public:
        /// @brief create an empty buffer
        ByteBuffer();
        ~ByteBuffer();
        /**
         * @brief belows are the functions that alters or read from the buffer
         *
         * @param v
         * @return ByteBuffer&
         */
        ByteBuffer &write_uint8(uint8_t v);
        ByteBuffer &write_uint16(uint16_t v);
        ByteBuffer &write_uint32(uint32_t v);
        ByteBuffer &write_uint64(uint64_t v);

        /**
         * @brief read integer value in the form of big endain
         * 
         * @return the integer value
         */
        uint8_t read_uint8();
        uint16_t read_uint16Be();
        uint32_t read_uint32Be();
        uint64_t read_uint64Be();

        /**
         * @brief parse the buffer into the form of hex string
         * all the data until writeIndex will be included
         *
         * @return std::string the formatted string
         */
        std::string toHexString();

        /**
         * @brief write a string of bytes in the form of hex data
         * e.g. std::string DATA("1A 2B 34 55");
         * every character must be in the form of the data in hex char, other throw
         *
         * @return ByteBuffer&
         */
        ByteBuffer &writeHexString(const std::string &expr);
        /**
         * @brief write a std::vector<uint8_t> into the buffer
         * 
         * @return ByteBuffer& this
         */
        ByteBuffer &writeByteVector(const std::vector<uint8_t> &expr);

        /**
         * @brief slice will return a new byte buffer with new pointer 
         * and new read & write index
         * the returned buffer is READ ONLY
         * 
         * @param length the length to cut from the beginning of the buffer
         * @return ByteBuffer the new buffer
         */
        ByteBuffer slice(size_t length);
        ByteBuffer slice(size_t offset,size_t length);
    };

};

#endif