/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <gtest/gtest.h>
#include <testHelpers.hpp>
#include <af/arith.h>
#include <af/array.h>
#include <af/data.h>

using std::endl;
using namespace af;

const int num = 10;

#define CPLX(TYPE) af_c##TYPE

#define COMPLEX_TESTS(Ta, Tb, Tc)                                     \
    TEST(ComplexTests, Test_##Ta##_##Tb) {                            \
        SUPPORTED_TYPE_CHECK(Ta);                                     \
        SUPPORTED_TYPE_CHECK(Tb);                                     \
        SUPPORTED_TYPE_CHECK(Tc);                                     \
                                                                      \
        af_dtype ta   = (af_dtype)dtype_traits<Ta>::af_type;          \
        af_dtype tb   = (af_dtype)dtype_traits<Tb>::af_type;          \
        array a       = randu(num, ta);                               \
        array b       = randu(num, tb);                               \
        array c       = complex(a, b);                                \
        Ta *h_a       = a.host<Ta>();                                 \
        Tb *h_b       = b.host<Tb>();                                 \
        CPLX(Tc) *h_c = c.host<CPLX(Tc)>();                           \
        for (int i = 0; i < num; i++)                                 \
            ASSERT_EQ(h_c[i], CPLX(Tc)(h_a[i], h_b[i]))               \
                << "for values: " << h_a[i] << "," << h_b[i] << endl; \
        freeHost(h_a);                                                \
        freeHost(h_b);                                                \
        freeHost(h_c);                                                \
    }                                                                 \
    TEST(ComplexTests, Test_cplx_##Ta##_##Tb##_left) {                \
        SUPPORTED_TYPE_CHECK(Ta);                                     \
        SUPPORTED_TYPE_CHECK(Tb);                                     \
                                                                      \
        af_dtype ta   = (af_dtype)dtype_traits<Ta>::af_type;          \
        array a       = randu(num, ta);                               \
        Tb h_b        = 0.3;                                          \
        array c       = complex(a, h_b);                              \
        Ta *h_a       = a.host<Ta>();                                 \
        CPLX(Ta) *h_c = c.host<CPLX(Ta)>();                           \
        for (int i = 0; i < num; i++)                                 \
            ASSERT_EQ(h_c[i], CPLX(Ta)(h_a[i], h_b))                  \
                << "for values: " << h_a[i] << "," << h_b << endl;    \
        freeHost(h_a);                                                \
        freeHost(h_c);                                                \
    }                                                                 \
                                                                      \
    TEST(ComplexTests, Test_cplx_##Ta##_##Tb##_right) {               \
        SUPPORTED_TYPE_CHECK(Ta);                                     \
        SUPPORTED_TYPE_CHECK(Tb);                                     \
                                                                      \
        af_dtype tb   = (af_dtype)dtype_traits<Tb>::af_type;          \
        Ta h_a        = 0.3;                                          \
        array b       = randu(num, tb);                               \
        array c       = complex(h_a, b);                              \
        Tb *h_b       = b.host<Tb>();                                 \
        CPLX(Tb) *h_c = c.host<CPLX(Tb)>();                           \
        for (int i = 0; i < num; i++)                                 \
            ASSERT_EQ(h_c[i], CPLX(Tb)(h_a, h_b[i]))                  \
                << "for values: " << h_a << "," << h_b[i] << endl;    \
        freeHost(h_b);                                                \
        freeHost(h_c);                                                \
    }                                                                 \
    TEST(ComplexTests, Test_##Ta##_##Tb##_Real) {                     \
        SUPPORTED_TYPE_CHECK(Ta);                                     \
        SUPPORTED_TYPE_CHECK(Tb);                                     \
        SUPPORTED_TYPE_CHECK(Tc);                                     \
                                                                      \
        af_dtype ta = (af_dtype)dtype_traits<Ta>::af_type;            \
        af_dtype tb = (af_dtype)dtype_traits<Tb>::af_type;            \
        array a     = randu(num, ta);                                 \
        array b     = randu(num, tb);                                 \
        array c     = complex(a, b);                                  \
        array d     = real(c);                                        \
        Ta *h_a     = a.host<Ta>();                                   \
        Tc *h_d     = d.host<Tc>();                                   \
        for (int i = 0; i < num; i++)                                 \
            ASSERT_EQ(h_d[i], h_a[i]) << "at: " << i << endl;         \
        freeHost(h_a);                                                \
        freeHost(h_d);                                                \
    }                                                                 \
    TEST(ComplexTests, Test_##Ta##_##Tb##_Imag) {                     \
        SUPPORTED_TYPE_CHECK(Ta);                                     \
        SUPPORTED_TYPE_CHECK(Tb);                                     \
        SUPPORTED_TYPE_CHECK(Tc);                                     \
                                                                      \
        af_dtype ta = (af_dtype)dtype_traits<Ta>::af_type;            \
        af_dtype tb = (af_dtype)dtype_traits<Tb>::af_type;            \
        array a     = randu(num, ta);                                 \
        array b     = randu(num, tb);                                 \
        array c     = complex(a, b);                                  \
        array d     = imag(c);                                        \
        Tb *h_b     = b.host<Tb>();                                   \
        Tc *h_d     = d.host<Tc>();                                   \
        for (int i = 0; i < num; i++)                                 \
            ASSERT_EQ(h_d[i], h_b[i]) << "at: " << i << endl;         \
        freeHost(h_b);                                                \
        freeHost(h_d);                                                \
    }                                                                 \
    TEST(ComplexTests, Test_##Ta##_##Tb##_Conj) {                     \
        SUPPORTED_TYPE_CHECK(Ta);                                     \
        SUPPORTED_TYPE_CHECK(Tb);                                     \
        SUPPORTED_TYPE_CHECK(Tc);                                     \
                                                                      \
        af_dtype ta   = (af_dtype)dtype_traits<Ta>::af_type;          \
        af_dtype tb   = (af_dtype)dtype_traits<Tb>::af_type;          \
        array a       = randu(num, ta);                               \
        array b       = randu(num, tb);                               \
        array c       = complex(a, b);                                \
        array d       = conjg(c);                                     \
        CPLX(Tc) *h_c = c.host<CPLX(Tc)>();                           \
        CPLX(Tc) *h_d = d.host<CPLX(Tc)>();                           \
        for (int i = 0; i < num; i++)                                 \
            ASSERT_EQ(conj(h_c[i]), h_d[i]) << "at: " << i << endl;   \
        freeHost(h_c);                                                \
        freeHost(h_d);                                                \
    }

COMPLEX_TESTS(float, float, float)
COMPLEX_TESTS(double, double, double)
COMPLEX_TESTS(float, double, double)
