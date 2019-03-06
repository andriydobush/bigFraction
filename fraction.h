/*==============================================================================================*/
/**  C++ fraction class header file:
*   @file fraction.h
*
*==============================================================================================*/
#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <functional>

#include <gmp.h>
#include <gmpxx.h>

/** Definition of common signed integer type.
 * int32_t: for better compatibility with x32 architecture
 * int64_t: possible in case you are shure that you will use only x64 system
 * int64_t NOT TESTED - if you use it, please send feedback about correctnes of working.
 */
#define FRACTION_INT int32_t

/** Maximum value of common integer type.
 * Is used for smart prediction of multiplication result
 */
#define FRACTION_INT_MAX 2147483647

/** @brief CLass for using fractions with big numbers.
 * GMP big integers are used simultaneously with common integer type
 * Optimised switching between gmp integer and common integer usage.
 * Smart predicion of multiplication result for decision which type should be used.
 */
class fraction
{
public:
    /** @brief Fraction constructor 
     * @param[in] n fraction numerator
     * @param[in] d  fraction denominator
     */
    fraction(FRACTION_INT n, FRACTION_INT d);

    /** @brief Fraction constructor 
     * @param[in] n fraction numerator
     * @param[in] d  fraction denominator
     */
    fraction(const mpz_class &n, const mpz_class &d);

    /** @brief Fraction constructor 
     * @param[in] n fraction numerator
     * @param[in] d  fraction denominator
     */
    fraction(const std::string n, const std::string d);

    /** @brief Fraction constructor with default values 0/1
     */
    fraction();

    /** @brief Default fraction destructor
     */
    ~fraction() = default;

    /** @brief Make inversed copy of fraction
     * return Inversed copy of fraction
     */
    fraction InverseCopy() const;

    /** @brief Get actual type, used for storing fraction
     * return true if mpz integer is used to store fraction data
     * return false if common integer is used to store fraction data
     */
    bool use_mpz() const { return use_mpz_; }

    /** @brief Prediction if multiplication of two integers will fits into ingeger
     *        without multiplication processing.
     * return true if op1*op2 < FRACTION_INT_MAX
     * return false if op1*op2 > FRACTION_INT_MAX
     */
    bool MulResFitsToFRACTION_INT(FRACTION_INT op1, FRACTION_INT op2) const;

    /** @brief Get numerator
     * return numerator of fraction
     */
    mpz_class get_num() const { return use_mpz_ ? num_mpz_ : num_int_; }

    /** @brief Get denominator
     * return denominator of fraction
     */
    mpz_class get_den() const { return use_mpz_ ? den_mpz_ : den_int_; }

    /** @brief Set numerator and denominator. Common integer type
     * @param[in] _num integer fraction numerator
     * @param[in] _den integer fraction denominator
     */
    void set_num_den(FRACTION_INT _num, FRACTION_INT _den);

    /** @brief Set numerator and denominator. Gmp integer type
     * @param[in] _num gmp integer fraction numerator
     * @param[in] _den gmp integer fraction denominator
     */
    void set_num_den(const mpz_class &num, const mpz_class &den);

    /** @brief Assignment operator
     * @param[in] assignment operand
     * return result fraction
     */
    fraction &operator=(const fraction &other);

    /** @brief Compound assignment operator +=
     * @param[in] assignment operand
     * return result fraction
     */
    fraction &operator+=(const fraction &f);

    /** @brief Compound assignment operator *=
     * @param[in] assignment operand
     * return result fraction
     */
    fraction &operator*=(const fraction &f);

    /** @brief Addition operator
     * @param[in] Addition operand
     * return result fraction
     */
    fraction operator+(const fraction &f) const;

    /** @brief Multiplication operator
     * @param[in] Multiplication operand
     * return result fraction
     */
    fraction operator*(const fraction &f) const;

    /** @brief Multiplication operator
     * @param[in] Multiplication operand 
     * return result fraction
     */
    fraction operator*(const int &f) const;

    /** @brief Division operator
     * @param[in] Division operand 
     * return result fraction
     */
    fraction operator/(const fraction &f) const;

    /** @brief Greater than operator
     * @param[in] operand 
     * return true if fraction greater than operand
     * return false if fraction not greater than operand
     */
    bool operator>(const fraction &f) const;

    /** @brief Less than operator
     * @param[in] operand 
     * return true if fraction less than operand
     * return false if fraction not less than operand
     */
    bool operator<(const fraction &f) const;

    /** @brief Greater than or equal to operator
     * @param[in] operand 
     * return true if fraction greater than or equal to operand
     * return false if fraction not greater than or equal to operand
     */
    bool operator>=(const fraction &f) const;

    /** @brief Less than or equal to operator
     * @param[in] operand 
     * return true if fraction less than or equal to operand
     * return false if fraction not less than or equal to operand
     */
    bool operator<=(const fraction &f) const;

    /** @brief Equal to operator
     * @param[in] operand 
     * return true if fraction equal to operand
     * return false if fraction not equal to operand
     */
    bool operator==(const fraction &f) const;

    /** @brief Operator: Not equal to 
     * @param[in] operand 
     * return false if fraction not equal to operand
     * return true if fraction equal to operand
     */
    bool operator!=(const fraction &f) const;

    /** @brief Operator: output stream
     * @param[in] stream
     * @param[in] operand
     */
    friend std::ostream& operator<<(std::ostream& os, const fraction &f);

    /** @brief base method for comparing operators 
     */
    bool ComparisonOperatorBase(const fraction &f,
                                std::function<bool(const mpz_class &f1, const mpz_class &f2)> comparator) const;

public:
    /** @brief Values for predicting multiplication result 
     */
    static FRACTION_INT fit_to_int_t_BJ_values[5];

    /** @brief Max value of addition operand, that will not cause int overflow. 
     */
    static FRACTION_INT ADD_OPERAND_MAX;

    /** @brief Zero fraction 0/1
     */
    static fraction zero_fraction;

    /** @brief One fraction 1/1
     */
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
