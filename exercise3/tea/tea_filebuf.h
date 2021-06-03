
#pragma once

#include <array>
#include <cstdint>
#include <streambuf>
#include <strstream>
#include <cstring>
#include <cstdint>


const auto g_tea_key = std::array<std::uint32_t, 4>{{ 0xA04D1BF9u, 0x082D1191u, 0xc2B959D7u, 0x1E35969Cu }};


// Implement your TEA stream buffer here

class vxor_streambuf: public std::streambuf
{
public:
    vxor_streambuf(std::streambuf *buffer, const int width) :
            buffer(buffer),
            size(width / 2)
    {
        previous_line = new char[size];
        std::memset(previous_line, 0, size);
        current_line = new char[size];
        setg(0, 0, 0);
        setp(current_line, current_line + size);
    }

    ~vxor_streambuf() override
    {
        sync();
        delete[] previous_line;
        delete[] current_line;
    }

    std::streambuf::int_type underflow() override
    {
        // Read line from original buffer
        std::streamsize read = buffer->sgetn(current_line, size);
        if (!read) return traits_type::eof();

        // Do vertical XOR decoding
        for (int i = 0; i < size; i += 1)
        {
            current_line[i] ^= previous_line[i];
            previous_line[i] = current_line[i];
        }

        setg(current_line, current_line, current_line + read);
        return traits_type::to_int_type(*gptr());
    }

    virtual std::streambuf::int_type overflow(std::streambuf::int_type value)
    {
        int write = pptr() - pbase();
        if (write)
        {
            // Do vertical XOR encoding
            for (int i = 0; i < size; i += 1)
            {
                char tmp = current_line[i];
                current_line[i] ^= previous_line[i];
                previous_line[i] = tmp;
            }

            // Write line to original buffer
            std::streamsize written = buffer->sputn(current_line, write);
            if (written != write) return traits_type::eof();
        }

        setp(current_line, current_line + size);
        if (!traits_type::eq_int_type(value, traits_type::eof())) sputc(value);
        return traits_type::not_eof(value);
    };

    virtual int sync()
    {
        std::streambuf::int_type result = this->overflow(traits_type::eof());
        buffer->pubsync();
        return traits_type::eq_int_type(result, traits_type::eof()) ? -1 : 0;
    }

private:
    std::streambuf *buffer;
    int size;
    char *previous_line;
    char *current_line;
};


/*** vxor_istream class ********************************************/

class vxor_istream: public std::istream
{
public:
    vxor_istream(std::istream &stream, const int width) :
            std::istream(new vxor_streambuf(stream.rdbuf(), width)) {}

    virtual ~vxor_istream()
    {
        delete rdbuf();
    }
};


/*** vxor_ostream class ********************************************/

class vxor_ostream: public std::ostream
{
public:
    vxor_ostream(std::ostream &stream, const int width) :
            std::ostream(new vxor_streambuf(stream.rdbuf(), width)) {}

    virtual ~vxor_ostream()
    {
        delete rdbuf();
    }
};



#include <cstdint>

void encrypt (uint32_t v[2]) {
    uint32_t v0=v[0], v1=v[1], sum=0;           /* set up */
    uint32_t delta=0x9E3779B9;                     /* a key schedule constant */
    uint32_t k0=g_tea_key[0], k1=g_tea_key[1], k2=g_tea_key[2], k3=g_tea_key[3];   /* cache key */
    for (uint32_t i=0; i<32; i++) {                         /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

void decrypt (uint32_t v[2]) {
    uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720;  /* set up; sum is (delta << 5) & 0xFFFFFFFF */
    uint32_t delta=0x9E3779B9;                     /* a key schedule constant */
    uint32_t k0=g_tea_key[0], k1=g_tea_key[1], k2=g_tea_key[2], k3=g_tea_key[3];   /* cache key */
    for (uint32_t i=0; i<32; i++) {                         /* basic cycle start */
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        sum -= delta;
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}
