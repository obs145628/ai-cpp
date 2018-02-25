#include "la/matrix.hh"
#include <algorithm>
#include <cassert>
#include "io/serial.hh"



std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    for (std::size_t i = 0; i < m.rows(); ++i)
    {
        os << "|";
        for (std::size_t j = 0; j < m.cols(); ++j)
        {
           os << " " << m(i, j) << " |";
        }
        os << std::endl;
    }

    return os;
}

SerialWriter& operator<<(SerialWriter& os, const Matrix& m)
{
    os << m.rows() << m.cols();
    os.write(m.begin(), m.end());
    return os;
}

SerialReader& operator>>(SerialReader& is, Matrix& m)
{
    std::size_t rows;
    std::size_t cols;
    is >> rows >> cols;

    m.assign(rows, cols);
    is.read(m.begin(), m.end());
    return is;
}





Matrix Matrix::hstack(const std::vector<Matrix>& mats)
{
    assert(mats.size() != 0);
    std::size_t rows = mats[0].rows();
    std::size_t cols = 0;
    for (const auto& m : mats)
    {
	assert(m.rows() == rows);
	cols += m.cols();
    }


    Matrix res(rows, cols);
    std::size_t mat_col = 0;
    std::size_t mati = 0;
    for (std::size_t j = 0; j < cols; ++j)
    {
	for (std::size_t i = 0; i < rows; ++i)
	    res(i, j) = mats[mati](i, mat_col);

	if (++mat_col == mats[mati].cols())
	{
	    mat_col = 0;
	    ++mati;
	}
    }

    return res;
}
