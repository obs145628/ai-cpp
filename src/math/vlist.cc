#include "math/vlist.hh"
#include <cassert>
#include "math/gauss.hh"

Vector VList::row_to_vec(const Matrix& m, std::size_t row)
{
  assert(row < m.rows());
  Vector res(m.cols());
  for (std::size_t i = 0; i < m.cols(); ++i)
    res[i] = m.at(row, i);
  return res;
}

Vector VList::col_to_vec(const Matrix& m, std::size_t col)
{
  assert(col < m.cols());
  Vector res(m.rows());
  for (std::size_t i = 0; i < m.rows(); ++i)
    res[i] = m.at(i, col);
  return res;
}

VList::list_t VList::mat_to_rows(const Matrix& m)
{
  list_t res;
  for (std::size_t i = 0; i < m.rows(); ++i)
    res.push_back(row_to_vec(m, i));
  return res;
}

VList::list_t VList::mat_to_cols(const Matrix& m)
{
  list_t res;
  for (std::size_t i = 0; i < m.cols(); ++i)
    res.push_back(col_to_vec(m, i));
  return res;
}

void VList::row_set(Matrix& m, std::size_t i, const Vector& v)
{
  assert(i < m.rows());
  assert(v.size() == m.cols());
  for (std::size_t j = 0; j < v.size(); ++j)
    m.at(i, j) = v[j];
}

void VList::col_set(Matrix& m, std::size_t i, const Vector& v)
{
  assert(i < m.cols());
  assert(v.size() == m.rows());
  for (std::size_t j = 0; j < v.size(); ++j)
    m.at(j, i) = v[j];
}

Matrix VList::rows_to_mat(const list_t& list)
{
  assert(list.size());
  Matrix res(list.size(), list[0].size());
  for (std::size_t i = 0; i < list.size(); ++i)
    row_set(res, i, list[i]);
  return res;
}

Matrix VList::cols_to_mat(const list_t& list)
{
  assert(list.size());
  Matrix res(list[0].size(), list.size());
  for (std::size_t i = 0; i < list.size(); ++i)
    col_set(res, i, list[i]);
  return res;
}

Matrix VList::rows_to_upper(const list_t& list)
{
  std::size_t n = list.size();
  auto res = Matrix::null(n, n);

  for (std::size_t i = 0; i < n; ++i)
    {
      const auto& v = list[i];
      assert(v.size() == n - i);
      for (std::size_t j = i; j < n; ++j)
        res.at(i, j) = v[j - i];
    }

  return res;
}

Matrix VList::cols_to_upper(const list_t& list)
{
  std::size_t n = list.size();
  auto res = Matrix::null(n, n);

  for (std::size_t j = 0; j < n; ++j)
    {
      const auto& v = list[j];
      assert(v.size() == j + 1);
      for (std::size_t i = 0; i <= j; ++i)
        res.at(i, j) = v[i];
    }

  return res;
}

Matrix VList::join_cols(const Matrix& m, const Vector& v)
{
  assert(m.rows() == v.size());
  Matrix res(m.rows(), m.cols() + 1);
  for (std::size_t i = 0; i < m.rows(); ++i)
    for (std::size_t j = 0; j < m.cols(); ++j)
      res.at(i, j) = m.at(i, j);
  VList::col_set(res, m.cols(), v);
  return res;
}

void VList::swap_row(Matrix& m, std::size_t a, std::size_t b)
{
  Vector va = row_to_vec(m, a);
  Vector vb = row_to_vec(m, b);
  row_set(m, a, vb);
  row_set(m, b, va);
}

void VList::swap_col(Matrix& m, std::size_t a, std::size_t b)
{
  Vector va = col_to_vec(m, a);
  Vector vb = col_to_vec(m, b);
  col_set(m, a, vb);
  col_set(m, b, va);
}

bool VList::is_orthogonal(const list_t& l)
{
  for (std::size_t i = 0; i < l.size(); ++i)
    for (std::size_t j = i + 1; j < l.size(); ++j)
      if (!l[i].is_orthogonal_to(l[j]))
        return false;
  return true;
}

bool VList::is_orthonormal(const list_t& l)
{
  for (const auto& v : l)
    if (!v.is_unit())
      return false;
  return is_orthogonal(l);
}

VList::list_t VList::normalize(const list_t& l)
{
  list_t res;
  for (const auto& v: l)
    res.push_back(v.normalize());
  return res;
}

Vector VList::project_orthogonal(const Vector& v, const list_t& l)
{
  Vector res = v;
  for (const auto& v2: l)
    res -= res.project_along(v2);
  return res;
}

Vector VList::project_orthogonal(const Vector& v, const list_t& l,
                                 Vector& coeffs)
{
  Vector res = v;
  Vector a(l.size() + 1);
  for (std::size_t i = 0; i < l.size(); ++i)
    {
      const auto& v2 = l[i];
      double v2norm = v2.norm_square();
      double x = v2norm ? res.dot(v2) / v2norm : 0;
      res -= x * v2;
      a[i] = x;
    }

  a[l.size()] = 1;
  coeffs = a;
  return res;
}

VList::list_t VList::orthogonalize(const list_t& l)
{
  list_t res;
  for (const auto& v : l)
    res.push_back(project_orthogonal(v, res));
  return res;
}

VList::list_t VList::orthogonalize(const list_t& l, list_t& coeffs)
{
  list_t res;
  coeffs.clear();
  for (const auto& v : l)
    {
      Vector temp(1);
      res.push_back(project_orthogonal(v, res, temp));
      coeffs.push_back(temp);
    }
  return res;
}

VList::list_t VList::basis_get(const list_t& l)
{
  auto l2 = orthogonalize(l);
  list_t res;
  for (const auto& v : l2)
    if (!is_fnull(v))
      res.push_back(v);
  return res;
}

VList::list_t VList::nullspace_get(const Matrix& a)
{
  list_t coeffs;
  auto l = orthogonalize(mat_to_cols(a), coeffs);
  Matrix r = VList::cols_to_upper(coeffs);
  Matrix rinv = Gauss::inverse_upper(r);

  list_t res;
  for (std::size_t i = 0; i < l.size(); ++i)
    if (is_fnull(l[i]))
      res.push_back(col_to_vec(rinv, i));
  return res;
}

std::ostream& operator<<(std::ostream& os, const VList::list_t& list)
{
  if (list.size() == 0)
    return os << "{}";

  os << "{\n";
  for (std::size_t i = 0; i < list.size(); ++i)
    {
      os << "  " << list[i];
      if (i + 1 == list.size())
        os << ",";
      os <<  "\n";
    }
  return os << "}";
}
