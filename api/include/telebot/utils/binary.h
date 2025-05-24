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

void Bool(uint8_t* data, bool value, size_t offset = 0);

void Byte(uint8_t* data, uint8_t value, size_t offset = 0);

void Char(uint8_t* data, char value, size_t offset = 0);

void Short(uint8_t* data, int16_t value, size_t offset = 0);

void Int(uint8_t* data, int32_t value, size_t offset = 0);

void Float(uint8_t* data, float value, size_t offset = 0);

void Long(uint8_t* data, int64_t value, size_t offset = 0);

void Double(uint8_t* data, double value, size_t offset = 0);

void String(uint8_t* data, std::string value, size_t length, size_t offset = 0);

void LenString(uint8_t* data, std::string value, size_t offset = 0);

} // namespace telebot::utils::binary
