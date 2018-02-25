#include "matrix.hh"
#include <cassert>


inline Matrix::Matrix()
        : chunk_(nullptr)
        , ptr_(nullptr)
        , rows_(0)
        , cols_(0)
{}

inline Matrix::Matrix(std::size_t rows, std::size_t cols)
        : chunk_(RealChunk::alloc(rows * cols))
        , ptr_(chunk_->data)
        , rows_(rows)
        , cols_(cols)
{
    chunk_->ref();
}

inline Matrix::Matrix(std::size_t rows, std::size_t cols,
                      const std::initializer_list<num_t> &vals)
        : Matrix(rows, cols)
{
    assert(vals.size() == rows * cols);
    std::copy(vals.begin(), vals.end(), begin());
}

template <class It>
Matrix::Matrix(std::size_t rows, std::size_t cols, It begin, It end)
        : Matrix(rows, cols)
{
    std::copy(begin, end, this->begin());
}

inline Matrix::Matrix(const Matrix &m)
        : chunk_(m.chunk_)
        , ptr_(m.ptr_)
        , rows_(m.rows_)
        , cols_(m.cols_)
{
    if (chunk_)
        chunk_->ref();
}

inline Matrix::Matrix(Matrix&& m)
        : chunk_(m.chunk_)
        , ptr_(m.ptr_)
        , rows_(m.rows_)
        , cols_(m.cols_)
{
    m.chunk_ = nullptr;
}

inline Matrix::~Matrix()
{
    if (chunk_)
        chunk_->unref();
}

inline Matrix& Matrix::operator=(const Matrix &m)
{
    if (&m == this)
        return *this;
    if (chunk_)
        chunk_->unref();

    chunk_ = m.chunk_;
    ptr_ = m.ptr_;
    rows_ = m.rows_;
    cols_ = m.cols_;

    if (chunk_)
        chunk_->ref();
    return *this;
}

inline Matrix& Matrix::operator=(Matrix&& m)
{
    if (&m == this)
        return *this;

    if (chunk_)
        chunk_->unref();

    chunk_ = m.chunk_;
    ptr_ = m.ptr_;
    rows_ = m.rows_;
    cols_ = m.cols_;

    m.chunk_ = nullptr;
    return *this;
}

inline void Matrix::assign(std::size_t rows, std::size_t cols)
{
    if (chunk_)
        chunk_->unref();

    chunk_ = RealChunk::alloc(rows * cols);
    ptr_ = chunk_->data;
    rows_ = rows;
    cols_ = cols;

    chunk_->ref();
}

inline num_t* Matrix::begin()
{
    return ptr_;
}

inline const num_t* Matrix::begin() const
{
    return ptr_;
}

inline num_t* Matrix::end()
{
    return ptr_ + rows_ * cols_;
}

inline const num_t* Matrix::end() const
{
    return ptr_ + rows_ * cols_;
}

inline std::size_t Matrix::rows() const
{
    return rows_;
}

inline std::size_t Matrix::cols() const
{
    return cols_;
}

inline Shape Matrix::shape() const
{
    return Shape({rows_, cols_});
}

inline RealChunk* Matrix::chunk() const
{
    return chunk_;
}

inline num_t& Matrix::operator()(std::size_t row, std::size_t col)
{
    return at(row, col);
}

inline const num_t& Matrix::operator()(std::size_t row,
                                        std::size_t col) const
{
    return at(row, col);
}

inline num_t& Matrix::at(std::size_t row, std::size_t col)
{
    assert(row < rows_);
    assert(col < cols_);
    return ptr_[row * cols_ + col];
}

inline const num_t& Matrix::at(std::size_t row, std::size_t col) const
{
    assert(row < rows_);
    assert(col < cols_);
    return ptr_[row * cols_ + col];
}

inline Matrix Matrix::sub(std::size_t row_begin, std::size_t row_end) const
{
    assert(row_begin < rows());
    assert(row_end <= rows());
    assert(row_begin < row_end);
    return Matrix::ref(chunk_, ptr_ + row_begin * cols(), row_end - row_begin, cols());
}

inline Vector Matrix::get_row(std::size_t row) const
{
    assert(row < rows());
    return Vector::ref(chunk_, ptr_ + row * cols(), cols());
}

inline Vector Matrix::operator[](std::size_t row) const
{
    return get_row(row);
}

inline Matrix Matrix::copy() const
{
    return Matrix(rows(), cols(), begin(), end());
}

inline Matrix Matrix::transpose() const
{
    Matrix res(cols(), rows());
    for (std::size_t i = 0; i < rows(); ++i)
	for (std::size_t j = 0; j < cols(); ++j)
	    res(j, i) = at(i, j);
    return res;
}

inline Matrix& Matrix::operator+=(const Matrix& m)
{
    assert(rows() == m.rows());
    assert(cols() == m.cols());
    vect_add(begin(), end(), m.begin(), begin());
    return *this;
}

inline Matrix& Matrix::operator-=(const Matrix& m)
{
    assert(rows() == m.rows());
    assert(cols() == m.cols());
    vect_sub(begin(), end(), m.begin(), begin());
    return *this;
}

inline Matrix& Matrix::operator*=(const Matrix& m)
{
    assert(rows() == m.rows());
    assert(cols() == m.cols());
    vect_mul(begin(), end(), m.begin(), begin());
    return *this;
}


inline Matrix& Matrix::operator/=(const Matrix& m)
{
    assert(rows() == m.rows());
    assert(cols() == m.cols());
    vect_div(begin(), end(), m.begin(), begin());
    return *this;
}


inline Matrix& Matrix::operator+=(num_t x)
{
    vect_num_add(begin(), end(), x, begin());
    return *this;
}

inline Matrix& Matrix::operator-=(num_t x)
{
    vect_num_sub(begin(), end(), x, begin());
    return *this;
}

inline Matrix& Matrix::operator*=(num_t x)
{
    vect_num_mul(begin(), end(), x, begin());
    return *this;
}

inline Matrix& Matrix::operator/=(num_t x)
{
    vect_num_div(begin(), end(), x, begin());
    return *this;
}



inline Matrix Matrix::with(std::size_t rows, std::size_t cols, num_t val)
{
    Matrix m(rows, cols);
    std::fill(m.begin(), m.end(), val);
    return m;
}

inline Matrix Matrix::zeros(std::size_t rows, std::size_t cols)
{
    return with(rows, cols, 0);
}

inline Matrix Matrix::ones(std::size_t rows, std::size_t cols)
{
    return with(rows, cols, 1);
}

inline Matrix Matrix::id(std::size_t n)
{
    auto res = Matrix::with(n, n, 0.0);
    for (std::size_t i = 0; i < n; ++i)
        res(i, i) = 1;
    return res;
}

inline Matrix Matrix::ref(RealChunk* chunk, num_t* ptr, std::size_t rows, std::size_t cols)
{
    assert(ptr >= chunk->data);
    assert(ptr + rows * cols <= chunk->data + chunk->size);
    Matrix m;
    m.chunk_ = chunk;
    m.ptr_ = ptr;
    m.rows_ = rows;
    m.cols_ = cols;
    chunk->ref();
    return m;
}


inline Matrix operator+(const Matrix& a, const Matrix& b)
{
    assert(a.rows() == b.rows());
    assert(a.cols() == b.cols());
    Matrix res(a.rows(), a.cols());
    vect_add(a.begin(), a.end(), b.begin(), res.begin());
    return res;
}

inline Matrix operator-(const Matrix& a, const Matrix& b)
{
    assert(a.rows() == b.rows());
    assert(a.cols() == b.cols());
    Matrix res(a.rows(), a.cols());
    vect_sub(a.begin(), a.end(), b.begin(), res.begin());
    return res;
}

inline Matrix operator*(const Matrix& a, const Matrix& b)
{
    assert(a.rows() == b.rows());
    assert(a.cols() == b.cols());
    Matrix res(a.rows(), a.cols());
    vect_mul(a.begin(), a.end(), b.begin(), res.begin());
    return res;
}

inline Matrix operator/(const Matrix& a, const Matrix& b)
{
    assert(a.rows() == b.rows());
    assert(a.cols() == b.cols());
    Matrix res(a.rows(), a.cols());
    vect_div(a.begin(), a.end(), b.begin(), res.begin());
    return res;
}

inline Matrix operator+(const Matrix& a, num_t b)
{
    Matrix res(a.rows(), a.cols());
    vect_num_add(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Matrix operator-(const Matrix& a, num_t b)
{
    Matrix res(a.rows(), a.cols());
    vect_num_sub(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Matrix operator*(const Matrix& a, num_t b)
{
    Matrix res(a.rows(), a.cols());
    vect_num_mul(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Matrix operator/(const Matrix& a, num_t b)
{
    Matrix res(a.rows(), a.cols());
    vect_num_div(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Matrix operator+(num_t a, const Matrix& b)
{
    Matrix res(b.rows(), b.cols());
    num_vect_add(a, b.begin(), b.end(), res.begin());
    return res;
}

inline Matrix operator-(num_t a, const Matrix& b)
{
    Matrix res(b.rows(), b.cols());
    num_vect_sub(a, b.begin(), b.end(), res.begin());
    return res;
}

inline Matrix operator*(num_t a, const Matrix& b)
{
    Matrix res(b.rows(), b.cols());
    num_vect_mul(a, b.begin(), b.end(), res.begin());
    return res;
}

inline Matrix operator/(num_t a, const Matrix& b)
{
    Matrix res(b.rows(), b.cols());
    num_vect_div(a, b.begin(), b.end(), res.begin());
    return res;
}

inline Matrix operator-(const Matrix& a)
{
    Matrix res(a.rows(), a.cols());
    vect_neg(a.begin(), a.end(), res.begin());
    return res;
}

inline bool operator==(const Matrix& a, const Matrix& b)
{
    return a.rows() == b.rows() && a.cols() == b.cols()
	&& vect_equals(a.begin(), a.end(), b.begin());
}

inline bool operator!=(const Matrix& a, const Matrix& b)
{
    return !(a == b);
}

inline Matrix sgn(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_sgn(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix abs(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_abs(v.begin(), v.end(), res.begin());
    return res;
}
inline Matrix pow(const Matrix& v, num_t x)
{
    Matrix res(v.rows(), v.cols());
    vect_pow(v.begin(), v.end(), x, res.begin());
    return res;
}

inline Matrix sqrt(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_sqrt(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix exp(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_exp(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix log(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_log(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix cos(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_cos(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix sin(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_sin(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix tan(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_tan(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix acos(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_acos(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix asin(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_asin(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix atan(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_atan(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix cosh(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_cosh(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix sinh(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_sinh(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix tanh(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_tanh(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix acosh(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_acosh(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix asinh(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_asinh(v.begin(), v.end(), res.begin());
    return res;
}

inline Matrix atanh(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    vect_atanh(v.begin(), v.end(), res.begin());
    return res;
}

inline num_t min(const Matrix& v)
{
    return vect_min(v.begin(), v.end());
}

inline num_t max(const Matrix& v)
{
    return vect_max(v.begin(), v.end());
}

inline num_t min_abs(const Matrix& v)
{
    return vect_min_abs(v.begin(), v.end());
}

inline num_t max_abs(const Matrix& v)
{
    return vect_max_abs(v.begin(), v.end());
}

inline num_t sum(const Matrix& v)
{
    return vect_sum(v.begin(), v.end());
}

inline num_t product(const Matrix& v)
{
    return vect_product(v.begin(), v.end());
}

inline num_t mean(const Matrix& v)
{
    return vect_mean(v.begin(), v.end());
}

inline Matrix sigmoid(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    num_t* out = res.begin();
    for (const num_t* it = v.begin(); it != v.end(); ++it)
        *(out++) = sigmoid(*it);
    return res;
}

inline Matrix sigmoid_prime(const Matrix& v)
{
    Matrix res(v.rows(), v.cols());
    num_t *out = res.begin();
    for (const num_t *it = v.begin(); it != v.end(); ++it)
        *(out++) = sigmoid_prime(*it);
    return res;
}

inline Matrix softmax(const Matrix& m)
{
    Matrix res(m.rows(), m.cols());
    for (std::size_t i = 0; i < m.rows(); ++i)
    {
	Vector sub = softmax(m[i]);
	Vector sub2 = res[i];
	std::copy(sub.begin(), sub.end(), sub2.begin());
    }
    return res;
}

inline num_t norm(const Matrix& a)
{
    return vect_norm(a.begin(), a.end());
}

inline num_t norm_square(const Matrix& a)
{
    return vect_norm_square(a.begin(), a.end());
}

inline num_t dist(const Matrix& a, const Matrix& b)
{
    assert(a.rows() == b.rows());
    assert(a.cols() == b.cols());
    return vect_dist(a.begin(), a.end(), b.begin());
}

inline num_t dist_square(const Matrix& a, const Matrix& b)
{
    assert(a.rows() == b.rows());
    assert(a.cols() == b.cols());
    return vect_dist_square(a.begin(), a.end(), b.begin());
}


inline Matrix dot(const Matrix& a, const Matrix& b)
{
    assert(a.cols() == b.rows());
    Matrix res(a.rows(), b.cols());

    for (std::size_t i = 0; i < res.rows(); ++i)
    {
        for (std::size_t j = 0; j < res.cols(); ++j)
        {
            num_t val = 0;
            for (std::size_t k = 0; k < a.cols(); ++k)
                val += a(i, k) * b(k, j);
            res(i, j) = val;
        }
    }

    return res;
}

inline Vector dot(const Matrix& a, const Vector& b)
{
    assert(a.cols() == b.size());
    Vector res(a.rows());

    for (std::size_t i = 0; i < res.size(); ++i)
    {
        num_t val = 0;
        for (std::size_t k = 0; k < a.cols(); ++k)
            val += a(i, k) * b[k];
        res[i] = val;
    }

    return res;
}

inline Vector dot(const Vector& a, const Matrix& b)
{
    assert(a.size() == b.rows());
    Vector res(b.cols());

    for (std::size_t j = 0; j < res.size(); ++j) {
        num_t val = 0;
        for (std::size_t k = 0; k < a.size(); ++k)
            val += a[k] * b(k, j);
        res[j] = val;
    }

    return res;

}

inline Matrix outer_product(const Vector& a, const Vector& b)
{
    Matrix res(a.size(), b.size());
    for (std::size_t i = 0; i < res.rows(); ++i)
        for (std::size_t j = 0; j < res.cols(); ++j)
            res(i, j) = a[i] * b[j];
    return res;
}

inline bool fequals(const Matrix& a, const Matrix& b)
{
    assert(a.rows() == b.rows() && a.cols() == b.cols());
    return vect_fequals(a.begin(), a.end(), b.begin());
}

inline bool fzero(const Matrix& m)
{
    return vect_fzero(m.begin(), m.end());
}


inline Matrix outer(const Vector& a, const Vector& b)
{
    Matrix res(a.size(), b.size());
    vect_outer(a.begin(), a.end(), b.begin(), b.end(), res.begin());
    return res;
}
