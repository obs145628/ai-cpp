#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>


class SerialWriter
{
public:
    SerialWriter(std::ostream& os);
    virtual ~SerialWriter() = default;

    std::ostream& out();
    const std::ostream& out() const;

    virtual void write_u8(std::uint8_t x) = 0;
    virtual void write_u16(std::uint16_t x) = 0;
    virtual void write_u32(std::uint32_t x) = 0;
    virtual void write_u64(std::uint64_t x) = 0;
    virtual void write_s8(std::int8_t x) = 0;
    virtual void write_s16(std::int16_t x) = 0;
    virtual void write_s32(std::int32_t x) = 0;
    virtual void write_s64(std::int64_t x) = 0;
    virtual void write_f32(float x) = 0;
    virtual void write_f64(double x) = 0;

    virtual void write_au8(const std::uint8_t* begin, const std::uint8_t* end);
    virtual void write_au16(const std::uint16_t* begin, const std::uint16_t* end);
    virtual void write_au32(const std::uint32_t* begin, const std::uint32_t* end);
    virtual void write_au64(const std::uint64_t* begin, const std::uint64_t* end);
    virtual void write_as8(const std::int8_t* begin, const std::int8_t* end);
    virtual void write_as16(const std::int16_t* begin, const std::int16_t* end);
    virtual void write_as32(const std::int32_t* begin, const std::int32_t* end);
    virtual void write_as64(const std::int64_t* begin, const std::int64_t* end);
    virtual void write_af32(const float* begin, const float* end);
    virtual void write_af64(const double* begin, const double* end);

    template <class It>
    void write(It begin, It end);

protected:

    template <class It>
    void write_loop_(It begin, It end);

private:
    std::ostream& os_;
};

SerialWriter& operator<<(SerialWriter& os, uint8_t x);
SerialWriter& operator<<(SerialWriter& os, uint16_t x);
SerialWriter& operator<<(SerialWriter& os, uint32_t x);
SerialWriter& operator<<(SerialWriter& os, uint64_t x);
SerialWriter& operator<<(SerialWriter& os, int8_t x);
SerialWriter& operator<<(SerialWriter& os, int16_t x);
SerialWriter& operator<<(SerialWriter& os, int32_t x);
SerialWriter& operator<<(SerialWriter& os, int64_t x);
SerialWriter& operator<<(SerialWriter& os, float x);
SerialWriter& operator<<(SerialWriter& os, double x);

template<class T>
SerialWriter& operator<<(SerialWriter& os, const std::vector<T>& vector);

SerialWriter& operator<<(SerialWriter& os, const std::string& str);

class BinarySerialWriter : public SerialWriter
{
public:
    BinarySerialWriter(std::ostream& os);

    void write_u8(std::uint8_t x) override;
    void write_u16(std::uint16_t x) override;
    void write_u32(std::uint32_t x) override;
    void write_u64(std::uint64_t x) override;
    void write_s8(std::int8_t x) override;
    void write_s16(std::int16_t x) override;
    void write_s32(std::int32_t x) override;
    void write_s64(std::int64_t x) override;
    void write_f32(float x) override;
    void write_f64(double x) override;

    void write_au8(const std::uint8_t* begin, const std::uint8_t* end) override;
    void write_au16(const std::uint16_t* begin, const std::uint16_t* end) override;
    void write_au32(const std::uint32_t* begin, const std::uint32_t* end) override;
    void write_au64(const std::uint64_t* begin, const std::uint64_t* end) override;
    void write_as8(const std::int8_t* begin, const std::int8_t* end) override;
    void write_as16(const std::int16_t* begin, const std::int16_t* end) override;
    void write_as32(const std::int32_t* begin, const std::int32_t* end) override;
    void write_as64(const std::int64_t* begin, const std::int64_t* end) override;
    void write_af32(const float* begin, const float* end) override;
    void write_af64(const double* begin, const double* end) override;

};

class TextSerialWriter : public SerialWriter
{
public:
    TextSerialWriter(std::ostream& os);

    void write_u8(std::uint8_t x) override;
    void write_u16(std::uint16_t x) override;
    void write_u32(std::uint32_t x) override;
    void write_u64(std::uint64_t x) override;
    void write_s8(std::int8_t x) override;
    void write_s16(std::int16_t x) override;
    void write_s32(std::int32_t x) override;
    void write_s64(std::int64_t x) override;
    void write_f32(float x) override;
    void write_f64(double x) override;
};


class SerialReader
{
public:
    SerialReader(std::istream& is);
    virtual ~SerialReader() = default;

    std::istream& in();
    const std::istream& in() const;

    virtual void read_u8(std::uint8_t& x) = 0;
    virtual void read_u16(std::uint16_t& x) = 0;
    virtual void read_u32(std::uint32_t& x) = 0;
    virtual void read_u64(std::uint64_t& x) = 0;
    virtual void read_s8(std::int8_t& x) = 0;
    virtual void read_s16(std::int16_t& x) = 0;
    virtual void read_s32(std::int32_t& x) = 0;
    virtual void read_s64(std::int64_t& x) = 0;
    virtual void read_f32(float& x) = 0;
    virtual void read_f64(double& x) = 0;

    virtual void read_au8(std::uint8_t* begin, std::uint8_t* end);
    virtual void read_au16(std::uint16_t* begin, std::uint16_t* end);
    virtual void read_au32(std::uint32_t* begin, std::uint32_t* end);
    virtual void read_au64(std::uint64_t* begin, std::uint64_t* end);
    virtual void read_as8(std::int8_t* begin, std::int8_t* end);
    virtual void read_as16(std::int16_t* begin, std::int16_t* end);
    virtual void read_as32(std::int32_t* begin, std::int32_t* end);
    virtual void read_as64(std::int64_t* begin, std::int64_t* end);
    virtual void read_af32(float* begin, float* end);
    virtual void read_af64(double* begin, double* end);

    template <class It>
    void read(It begin, It end);

protected:

    template <class It>
    void read_loop_(It begin, It end);

private:
    std::istream& is_;
};

SerialReader& operator>>(SerialReader& is, uint8_t& x);
SerialReader& operator>>(SerialReader& is, uint16_t& x);
SerialReader& operator>>(SerialReader& is, uint32_t& x);
SerialReader& operator>>(SerialReader& is, uint64_t& x);
SerialReader& operator>>(SerialReader& is, int8_t& x);
SerialReader& operator>>(SerialReader& is, int16_t& x);
SerialReader& operator>>(SerialReader& is, int32_t& x);
SerialReader& operator>>(SerialReader& is, int64_t& x);
SerialReader& operator>>(SerialReader& is, float& x);
SerialReader& operator>>(SerialReader& is, double& x);

template<class T>
SerialReader& operator>>(SerialReader& os, std::vector<T>& vector);

SerialReader& operator>>(SerialReader& os, std::string& str);

class BinarySerialReader : public SerialReader
{
public:
    BinarySerialReader(std::istream& in);

    void read_u8(std::uint8_t& x) override;
    void read_u16(std::uint16_t& x) override;
    void read_u32(std::uint32_t& x) override;
    void read_u64(std::uint64_t& x) override;
    void read_s8(std::int8_t& x) override;
    void read_s16(std::int16_t& x) override;
    void read_s32(std::int32_t& x) override;
    void read_s64(std::int64_t& x) override;
    void read_f32(float& x) override;
    void read_f64(double& x) override;

    void read_au8(std::uint8_t* begin, std::uint8_t* end) override;
    void read_au16(std::uint16_t* begin, std::uint16_t* end) override;
    void read_au32(std::uint32_t* begin, std::uint32_t* end) override;
    void read_au64(std::uint64_t* begin, std::uint64_t* end) override;
    void read_as8(std::int8_t* begin, std::int8_t* end) override;
    void read_as16(std::int16_t* begin, std::int16_t* end) override;
    void read_as32(std::int32_t* begin, std::int32_t* end) override;
    void read_as64(std::int64_t* begin, std::int64_t* end) override;
    void read_af32(float* begin, float* end) override;
    void read_af64(double* begin, double* end) override;

};

class TextSerialReader : public SerialReader
{
public:
    TextSerialReader(std::istream& is);

    void read_u8(std::uint8_t& x) override;
    void read_u16(std::uint16_t& x) override;
    void read_u32(std::uint32_t& x) override;
    void read_u64(std::uint64_t& x) override;
    void read_s8(std::int8_t& x) override;
    void read_s16(std::int16_t& x) override;
    void read_s32(std::int32_t& x) override;
    void read_s64(std::int64_t& x) override;
    void read_f32(float& x) override;
    void read_f64(double& x) override;
};

#include "serial.hxx"
