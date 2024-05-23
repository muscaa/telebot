#include "config.h"

// Writer

static void write(byte b, va_list args) {
    ofstream* out = va_arg(args, ofstream*);
    (*out).write(reinterpret_cast<char*>(&b), sizeof(byte));
}

static byte read(va_list args) {
    ifstream* in = va_arg(args, ifstream*);
    byte b;
    (*in).read(reinterpret_cast<char*>(&b), sizeof(byte));
    return b;
}

utils::ConfigWriter::ConfigWriter(string file) : outStream(file, ios::binary) {}

void utils::ConfigWriter::Bool(bool value) {
    bool_to_bytes(value, write, &outStream);
}

void utils::ConfigWriter::Byte(byte value) {
    byte_to_bytes(value, write, &outStream);
}

void utils::ConfigWriter::Char(char value) {
    char_to_bytes(value, write, &outStream);
}

void utils::ConfigWriter::Int(int value) {
    int_to_bytes(value, write, &outStream);
}

void utils::ConfigWriter::Long(long value) {
    long_to_bytes(value, write, &outStream);
}

void utils::ConfigWriter::Float(float value) {
    float_to_bytes(value, write, &outStream);
}

void utils::ConfigWriter::Double(double value) {
    double_to_bytes(value, write, &outStream);
}

void utils::ConfigWriter::String(string value, int length) {
    for (int i = 0; i < length; i++) {
        Char(value[i]);
    }
}

void utils::ConfigWriter::LenString(string value) {
    Int(value.length());
    String(value, value.length());
}

void utils::ConfigWriter::Bytes(byte* buf, int len) {
    for (int i = 0; i < len; i++) {
        Byte(buf[i]);
    }
}

void utils::ConfigWriter::flush() {
    outStream.flush();
}

void utils::ConfigWriter::close() {
    outStream.close();
}

// Reader

utils::ConfigReader::ConfigReader(string file) : inStream(file, ios::binary) {}

bool utils::ConfigReader::Bool() {
    return bytes_to_bool(read, &inStream);
}

byte utils::ConfigReader::Byte() {
    return bytes_to_byte(read, &inStream);
}

char utils::ConfigReader::Char() {
    return bytes_to_char(read, &inStream);
}

int utils::ConfigReader::Int() {
    return bytes_to_int(read, &inStream);
}

long utils::ConfigReader::Long() {
    return bytes_to_long(read, &inStream);
}

float utils::ConfigReader::Float() {
    return bytes_to_float(read, &inStream);
}

double utils::ConfigReader::Double() {
    return bytes_to_double(read, &inStream);
}

string utils::ConfigReader::String(int length) {
    string result = "";
    for (int i = 0; i < length; i++) {
        result += Char();
    }
    return result;
}

string utils::ConfigReader::LenString() {
    int length = Int();
    return String(length);
}

void utils::ConfigReader::Bytes(byte* buf, int len) {
    for (int i = 0; i < len; i++) {
        buf[i] = Byte();
    }
}

void utils::ConfigReader::close() {
    inStream.close();
}
