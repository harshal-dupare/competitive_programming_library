

#include <vector>
#include <iostream>

namespace linalg
{
    using namespace linalg;
    // @tparam `T` T() must initilize it to zero element of T
    // @tparam `IS_SQUARE` set true if you want to enforce square matrix only
    template <typename T, typename I = int, bool IS_SQUARE = false>
    class matrix
    {
    public:
        typedef matrix<T, I, IS_SQUARE> mat;
        std::vector<std::vector<T>> a;
        I n, m;
        matrix(I _n, I _m)
        {
            if (IS_SQUARE)
                assert(n == m);
            this->n = _n;
            this->m = _m;
            a.assign(_n, std::vector<T>(_m, T()));
        }
        matrix(I n)
        {
            this->n = n;
            a.assign(n, std::vector<T>(n, T()));
        }
        matrix(const std::vector<std::vector<T>> &_a)
        {
            a = _a;
            n = (I)_a.size();
            m = (I)_a[0].size();
            if (IS_SQUARE)
                assert(n == m);
        }
        matrix(const mat &_m)
        {
            a = m.a;
            n = m.n;
            m = m.m;
            if (IS_SQUARE)
                assert(n == m);
        }

        mat operator-(const mat &a)
        {
            mat temp(a);
            for (I i = 0; i < a.n; i++)
            {
                for (I j = 0; j < a.m; j++)
                {
                    temp.a[i][j] = -a.a[i][j];
                }
            }
            return temp;
        }

        friend mat operator+(const mat &a, const mat &b)
        {
            assert(a.n == b.n);
            assert(a.m == b.m);
            mat temp(a);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] += b.a[i][j];
                }
            }
            return temp;
        }
        void operator+=(const mat &b)
        {
            *this = b + (*this);
        }

        friend mat operator-(const mat &a, const mat &b)
        {
            assert(a.n == b.n);
            assert(a.m == b.m);
            mat temp(a);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] -= b.a[i][j];
                }
            }
            return temp;
        }
        void operator-=(const mat &b)
        {
            *this = (*this) - b;
        }

        friend mat operator*(const mat &a, const mat &b)
        {
            assert(a.m == b.n);
            mat temp(a.n, b.m);
            for (I i = 0; i < temp.n; i++)
            {
                for (I j = 0; j < temp.m; j++)
                {
                    temp.a[i][j] = 0;
                    for (I k = 0; k < b.n; k++)
                    {
                        temp.a[i][j] += a.a[i][k] * b.a[k][j];
                    }
                }
            }
            return temp;
        }
        void operator*=(const mat &b)
        {
            *this = b * (*this);
        }

        friend mat operator/(const mat &a, const mat &b)
        {
            assert(a.m == b.m);
            mat temp(a.n, b.n);
            return temp;
        }
        void operator/=(const mat &b)
        {
            *this = (*this) / b;
        }

        // k = k*I_{n,m} assumptions
        friend mat operator+(const mat &a, const T &k)
        {
            mat temp(a);
            for (I i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] += k;
            }
            return temp;
        }
        friend mat operator+(const T &k, const mat &a)
        {
            mat temp(a);
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

        friend mat operator-(const mat &a, const T &k)
        {
            mat temp(a);
            for (I i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] -= k;
            }
            return temp;
        }
        friend mat operator-(const T &k, const mat &a)
        {
            mat temp(a);
            for (I i = 0; i < std::min(temp.n, temp.m); i++)
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

        friend mat operator*(const mat &a, const T &k)
        {
            mat temp;
            for (I i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] = temp.a[i][i] * k;
            }
            return temp;
        }
        friend mat operator*(const T &k, const mat &a)
        {
            mat temp;
            for (I i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] = k * temp.a[i][i];
            }
            return temp;
        }
        void operator*=(const T &k)
        {
            for (I i = 0; i < std::min(n, m); i++)
            {
                this->a[i][i] *= k;
            }
        }

        friend mat operator/(const mat &a, const T &k)
        {
            mat temp;
            for (I i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] /= k;
            }
            return temp;
        }
        friend mat operator/(const T &k, const mat &a)
        {
            mat temp;
            for (I i = 0; i < std::min(temp.n, temp.m); i++)
            {
                temp.a[i][i] = k / a.a[i][i];
            }
            return temp;
        }
        // O(n*m)
        void operator/=(const T &k)
        {
            for (I i = 0; i < n; i++)
            {
                for (I j = 0; j < m; j++)
                {
                    this->a[i][j] = T();
                }
            }

            for (I i = 0; i < std::min(n, m); i++)
            {
                this->a[i][i] = this->a[i][i] / k;
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const mat &m)
        {
            for (I i = 0; i < m.n; i++)
            {
                for (I j = 0; j < m.m; j++)
                {
                    os << m.a[i][j] << " ";
                }
                os << "\n";
            }
        }
    };

    // @tparam `T` floating point value or something which has `/=(T)` and `>0` defined
    template <typename T, typename I = int, bool IS_SQUARE = false>
    inline void row_normalize(matrix<T, I, IS_SQUARE> &a)
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
    template <typename T, typename I = int, bool IS_SQUARE = false>
    inline void col_normalize(matrix<T, I, IS_SQUARE> &a)
    {
        std::vector<T> sus(a.n);
        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
            {
                su[i] += a.a[i][j];
            }
        }

        for (I i = 0; i < a.n; i++)
        {
            for (I j = 0; j < a.m; j++)
            {
                a.a[i][j] /= su[i];
            }
        }
    }

    template <typename T, typename I = int, bool IS_SQUARE = false>
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

    template <typename T, typename I = int, bool IS_SQUARE = false>
    I rank(const matrix<T, I, IS_SQUARE> &a)
    {
        return I();
    }

    template <typename T, typename I = int, bool IS_SQUARE = false>
    matrix<T, I, IS_SQUARE> submatrix(const matrix<T, I, IS_SQUARE> &a, const std::vector<I> &r, const std::vector<I> &c, bool include_rc = true)
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
        matrix<T, I, IS_SQUARE> suba((I)nr.size(), (I)nc.size());
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

    template <typename T, typename I = int, bool IS_SQUARE = false>
    T trace(const matrix<T, I, IS_SQUARE> &a)
    {
        assert(a.n == a.m)

            T t = t();
        for (I i = 0; i < a.n; i++)
            t += a.a[i][i];
        return t;
    }

    template <typename T, typename I = int, bool IS_SQUARE = false>
    matrix<T, I, IS_SQUARE> adjoint(const matrix<T, I, IS_SQUARE> &a)
    {
        return matrix<T, I, IS_SQUARE>();
    }

    template <typename T, typename I = int, bool IS_SQUARE = false>
    matrix<T, I, IS_SQUARE> inverse(const matrix<T, I, IS_SQUARE> &a)
    {
        return matrix<T, I, IS_SQUARE>();
    }

    template <typename T, typename I = int, bool IS_SQUARE = false>
    T det(const matrix<T, I, IS_SQUARE> &a)
    {
        return T();
    }

    template <typename T, typename I = int, bool IS_SQUARE = false>
    matrix<T, I, IS_SQUARE> eigenvalues(const matrix<T, I, IS_SQUARE> &a)
    {
        return matrix<T, I, IS_SQUARE>();
    }

    template <typename T, typename I = int, bool IS_SQUARE = false>
    matrix<T, I, IS_SQUARE> eigenvectors(const matrix<T, I, IS_SQUARE> &a)
    {
        return matrix<T, I, IS_SQUARE>();
    }

    // transpose
}
