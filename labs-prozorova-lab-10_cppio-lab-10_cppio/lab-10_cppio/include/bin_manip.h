#ifndef BIN_MANIP_H
#define BIN_MANIP_H

#include <cstdint>
#include <iostream>

class write_le_int32 {
public:
    explicit write_le_int32(int32_t x);
    friend std::ofstream &operator<<(std::ofstream &out, const write_le_int32 &data);

protected:
    int32_t _i;
};

class read_le_int32 {
public:
    explicit read_le_int32(int32_t &x);
    friend std::ifstream &operator>>(std::ifstream &in,const read_le_int32 &data);

protected:
    int32_t& _i;
};

class write_bool {
public:
    explicit write_bool(bool x);
    friend std::ofstream &operator<<(std::ofstream &out, const write_bool &data);

protected:
    bool _i;
};

class read_bool {
public:
    explicit read_bool(bool &x);
    friend std::ifstream &operator>>(std::ifstream &in,const read_bool &data);

protected:
    bool &_i;
};

class write_c_str {
public:
    explicit write_c_str(char *x);
    friend std::ofstream &operator<<(std::ofstream &out, const write_c_str &data);

protected:
    char* _i;
};

class read_c_str {
public:
    explicit read_c_str(char *x, std::size_t s);
    friend std::ifstream &operator>>(std::ifstream &in,const read_c_str &data);

protected:
    char *_i;
    std::size_t size;
};

#endif
