#pragma once

#include "serial.hh"
#include <limits>

inline SerialWriter::SerialWriter(std::ostream& os)
    : os_(os)
{}

inline std::ostream& SerialWriter::out()
{
    return os_;
}

inline const std::ostream& SerialWriter::out() const
{
    return os_;
}

inline void SerialWriter::write_au8(const std::uint8_t* begin, const std::uint8_t* end)
{
    write_loop_(begin, end);
}

inline void SerialWriter::write_au16(const std::uint16_t* begin, const std::uint16_t* end)
{
    write_loop_(begin, end);
}

inline void SerialWriter::write_au32(const std::uint32_t* begin, const std::uint32_t* end)
{
    write_loop_(begin, end);
}

inline void SerialWriter::write_au64(const std::uint64_t* begin, const std::uint64_t* end)
{
    write_loop_(begin, end);
}

inline void SerialWriter::write_as8(const std::int8_t* begin, const std::int8_t* end)
{
    write_loop_(begin, end);
}

inline void SerialWriter::write_as16(const std::int16_t* begin, const std::int16_t* end)
{
    write_loop_(begin, end);
}

inline void SerialWriter::write_as32(const std::int32_t* begin, const std::int32_t* end)
{
    write_loop_(begin, end);
}

inline void SerialWriter::write_as64(const std::int64_t* begin, const std::int64_t* end)
{
    write_loop_(begin, end);
}

inline void SerialWriter::write_af32(const float* begin, const float* end)
{
    write_loop_(begin, end);
}

inline void SerialWriter::write_af64(const double* begin, const double* end)
{
    write_loop_(begin, end);
}

template <class It>
void SerialWriter::write(It begin, It end)
{
    write_loop_(begin, end);
}

template<>
inline void SerialWriter::write(const std::uint8_t* begin,const std::uint8_t* end)
{
    write_au8(begin, end);
}

template<>
inline void SerialWriter::write(const std::uint16_t* begin, const std::uint16_t* end)
{
    write_au16(begin, end);
}

template<>
inline void SerialWriter::write(const std::uint32_t* begin, const std::uint32_t* end)
{
    write_au32(begin, end);
}

template<>
inline void SerialWriter::write(const std::uint64_t* begin, const std::uint64_t* end)
{
    write_au64(begin, end);
}

template<>
inline void SerialWriter::write(const std::int8_t* begin, const std::int8_t* end)
{
    write_as8(begin, end);
}

template<>
inline void SerialWriter::write(const std::int16_t* begin, const std::int16_t* end)
{
    write_as16(begin, end);
}

template<>
inline void SerialWriter::write(const std::int32_t* begin, const std::int32_t* end)
{
    write_as32(begin, end);
}

template<>
inline void SerialWriter::write(const std::int64_t* begin, const std::int64_t* end)
{
    write_as64(begin, end);
}

template<>
inline void SerialWriter::write(const float* begin, const float* end)
{
    write_af32(begin, end);
}

template<>
inline void SerialWriter::write(const double* begin, const double* end)
{
    write_af64(begin, end);
}

template <class It>
void SerialWriter::write_loop_(It begin, It end)
{
    for (auto it = begin; it != end; ++it)
        *this << *it;
}


inline SerialWriter& operator<<(SerialWriter& os, uint8_t x)
{
    os.write_u8(x);
    return os;
}

inline SerialWriter& operator<<(SerialWriter& os, uint16_t x)
{
    os.write_u16(x);
    return os;
}

inline SerialWriter& operator<<(SerialWriter& os, uint32_t x)
{
    os.write_u32(x);
    return os;
}

inline SerialWriter& operator<<(SerialWriter& os, uint64_t x)
{
    os.write_u64(x);
    return os;
}

inline SerialWriter& operator<<(SerialWriter& os, int8_t x)
{
    os.write_s8(x);
    return os;
}

inline SerialWriter& operator<<(SerialWriter& os, int16_t x)
{
    os.write_s16(x);
    return os;
}

inline SerialWriter& operator<<(SerialWriter& os, int32_t x)
{
    os.write_s32(x);
    return os;
}

inline SerialWriter& operator<<(SerialWriter& os, int64_t x)
{
    os.write_s64(x);
    return os;
}

inline SerialWriter& operator<<(SerialWriter& os, float x)
{
    os.write_f32(x);
    return os;
}

inline SerialWriter& operator<<(SerialWriter& os, double x)
{
    os.write_f64(x);
    return os;
}


template<class T>
SerialWriter& operator<<(SerialWriter& os, const std::vector<T>& vector)
{
    os << vector.size();
    os.write(vector.data(), vector.data() + vector.size());
    return os;
}

inline SerialWriter& operator<<(SerialWriter& os, const std::string& str)
{
    os << str.size();
    os.write(str.data(), str.data() + str.size());
    return os;
}

template <class T>
inline void serial_write_bin(std::ostream& os, const T& val)
{
    auto n = sizeof(T);
    auto data = reinterpret_cast<const char*>(&val);
    os.write(data, n);
}

template <class T>
inline void serial_write_bin(std::ostream& os, const T* it, std::size_t n)
{
    auto data = reinterpret_cast<const char*>(it);
    os.write(data, n * sizeof(T));
}



inline BinarySerialWriter::BinarySerialWriter(std::ostream &os)
    : SerialWriter(os)
{}

inline void BinarySerialWriter::write_u8(std::uint8_t x)
{
    serial_write_bin<uint8_t>(out(), x);
}

inline void BinarySerialWriter::write_u16(std::uint16_t x)
{
    serial_write_bin<uint16_t>(out(), x);
}

inline void BinarySerialWriter::write_u32(std::uint32_t x)
{
    serial_write_bin<uint32_t>(out(), x);
}

inline void BinarySerialWriter::write_u64(std::uint64_t x)
{
    serial_write_bin<uint64_t>(out(), x);
}

inline void BinarySerialWriter::write_s8(std::int8_t x)
{
    serial_write_bin<int8_t>(out(), x);
}

inline void BinarySerialWriter::write_s16(std::int16_t x)
{
    serial_write_bin<int16_t>(out(), x);
}

inline void BinarySerialWriter::write_s32(std::int32_t x)
{
    serial_write_bin<int32_t>(out(), x);
}

inline void BinarySerialWriter::write_s64(std::int64_t x)
{
    serial_write_bin<int64_t>(out(), x);
}

inline void BinarySerialWriter::write_f32(float x)
{
    serial_write_bin<float>(out(), x);
}

inline void BinarySerialWriter::write_f64(double x)
{
    serial_write_bin<double>(out(), x);
}

inline void BinarySerialWriter::write_au8(const std::uint8_t* begin, const std::uint8_t* end)
{
    serial_write_bin<uint8_t>(out(), begin, end - begin);
}

inline void BinarySerialWriter::write_au16(const std::uint16_t* begin, const std::uint16_t* end)
{
    serial_write_bin<uint16_t>(out(), begin, end - begin);
}

inline void BinarySerialWriter::write_au32(const std::uint32_t* begin, const std::uint32_t* end)
{
    serial_write_bin<uint32_t>(out(), begin, end - begin);
}

inline void BinarySerialWriter::write_au64(const std::uint64_t* begin, const std::uint64_t* end)
{
    serial_write_bin<uint64_t>(out(), begin, end - begin);
}

inline void BinarySerialWriter::write_as8(const std::int8_t* begin, const std::int8_t* end)
{
    serial_write_bin<int8_t>(out(), begin, end - begin);
}

inline void BinarySerialWriter::write_as16(const std::int16_t* begin, const std::int16_t* end)
{
    serial_write_bin<int16_t>(out(), begin, end - begin);
}

inline void BinarySerialWriter::write_as32(const std::int32_t* begin, const std::int32_t* end)
{
    serial_write_bin<int32_t>(out(), begin, end - begin);
}

inline void BinarySerialWriter::write_as64(const std::int64_t* begin, const std::int64_t* end)
{
    serial_write_bin<int64_t>(out(), begin, end - begin);
}

inline void BinarySerialWriter::write_af32(const float* begin, const float* end)
{
    serial_write_bin<float>(out(), begin, end - begin);
}

inline void BinarySerialWriter::write_af64(const double* begin, const double* end)
{
    serial_write_bin<double>(out(), begin, end - begin);
}

inline TextSerialWriter::TextSerialWriter(std::ostream &os)
        : SerialWriter(os)
{
    typedef std::numeric_limits<double> prec;
    os.precision(prec::max_digits10);
}

inline void TextSerialWriter::write_u8(uint8_t x)
{
    out() << static_cast<int>(x) << std::endl;
}

inline void TextSerialWriter::write_u16(uint16_t x)
{
    out() << x << std::endl;
}

inline void TextSerialWriter::write_u32(uint32_t x)
{
    out() << x << std::endl;
}

inline void TextSerialWriter::write_u64(uint64_t x)
{
    out() << x << std::endl;
}

inline void TextSerialWriter::write_s8(int8_t x)
{
    out() << static_cast<int>(x) << std::endl;
}

inline void TextSerialWriter::write_s16(int16_t x)
{
    out() << x << std::endl;
}

inline void TextSerialWriter::write_s32(int32_t x)
{
    out() << x << std::endl;
}

inline void TextSerialWriter::write_s64(int64_t x)
{
    out() << x << std::endl;
}

inline void TextSerialWriter::write_f32(float x)
{
    out() << x << std::endl;
}

inline void TextSerialWriter::write_f64(double x)
{
    out() << x << std::endl;
}




inline SerialReader::SerialReader(std::istream& is)
        : is_(is)
{}

inline std::istream& SerialReader::in()
{
    return is_;
}

inline const std::istream& SerialReader::in() const
{
    return is_;
}

inline void SerialReader::read_au8(std::uint8_t* begin, std::uint8_t* end)
{
    read_loop_(begin, end);
}

inline void SerialReader::read_au16(std::uint16_t* begin, std::uint16_t* end)
{
    read_loop_(begin, end);
}

inline void SerialReader::read_au32(std::uint32_t* begin, std::uint32_t* end)
{
    read_loop_(begin, end);
}

inline void SerialReader::read_au64(std::uint64_t* begin, std::uint64_t* end)
{
    read_loop_(begin, end);
}

inline void SerialReader::read_as8(std::int8_t* begin, std::int8_t* end)
{
    read_loop_(begin, end);
}

inline void SerialReader::read_as16(std::int16_t* begin, std::int16_t* end)
{
    read_loop_(begin, end);
}

inline void SerialReader::read_as32(std::int32_t* begin, std::int32_t* end)
{
    read_loop_(begin, end);
}

inline void SerialReader::read_as64(std::int64_t* begin, std::int64_t* end)
{
    read_loop_(begin, end);
}

inline void SerialReader::read_af32(float* begin, float* end)
{
    read_loop_(begin, end);
}

inline void SerialReader::read_af64(double* begin, double* end)
{
    read_loop_(begin, end);
}

template <class It>
void SerialReader::read(It begin, It end)
{
    read_loop_(begin, end);
}

template <class It>
void SerialReader::read_loop_(It begin, It end)
{
    for (It it = begin; it != end; ++it)
        *this >> *it;
}


inline SerialReader& operator>>(SerialReader& os, uint8_t& x)
{
    os.read_u8(x);
    return os;
}

inline SerialReader& operator>>(SerialReader& os, uint16_t& x)
{
    os.read_u16(x);
    return os;
}

inline SerialReader& operator>>(SerialReader& os, uint32_t& x)
{
    os.read_u32(x);
    return os;
}

inline SerialReader& operator>>(SerialReader& os, uint64_t& x)
{
    os.read_u64(x);
    return os;
}

inline SerialReader& operator>>(SerialReader& os, int8_t& x)
{
    os.read_s8(x);
    return os;
}

inline SerialReader& operator>>(SerialReader& os, int16_t& x)
{
    os.read_s16(x);
    return os;
}

inline SerialReader& operator>>(SerialReader& os, int32_t& x)
{
    os.read_s32(x);
    return os;
}

inline SerialReader& operator>>(SerialReader& os, int64_t& x)
{
    os.read_s64(x);
    return os;
}

inline SerialReader& operator>>(SerialReader& os, float& x)
{
    os.read_f32(x);
    return os;
}

inline SerialReader& operator>>(SerialReader& is, double& x)
{
    is.read_f64(x);
    return is;
}

template<class T>
SerialReader& operator>>(SerialReader& is, std::vector<T>& vector)
{
    std::size_t size;
    is >> size;
    vector.resize(size);
    is.read(vector.data(), vector.data() + size);
    return is;
}

inline SerialReader& operator>>(SerialReader& os, std::string& str)
{
    std::size_t size;
    os >> size;

    str.resize(size);
    auto begin = const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>((str.data())));
    os.read(begin, begin + size);
    return os;
}

inline BinarySerialReader::BinarySerialReader(std::istream& in)
    : SerialReader(in)
{}

template <class T>
void serial_read_bin(std::istream& is, T& val)
{
    auto n = sizeof(T);
    auto data = reinterpret_cast<char*>(&val);
    is.read(data, n);
}

template <class T>
void serial_read_bin(std::istream& is, T* val, std::size_t n)
{
    auto data = reinterpret_cast<char*>(val);
    is.read(data, n * sizeof(T));
}

inline void BinarySerialReader::read_u8(std::uint8_t& x)
{
    serial_read_bin<uint8_t>(in(), x);
}

inline void BinarySerialReader::read_u16(std::uint16_t& x)
{
    serial_read_bin<uint16_t>(in(), x);
}

inline void BinarySerialReader::read_u32(std::uint32_t& x)
{
    serial_read_bin<uint32_t>(in(), x);
}

inline void BinarySerialReader::read_u64(std::uint64_t& x)
{
    serial_read_bin<uint64_t>(in(), x);
}

inline void BinarySerialReader::read_s8(std::int8_t& x)
{
    serial_read_bin<int8_t>(in(), x);
}

inline void BinarySerialReader::read_s16(std::int16_t& x)
{
    serial_read_bin<int16_t>(in(), x);
}

inline void BinarySerialReader::read_s32(std::int32_t& x)
{
    serial_read_bin<int32_t>(in(), x);
}

inline void BinarySerialReader::read_s64(std::int64_t& x)
{
    serial_read_bin<int64_t>(in(), x);
}

inline void BinarySerialReader::read_f32(float& x)
{
    serial_read_bin<float>(in(), x);
}

inline void BinarySerialReader::read_f64(double& x)
{
    serial_read_bin<double>(in(), x);
}

inline void BinarySerialReader::read_au8(std::uint8_t* begin, std::uint8_t* end)
{
    serial_read_bin<uint8_t> (in(), begin, end - begin);
}

inline void BinarySerialReader::read_au16(std::uint16_t* begin, std::uint16_t* end)
{
    serial_read_bin<uint16_t> (in(), begin, end - begin);
}

inline void BinarySerialReader::read_au32(std::uint32_t* begin, std::uint32_t* end)
{
    serial_read_bin<uint32_t> (in(), begin, end - begin);
}

inline void BinarySerialReader::read_au64(std::uint64_t* begin, std::uint64_t* end)
{
    serial_read_bin<uint64_t> (in(), begin, end - begin);
}

inline void BinarySerialReader::read_as8(std::int8_t* begin, std::int8_t* end)
{
    serial_read_bin<int8_t> (in(), begin, end - begin);
}

inline void BinarySerialReader::read_as16(std::int16_t* begin, std::int16_t* end)
{
    serial_read_bin<int16_t> (in(), begin, end - begin);
}

inline void BinarySerialReader::read_as32(std::int32_t* begin, std::int32_t* end)
{
    serial_read_bin<int32_t> (in(), begin, end - begin);
}

inline void BinarySerialReader::read_as64(std::int64_t* begin, std::int64_t* end)
{
    serial_read_bin<int64_t> (in(), begin, end - begin);
}

inline void BinarySerialReader::read_af32(float* begin, float* end)
{
    serial_read_bin<float> (in(), begin, end - begin);
}

inline void BinarySerialReader::read_af64(double* begin, double* end)
{
    serial_read_bin<double> (in(), begin, end - begin);
}

inline TextSerialReader::TextSerialReader(std::istream& is)
        : SerialReader(is)
{}


inline void TextSerialReader::read_u8(std::uint8_t& x)
{
    int temp;
    in() >> temp;
    x = static_cast<uint8_t >(temp);
}

inline void TextSerialReader::read_u16(std::uint16_t& x)
{
    in() >> x;
}

inline void TextSerialReader::read_u32(std::uint32_t& x)
{
    in() >> x;
}

inline void TextSerialReader::read_u64(std::uint64_t& x)
{
    in() >> x;
}

inline void TextSerialReader::read_s8(std::int8_t& x)
{
    int temp;
    in() >> temp;
    x = static_cast<int8_t >(temp);
}

inline void TextSerialReader::read_s16(std::int16_t& x)
{
    in() >> x;
}

inline void TextSerialReader::read_s32(std::int32_t& x)
{
    in() >> x;
}

inline void TextSerialReader::read_s64(std::int64_t& x)
{
    in() >> x;
}

inline void TextSerialReader::read_f32(float& x)
{
    in() >> x;
}

inline void TextSerialReader::read_f64(double& x)
{
    in() >> x;
}
