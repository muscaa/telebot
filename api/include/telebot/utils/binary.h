#pragma once

#include <cstdint>
#include <string>

namespace telebot::utils::binary {

// reading

bool Bool(const uint8_t* data, size_t& offset);

uint8_t Byte(const uint8_t* data, size_t& offset);

char Char(const uint8_t* data, size_t& offset);

int16_t Short(const uint8_t* data, size_t& offset);

int32_t Int(const uint8_t* data, size_t& offset);

float Float(const uint8_t* data, size_t& offset);

int64_t Long(const uint8_t* data, size_t& offset);

double Double(const uint8_t* data, size_t& offset);

std::string String(const uint8_t* data, size_t& offset, size_t length);

std::string LenString(const uint8_t* data, size_t& offset);

// writing

void Bool(uint8_t* data, size_t& offset, bool value);

void Byte(uint8_t* data, size_t& offset, uint8_t value);

void Char(uint8_t* data, size_t& offset, char value);

void Short(uint8_t* data, size_t& offset, int16_t value);

void Int(uint8_t* data, size_t& offset, int32_t value);

void Float(uint8_t* data, size_t& offset, float value);

void Long(uint8_t* data, size_t& offset, int64_t value);

void Double(uint8_t* data, size_t& offset, double value);

void String(uint8_t* data, size_t& offset, std::string value, size_t length);

void LenString(uint8_t* data, size_t& offset, std::string value);

} // namespace telebot::utils::binary
