#pragma once

#include "../utils_base.h"
#include "../types/byte.h"

namespace utils {

class ConfigWriter {
private:
    ofstream outStream;

public:
    ConfigWriter(string file);

    void Bool(bool value);

    void Byte(byte value);

    void Char(char value);

    void Int(int value);

    void Long(long value);

    void Float(float value);

    void Double(double value);

    void String(string value, int length);

    void LenString(string value);

    void Bytes(byte* buf, int len);

    void flush();

    void close();
};

class ConfigReader {
private:
    ifstream inStream;

public:
    ConfigReader(string file);

    bool Bool();

    byte Byte();

    char Char();

    int Int();

    long Long();

    float Float();

    double Double();

    string String(int length);

    string LenString();

    void Bytes(byte* buf, int len);

    void close();
};

}
