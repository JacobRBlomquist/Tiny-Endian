/*
        Copyright 2020 Jacob R. Blomquist (Jacobrb95@gmail.com)

        Permission is hereby granted, free of charge, to any person obtaining a copy of 
        this software and associated documentation files (the "Software"), to deal in 
        the Software without restriction, including without limitation the rights to use, 
        copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
        Software, and to permit persons to whom the Software is furnished to do so, subject 
        to the following conditions:

        The above copyright notice and this permission notice shall be included in all copies 
        or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
        INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
        PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
        FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
        OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
        DEALINGS IN THE SOFTWARE.
 */ 

#ifndef ENDIAN_H
#define ENDIAN_H

#include <cstdint>
#include <cstring>

namespace endian
{

/**
 * Finds out what the endianness of the current Architecture is.
 * Returns 1 if it is Big Endian, and 0 otherwise.
 */ 
static bool Arch_Is_Big_Endian()
{
        union {
                uint32_t i;
                char c[4];
        } bint = {0x01020304};
        return bint.c[0] == 1;
}

class Float64
{
private:
        unsigned char data[8];

public:
        Float64() {}
        Float64(double a)
        {
                Set(a);
        }

        Float64 &operator=(double other)
        {
                Set(other);
        }
        double Little()
        {
                double ret = 0;
                uint64_t raw = (std::uint64_t)(((std::uint64_t)data[0]) | ((std::uint64_t)data[1] << 8) | ((std::uint64_t)data[2] << 16) | ((std::uint64_t)data[3] << 24) | ((std::uint64_t)data[4] << 32) | ((std::uint64_t)data[5] << 40) | ((std::uint64_t)data[6] << 48) | ((std::uint64_t)data[7] << 56));
                memcpy(&ret, &raw, 8);
                return ret;
        }

        double Big()
        {
                double ret = 0;
                uint64_t raw = ((std::uint64_t)data[0] << 56) | ((std::uint64_t)data[1] << 48) | ((std::uint64_t)data[2] << 40) | ((std::uint64_t)data[3] << 32) | ((std::uint64_t)data[4] << 24) | ((std::uint64_t)data[5] << 16) | ((std::uint64_t)data[6] << 8) | ((std::uint64_t)data[7]);
                memcpy(&ret, &raw, 8);
                return ret;
        }

        char *LittleAsBytes()
        {
                char *ret = new char[8];
                ret[0] = data[7];
                ret[1] = data[6];
                ret[2] = data[5];
                ret[3] = data[4];
                ret[4] = data[3];
                ret[5] = data[2];
                ret[6] = data[1];
                ret[7] = data[0];
                return ret;
        }

        char *BigAsBytes()
        {
                char *ret = new char[8];
                memcpy(ret, &data, 8);
                return ret;
        }

        void Set(double i)
        {
                memcpy(&data, &i, 8);
                if (!Arch_Is_Big_Endian())
                {
                        char swapped[8];
                        swapped[0] = data[7];
                        swapped[1] = data[6];
                        swapped[2] = data[5];
                        swapped[3] = data[4];
                        swapped[4] = data[3];
                        swapped[5] = data[2];
                        swapped[6] = data[1];
                        swapped[7] = data[0];

                        memcpy(&data, &swapped, 8);
                }
        }
};

class Float32
{
private:
        unsigned char data[4];

public:
        Float32() {}
        Float32(float a)
        {
                Set(a);
        }

        Float32 &operator=(float other)
        {
                Set(other);
        }
        float Little()
        {
                float ret = 0;
                unsigned int raw = (int)((data[0]) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));
                memcpy(&ret, &raw, 4);
                return ret;
        }

        char *LittleAsBytes()
        {
                char *ret = new char[4];
                ret[0] = data[3];
                ret[1] = data[2];
                ret[2] = data[1];
                ret[3] = data[0];
                return ret;
        }

        char *BigAsBytes()
        {
                char *ret = new char[4];
                memcpy(ret, &data, 4);
                return ret;
        }

        float Big()
        {
                float ret = 0;
                unsigned int raw = (int)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
                memcpy(&ret, &raw, 4);
                return ret;
        }

        void Set(float i)
        {
                memcpy(&data, &i, 4);
                if (!Arch_Is_Big_Endian())
                {
                        char swapped[4];
                        swapped[0] = data[3];
                        swapped[1] = data[2];
                        swapped[2] = data[1];
                        swapped[3] = data[0];

                        memcpy(&data, &swapped, 4);
                }
        }
};

class Int16
{
private:
        unsigned char data[2];

public:
        Int16() {}

        Int16(int a)
        {
                Set(a);
        }

        Int16 &operator=(short other)
        {
                Set(other);
        }

        char *LittleAsBytes()
        {
                char *ret = new char[2];
                ret[0] = data[1];
                ret[1] = data[0];
                return ret;
        }

        char *BigAsBytes()
        {
                char *ret = new char[2];
                memcpy(ret, &data, 2);
                return ret;
        }

        unsigned short Little()
        {
                return (short)((data[0]) | (data[1] << 8));
        }

        unsigned short Big()
        {
                return (short)((data[0] << 8) | (data[1]));
        }

        void Set(short i)
        {
                data[0] = (unsigned char)(i >> 8); //msb
                data[1] = (unsigned char)(i);
        }
};

class Int32
{
private:
        unsigned char data[4];

public:
        Int32() {}

        Int32(int a)
        {
                Set(a);
        }

        Int32 &operator=(int other)
        {
                Set(other);
        }

        char *LittleAsBytes()
        {
                char *ret = new char[4];
                ret[0] = data[3];
                ret[1] = data[2];
                ret[2] = data[1];
                ret[3] = data[0];
                return ret;
        }

        char *BigAsBytes()
        {
                char *ret = new char[4];
                memcpy(ret, &data, 4);
                return ret;
        }

        unsigned int Little()
        {
                return (int)((data[0]) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));
        }

        unsigned int Big()
        {
                return (int)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
        }

        void Set(int i)
        {
                data[0] = (unsigned char)(i >> 24); //msb
                data[1] = (unsigned char)(i >> 16);
                data[2] = (unsigned char)(i >> 8);
                data[3] = (unsigned char)(i);
        }
};

class Int64
{
private:
        unsigned char data[8];

public:
        Int64() {}

        Int64(std::uint64_t a)
        {
                Set(a);
        }

        Int64 &operator=(std::uint64_t other)
        {
                Set(other);
        }

        char *LittleAsBytes()
        {
                char *ret = new char[8];
                ret[0] = data[7];
                ret[1] = data[6];
                ret[2] = data[5];
                ret[3] = data[4];
                ret[4] = data[3];
                ret[5] = data[2];
                ret[6] = data[1];
                ret[7] = data[0];
                return ret;
        }

        char *BigAsBytes()
        {
                char *ret = new char[8];
                memcpy(ret, &data, 8);
                return ret;
        }

        std::uint64_t Little()
        {
                return (std::uint64_t)(((std::uint64_t)data[0]) | ((std::uint64_t)data[1] << 8) | ((std::uint64_t)data[2] << 16) | ((std::uint64_t)data[3] << 24) | ((std::uint64_t)data[4] << 32) | ((std::uint64_t)data[5] << 40) | ((std::uint64_t)data[6] << 48) | ((std::uint64_t)data[7] << 56));
        }

        std::uint64_t Big()
        {

                return ((std::uint64_t)data[0] << 56) | ((std::uint64_t)data[1] << 48) | ((std::uint64_t)data[2] << 40) | ((std::uint64_t)data[3] << 32) | ((std::uint64_t)data[4] << 24) | ((std::uint64_t)data[5] << 16) | ((std::uint64_t)data[6] << 8) | ((std::uint64_t)data[7]);
        }

        void Set(std::uint64_t i)
        {
                data[0] = (unsigned char)(i >> 56); //msb
                data[1] = (unsigned char)(i >> 48);
                data[2] = (unsigned char)(i >> 40);
                data[3] = (unsigned char)(i >> 32);
                data[4] = (unsigned char)(i >> 24);
                data[5] = (unsigned char)(i >> 16);
                data[6] = (unsigned char)(i >> 8);
                data[7] = (unsigned char)(i);
        }
};
} // namespace endian
#endif //ENDIAN_H