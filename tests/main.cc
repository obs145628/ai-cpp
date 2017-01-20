#include <cmath>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <iostream>

#include "check-matrix.hh"
#include "shell.hh"
#include "math.hh"

void lp_print(const Matrix& a, const Vector& c, const Vector& res,
              const Vector& d, const Vector& vars, real_t z)
{
  std::size_t n = a.rows();
  std::size_t p = a.cols();

  (void) n;
  (void) p;
  (void) res;

  std::cout << "c_i: ";
  for (std::size_t i = 0; i < n ; ++i)
    std::cout << c[vars[i]] << " ";
  std::cout << "\n";

  std::cout << "  i: ";
  for (std::size_t i = 0; i < n ; ++i)
    std::cout << vars[i] << " ";
  std::cout << "\n";

  Matrix disp(n + 2, p + 1);
  for (std::size_t i = 0; i < n; ++i)
    for (std::size_t j = 0; j < p; ++j)
      disp.at(i, j) = a.at(i, j);

  for (std::size_t i = 0; i < n; ++i)
    disp.at(i, p) = res[vars[i]];

  for (std::size_t i = 0; i < p; ++i)
    disp.at(n, i) = c[i];
  for (std::size_t i = 0; i < p; ++i)
    disp.at(n + 1, i) = d[i];

  disp.at(n + 1, p) = z;
  
  std::cout << disp << "\n";
  std::cout << "\n\n";
}

Vector lp(Matrix a, const Vector& c, Vector res)
{
  Vector d = c;
  std::size_t n = a.rows();
  std::size_t p = a.cols();

  Vector vars(n);
  for (std::size_t i = 0; i < n; ++i)
    vars[i] = n + i;

  real_t z = 0;
  for (std::size_t i = 0; i < n; ++i)
    z += c[i] * res[i];

  lp_print(a, c, res, d, vars, z);

  std::size_t it = 0;

  while (true)
    {
      std::size_t e = 0;
      std::size_t s = 0;
      bool finished = true;
      for (std::size_t i = 0; i < p; ++i)
        {
          if (d[i] <= 0)
            continue;
          if (finished || d[i] > d[e])
            e = i;
          finished = false;
        }

      if (finished)
        break;

      for (std::size_t i = 0; i < n; ++i)
        if (c[vars[i]] <= c[vars[s]])
          s = i;

      //if (it == 1)
      //s = 0;



      std::cout << "e = " << e << std::endl;
      std::cout << "s = " << vars[s] << std::endl;

      real_t coeff = a.at(s, e);
      for (std::size_t i = 0; i < p; ++i)
        a.at(s, i) /= coeff;
      res[vars[s]] /= coeff;

      for (std::size_t i = 0; i < n; ++i)
        {
          if (i == s)
            continue;
          real_t coeff = a.at(i, e);
          for (std::size_t j = 0; j < p; ++j)
            a.at(i, j) -= coeff * a.at(s, j);
          res[vars[i]] -= coeff * res[vars[s]];
        }

      real_t dcoeff = d[e];
      for (std::size_t i = 0; i < p; ++i)
        d[i] -= dcoeff * a.at(s, i);
      z += std::abs(dcoeff * res[vars[s]]);

      res[e] = res[vars[s]];
      res[vars[s]] = 0;
      vars[s] = e;

      ++it;
      lp_print(a, c, res, d, vars, z);
      //break;
    }

  return res;
}

int main()
{

  Matrix a(3, 6,
           {
             1, 1, 1, 1, 0, 0,
             80, 95, 90, 0, 1, 0,
             1, -1, -1, 0, 0, 1
           });

  Vector c {10, 8, 7, 0, 0, 0};
  Vector res{0, 0, 0, 1000, 90000, 100};

  Vector x = lp(a, c, res);

  std::cout << " x = " << x << std::endl;
  real_t z = 0;
  for (std::size_t i = 0; i < c.size(); ++i)
    z += c[i] * x[i];
  std::cout << "z = " << z << std::endl;

  return 0;
}
