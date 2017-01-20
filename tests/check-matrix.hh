#include <iostream>
#include <fstream>
#include <unistd.h>
#include <iostream>

#include "shell.hh"
#include "math.hh"

template <class F>
void check_system(std::size_t n, bool disp, F f)
{
  Random rand;
  Matrix m(n, n);
  for (std::size_t i = 0; i < n; ++i)
    for (std::size_t j = 0; j < n; ++j)
      m.at(i, j) = rand.double_get() * 1000.0 - 500.0;

  Vector b(n);
  for (std::size_t i = 0; i < n; ++i)
    b[i] = rand.double_get() * 1000.0 - 500.0;
  if (disp)
    {
      std::cout << m << std::endl;
      std::cout << b << std::endl;
    }

  Vector x = f(m, b);
  Vector b2 = m * x;
  if (disp)
    {
      std::cout << x << std::endl;
      std::cout << b2 << std::endl;
    }
  assert(fequals(b, b2));
}

template <class F>
void check_systems(std::size_t n, bool disp, F f)
{
  Random rand;
  Matrix m(n, n);
  for (std::size_t i = 0; i < n; ++i)
    for (std::size_t j = 0; j < n; ++j)
      m.at(i, j) = rand.double_get() * 1000.0 - 500.0;

  Matrix b(n, n);
  for (std::size_t i = 0; i < n; ++i)
    for (std::size_t j = 0; j < n; ++j)
      b.at(i, j) = rand.double_get() * 1000.0 - 500.0;

  if (disp)
    {
      std::cout << m << std::endl;
      std::cout << b << std::endl;
    }

  Matrix x = f(m, b);
  Matrix b2 = m * x;

  if (disp)
    {
      std::cout << x << std::endl;
      std::cout << b2 << std::endl;
    }
  assert(fequals(b, b2));
}

template <class F>
void check_inverse(std::size_t n, bool disp, F f)
{
  Random rand;
  Matrix m(n, n);
  for (std::size_t i = 0; i < n; ++i)
    for (std::size_t j = 0; j < n; ++j)
      m.at(i, j) = rand.double_get() * 1000.0 - 500.0;

  if (disp)
    std::cout << m << std::endl;

  Matrix x = f(m);
  Matrix i = m * x;
  if (disp)
    {
      std::cout << x << std::endl;
      std::cout << i << std::endl;
    }
  assert(fequals(i, Matrix::id(n)));
}

template <class F>
void check_decomp2(std::size_t rows, std::size_t cols,
                   bool disp, F f)
{
  Random rand;
  Matrix m(rows, cols);
  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
      m.at(i, j) = rand.double_get() * 1000.0 - 500.0;

  if (disp)
    std::cout << m << std::endl;

  auto res = f(m);
  Matrix a = res[0];
  Matrix b = res[1];
  if (disp)
    {
      std::cout << a << std::endl;
      std::cout << b << std::endl;
    }

  Matrix ab = a * b;
  if (disp)
    std::cout << ab << std::endl;
  assert(fequals(m, ab));
}

void check_plu(std::size_t n, bool disp)
{
  Random rand;
  Matrix m(n, n);
  for (std::size_t i = 0; i < n; ++i)
    for (std::size_t j = 0; j < n; ++j)
      m.at(i, j) = rand.double_get() * 1000.0 - 500.0;

  if (disp)
    std::cout << m << std::endl;

  auto res = LU::plu(m);
  Matrix p = res[0];
  Matrix l = res[1];
  Matrix u = res[2];
  if (disp)
    {
      std::cout << p << std::endl;
      std::cout << l << std::endl;
      std::cout << u << std::endl;
    }

  Matrix pa = p * m;
  Matrix lu = l * u;
  if (disp)
    {
      std::cout << pa << std::endl;
      std::cout << lu << std::endl;
    }
  assert(fequals(pa, lu));
}

void check_ortho(std::size_t m, std::size_t n, bool disp)
{
  Random rand;
  Matrix a(m, n);
  for (std::size_t i = 0; i < m; ++i)
    for (std::size_t j = 0; j < n; ++j)
      a.at(i, j) = rand.double_get() * 1000.0 - 500.0;

  if (disp)
    std::cout << a << std::endl;

  auto res = VList::orthogonalize(VList::mat_to_cols(a));
  Matrix b = VList::cols_to_mat(res);
  if (disp)
    std::cout << b << std::endl;
  assert(VList::is_orthogonal(res));

  auto res2 = VList::normalize(res);
  Matrix b2 = VList::cols_to_mat(res2);
  if (disp)
    std::cout << b2 << std::endl;
  assert(VList::is_orthonormal(res2));
}

void check_ortho2(std::size_t m, std::size_t n, bool disp)
{
  Random rand;
  Matrix a(m, n);
  for (std::size_t i = 0; i < m; ++i)
    for (std::size_t j = 0; j < n; ++j)
      a.at(i, j) = rand.double_get() * 1000.0 - 500.0;

  if (disp)
    std::cout << a << std::endl;

  VList::list_t coeffs;
  auto res = VList::orthogonalize(VList::mat_to_cols(a), coeffs);
  Matrix b = VList::cols_to_mat(res);
  Matrix r = VList::cols_to_upper(coeffs);
  if (disp)
    {
      std::cout << b << std::endl;
      std::cout << r << std::endl;
    }
  assert(VList::is_orthogonal(res));

  Matrix br = b * r;
  if (disp)
    std::cout << br << std::endl;
  assert(fequals(a, br));
}

void check_qr(std::size_t m, std::size_t n, bool disp)
{
  Random rand;
  Matrix a(m, n);
  for (std::size_t i = 0; i < m; ++i)
    for (std::size_t j = 0; j < n; ++j)
      a.at(i, j) = rand.double_get() * 1000.0 - 500.0;

  if (disp)
    std::cout << a << std::endl;

  auto res = QR::gram_schmidt(a);
  Matrix q = res[0];
  Matrix r = res[1];
  Matrix qr = q * r;
  if (disp)
    {
      std::cout << q << std::endl;
      std::cout << r << std::endl;
      std::cout << qr << std::endl;
    }
  assert(fequals(a, qr));
  assert(VList::is_orthonormal(VList::mat_to_cols(q)));
}
