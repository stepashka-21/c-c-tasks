#include "bin_manip.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include "string.h"

write_le_int32::write_le_int32(int32_t x) : _i(x) {}

std::ofstream& operator<<(std::ofstream& out, const write_le_int32& data) {
    int32_t val = data._i;
    uint8_t buf[4];
    for (int i = 0; i < 4; ++i) {
        buf[i] = (val >> (i * 8)) & 0xFF;
    }
    out.write(reinterpret_cast<char*>(buf), 4);
    return out;
}

read_le_int32::read_le_int32(int32_t& x) : _i(x) {}

std::ifstream& operator>>(std::ifstream& in, const read_le_int32& data) {
    uint8_t buf[4];
    in.read(reinterpret_cast<char*>(buf), 4);
    data._i = 0;
    for (int i = 3; i >= 0; i--) {
        data._i = (data._i << 8) + buf[i];
    }
    return in;
}

write_bool::write_bool(bool x) : _i(x) {}

std::ofstream& operator<<(std::ofstream& out, const write_bool& data) {
    out.write(reinterpret_cast<const char*>(&data._i), sizeof(data._i));
    return out;
}

read_bool::read_bool(bool& x) : _i(x) {}

std::ifstream& operator>>(std::ifstream& in,const read_bool& data) {
    in.read(reinterpret_cast<char*>(&data._i), sizeof(data._i));
    return in;
}

write_c_str::write_c_str(char* x) : _i(x) {}

std::ofstream& operator<<(std::ofstream& out, const write_c_str& data) {
    size_t len = strlen(data._i) + 1;
    out.write(data._i, len);
    return out;
}

read_c_str::read_c_str(char* x, std::size_t s) : _i(x), size(s) {}

std::ifstream& operator>>(std::ifstream& in,const read_c_str& data) {
    for (int32_t i = 0; i < (int32_t)data.size; i++) {
        in.read(data._i + i, 1);
        if (!data._i[i]) { 
            return in; 
        }
    }
    return in;
}
