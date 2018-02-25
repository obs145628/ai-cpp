#include "la/mat_dec.hh"
#include "la/functions.hh"

Vector solve_lower(const Matrix& m, const Vector& b)
{
    assert(m.rows() == m.cols());
    assert(m.rows() == b.size());
    std::size_t n = m.rows();
    Vector x(n);

    for (std::size_t k = 0; k < n; ++k)
    {
        num_t val = b[k];
        for (std::size_t i = 0; i < k; ++i)
            val -= m(k, i) * x[i];
        x[k] = val / m(k, k);
    }


    return x;
}

Vector solve_upper(const Matrix& m, const Vector& b)
{
    assert(m.rows() == m.cols());
    assert(m.rows() == b.size());
    std::size_t n = m.rows();
    Vector x(n);

    for (std::size_t k = n - 1; k < n; --k)
    {
        num_t val = b[k];
        for (std::size_t i = k + 1; i < n; ++i)
            val -= m(k, i) * x[i];
        x[k] = val / m(k, k);
    }

    return x;
}

Matrix transpose(const Matrix& m)
{
    Matrix res(m.cols(), m.rows());
    for (std::size_t i = 0; i < m.cols(); ++i)
        for (std::size_t j = 0; j < m.rows(); ++j)
            res(i, j) = m(j, i);
    return res;
}

Matrix inverse(const Matrix& m)
{
    return plu_inverse(m);
}


bool plu_decomposition(const Matrix& m, Matrix& p, Matrix& l, Matrix& u,
                       std::vector<std::size_t>& pv,
                       bool& even_permuts)
{
    assert(m.rows() == m.cols());
    Matrix res = m.copy();
    std::size_t n = m.rows();
    std::size_t nb_permuts = 0;
    std::vector<num_t> inv_largest(n);
    std::vector<std::size_t> permuts(n);
    for (std::size_t i = 0; i < n; ++i)
        permuts[i] = i;

    //Find max element in each row
    //If max is 0 => rows of 0 => can't decompose
    for (std::size_t i = 0; i < n; ++i)
    {
        num_t max = 0;
        for (std::size_t j = 0; j < n; ++j)
        {
            if (std::abs(res(i, j)) > max)
                max = std::abs(res(i, j));
        }

        if (max == 0)
            return false;
        inv_largest[i] = 1.0 / max;
    }

    // decompose collumn b collumn
    for (std::size_t k = 0; k < n; ++k)
    {


        //find max element among of the collumn at or below current collumn
        //if max is 0 => no pivot => can't decompose
        num_t max_val = 0;
        std::size_t max_i = k;

        for (std::size_t i = k; i < n; ++i)
        {
            num_t val = inv_largest[i] * std::abs(res(i, k));
            if (val > max_val)
            {
                max_val = val;
                max_i = i;
            }
        }

        if (max_val == 0)
        {
            return false;
        }



        //Swqp current row with the pivot
        if (max_i != k)
        {
            for (std::size_t j = 0; j < n; ++j)
                std::swap(res(max_i, j), res(k, j));

            std::swap(inv_largest[max_i], inv_largest[k]);
            std::swap(permuts[max_i], permuts[k]);
            ++nb_permuts;
        }


        for (std::size_t i = k + 1; i < n; ++i)
        {
            //Divide all elements in column below the diagonal by the pivot value
            res(i, k) /= res(k, k);

            //Apply Gaussian elimination
            for (std::size_t j = k + 1; j < n; ++j)
                res(i, j) -= res(i, k) * res(k, j);
        }
    }

    Matrix pout = Matrix::with(n, n, 0);
    for (std::size_t i = 0; i < n; ++i)
        pout(i, permuts[i]) = 1;

    Matrix lout = Matrix::id(n);
    for (std::size_t i = 0; i < n; ++i)
        for (std::size_t j = 0; j < i; ++j)
            lout(i, j) = res(i, j);

    Matrix uout = Matrix::with(n, n, 0);
    for (std::size_t i = 0; i < n; ++i)
        for (std::size_t j = i; j < n; ++j)
            uout(i, j) = res(i, j);

    p = pout;
    l = lout;
    u = uout;
    pv = permuts;
    even_permuts = nb_permuts % 2 == 0;
    return true;
}

Vector plu_solve(const Matrix& m, const Vector& b)
{
    assert(m.rows() == m.cols());
    assert(m.rows() == b.size());
    std::size_t n = m.rows();
    Matrix p;
    Matrix l;
    Matrix u;
    std::vector<std::size_t> pv;
    bool permuts;
    bool ok = plu_decomposition(m, p, l, u, pv, permuts);
    if (!ok)
        return Vector{};

    Vector b2(n);
    for (std::size_t i = 0; i < n; ++i)
        b2[pv[i]] = b[i];

    Vector y = solve_lower(l, b2);
    Vector x = solve_upper(u, y);
    return x;
}

Matrix plu_solve(const Matrix& m, const Matrix& b)
{
    assert(m.rows() == m.cols());
    assert(b.rows() == b.cols());
    assert(m.rows() == b.rows());
    std::size_t n = m.rows();
    Matrix p;
    Matrix l;
    Matrix u;
    std::vector<std::size_t> pv;
    bool permuts;
    bool ok = plu_decomposition(m, p, l, u, pv, permuts);
    if (!ok)
        return Matrix{};
    Matrix res(n, n);

    for (std::size_t k = 0; k < n; ++k)
    {
        Vector b2(n);
        for (std::size_t i = 0; i < n; ++i)
            b2[pv[i]] = b(i, k);

        Vector y = solve_lower(l, b2);
        Vector x = solve_upper(u, y);
        for (std::size_t i = 0; i < n; ++i)
            res(i, k) = x[i];
    }

    return res;
}

Matrix plu_inverse(const Matrix& m)
{
    assert(m.rows() == m.cols());
    return plu_solve(m, Matrix::id(m.rows()));
}

