#include "utils/ByteBuffer.h"

void QQDommy::ByteBuffer::resize()
{
    size_t newSize = capacity * 2;
    uint8_t *newBuffer = new uint8_t[newSize];
    // only copy the part with original data
    memcpy(newBuffer, data, writeIndex);
    // delete the previous
    delete data;
    data = newBuffer;
}

void QQDommy::ByteBuffer::check_readOnly()
{
    if (isReadOnly)
        throw ReadOnlyBufferException();
}

void QQDommy::ByteBuffer::check_outOfBound(size_t val)
{
    if (val + readIndex > writeIndex)
        throw BufferOutOfBoundException();
}

void QQDommy::ByteBuffer::check_resize(size_t s)
{
    if (s + writeIndex > capacity)
    {
        // out of bound
        // operate resize instantly
        resize();
    }
}

QQDommy::ByteBuffer::ByteBuffer()
{
    // initialize buffer

    this->data = new uint8_t[DEFAULT_BUFFER_SIZE];
}

QQDommy::ByteBuffer::~ByteBuffer()
{
    // initialize buffer

    if (!isReadOnly)
        delete data;
}

#define check_before_write         \
    this->check_resize(sizeof(v)); \
    check_readOnly();

QQDommy::ByteBuffer &QQDommy::ByteBuffer::write_uint8(uint8_t v)
{
    // TODO: 在此处插入 return 语句
    check_before_write
        uint8_t value = v;
    memcpy(data + writeIndex, &value, sizeof(value));
    writeIndex += sizeof(v);

    return *this;
}

QQDommy::ByteBuffer &QQDommy::ByteBuffer::write_uint16(uint16_t v)
{
    // TODO: 在此处插入 return 语句
    check_before_write
        uint16_t value = ((v & 0xff) << 8) + ((v & 0xff00) >> 8);
    memcpy(data + writeIndex, &value, sizeof(value));
    writeIndex += sizeof(v);

    return *this;
}

QQDommy::ByteBuffer &QQDommy::ByteBuffer::write_uint32(uint32_t v)
{
    // TODO: 在此处插入 return 语句
    check_before_write
        uint32_t value = ((v & 0x000000ff) << 24) + ((v & 0x0000ff00) << 8) + ((v & 0x00ff0000) >> 8) + ((v & 0xff000000) >> 24);
    memcpy(data + writeIndex, &value, sizeof(v));
    writeIndex += sizeof(v);
    return *this;
}

QQDommy::ByteBuffer &QQDommy::ByteBuffer::write_uint64(uint64_t v)
{
    // TODO: 在此处插入 return 语句
    check_before_write
        // swap endian
        uint64_t value = ((v & 0xff) << 56) + ((v & 0xff00) << 40) + ((v & 0xff0000) << 24) + ((v & 0xff000000) << 8) + ((v & 0xff00000000) >> 8) + ((v & 0xff0000000000) >> 24) + ((v & 0xff000000000000) >> 40) + ((v & 0xff00000000000000) >> 56);
    memcpy(data + writeIndex, &value, sizeof(value));
    writeIndex += sizeof(v);

    return *this;
}

uint8_t QQDommy::ByteBuffer::read_uint8()
{
    // TODO: 在此处插入 return 语句
    check_outOfBound(sizeof(uint8_t));
    uint8_t value = data[readIndex];
    readIndex++;
    return value;
}

uint16_t QQDommy::ByteBuffer::read_uint16Be()
{
    uint16_t b1 = ((uint16_t)read_uint8()) << 8;
    uint16_t b2 = ((uint16_t)read_uint8());
    return b1 + b2;
}

uint32_t QQDommy::ByteBuffer::read_uint32Be()
{
    uint32_t b1 = ((uint32_t)read_uint8()) << 24,
             b2 = ((uint32_t)read_uint8()) << 16,
             b3 = ((uint32_t)read_uint8()) << 8,
             b4 = ((uint32_t)read_uint8());
    return b1 + b2 + b3 + b4;
}

uint64_t QQDommy::ByteBuffer::read_uint64Be()
{
    uint64_t b1 = ((uint64_t)read_uint8()) << 56,
             b2 = ((uint64_t)read_uint8()) << 48,
             b3 = ((uint64_t)read_uint8()) << 40,
             b4 = ((uint64_t)read_uint8()) << 32,
             b5 = ((uint64_t)read_uint8()) << 24,
             b6 = ((uint64_t)read_uint8()) << 16,
             b7 = ((uint64_t)read_uint8()) << 8,
             b8 = ((uint64_t)read_uint8());
    return b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8;
}

std::string QQDommy::ByteBuffer::toHexString()
{
    std::string result;
    for (size_t i = 0; i < writeIndex; i++)
    {
        uint8_t currentByte = data[i];
        uint8_t h4 = currentByte >> 4;
        uint8_t l4 = currentByte & 0x0f;
        result += HEX_CHAR.at(h4);
        result += HEX_CHAR.at(l4);
        result += ' ';
    }

    return result;
}

QQDommy::ByteBuffer &QQDommy::ByteBuffer::writeHexString(const std::string &expr)
{
    // TODO: 在此处插入 return 语句
    std::string word;
    std::istringstream reader(expr);

    while (reader >> word)
    {
        // loop hex
        // hex should be in pair
        if (word.length() != 2)
            throw IllegalHexExprException(expr);
        if (HEX_VAL.find(word.at(0)) == HEX_VAL.end() || HEX_VAL.find(word.at(0)) == HEX_VAL.end())
            throw IllegalHexExprException(expr);
        // not male formed
        int8_t h4 = HEX_VAL.at(word.at(0));
        int8_t l4 = HEX_VAL.at(word.at(1));
        write_uint8(l4 + (h4 << 4));
    }

    // noerror
    return *this;
}

QQDommy::ByteBuffer &QQDommy::ByteBuffer::writeByteVector(const std::vector<uint8_t> &expr)
{
    // TODO: 在此处插入 return 语句
    for (auto i = expr.begin(); i != expr.end(); i++)
    {
        write_uint8(*i);
    }
    return *this;
}

QQDommy::ByteBuffer QQDommy::ByteBuffer::slice(size_t length)
{
    return slice(0, length);
}

QQDommy::ByteBuffer QQDommy::ByteBuffer::slice(size_t offset, size_t length)
{
    ByteBuffer inherit;
    // illegal operation, reaching the limit of the buffer
    if (offset >= writeIndex ||
        length == 0 ||
        length + offset >= writeIndex)
        throw BufferOutOfBoundException();
    inherit.data = this->data + offset;
    inherit.writeIndex = length;
    // no writing the read only
    inherit.isReadOnly = true;
    return inherit;
}

QQDommy::IllegalHexExprException::IllegalHexExprException(const std::string &expr)
{
    this->expr = "error expr : " + expr;
}

const char *QQDommy::IllegalHexExprException::what() const noexcept
{
    return expr.c_str();
}

const char *QQDommy::BufferOutOfBoundException::what() const noexcept
{
    return "the buffer operation was out of bound";
}

const char *QQDommy::ReadOnlyBufferException::what() const noexcept
{
    return "trying to read an read only buffer";
}