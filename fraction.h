#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <functional>

#include <gmp.h>
#include <gmpxx.h>

#define FRACTION_INT int32_t
#define FRACTION_INT_MAX 2147483647

class fraction
{
public:
    fraction(FRACTION_INT n, FRACTION_INT d);

    fraction(const mpz_class &n, const mpz_class &d);

    fraction(const std::string n, const std::string d);

    fraction();

    ~fraction() = default;

    fraction InverseCopy() const;

    bool use_mpz() const { return use_mpz_; }

    bool MulResFitsToFRACTION_INT(FRACTION_INT op1, FRACTION_INT op2) const;

    mpz_class get_num() const { return use_mpz_ ? num_mpz_ : num_int_; }

    mpz_class get_den() const { return use_mpz_ ? den_mpz_ : den_int_; }

    void set_num_den(FRACTION_INT _num, FRACTION_INT _den);

    void set_num_den(const mpz_class &num, const mpz_class &den);

    void printFract() const;

    fraction &operator=(const fraction &other);

    fraction &operator+=(const fraction &f);

    fraction &operator*=(const fraction &f);

    fraction operator+(const fraction &f) const;

    fraction operator*(const fraction &f) const;

    fraction operator*(const int &f) const;

    fraction operator/(const fraction &f) const;

    bool operator>(const fraction &f) const;

    bool operator<(const fraction &f) const;

    bool operator>=(const fraction &f) const;

    bool operator<=(const fraction &f) const;

    bool operator==(const fraction &f) const;

    bool operator!=(const fraction &f) const;

    bool ComparisonOperatorBase(const fraction &f,
                                std::function<bool(const mpz_class &f1, const mpz_class &f2)> comparator) const;

public:
    static FRACTION_INT fit_to_int_t_BJ_values[5];

    static FRACTION_INT ADD_OPERAND_MAX;

    static fraction zero_fraction;

    static fraction one_fraction;

private:
    static FRACTION_INT gcf(FRACTION_INT a, FRACTION_INT b);

    void NormalizeMpzFrac();

    void NormalizeIntFrac();

    void NormalizeThis();

    static fraction NormalizeFRACTION_INT(FRACTION_INT num, FRACTION_INT den);

    static fraction NormalizeMpz(const mpz_class &num, const mpz_class &den);

private:
    FRACTION_INT num_int_;
    FRACTION_INT den_int_;

    mpz_class num_mpz_;
    mpz_class den_mpz_;

    bool use_mpz_;
};
