
// FIXME communication between differnet types of matrices
#include <vector>
#include <iostream>
#include <math.h>
#include "../utils/debug_out.hpp"

namespace linalg
{

    template <typename T, typename I>
    class matrix;

    // FIXME generalize and test
    template <typename T>
    bool isZero(const T &a)
    {
        T eps = (T)1e-7;
        if (a <= eps && a >= -eps)
            return true;

        return false;
    }

    template <typename T, typename I>
    bool isZeroMatrix(const matrix<T,I>& a)
    {
        for(I i=0;i<a.n;i++)
        {
            for(I j=0;j<a.m;j++)
            {
                if(!isZero(a.a[i][j]))
                {
                    return false;
                }
            }
        }

        return true;
    }

    template <typename T, typename I>
    void remove_precision_error(matrix<T,I>& a)
    {
        for(I i=0;i<a.n;i++)
        {
            for(I j=0;j<a.m;j++)
            {
                if(!isZero(a.a[i][j]))
                {
                    a.a[i][j] = (T)0;
                }
            }
        }
    }

    // FIXME add extended inverse for non square matrix
    template <typename T, typename I>
    linalg::matrix<T, I> inverse(linalg::matrix<T, I> a)
    {
        if (a.n == a.m)
        {
            linalg::matrix<T, I> inva;
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

                try
                {
                    if (linalg::isZero<T>(maxt))
                    {
                        throw std::string("\n\x1B[31mERROR\033[0m: Matrix is not invertable, Ignoring the column : ");
                    }
                }

                catch(const std::string& execption)
                {
                    std::cerr << execption << i <<std::endl;
                    continue;
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
            return linalg::matrix<T, I>();
        }
    }

    // ordering <,> is not defined for matrix
    // @tparam `T` T() must initilize it to zero element of T
    template <typename T, typename I>
    class matrix
    {
    public:
        std::vector<std::vector<T>> a;
        I n, m;
        matrix() : n(0), m(0) {}
        matrix(I _n, I _m, T fill = T())
        {
            this->n = _n;
            this->m = _m;
            a.assign(_n, std::vector<T>(_m, fill));
        }
        matrix(const std::vector<std::vector<T>> &_a)
        {
            a = _a;
            n = (I)_a.size();
            m = (I)_a[0].size();
        }
        matrix(const linalg::matrix<T, I> &_m)
        {
            this->a = _m.a;
            this->n = _m.n;
            this->m = _m.m;
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
        }
        void operator=(const linalg::matrix<T, I> &_m)
        {
            this->a = _m.a;
            this->n = _m.n;
            this->m = _m.m;
        }

        linalg::matrix<T, I> operator+(const linalg::matrix<T, I> &b)
        {
            assert(this->n == b.n);
            assert(this->m == b.m);
            linalg::matrix<T, I> temp(*this);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] += b.a[i][j];
                }
            }
            return temp;
        }
        void operator+=(const linalg::matrix<T, I> &b)
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

        linalg::matrix<T, I> operator-(const linalg::matrix<T, I> &b)
        {
            assert(this->n == b.n);
            assert(this->m == b.m);
            linalg::matrix<T, I> temp(*this);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] -= b.a[i][j];
                }
            }
            return temp;
        }
        void operator-=(const linalg::matrix<T, I> &b)
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

        linalg::matrix<T, I> operator*(const linalg::matrix<T, I> &b)
        {
            assert(this->m == b.n);
            linalg::matrix<T, I> temp(this->n, b.m);
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
        void operator*=(const linalg::matrix<T, I> &b)
        {
            *this = (*this) * b;
        }

        linalg::matrix<T, I> operator/(const linalg::matrix<T, I> &b)
        {
            assert(this->m == b.m);
            linalg::matrix<T, I> temp(this->n, b.n);
            temp *= linalg::inverse<T, I>(b);
            return temp;
        }
        void operator/=(const linalg::matrix<T, I> &b)
        {
            assert(this->m == b.m);
            *this = (*this) * linalg::inverse<T, I>(b);
        }

        // scalar operators
        // k = k*I_{n,m} assumptions
        friend linalg::matrix<T, I> operator+(const linalg::matrix<T, I> &a, const T &k)
        {
            linalg::matrix<T, I> temp(a);
            for (I i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] += k;
            }
            return temp;
        }
        friend linalg::matrix<T, I> operator+(const T &k, const linalg::matrix<T, I> &a)
        {
            linalg::matrix<T, I> temp(a);
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

        friend linalg::matrix<T, I> operator-(const linalg::matrix<T, I> &a, const T &k)
        {
            linalg::matrix<T, I> temp(a);
            for (I i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] -= k;
            }
            return temp;
        }
        friend linalg::matrix<T, I> operator-(const T &k, const linalg::matrix<T, I> &a)
        {
            linalg::matrix<T, I> temp(a);
            for (I i = 0; i < temp.n; i++)
            {
            for (I j = 0; j <  temp.m; j++)
            {
                temp.a[i][j] = (i==j?k:T(0)) - temp.a[i][j];
            }
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

        friend linalg::matrix<T, I> operator*(const linalg::matrix<T, I> &a, const T &k)
        {
            linalg::matrix<T, I> temp(a);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] = temp.a[i][j] * k;
                }
            }
            return temp;
        }
        friend linalg::matrix<T, I> operator*(const T &k, const linalg::matrix<T, I> &a)
        {
            linalg::matrix<T, I> temp(a);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
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

        friend linalg::matrix<T, I> operator/(const linalg::matrix<T, I> &a, const T &k)
        {
            linalg::matrix<T, I> temp(a);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] = temp.a[i][j] / k;
                }
            }
            return temp;
        }
        friend linalg::matrix<T, I> operator/(const T &k, const linalg::matrix<T, I> &a)
        {
            linalg::matrix<T, I> temp(a);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
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

        bool operator==(const linalg::matrix<T, I> &b)
        {
            if (this->n != b.n || this->m != b.m)
                return false;
            for (I i = 0; i < b.n; i++)
                for (I j = 0; j < b.m; j++)
                    if (this->a[i][j] != b.a[i][j])
                        return false;
            return true;
        }
        bool operator!=(const linalg::matrix<T, I> &b)
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
        friend bool operator==(const T &k, const linalg::matrix<T, I> &a)
        {
            if (a.n != a.m)
                return false;
            for (I i = 0; i < a.n; i++)
                for (I j = 0; j < a.m; j++)
                {
                    if ((i == j ? k : T()) != a.a[i][j])
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
        friend bool operator!=(const T &k, const linalg::matrix<T, I> &a)
        {
            if (a.n != a.m)
                return true;
            for (I i = 0; i < a.n; i++)
                for (I j = 0; j < a.m; j++)
                {
                    if ((i == j ? k : T()) != a.a[i][j])
                        return true;
                }
            return false;
        }

        /// this -= k * a
        void reduce(const T &k, const linalg::matrix<T, I> &a)
        {
            assert(a.n == this->n);
            assert(a.m == this->m);
            if (linalg::isZero(k))
            {
                return;
            }
            (*this) -= k * a;
        }
        // linalg::matrix<T, I>[i][:] -= k*linalg::matrix<T, I>[j][:]
        void row_reduce(I i, I j, const T &k)
        {
            if (linalg::isZero(k))
                return;
            for (I t = 0; t < this->m; t++)
                this->a[i][t] -= k * this->a[j][t];
        }
        // mat[:][i] -= k*mat[:][j]
        void col_reduce(I i, I j, const T &k)
        {
            if (linalg::isZero(k))
                return;
            for (I t = 0; t < this->n; t++)
                this->a[t][i] -= k * this->a[t][j];
        }
        void row_scale(I i, const T &k)
        {
            if (linalg::isZero(k))
            {
                for (I t = 0; t < this->m; t++)
                    this->a[i][t] = T();
                return;
            }
            for (I t = 0; t < this->m; t++)
                this->a[i][t] *= k;
        }
        void col_scale(I i, const T &k)
        {
            if (linalg::isZero(k))
            {
                for (I t = 0; t < this->n; t++)
                    this->a[t][0] = T();
                return;
            }
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

        friend std::ostream &operator<<(std::ostream &os, const linalg::matrix<T, I> &a)
        {
            os << "[";
            for (I i = 0; i < a.n; i++)
            {
                os << "[";
                for (I j = 0; j < a.m; j++)
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
    template <typename T, typename I>
    inline void row_normalize(linalg::matrix<T, I> &a)
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
    template <typename T, typename I>
    inline void col_normalize(linalg::matrix<T, I> &a)
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

    template <typename T, typename I>
    I rank(linalg::matrix<T, I> a)
    {
        I rk = 0;
        for (I i = 0; i < std::min(a.n, a.m); i++)
        {
            // bring max i'th col value in the rk'th row
            I maxi = rk;
            T maxt = (a.a[rk][i] < T() ? -a.a[rk][i] : a.a[rk][i]);
            for (I j = rk + 1; j < a.n; j++)
            {
                if (maxt < a.a[j][i] || maxt < -a.a[j][i])
                {
                    maxi = j;
                    maxt = (a.a[j][i] < T() ? -a.a[j][i] : a.a[j][i]);
                }
            }
            a.row_swap(rk, maxi);
            // bring max i'th col value in the i'th row

            // if non zero element is found then that col has a independent vector so rank++
            if (!linalg::isZero<T>(maxt))
            {
                T scale(1);
                scale /= a.a[rk][i];
                a.row_scale(rk, scale);
                for (I j = rk + 1; j < a.n; j++)
                {
                    scale = a.a[j][i];
                    a.row_reduce(j, i, scale);
                }
                rk++;
            }
        }
        return rk;
    }

    template <typename T, typename I>
    linalg::matrix<T, I> submatrix(const linalg::matrix<T, I> &a, const std::vector<I> &r, const std::vector<I> &c, bool include_r = true, bool include_c = true)
    {
        std::vector<I> nr, nc;
        if (!include_r)
        {
            std::vector<I> tnr = r;
            std::sort(tnr.begin(), tnr.end());
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
        }
        else
        {
            nr = r;
        }
        if (!include_c)
        {
            std::vector<I> tnc = c;
            std::sort(tnc.begin(), tnc.end());
            I id = 0;
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
            nc = c;
        }
        linalg::matrix<T, I> suba((I)nr.size(), (I)nc.size());
        I rid = 0, cid = 0;
        for (auto ri : nr)
        {
            cid = 0;
            for (auto ci : nc)
            {
                suba.a[rid][cid] = a.a[ri][ci];
                cid++;
            }
            rid++;
        }
        return suba;
    }

    template <typename T, typename I>
    T trace(const linalg::matrix<T, I> &a)
    {
        assert(a.n == a.m);
        T t = T();
        for (I i = 0; i < a.n; i++)
            t += a.a[i][i];
        return t;
    }

    template <typename T, typename I>
    T det(linalg::matrix<T, I> a)
    {
        if (a.n == a.m)
        {
            T deta(1);
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
                        maxt = (a.a[j][i] < T() ? -a.a[i][i] : a.a[j][i]);
                    }
                }
                a.row_swap(i, maxi);
                // bring max i'th col value in the i'th row
                /// mdebug(maxi,maxt);
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
                // debug(a);
            }
            return deta;
        }
        else
        {
            return T();
        }
    }

    template <typename T, typename I>
    linalg::matrix<T, I> adjoint(const linalg::matrix<T, I> &a)
    {
        return linalg::inverse<T, I>(a) * linalg::det<T, I>(a);
    }

    // FIXME: not-required : there is divide and conqure algo to reduce the cache misses
    template <typename T, typename I>
    linalg::matrix<T, I> transpose(const linalg::matrix<T, I> &a)
    {
        linalg::matrix<T, I> ta(a.m, a.n);
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
            {
                ta.a[j][i] = a.a[i][j];
            }
        }
        return ta;
    }

    // only column vectors
    template <typename T, typename I>
    T inner_product(const linalg::matrix<T, I> &a, const linalg::matrix<T, I> &b)
    {
        assert(a.m == (I)1);
        assert(b.m == (I)1);
        assert(a.n == b.n);
        return (linalg::transpose<T, I>(a) * b).a[0][0];
    }

    // only column vectors
    template <typename T, typename I>
    T norm_p(const linalg::matrix<T, I> &a, T p)
    {
        T nor = 0;
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
            {
                nor += std::pow(a[i][j], p);
            }
        }
        return std::pow(nor, (1 / p));
    }

    // FIXME test
    template <typename T, typename I>
    void unitize(linalg::matrix<T, I> &u)
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

    template <typename T, typename I>
    void gram_schmidt_process(std::vector<linalg::matrix<T, I>> &u,bool _unitize=false)
    {
        for (I i = 0; i < (I)u.size(); i++)
        {
            linalg::matrix<T, I> tp(u[i]);
            for (I j = 0; j < i; j++)
            {
                tp.reduce(linalg::inner_product<T, I>(u[j], u[i]), u[j]);
            }
            u[i] = tp;
            if(_unitize) unitize<T, I>(u[i]);
        }
    }

    template <typename T, typename I>
    bool isdiagonal(const linalg::matrix<T, I> &a)
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

    template <typename T, typename I>
    bool is_upper_triangular(const linalg::matrix<T, I> &a)
    {
        if (a.n != a.m)
            return false;
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
            {
                if (i <= j)
                    continue;
                if (!linalg::isZero<T>(a.a[i][j]))
                    return false;
            }
        }
        return true;
    }

    template <typename T, typename I>
    bool is_lower_triangular(const linalg::matrix<T, I> &a)
    {
        if (a.n != a.m)
            return false;
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
            {
                if (i >= j)
                    continue;
                if (!linalg::isZero<T>(a.a[i][j]))
                    return false;
            }
        }
        return true;
    }

    // FIXME test
    template <typename T, typename I>
    std::pair<linalg::matrix<T, I>, linalg::matrix<T, I>> QR_factorization(const linalg::matrix<T, I> &a)
    {
        assert(a.n == a.m);
        std::vector<linalg::matrix<T, I>> u(a.m, linalg::matrix<T, I>(a.n, (I)1));
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
                u[j].a[i][0] = a.a[i][j];
        }
        linalg::gram_schmidt_process<T, I>(u);
        std::pair<linalg::matrix<T, I>, linalg::matrix<T, I>> QR = {a, a};
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
                QR.first.a[i][j] = u[j].a[i][0];
        }
        QR.second = linalg::transpose<T, I>(QR.first) * a;
        return QR;
    }

    // FIXME test
    template <typename T, typename I>
    std::pair<linalg::matrix<T, I>, linalg::matrix<T, I>> eigenpairs_QR_algorithm(const linalg::matrix<T, I> &a, I k_max = 100)
    {
        assert(a.n == a.m);
        bool converged = false;
        I k = 0;
        std::pair<linalg::matrix<T, I>, linalg::matrix<T, I>> QDk = {a, a};
        while ((!converged) && k < k_max)
        {
            QDk = linalg::QR_factorization<T, I>(QDk.second);
            QDk.second = QDk.second * QDk.first;
            converged = linalg::isdiagonal<T, I>(QDk.second);
            k++;
        }
        return QDk;
    }

    // FIXME other than QR algorithm
    template <typename T, typename I>
    std::vector<T> eigenvalues(const linalg::matrix<T, I> &a)
    {
        return std::vector<T>();
    }

    // FIXME other than QR algorithm
    template <typename T, typename I>
    linalg::matrix<T, I> eigenvectors(const linalg::matrix<T, I> &a)
    {
        return linalg::matrix<T, I>();
    }

    template <typename T, typename I>
    void balancing_parlett_reinsch(linalg::matrix<T, I> &a, T radix_base = (T)2, T p_norm = (T)2, double confidence = 0.95, I max_itr = 100)
    {
        assert(a.n == a.m);
        I n = a.n;
        // set D = I
        linalg::matrix<T, I> D(n, 1);
        for (I i = 0; i < n; i++)
            D.a[i][0] = (T)1;

        bool converged = false;
        T ip_norm = T(1) / p_norm;
        while (!converged && max_itr > 0)
        {
            confidence = true;
            for (I i = 0; i < n; i++)
            {
                T c = 0, r = 0, s = 0, f = 1;
                for (I j = 0; j < n; j++)
                {
                    if (j == i)
                        continue;
                    r += std::pow(a.a[i][j], p_norm);
                    c += std::pow(a.a[j][i], p_norm);
                }

                s = c + r;
                c = std::pow(c, ip_norm);
                r = std::pow(r, ip_norm);
                while (c < r / radix_base)
                {
                    c *= radix_base;
                    f *= radix_base;
                    r /= radix_base;
                }

                while (c >= r * radix_base)
                {
                    c /= radix_base;
                    f /= radix_base;
                    r *= radix_base;
                }
                c = std::pow(c, p_norm);
                r = std::pow(r, p_norm);
                if (c + r < confidence * f)
                {
                    converged = false;
                    D.a[i][0] *= f;
                    for (I j = 0; j < n; j++)
                    {
                        if (j == i)
                            continue;
                        a.a[j][i] *= f;
                        a.a[i][j] /= f;
                    }
                }
            }
            max_itr--;
        }
    }

    template <typename T, typename I>
    std::pair<linalg::matrix<T, I>, linalg::matrix<T, I>> reduce_dim(linalg::matrix<T, I> &a, std::vector<I>& li_colids)
    {
        li_colids.clear();
        std::vector<I> nonzero_rids;
        I ct = 0;
        std::vector<linalg::matrix<T, I>> li_cols;
        for (I i = 0; ct < a.n && i < a.m; i++)
        {
            matrix<T,I> nvec(a.n,(I)1);
            for(I j=0;j<a.n;j++)
            {
                nvec.a[j][0] = a.a[j][i];
            }
            for(I j=0;j<(I)li_cols.size();j++)
            {
                T scale = ((T)1)/li_colids[j].a[nonzero_rids[j]][0];
                if(!isZero(nvec.a[nonzero_rids[j]][0])) nvec-=(nvec.a[nonzero_rids[j]][0])*(scale*li_cols[j]);
            }

            if(isZeroMatrix(nvec))
            {
                continue;
            }

            remove_precision_error(nvec);

            li_colids.push_back(i);
            li_cols.push_back(nvec);
            ct++;
            for(I j=0;j<nvec.n;j++)
            {
                if(!isZero(nvec.a[j][0]))
                {
                    nonzero_rids.push_back(j);
                    break;
                }
            }
        }

        assert(nonzero_rids.size()==li_cols.size());
        
        std::pair<linalg::matrix<T, I>, linalg::matrix<T, I>> AinvA;
        AinvA.first = linalg::matrix<T, I>(a.n,ct);

        for(I i=0;i<a.n;i++)
        {
            for(I j=0;j<ct;j++)
            {
                AinvA.first.a[i][j] = a.a[i][li_colids[j]];
            }
        }

        AinvA.second = inverse(AinvA.first);

        a=AinvA.second*a;

        return AinvA;
    }

    // FIXME LU decomposition
    // FIXME SVD -> psoudo inverse
}
