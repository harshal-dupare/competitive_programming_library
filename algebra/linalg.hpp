
// FIXME communication between differnet types of matrices
#include <vector>
#include <iostream>
#include <math.h>
#include "../utils/debug_out.hpp"

namespace linalg
{

    template <typename T, typename I, bool IS_SQUARE>
    class matrix;

    // FIXME generalize and test
    template <typename T>
    bool isZero(const T &a)
    {
        T eps = (T)1e-6;
        if (std::abs(a) <= eps)
            return true;

        return false;
    }

    // FIXME add extended inverse for non square matrix
    template <typename T, typename I, bool IS_SQUARE>
    linalg::matrix<T, I, IS_SQUARE> inverse(linalg::matrix<T, I, IS_SQUARE> a)
    {
        if (IS_SQUARE || a.n == a.m)
        {
            linalg::matrix<T, I, IS_SQUARE> inva;
            inva.diagonal(a.n, T(1));
            // std::vector<std::pair<I, I>> swaps;

            for (I i = 0; i < a.n; i++)
            {
                // bring max i'th col value in the i'th row
                I maxi = i;
                T maxt = (a.a[i][i] < T() ? -a.a[i][i] : a.a[i][i]);
                for (I j = i + 1; j < a.n; j++)
                {
                    if (maxt < a.a[j][i] || maxt < -a.a[j][i])
                    {
                        maxi = j;
                        maxt = (a.a[j][i] < T() ? -a.a[j][i] : a.a[j][i]);
                    }
                }
                a.row_swap(i, maxi);
                inva.row_swap(i, maxi);
                // swaps.emplace_back(i, maxi);
                // bring max i'th col value in the i'th row

                if (linalg::isZero<T>(maxt))
                {
                    std::cerr<<a<<std::endl;
                    assert(false && "matrix is not invertable");
                }
                T scale(1);
                scale /= a.a[i][i];
                a.row_scale(i, scale);
                inva.row_scale(i, scale);
                for (I j = 0; j < a.n; j++)
                {
                    if (j == i)
                        continue;
                    T jscale = a.a[j][i];
                    a.row_reduce(j, i, jscale);
                    inva.row_reduce(j, i, jscale);
                }

                // debug(a);
                // debug(inva);
                // debug(maxi);
                // debug(swaps);
            }
            // // apply the swaps in reverse to get the original order back
            // for (auto prs = swaps.rbegin(); prs != swaps.rend(); prs++)
            // {
            //     inva.row_swap(prs->first, prs->second);
            // }
            return inva;
        }
        else
        {
            return linalg::matrix<T, I, IS_SQUARE>();
        }
    }

    // ordering <,> is not defined for matrix
    // @tparam `T` T() must initilize it to zero element of T
    // @tparam `IS_SQUARE` set true if you want to enforce square matrix only
    template <typename T, typename I, bool IS_SQUARE>
    class matrix
    {
    public:
        std::vector<std::vector<T>> a;
        I n, m;
        matrix() : n(0), m(0) {}
        matrix(I _n, I _m)
        {
            if (IS_SQUARE)
                assert(_n == _m);
            this->n = _n;
            this->m = _m;
            a.assign(_n, std::vector<T>(_m, T()));
        }
        matrix(const std::vector<std::vector<T>> &_a)
        {
            a = _a;
            n = (I)_a.size();
            m = (I)_a[0].size();
            if (IS_SQUARE)
                assert(this->n == this->m);
        }
        matrix(const linalg::matrix<T, I, IS_SQUARE> &_m)
        {
            this->a = _m.a;
            this->n = _m.n;
            this->m = _m.m;
            if (IS_SQUARE)
                assert(this->n == this->m && "failed due to passing wrong size matrix");
        }
        void diagonal(const I _n, const T &k)
        {
            this->n = _n;
            this->m = _n;
            this->a.assign(_n, std::vector<T>(_n, T()));
            for (I i = 0; i < this->n; i++)
                this->a[i][i] = k;
        }
        void operator=(const std::vector<std::vector<T>> &_a)
        {
            a = _a;
            n = (I)_a.size();
            m = (I)_a[0].size();
            if (IS_SQUARE)
                assert(this->n == this->m);
        }
        void operator=(const linalg::matrix<T, I, IS_SQUARE> &_m)
        {
            this->a = _m.a;
            this->n = _m.n;
            this->m = _m.m;
            if (IS_SQUARE)
                assert(this->n == this->m);
        }

        template <typename NT, typename NI, bool NIS_SQUARE>
        friend linalg::matrix<NT, NI, NIS_SQUARE> operator-(const linalg::matrix<NT, NI, NIS_SQUARE> &a)
        {
            linalg::matrix<NT, NI, NIS_SQUARE> temp(a);
            for (NI i = 0; i < a.n; i++)
            {
                for (NI j = 0; j < a.m; j++)
                {
                    temp.a[i][j] = -temp.a[i][j];
                }
            }
            return temp;
        }

        linalg::matrix<T, I, IS_SQUARE> operator+(const linalg::matrix<T, I, IS_SQUARE> &b)
        {
            assert(this->n == b.n);
            assert(this->m == b.m);
            linalg::matrix<T, I, IS_SQUARE> temp(*this);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] += b.a[i][j];
                }
            }
            return temp;
        }
        void operator+=(const linalg::matrix<T, I, IS_SQUARE> &b)
        {
            assert(this->n == b.n);
            assert(this->m == b.m);
            for (I i = 0; i < b.n; i++)
            {
                for (I j = 0; j < b.m; j++)
                {
                    this->a[i][j] += b.a[i][j];
                }
            }
        }

        linalg::matrix<T, I, IS_SQUARE> operator-(const linalg::matrix<T, I, IS_SQUARE> &b)
        {
            assert(this->n == b.n);
            assert(this->m == b.m);
            linalg::matrix<T, I, IS_SQUARE> temp(*this);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] -= b.a[i][j];
                }
            }
            return temp;
        }
        void operator-=(const linalg::matrix<T, I, IS_SQUARE> &b)
        {
            assert(this->n == b.n);
            assert(this->m == b.m);
            for (I i = 0; i < b.n; i++)
            {
                for (I j = 0; j < b.m; j++)
                {
                    this->a[i][j] -= b.a[i][j];
                }
            }
        }

        linalg::matrix<T, I, IS_SQUARE> operator*(const linalg::matrix<T, I, IS_SQUARE> &b)
        {
            assert(this->m == b.n);
            linalg::matrix<T, I, IS_SQUARE> temp(this->n, b.m);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] = 0;
                    for (I k = 0; k < b.n; k++)
                    {
                        temp.a[i][j] += this->a[i][k] * b.a[k][j];
                    }
                }
            }
            return temp;
        }
        void operator*=(const linalg::matrix<T, I, IS_SQUARE> &b)
        {
            *this = (*this) * b;
        }

        linalg::matrix<T, I, IS_SQUARE> operator/(const linalg::matrix<T, I, IS_SQUARE> &b)
        {
            assert(this->m == b.m);
            linalg::matrix<T, I, IS_SQUARE> temp(this->n, b.n);
            temp *= linalg::inverse<T, I, IS_SQUARE>(b);
            return temp;
        }
        void operator/=(const linalg::matrix<T, I, IS_SQUARE> &b)
        {
            assert(this->m == b.m);
            *this = (*this) * linalg::inverse<T, I, IS_SQUARE>(b);
        }

        // k = k*I_{n,m} assumptions
        template <typename NT, typename NI, bool NIS_SQUARE>
        friend linalg::matrix<NT, NI, NIS_SQUARE> operator+(const linalg::matrix<NT, NI, NIS_SQUARE> &a, const NT &k)
        {
            linalg::matrix<NT, NI, NIS_SQUARE> temp(a);
            for (NI i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] += k;
            }
            return temp;
        }

        template <typename NT, typename NI, bool NIS_SQUARE>
        friend linalg::matrix<NT, NI, NIS_SQUARE> operator+(const NT &k, const linalg::matrix<NT, NI, NIS_SQUARE> &a)
        {
            linalg::matrix<NT, NI, NIS_SQUARE> temp(a);
            for (I i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] = k + temp.a[i][i];
            }
            return temp;
        }
        void operator+=(const T &k)
        {
            for (I i = 0; i < std::min(n, m); i++)
            {
                this->a[i][i] += k;
            }
        }

        template <typename NT, typename NI, bool NIS_SQUARE>
        friend linalg::matrix<NT, NI, NIS_SQUARE> operator-(const linalg::matrix<NT, NI, NIS_SQUARE> &a, const NT &k)
        {
            linalg::matrix<NT, NI, NIS_SQUARE> temp(a);
            for (NI i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] -= k;
            }
            return temp;
        }
        template <typename NT, typename NI, bool NIS_SQUARE>
        friend linalg::matrix<NT, NI, NIS_SQUARE> operator-(const NT &k, const linalg::matrix<NT, NI, NIS_SQUARE> &a)
        {
            linalg::matrix<NT, NI, NIS_SQUARE> temp(a);
            for (NI i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] = k - temp.a[i][i];
            }
            return temp;
        }
        void operator-=(const T &k)
        {
            for (I i = 0; i < std::min(n, m); i++)
            {
                this->a[i][i] -= k;
            }
        }

        template <typename NT, typename NI, bool NIS_SQUARE>
        friend linalg::matrix<NT, NI, NIS_SQUARE> operator*(const linalg::matrix<NT, NI, NIS_SQUARE> &a, const NT &k)
        {
            linalg::matrix<NT, NI, NIS_SQUARE> temp(a);
            for (NI i = 0; i < temp.n; i++)
            {
                for (NI j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] = temp.a[i][j] * k;
                }
            }
            return temp;
        }
        template <typename NT, typename NI, bool NIS_SQUARE>
        friend linalg::matrix<NT, NI, NIS_SQUARE> operator*(const NT &k, const linalg::matrix<NT, NI, NIS_SQUARE> &a)
        {
            linalg::matrix<NT, NI, NIS_SQUARE> temp(a);
            for (NI i = 0; i < temp.n; i++)
            {
                for (NI j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] = k * temp.a[i][j];
                }
            }
            return temp;
        }
        void operator*=(const T &k)
        {
            for (I i = 0; i < this->n; i++)
            {
                for (I j = 0; j < this->m; j++)
                {
                    this->a[i][j] = this->a[i][j] * k;
                }
            }
        }

        template <typename NT, typename NI, bool NIS_SQUARE>
        friend linalg::matrix<NT, NI, NIS_SQUARE> operator/(const linalg::matrix<NT, NI, NIS_SQUARE> &a, const NT &k)
        {
            linalg::matrix<NT, NI, NIS_SQUARE> temp(a);
            for (NI i = 0; i < temp.n; i++)
            {
                for (NI j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] = temp.a[i][j] / k;
                }
            }
            return temp;
        }
        template <typename NT, typename NI, bool NIS_SQUARE>
        friend linalg::matrix<NT, NI, NIS_SQUARE> operator/(const NT &k, const linalg::matrix<NT, NI, NIS_SQUARE> &a)
        {
            linalg::matrix<NT, NI, NIS_SQUARE> temp(a);
            for (NI i = 0; i < temp.n; i++)
            {
                for (NI j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] = k / temp.a[i][j];
                }
            }
            return temp;
        }
        void operator/=(const T &k)
        {
            for (I i = 0; i < this->n; i++)
            {
                for (I j = 0; j < this->m; j++)
                {
                    this->a[i][j] = this->a[i][j] / k;
                }
            }
        }

        bool operator==(const linalg::matrix<T, I, IS_SQUARE> &b)
        {
            if (this->n != b.n || this->m != b.m)
                return false;
            for (I i = 0; i < b.n; i++)
                for (I j = 0; j < b.m; j++)
                    if (this->a[i][j] != b.a[i][j])
                        return false;
            return true;
        }
        bool operator!=(const linalg::matrix<T, I, IS_SQUARE> &b)
        {
            if (this->n != b.n || this->m != b.m)
                return true;
            for (I i = 0; i < b.n; i++)
                for (I j = 0; j < b.m; j++)
                    if (this->a[i][j] != b.a[i][j])
                        return true;
            return false;
        }
        bool operator==(const T &k)
        {
            if (this->n != this->m)
                return false;
            for (I i = 0; i < this->n; i++)
                for (I j = 0; j < this->m; j++)
                {
                    if (this->a[i][j] != (i == j ? k : T()))
                        return false;
                }
            return true;
        }
        template <typename NT, typename NI, bool NIS_SQUARE>
        friend bool operator==(const NT &k, const linalg::matrix<NT, NI, NIS_SQUARE> &a)
        {
            if (a.n != a.m)
                return false;
            for (NI i = 0; i < a.n; i++)
                for (NI j = 0; j < a.m; j++)
                {
                    if ((i == j ? k : NT()) != a.a[i][j])
                        return false;
                }
            return true;
        }

        bool operator!=(const T &k)
        {
            if (a.n != a.m)
                return true;
            for (I i = 0; i < a.n; i++)
                for (I j = 0; j < a.m; j++)
                {
                    if (a.a[i][j] != (i == j ? k : T()))
                        return true;
                }
            return false;
        }
        template <typename NT, typename NI, bool NIS_SQUARE>
        friend bool operator!=(const NT &k, const linalg::matrix<NT, NI, NIS_SQUARE> &a)
        {
            if (a.n != a.m)
                return true;
            for (NI i = 0; i < a.n; i++)
                for (NI j = 0; j < a.m; j++)
                {
                    if ((i == j ? k : NT()) != a.a[i][j])
                        return true;
                }
            return false;
        }

        // linalg::matrix<T, I, IS_SQUARE>[i][:] -= k*linalg::matrix<T, I, IS_SQUARE>[j][:]
        void row_reduce(I i, I j, const T &k)
        {
            for (I t = 0; t < this->m; t++)
                this->a[i][t] -= k * this->a[j][t];
        }
        // mat[:][i] -= k*mat[:][j]
        void col_reduce(I i, I j, const T &k)
        {
            for (I t = 0; t < this->n; t++)
                this->a[t][i] -= k * this->a[t][j];
        }
        void row_scale(I i, const T &k)
        {
            for (I t = 0; t < this->m; t++)
                this->a[i][t] *= k;
        }
        void col_scale(I i, const T &k)
        {
            for (I t = 0; t < this->n; t++)
                this->a[t][i] *= k;
        }
        void row_swap(I i, I j)
        {
            if (i == j)
                return;
            std::swap(this->a[i], this->a[j]);
        }
        void col_swap(I i, I j)
        {
            if (i == j)
                return;
            for (I t = 0; t < this->n; t++)
                std::swap(this->a[t][i], this->a[t][j]);
        }

        template <typename NT, typename NI, bool NIS_SQUARE>
        friend std::ostream &operator<<(std::ostream &os, const linalg::matrix<NT, NI, NIS_SQUARE> &a)
        {
            os << "[";
            for (NI i = 0; i < a.n; i++)
            {
                os << "[";
                for (NI j = 0; j < a.m; j++)
                {
                    os << a.a[i][j];
                    if (j != a.m - 1)
                    {
                        os << ", ";
                    }
                }
                os << "]";
                if (i != a.n - 1)
                {
                    os << ", ";
                }
            }
            os << "]";
            return os;
        }
    };

    // @tparam `T` floating point value or something which has `/=(T)` and `>0` defined
    template <typename T, typename I, bool IS_SQUARE>
    inline void row_normalize(linalg::matrix<T, I, IS_SQUARE> &a)
    {
        for (I i = 0; i < a.n; i++)
        {
            T su = T();
            for (I j = 0; j < a.m; j++)
            {
                su += a.a[i][j];
            }
            for (I j = 0; j < a.m; j++)
            {
                a.a[i][j] /= su;
            }
        }
    }

    // @tparam `T` floating point value or something which has `/=(T)` and `>0` defined
    template <typename T, typename I, bool IS_SQUARE>
    inline void col_normalize(linalg::matrix<T, I, IS_SQUARE> &a)
    {
        std::vector<T> sus(a.m);
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
            {
                sus[j] += a.a[i][j];
            }
        }

        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
            {
                a.a[i][j] /= sus[j];
            }
        }
    }

    template <typename T, typename I>
    T pow(T a, I n)
    {
        T ta = 1;
        while (n > 0)
        {
            if (n & 1)
            {
                ta *= a;
            }
            n >>= 1;
            a *= a;
        }
        return ta;
    }

    template <typename T, typename I, bool IS_SQUARE>
    I rank(linalg::matrix<T, I, IS_SQUARE> a)
    {
        I rk = 0;
        for (I i = 0; i < std::min(a.n, a.m); i++)
        {
            // bring max i'th col value in the i'th row
            I maxi = i;
            T maxt = (a.a[i][i] < T() ? -a.a[i][i] : a.a[i][i]);
            for (I j = i + 1; j < a.n; j++)
            {
                if (maxt < a.a[j][i] || maxt < -a.a[j][i])
                {
                    maxi = j;
                    maxt = (a.a[j][i] < T() ? -a.a[j][i] : a.a[j][i]);
                }
            }
            a.row_swap(i, maxi);
            // bring max i'th col value in the i'th row

            // if det becomes zero
            if (linalg::isZero<T>(maxt))
                break;
            rk++;

            T scale(1);
            scale /= a.a[i][i];
            a.row_scale(i, scale);
            for (I j = i + 1; j < a.n; j++)
            {
                if (j == i)
                    continue;
                scale = a.a[j][i];
                a.row_reduce(j, i, scale);
            }
        }
        return rk;
    }

    template <typename T, typename I, bool IS_SQUARE>
    linalg::matrix<T, I, IS_SQUARE> submatrix(const linalg::matrix<T, I, IS_SQUARE> &a, const std::vector<I> &r, const std::vector<I> &c, bool include_rc = true)
    {
        std::vector<I> nr, nc;
        if (!include_rc)
        {
            std::vector<I> tnr = r, tnc = c;
            std::sort(tnr.begin(), tnr.end());
            std::sort(tnc.begin(), tnc.end());
            I id = 0;
            for (I i = 0; i < a.n; i++)
            {
                if (id == (I)tnr.size())
                {
                    nr.push_back(i);
                }
                else if (tnr[id] != i)
                {
                    nr.push_back(i);
                }
                else
                {
                    id++;
                }
            }
            id = 0;
            for (I i = 0; i < a.m; i++)
            {
                if (id == (I)tnc.size())
                {
                    nc.push_back(i);
                }
                else if (tnc[id] != i)
                {
                    nc.push_back(i);
                }
                else
                {
                    id++;
                }
            }
        }
        else
        {
            nr = r;
            nc = c;
        }
        linalg::matrix<T, I, IS_SQUARE> suba((I)nr.size(), (I)nc.size());
        I rid = 0, cid = 0;
        for (auto ri : nr)
        {
            cid = 0;
            for (auto ci : nc)
            {
                suba[rid][cid] = a[ri][ci];
                cid++;
            }
            rid++;
        }
        return suba;
    }

    template <typename T, typename I, bool IS_SQUARE>
    T trace(const linalg::matrix<T, I, IS_SQUARE> &a)
    {
        assert(a.n == a.m);
        T t = T();
        for (I i = 0; i < a.n; i++)
            t += a.a[i][i];
        return t;
    }

    template <typename T, typename I, bool IS_SQUARE>
    T det(linalg::matrix<T, I, IS_SQUARE> a)
    {
        if (IS_SQUARE || a.n == a.m)
        {
            T deta(1);
            for (I i = 0; i < a.n; i++)
            {
                // bring max i'th col value in the i'th row
                I maxi = 0;
                T maxt = (a.a[i][i] < T() ? -a.a[i][i] : a.a[i][i]);
                for (I j = i + 1; j < a.n; j++)
                {
                    if (maxt < a.a[j][i] || maxt < -a.a[j][i])
                    {
                        maxi = j;
                        maxt = (a.a[j][i] < T() ? -a.a[i][i] : a.a[j][i]);
                    }
                }
                a.row_swap(i, maxi);
                // bring max i'th col value in the i'th row

                // if det becomes zero
                if (linalg::isZero<T>(maxt))
                    return T();
                deta *= a.a[i][i];

                T scale(1);
                scale /= a.a[i][i];
                a.row_scale(i, scale);
                for (I j = i + 1; j < a.n; j++)
                {
                    if (j == i)
                        continue;
                    T jscale = a.a[j][i];
                    a.row_reduce(j, i, jscale);
                }
            }
        }
        else
        {
            return T();
        }
    }

    template <typename T, typename I, bool IS_SQUARE>
    linalg::matrix<T, I, IS_SQUARE> adjoint(const linalg::matrix<T, I, IS_SQUARE> &a)
    {
        return linalg::inverse<T, I, IS_SQUARE>(a) * linalg::det<T, I, IS_SQUARE>(a);
    }

    // FIXME: not-required : there is divide and conqure algo to reduce the cache misses
    template <typename T, typename I, bool IS_SQUARE>
    linalg::matrix<T, I, IS_SQUARE> transpose(const linalg::matrix<T, I, IS_SQUARE> &a)
    {
        linalg::matrix<T, I, IS_SQUARE> ta(a.m, a.n);
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
            {
                ta.a[j][i] = a.a[i][j];
            }
        }
        return ta;
    }

    // FIXME test
    // only column vectors
    template <typename T, typename I, bool IS_SQUARE>
    T inner_product(const linalg::matrix<T, I, IS_SQUARE> &a, const linalg::matrix<T, I, IS_SQUARE> &b)
    {
        assert(a.m == (I)1);
        assert(b.m == (I)1);
        assert(a.n == b.n);
        return (linalg::transpose<T, I, IS_SQUARE>(a) * b).a[0][0];
    }

    // FIXME test
    template <typename T, typename I, bool IS_SQUARE>
    void unitize(linalg::matrix<T, I, IS_SQUARE> &u)
    {
        assert(u.n == (I)1 || u.m == (I)1);

        T su = T();
        if (u.n == (I)1)
            for (I i = 0; i < u.m; i++)
                su += u.a[0][i] * u.a[0][i];
        else
            for (I i = 0; i < u.n; i++)
                su += u.a[i][0] * u.a[i][0];
        su = std::sqrt(su);
        if (u.n == (I)1)
            for (I i = 0; i < u.m; i++)
                u.a[0][i] /= su;
        else
            for (I i = 0; i < u.n; i++)
                u.a[i][0] /= su;
    }

    // FIXME test
    template <typename T, typename I, bool IS_SQUARE>
    void gram_schmidt_process(std::vector<linalg::matrix<T, I, IS_SQUARE>> &u)
    {
        for (I i = 0; i < (I)u.size(); i++)
        {
            linalg::matrix<T, I, IS_SQUARE> tp(u[i]);
            for (I j = 0; j < i; j++)
            {
                tp -= u[j] * linalg::inner_product<T, I, IS_SQUARE>(u[j], u[i]);
            }
            u[i] = tp;
            unitize<T, I, IS_SQUARE>(u[i]);
        }
    }

    // FIXME test
    template <typename T, typename I, bool IS_SQUARE>
    bool isdiagonal(const linalg::matrix<T, I, IS_SQUARE> &a)
    {
        if (a.n != a.m)
            return false;
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
            {
                if (i == j)
                    continue;
                if (!linalg::isZero<T>(a.a[i][j]))
                    return false;
            }
        }
        return true;
    }

    // FIXME test
    template <typename T, typename I, bool IS_SQUARE>
    std::pair<linalg::matrix<T, I, IS_SQUARE>, linalg::matrix<T, I, IS_SQUARE>> QR_factorization(const linalg::matrix<T, I, IS_SQUARE> &a)
    {
        assert(a.n == a.m);
        std::vector<linalg::matrix<T, I, false>> u(a.m, linalg::matrix<T, I, false>(a.n, (I)1));
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
                u[j].a[i][0] = a.a[i][j];
        }
        linalg::gram_schmidt_process<T, I, false>(u);
        std::pair<linalg::matrix<T, I, IS_SQUARE>, linalg::matrix<T, I, IS_SQUARE>> QR = {a, a};
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
                QR.first.a[i][j] = u[j].a[i][0];
        }
        QR.second = linalg::transpose<T, I, IS_SQUARE>(QR.first) * a;
        return QR;
    }

    // FIXME test
    template <typename T, typename I, bool IS_SQUARE>
    std::pair<linalg::matrix<T, I, IS_SQUARE>, linalg::matrix<T, I, IS_SQUARE>> eigenpairs_QR_algorithm(const linalg::matrix<T, I, IS_SQUARE> &a, I k_max = 100)
    {
        assert(a.n == a.m);
        bool converged = false;
        I k = 0;
        std::pair<linalg::matrix<T, I, IS_SQUARE>, linalg::matrix<T, I, IS_SQUARE>> QDk = {a, a};
        while ((!converged) && k < k_max)
        {
            QDk = linalg::QR_factorization<T, I, IS_SQUARE>(QDk.second);
            QDk.second = QDk.second * QDk.first;
            converged = linalg::isdiagonal<T, I, IS_SQUARE>(QDk.second);
            k++;
        }
        return QDk;
    }

    // FIXME other than QR algorithm
    template <typename T, typename I, bool IS_SQUARE>
    std::vector<T> eigenvalues(const linalg::matrix<T, I, IS_SQUARE> &a)
    {
        return std::vector<T>();
    }

    // FIXME other than QR algorithm
    template <typename T, typename I, bool IS_SQUARE>
    linalg::matrix<T, I, IS_SQUARE> eigenvectors(const linalg::matrix<T, I, IS_SQUARE> &a)
    {
        return linalg::matrix<T, I, IS_SQUARE>();
    }

}