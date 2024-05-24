#include "config.h"

// Writer

static void write(byte b, ofstream& out) {
    out.write(reinterpret_cast<char*>(&b), sizeof(byte));
}

static byte read(ifstream& in) {
    byte b;
    in.read(reinterpret_cast<char*>(&b), sizeof(byte));
    return b;
}

utils::ConfigWriter::ConfigWriter(string file) : outStream(file, ios::binary) {}

void utils::ConfigWriter::Bool(bool value) {
    bool_to_bytes(value, [&](byte b) { write(b, outStream); });
}

void utils::ConfigWriter::Byte(byte value) {
    byte_to_bytes(value, [&](byte b) { write(b, outStream); });
}

void utils::ConfigWriter::Char(char value) {
    char_to_bytes(value, [&](byte b) { write(b, outStream); });
}

void utils::ConfigWriter::Int(int value) {
    int_to_bytes(value, [&](byte b) { write(b, outStream); });
}

void utils::ConfigWriter::Long(long value) {
    long_to_bytes(value, [&](byte b) { write(b, outStream); });
}

void utils::ConfigWriter::Float(float value) {
    float_to_bytes(value, [&](byte b) { write(b, outStream); });
}

void utils::ConfigWriter::Double(double value) {
    double_to_bytes(value, [&](byte b) { write(b, outStream); });
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
    return bytes_to_bool([&]() { return read(inStream); });
}

byte utils::ConfigReader::Byte() {
    return bytes_to_byte([&]() { return read(inStream); });
}

char utils::ConfigReader::Char() {
    return bytes_to_char([&]() { return read(inStream); });
}

int utils::ConfigReader::Int() {
    return bytes_to_int([&]() { return read(inStream); });
}

long utils::ConfigReader::Long() {
    return bytes_to_long([&]() { return read(inStream); });
}

float utils::ConfigReader::Float() {
    return bytes_to_float([&]() { return read(inStream); });
}

double utils::ConfigReader::Double() {
    return bytes_to_double([&]() { return read(inStream); });
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
