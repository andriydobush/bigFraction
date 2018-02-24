#include <algorithm>
#include "fraction.h"

FRACTION_INT fraction::fit_to_int_t_BJ_values[5] = {
        (FRACTION_INT) sqrt(sqrt(sqrt(FRACTION_INT_MAX))),
        (FRACTION_INT) sqrt(sqrt(FRACTION_INT_MAX)),
        (FRACTION_INT) sqrt(FRACTION_INT_MAX),
        FRACTION_INT_MAX / (FRACTION_INT) sqrt(sqrt(FRACTION_INT_MAX)),
        FRACTION_INT_MAX / (FRACTION_INT) sqrt(sqrt(sqrt(FRACTION_INT_MAX)))
};

FRACTION_INT fraction::ADD_OPERAND_MAX = FRACTION_INT_MAX / 10;

fraction fraction::zero_fraction(0,1);

fraction fraction::one_fraction(1,1);

FRACTION_INT fraction::gcf(FRACTION_INT a, FRACTION_INT b)
{
    if (b == 0)
    {
        return abs(a);
    }
    else
        return gcf(b, a % b);
    return 0;
}

void fraction::NormalizeMpzFrac()
{
    // handle cases involving 0
    if (den_mpz_ == 0 || num_mpz_ == 0)
    {
        num_mpz_ = 0;
        den_mpz_ = 1;
        return;
    }
    // put negative sign in numerator only
    if (den_mpz_ < 0)
    {
        num_mpz_ *= (-1);
        den_mpz_ *= (-1);
    }
    // factor out GCF from numerator and denominator
    mpz_class buf;
    mpz_gcd(buf.get_mpz_t(), num_mpz_.get_mpz_t(), den_mpz_.get_mpz_t());
    if (buf > 1)
    {
        num_mpz_ /= buf;
        den_mpz_ /= buf;
    }
    //If fits in int use int instead of mpz class
    if (num_mpz_ < FRACTION_INT_MAX && den_mpz_ < FRACTION_INT_MAX)
    {
        den_int_ = static_cast<FRACTION_INT>(den_mpz_.get_si());
        num_int_ = static_cast<FRACTION_INT>(num_mpz_.get_si());
        use_mpz_ = false;
    }
}

void fraction::NormalizeIntFrac()
{
    // handle cases involving 0
    if (den_int_ == 0 || num_int_ == 0)
    {
        num_int_ = 0;
        den_int_ = 1;
        return;
    }
    // put negative sign in numerator only
    if (den_int_ < 0)
    {
        num_int_ *= (-1);
        den_int_ *= (-1);
    }

    auto buf = gcf(num_int_, den_int_);
    // factor out GCF from numerator and denominator
    if (buf > 1)
    {
        num_int_ /= buf;
        den_int_ /= buf;
    }
}

void fraction::NormalizeThis()
{
    use_mpz_ ? NormalizeMpzFrac() : NormalizeIntFrac();
}

fraction fraction::NormalizeFRACTION_INT(FRACTION_INT num, FRACTION_INT den)
{
    // handle cases involving 0
    if (den == 0 || num == 0)
    {
        num = 0;
        den = 1;
    }
    // put negative sign in numerator only
    if (den < 0)
    {
        num *= (-1);
        den *= (-1);
    }

    // factor out GCF from numerator and denominator
    auto buf = gcf(num, den);
    if (buf > 1)
    {
        num /= buf;
        den /= buf;
    }
    return fraction(num, den);
}

fraction fraction::NormalizeMpz(const mpz_class &num_, const mpz_class &den_)
{
    // handle cases involving 0
    auto num = num_;
    auto den = den_;
    if (den == 0 || num == 0)
    {
        num = 0;
        den = 1;
    }
    // put negative sign in numerator only
    if (den < 0)
    {
        num *= (-1);
        den *= (-1);
    }
    mpz_class buf;
    mpz_gcd(buf.get_mpz_t(), num.get_mpz_t(), den.get_mpz_t());
    if (buf > 1)
    {
        num /= buf;
        den /= buf;
    }
    return fraction(num, den);
}


fraction &fraction::operator=(const fraction &other)
{
    num_int_ = other.num_int_;
    den_int_ = other.den_int_;

    num_mpz_ = other.num_mpz_;
    den_mpz_ = other.den_mpz_;
    use_mpz_ = other.use_mpz_;
    return *this;
}

fraction::fraction(FRACTION_INT n, FRACTION_INT d) : num_int_(n), den_int_(d), use_mpz_(false)
{
    this->NormalizeThis();
}

fraction::fraction(const mpz_class &n_mpz, const mpz_class &d_mpz)
{
    if (n_mpz < FRACTION_INT_MAX && d_mpz < FRACTION_INT_MAX)
    {
        den_int_ = static_cast<FRACTION_INT>(d_mpz.get_si());
        num_int_ = static_cast<FRACTION_INT>(n_mpz.get_si());
        use_mpz_ = false;
    }
    else
    {
        num_mpz_ = n_mpz;
        den_mpz_ = d_mpz;
        use_mpz_ = true;
    }
    this->NormalizeThis();
}

fraction::fraction(const std::string n, const std::string d)
{
    num_mpz_.set_str (n, 10);
    den_mpz_.set_str (d, 10);
    use_mpz_ = true;
    this->NormalizeThis();
}

fraction::fraction() : num_int_(0), den_int_(1), use_mpz_(false)
{
}

void fraction::printFract() const
{
    if (use_mpz_)
        std::cout << num_mpz_ << "/" << den_mpz_;
    else
        std::cout << num_int_ << "/" << den_int_;
}

fraction fraction::operator+(const fraction &f) const
{
    mpz_class n_mpz;
    mpz_class d_mpz;
    mpz_class mpz_buf_mul1;
    mpz_class mpz_buf_mul2;
    mpz_class mpz_buf_mul3;
    mpz_class mpz_op1;
    mpz_class mpz_op2;
    FRACTION_INT num_res_bj_int;
    FRACTION_INT den_res_bj_int;
    FRACTION_INT mul1_res = -1;
    FRACTION_INT mul2_res = -1;
    FRACTION_INT mul3_res = -1;
    if (!this->use_mpz_ && !f.use_mpz())
    {
        bool mul1_use_mpz = true;
        bool mul2_use_mpz = true;
        bool mul3_use_mpz = true;
        if (MulResFitsToFRACTION_INT(this->num_int_, f.den_int_))
        {
            mul1_res = this->num_int_ * f.den_int_;
            mul1_use_mpz = false;
        }
        if (MulResFitsToFRACTION_INT(f.num_int_, this->den_int_))
        {
            mul2_res = f.num_int_ * this->den_int_;
            mul2_use_mpz = false;
        }
        if (MulResFitsToFRACTION_INT(f.den_int_, this->den_int_))
        {
            mul3_res = this->den_int_ * f.den_int_;
            mul3_use_mpz = false;
        }
        if (!mul1_use_mpz && !mul2_use_mpz && !mul3_use_mpz)
        {
            if (mul1_res < ADD_OPERAND_MAX && mul2_res < ADD_OPERAND_MAX)
            {
                num_res_bj_int = mul1_res + mul2_res;
                den_res_bj_int = mul3_res;
                return fraction(num_res_bj_int, den_res_bj_int);
            }
            else
            {
                n_mpz = mul1_res + mul2_res;
                d_mpz = mul3_res;
                return fraction(n_mpz, d_mpz);
            }
        }
        else
        {
            if (mul1_use_mpz && !mul2_use_mpz && !mul3_use_mpz)
            {
                mpz_op1 = this->num_int_;
                mpz_op2 = f.num_int_;
                mpz_buf_mul1 = mpz_op1 * mpz_op2;
                n_mpz = mpz_buf_mul1 + mul2_res;
                d_mpz = mul3_res;
            }
            else if (mul1_use_mpz && mul2_use_mpz && !mul3_use_mpz)
            {
                mpz_op1 = this->num_int_;
                mpz_op2 = f.num_int_;
                mpz_buf_mul1 = mpz_op1 * mpz_op2;
                mpz_op1 = f.num_int_;
                mpz_op2 = this->den_int_;
                mpz_buf_mul2 = mpz_op1 * mpz_op2;
                n_mpz = mpz_buf_mul1 + mpz_buf_mul2;
                d_mpz = mul3_res;
            }
            else if (mul1_use_mpz && mul2_use_mpz && mul3_use_mpz)
            {
                mpz_op1 = this->num_int_;
                mpz_op2 = f.den_int_;
                mpz_buf_mul1 = mpz_op1 * mpz_op2;
                mpz_op1 = f.num_int_;
                mpz_op2 = this->den_int_;
                mpz_buf_mul2 = mpz_op1 * mpz_op2;
                mpz_op1 = this->den_int_;
                mpz_op2 = f.den_int_;
                mpz_buf_mul3 = mpz_op1 * mpz_op2;
                n_mpz = mpz_buf_mul1 + mpz_buf_mul2;
                d_mpz = mpz_buf_mul3;
            }
            else if (!mul1_use_mpz && mul2_use_mpz && mul3_use_mpz)
            {
                mpz_op1 = f.num_int_;
                mpz_op2 = this->den_int_;
                mpz_buf_mul2 = mpz_op1 * mpz_op2;
                mpz_op1 = this->den_int_;
                mpz_op2 = f.den_int_;
                mpz_buf_mul3 = mpz_op1 * mpz_op2;
                n_mpz = mul1_res + mpz_buf_mul2;
                d_mpz = mpz_buf_mul3;
            }
            else if (!mul1_use_mpz && !mul2_use_mpz && mul3_use_mpz)
            {
                mpz_op1 = this->den_int_;
                mpz_op2 = f.den_int_;
                mpz_buf_mul3 = mpz_op1 * mpz_op2;
                n_mpz = mul1_res + mul2_res;
                d_mpz = mpz_buf_mul3;
            }
            else if (!mul1_use_mpz && mul2_use_mpz && !mul3_use_mpz)
            {
                mpz_op1 = this->den_int_;
                mpz_op2 = f.num_int_;
                mpz_buf_mul2 = mpz_op1 * mpz_op2;
                n_mpz = mul1_res + mpz_buf_mul2;
                d_mpz = mul3_res;
            }
            else if (mul1_use_mpz && !mul2_use_mpz && mul3_use_mpz)
            {
                mpz_op1 = this->num_int_;
                mpz_op2 = f.den_int_;
                mpz_buf_mul1 = mpz_op1 * mpz_op2;
                mpz_op1 = this->den_int_;
                mpz_op2 = f.den_int_;
                mpz_buf_mul3 = mpz_op1 * mpz_op2;
                n_mpz = mpz_buf_mul1 + mul2_res;
                d_mpz = mpz_buf_mul3;
            }
            return fraction(n_mpz, d_mpz);
        }
    }
    if (!this->use_mpz_ && f.use_mpz_)
    {
        n_mpz = (this->num_int_ * f.den_mpz_) + (f.num_mpz_ * this->den_int_);
        d_mpz = this->den_int_ * f.den_mpz_;
        return fraction(n_mpz, d_mpz);
    }

    if (this->use_mpz_ && !f.use_mpz_)
    {
        mpz_class mul1, mul2, op_buf;
        op_buf = f.num_int_;
        mul1 = op_buf * this->den_mpz_;
        op_buf = f.den_int_;
        mul2 = this->num_mpz_ * op_buf;
        n_mpz = mul1 + mul2;
        d_mpz = den_mpz_ * f.den_int_;
        return fraction(n_mpz, d_mpz);
    }

    if (den_mpz_ == f.den_mpz_)
    {
        return fraction((this->num_mpz_ + f.num_mpz_), den_mpz_);
    }
    else
    {
        n_mpz = (this->num_mpz_ * f.den_mpz_) + (f.num_mpz_ * this->den_mpz_);
        d_mpz = den_mpz_ * f.den_mpz_;

        return fraction(n_mpz, d_mpz);
    }

}

fraction fraction::operator*(const fraction &f) const
{
    mpz_class n_mpz;
    mpz_class d_mpz;
    FRACTION_INT n_int = -1;
    FRACTION_INT d_int = -1;
    if (!this->use_mpz_ && !f.use_mpz())
    {
        bool res_n_use_mpz = true;
        if (MulResFitsToFRACTION_INT(this->num_int_, f.num_int_))
        {
            n_int = this->num_int_ * f.num_int_;
            res_n_use_mpz = false;
        }
        else
        {
            n_mpz = this->num_int_ * f.num_int_;
        }
        if (MulResFitsToFRACTION_INT(this->den_int_, f.den_int_))
        {
            d_int = this->den_int_ * f.den_int_;
            if (!res_n_use_mpz)
                return fraction(n_int, d_int);

            d_mpz = d_int;
        }
        else
        {
            d_mpz = static_cast<mpz_class>(this->den_int_) * static_cast<mpz_class>(f.den_int_);
            if (!res_n_use_mpz)
            {
                n_mpz = n_int;
            }

        }
    }
    else if (!use_mpz_ && f.use_mpz())
    {
        n_mpz = this->num_int_ * f.num_mpz_;
        d_mpz = this->den_int_ * f.den_mpz_;
    }
    else if (use_mpz_ && !f.use_mpz())
    {
        n_mpz = this->num_mpz_ * f.num_int_;
        d_mpz = this->den_mpz_ * f.den_int_;
    }
    else //if (use_mpz_ == true && f.use_mpz() == true)
    {
        n_mpz = this->num_mpz_ * f.num_mpz_;
        d_mpz = this->den_mpz_ * f.den_mpz_;

    }
    return fraction(n_mpz, d_mpz);
}

fraction fraction::operator*(const int &i) const
{
    fraction f (i, 1);
    return *this * f;
}

fraction fraction::operator/(const fraction &f) const
{
    return *this * f.InverseCopy();
}

bool fraction::operator>(const fraction &f) const
{
    return ComparisonOperatorBase(f, [](const mpz_class &f1, const mpz_class &f2) { return f1 > f2; });
}

bool fraction::operator<(const fraction &f) const
{
    return ComparisonOperatorBase(f, [](const mpz_class &f1, const mpz_class &f2) { return f1 < f2; });
}

bool fraction::operator<=(const fraction &f) const
{
    return ComparisonOperatorBase(f, [](const mpz_class &f1, const mpz_class &f2) { return f1 <= f2; });
}

bool fraction::operator>=(const fraction &f) const
{
    return ComparisonOperatorBase(f, [](const mpz_class &f1, const mpz_class &f2) { return f1 >= f2; });
}

//extra multiplying, but literally affect performance
bool fraction::operator==(const fraction &f) const
{
    return ComparisonOperatorBase(f, [](const mpz_class &f1, const mpz_class &f2) { return f1 == f2; });
}

bool fraction::ComparisonOperatorBase(const fraction &f,
                                      std::function<bool(const mpz_class &f1, const mpz_class &f2)> comparator) const
{
    mpz_class n = this->use_mpz_ ? this->num_mpz_ : this->num_int_;
    mpz_class d = this->use_mpz_ ? this->den_mpz_ : this->den_int_;

    mpz_class n_f = f.use_mpz_ ? f.num_mpz_ : f.num_int_;
    mpz_class d_f = f.use_mpz_ ? f.den_mpz_ : f.den_int_;

    return comparator(n * d_f, n_f * d);
}

bool fraction::operator!=(const fraction &f) const
{
    return !(*this == f);
}

bool fraction::MulResFitsToFRACTION_INT(FRACTION_INT op1, FRACTION_INT op2) const
{
    //make op1 always less than op2
    if (op1 > op2)
    {
        std::swap(op1, op2);
    }
    return (op1 < fraction::fit_to_int_t_BJ_values[2] && op2 < fraction::fit_to_int_t_BJ_values[2]) ||
           (op1 < fraction::fit_to_int_t_BJ_values[1] && op2 < fraction::fit_to_int_t_BJ_values[3]) ||
           (op1 < fraction::fit_to_int_t_BJ_values[0] && op2 < fraction::fit_to_int_t_BJ_values[4]);

}

void fraction::set_num_den(FRACTION_INT _num, FRACTION_INT _den)
{
    num_int_ = _num;
    den_int_ = _den;
    use_mpz_ = false;
    NormalizeIntFrac();
}

void fraction::set_num_den(const mpz_class &num, const mpz_class &den)
{
    num_mpz_ = num;
    den_mpz_ = den;
    use_mpz_ = true;
    NormalizeMpzFrac();
}


fraction fraction::InverseCopy() const
{
    auto this_copy = *this;
    std::swap(this_copy.num_mpz_, this_copy.den_mpz_);
    std::swap(this_copy.num_int_, this_copy.den_int_);
    return this_copy;
}

fraction &fraction::operator+=(const fraction &fraction)
{
    *this = *this + fraction;
    return *this;
}

fraction &fraction::operator*=(const fraction &f)
{
    *this = *this * f;
    return *this;
}
