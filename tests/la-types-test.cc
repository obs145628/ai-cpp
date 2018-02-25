#include "la-types-test.hh"
#include <fstream>
#include "la/functions.hh"
#include "la/matrix.hh"
#include "la/tensor.hh"
#include "la/vector.hh"

void LATypesTest::init()
{
    register_test("vector_operations", &LATypesTest::test_vector_ops);
    register_test("vector_functions", &LATypesTest::test_vector_functions);
    register_test("dot_product", &LATypesTest::test_dot);
    register_test("serialization", &LATypesTest::test_serial);
}

void LATypesTest::test_vector_ops()
{
    Vector v1 {4, 2, 3, 6};
    Vector v2 {3, 5, 2, -2};

    Vector v3 = v1 + v2;
    TEST_EQ(v3, (Vector{7, 7, 5, 4}));
    Vector v4 = v1.copy();
    v4 += Vector {4, 6, 1, 3};
    TEST_EQ(v4, (Vector{8, 8, 4, 9}));

    Vector v5 = v1 - v2;
    TEST_EQ(v5, (Vector{1, -3, 1, 8}));
    Vector v6 = v1.copy();
    v6 -= Vector {4, 6, 1, 3};
    TEST_EQ(v6, (Vector{0, -4, 2, 3}));

    Vector v7 = v1 * v2;
    TEST_EQ(v7, (Vector{12, 10, 6, -12}));
    Vector v8 = v1.copy();
    v8 *= Vector {4, 6, 1, 3};
    TEST_EQ(v8, (Vector{16, 12, 3, 18}));

    Vector v9 = v1 / v2;
    TEST_EQ(v9, (Vector{4. / 3., 2. / 5., 3. / 2., -6. /2.}));
    Vector v10 = v1.copy();
    v10 /= v1;
    TEST_EQ(v10, (Vector{1, 1, 1, 1}));

    Vector v11 = v1 + 2;
    TEST_EQ(v11, (Vector{6, 4, 5, 8}));
    Vector v12 = v1.copy();
    v12 += 2;
    TEST_EQ(v12, (Vector{6, 4, 5, 8}));

    Vector v13 = v1 - 2;
    TEST_EQ(v13, (Vector{2, 0, 1, 4}));
    Vector v14 = v1.copy();
    v14 -= 2;
    TEST_EQ(v14, (Vector{2, 0, 1, 4}));

    Vector v15 = v1 * 2;
    TEST_EQ(v15, (Vector{8, 4, 6, 12}));
    Vector v16 = v1.copy();
    v16 *= 2;
    TEST_EQ(v16, (Vector{8, 4, 6, 12}));

    Vector v17 = v1 / 2;
    TEST_EQ(v17, (Vector{2, 1, 1.5, 3}));
    Vector v18 = v1.copy();
    v18 /= 2;
    TEST_EQ(v18, (Vector{2, 1, 1.5, 3}));

    TEST_EQ(norm_square(v1), num_t{65.});
    TEST_EQ(norm(Vector{3, 4}), num_t{5.});
    
}

void LATypesTest::test_vector_functions()
{
    TEST_EQ(min(Vector{1, 4, 6}), num_t(1));
    TEST_EQ(max(Vector{1, 4, 6}), num_t(6));
    TEST_EQ(min_abs(Vector{1, -4, 6}), num_t(1));
    TEST_EQ(max_abs(Vector{1, 4, -6}), num_t(6));
    TEST_EQ(sum(Vector{1, 4, 6}), num_t(11));
    TEST_EQ(product(Vector{1, 4, 6}), num_t(24));
    TEST_EQ(mean(Vector{2, 4, 6}), num_t(4));
    TEST_EQ(dot(Vector{2, 4}, Vector{3, 1}), num_t(10));
    TEST_EQ(dist_square(Vector{2, 4}, Vector{3, 1}), num_t(10));
    TEST_EQ(dist(Vector{2, 4}, Vector{2, 1}), num_t(3));
    TEST(fequals(Vector{2, 4}, Vector{2, 4}));
    TEST(!fzero(Vector{2, 4}));
    TEST(fzero(Vector{0, 0}));
}

void LATypesTest::test_dot()
{
    Vector n1 {3};
    Vector n2 {4};

    Vector v1 {3, 5, 8};
    Vector v2 {4, -1, 2};

    Matrix rv1 (1, v1.size(), v1.begin(), v1.end());
    Matrix rv2 (1, v2.size(), v2.begin(), v2.end());
    Matrix cv1 (v1.size(), 1, v1.begin(), v1.end());
    Matrix cv2 (v1.size(), 1, v2.begin(), v2.end());

    Matrix m1 (3, 3, {
            4, 3, 1,
            8, -2, 1,
            12, 6, 9
    });

    TEST(fequals(dot(n1, n2), 12));
    TEST(fequals(dot(v1, v2), 23));
    TEST(fequals(dot(rv1, v2), Vector {23}));
    TEST(fequals(dot(v1, cv2), Vector {23}));
    TEST(fequals(dot(rv1, cv2), Matrix(1, 1, {23})));
    TEST(fequals(dot(rv2, cv1), Matrix(1, 1, {23})));

    Vector t1 = v1.copy();
    TEST(fequals(v1, t1));
    t1[0] = 8;
    TEST(!fequals(v1, t1));

    Vector t2 = v1;
    TEST(fequals(v1, t2));
    t2[0] = 8;
    TEST(fequals(v1, t2));

    Matrix t3 = m1.copy();
    TEST(fequals(m1, t3));
    t3(0, 1) = 16;
    TEST(!fequals(m1, t3));

    Matrix t4 = m1;
    TEST(fequals(m1, t4));
    t4(0, 1) = 16;
    TEST(fequals(m1, t4));
}

void LATypesTest::test_serial()
{
    Vector v {3, 8, 7, 4};

    Matrix m (2, 3, {
            4, 6, 7,
            11, -1, 3.5
    });

    std::string str {"hello"};
    Tensor tv(v);
    Tensor tm(m);

    Vector v2;
    Matrix m2;
    std::string str2;
    Tensor tv2;
    Tensor tm2;

    {
        std::ofstream fs("./test.data");
        TextSerialWriter writer(fs);
        writer << v << m << str << tv << tm;
    }

    {
        std::ifstream fs("./test.data");
        TextSerialReader reader(fs);
        reader >> v2 >> m2 >> str2 >> tv2 >> tm2;
    }

    TEST(v == v2);
    TEST(m == m2);
    TEST(str == str2);
    TEST(tv == tv2);
    TEST(tm == tm2);
}
