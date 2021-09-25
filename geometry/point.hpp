#pragma once

#include <bits/stdc++.h>

using namespace std;

double GEOM_EPS = 1e-5;

template <typename R>
class point2
{
public:
    R x;
    R y;

    point2(R x = 0, R y = 0)
    {
        this->x = x;
        this->y = y;
    }

    void set(R x, R y)
    {
        this->x = x;
        this->y = y;
    }

    // returns 1 if this comes before other -1 if other before this and else 0
    int before(const point2<R> &other)
    {
        if (abs(this->y - other.y) < GEOM_EPS)
        {
            int k = 0;
            if (this->x < other.x)
            {
                k = 1;
            }
            else
            {
                k = -1;
            }

            return k;
        }
        else if (this->y > other.y)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    void operator&=(const point2<R> &other)
    {
        this->x = other.x;
        this->y = other.y;
    }

    void operator+=(const point2<R> &other)
    {
        this->x += other.x;
        this->y += other.y;
    }

    void operator-=(const point2<R> &other)
    {
        this->x -= other.x;
        this->y -= other.y;
    }

    void operator*=(R f)
    {
        this->x *= f;
        this->y *= f;
    }

    void operator/=(R f)
    {
        this->x /= f;
        this->y /= f;
    }

    point2<R> operator+(const point2<R> &other)
    {
        return point2<R>(this->x + other.x, this->y + other.y);
    }

    point2<R> operator-(const point2<R> &other)
    {
        return point2<R>(this->x - other.x, this->y - other.y);
    }

    point2<R> operator*(R f)
    {
        return point2<R>(f * this->x, f * this->y);
    }

    point2<R> operator/(R f)
    {
        return point2<R>(this->x / f, this->y / f);
    }

    bool operator<=(const point2<R> &other)
    {
        // this->show();
        // other.show();
        if (this->before(other) == -1)
        {
            // OK("before\n");
            return false;
        }
        else
        {
            // OK("after\n");
            return true;
        }
    }

    R abs(point2<R> origin = point2<R>(0.0, 0.0))
    {
        return sqrt((origin.x - this->x) * (origin.x - this->x) + (origin.y - this->y) * (origin.y - this->y));
    }

    R dot(point2<R> other)
    {
        return this->x * other.x + this->y * other.y;
    }

    R cross(point2<R> other)
    {
        return this->x * other.y - this->y * other.x;
    }

    // O(1) time
    // returns distance square of this point2<R,GEOM_EPS> from point2<R,GEOM_EPS> a
    R dist_square(point2<R> &a)
    {
        R d2 = (a.x - this->x) * (a.x - this->x) + (a.y - this->y) * (a.y - this->y);
        return d2;
    }

    // O(1) time
    // Distance from line ---p1----p2----
    R dist_line(point2<R> &p1, point2<R> &p2)
    {
        R delta = abs((p1.x - p2.x) * (this->y - p1.y) - (this->x - p1.x) * (p1.y - p2.y));
        return delta;
    }

    // O(1) time
    // clockwise
    int span_interior(point2<R> &last, point2<R> &next)
    {
        R v1x = this->x - last.x;
        R v1y = this->y - last.y;
        R v2x = next.x - this->x;
        R v2y = next.y - this->y;

        R cross_product = v1x * v2y - v1y * v2x;

        if (abs(cross_product) <= GEOM_EPS)
            return 0; // i.e. if all points are on a line i.e. crossproduct is zero

        if (cross_product > 0.0)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    // O(1) time
    // returns 1 if in the segment , 0 if on the line contaning the segment, else -1
    int in_segment(point2<R> &p1, point2<R> &p2)
    {
        R delta = (p1.x - p2.x) * (this->y - p1.y) - (this->x - p1.x) * (p1.y - p2.y);

        // not on line
        // OK(delta)
        if (abs(delta) > GEOM_EPS)
        {
            return -1;
        }

        // if on line then need to check if inside the segment

        int sign_p1x, sign_p2y, sign_p2x, sign_p1y;
        R temp;
        temp = this->x - p1.x;
        if (abs(temp) <= GEOM_EPS)
            sign_p1x = 0;
        else if (temp > 0)
            sign_p1x = 1;
        else
            sign_p1x = -1;

        temp = this->y - p1.y;
        if (abs(temp) <= GEOM_EPS)
            sign_p1y = 0;
        else if (temp > 0)
            sign_p1y = 1;
        else
            sign_p1y = -1;

        temp = this->x - p2.x;
        if (abs(temp) <= GEOM_EPS)
            sign_p2x = 0;
        else if (temp > 0)
            sign_p2x = 1;
        else
            sign_p2x = -1;

        temp = this->y - p2.y;
        if (abs(temp) <= GEOM_EPS)
            sign_p2y = 0;
        else if (temp > 0)
            sign_p2y = 1;
        else
            sign_p2y = -1;

        int side;

        if (!(sign_p1x == 0 || sign_p2x == 0))
        {
            int vote_x = sign_p1x * sign_p2x;
            if (vote_x == -1)
            {
                // if point2<R,GEOM_EPS> is in the segment
                side = 1;
            }
            else
            {
                // if point2<R,GEOM_EPS> is not in the segment but on the line
                side = 0;
            }

            return side;
        }
        else if (!(sign_p1y == 0 || sign_p2y == 0))
        {
            int vote_y = sign_p1y * sign_p2y;
            if (vote_y == -1)
            {
                // if point2<R,GEOM_EPS> is in the segment
                side = 1;
            }
            else
            {
                // if point2<R,GEOM_EPS> is not in the segment but on the line
                side = 0;
            }
            return side;
        }
        else
        {
            side = 0;
        }

        return side;
    }

    // O(1) time
    // 1, if on same side
    // 0, if any of a or this on the line p1--p2
    // -1, if not on the same side
    int on_same_side(point2<R> &a, point2<R> &p1, point2<R> &p2)
    {
        /*
        line is formed by p1 and p2
        (p1x -p2x)(y-p1y) - (x-p1x)(p1y-p2y) = 0 if on line else > 0 or < 0 tells the side of line
        the function returns 1 if both on same side 0 if anyone on the line and -1 if both on different side
        */
        R delta_a = (p1.x - p2.x) * (a.y - p1.y) - (a.x - p1.x) * (p1.y - p2.y);
        R delta_this = (p1.x - p2.x) * (this->y - p1.y) - (this->x - p1.x) * (p1.y - p2.y);
        int sgn_a = 0, sgn_this = 0;
        if (abs(delta_a) <= GEOM_EPS)
            sgn_a = 0;
        else if (delta_a > 0)
            sgn_a = 1;
        else
            sgn_a = -1;

        if (abs(delta_this) <= GEOM_EPS)
            sgn_this = 0;
        else if (delta_this > 0)
            sgn_this = 1;
        else
            sgn_this = -1;

        if (sgn_a == 0 || sgn_this == 0)
            return 0;
        if (sgn_a == sgn_this)
            return 1;
        else
            return -1;
    }

    // O(1) time
    // -1, if not on the triangle
    // 0, if on the triangle ( segments of the triangle )
    // 1, in the triangle but not on it
    int in_triangle(point2<R> &a, point2<R> &b, point2<R> &c)
    {
        int abc, bca, cab;
        abc = this->on_same_side(a, b, c);
        bca = this->on_same_side(b, c, a);
        cab = this->on_same_side(c, a, b);
        int sign_bc = this->in_segment(b, c);
        int sign_ca = this->in_segment(c, a);
        int sign_ab = this->in_segment(a, b);

        // if all are 1 then its in the triangle
        if (abc == 1 && bca == 1 && cab == 1)
        {
            return 1;
        }

        // if on the other side of any line then its not in/on the triangle
        if ((abc == -1) || (bca == -1) || (cab == -1))
        {
            return -1;
        }

        // if on any of the lines then need to check if inside thesegment or not
        if (abc == 0)
        {
            if (sign_bc == 1)
            {
                // if in the segment bc
                return 0;
            }
            else
            {
                // on the line containg segment bc
                return -1;
            }
        }
        else if (bca == 0)
        {
            if (sign_ca == 1)
            {
                // if in the segment ca
                return 0;
            }
            else
            {
                // on the line containg segment ca
                return -1;
            }
        }
        else
        {
            if (sign_ab == 1)
            {
                // if in the segment ab
                return 0;
            }
            else
            {
                // on the line containg segment ab
                return -1;
            }
        }

        return 1;
    }

    friend ostream &operator<<(ostream &os, const point2<R> &n)
    {
        os << "(" << n.x << "," << n.y << ")";
        return os;
    }
};

template <typename R>
class point3
{
public:
    R x;
    R y;
    R z;

    point3(R x = 0, R y = 0, R z = 0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void set(R x, R y, R z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // returns 1 if this comes before other -1 if other before this and else 0
    int before(const point3<R> &other)
    {
        if (abs(this->z - other.z) < GEOM_EPS)
        {
            if (abs(this->y - other.y) < GEOM_EPS)
            {
                if (abs(this->x - other.x) < GEOM_EPS)
                {
                    return 0;
                }
                else if (this->x > other.x)
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
            else if (this->y > other.y)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        else if (this->z > other.z)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    bool iszero()
    {
        if (abs(this->x) <= GEOM_EPS && abs(this->y) <= GEOM_EPS && abs(this->z) <= GEOM_EPS)
        {
            return true;
        }

        return false;
    }

    void unitize()
    {
        R len = this->length();
        if (len <= sqrt((R)3.0) * GEOM_EPS)
        {
            this->x = 0.0;
            this->y = 0.0;
            this->z = 0.0;
        }
        else
        {
            R largest = max(abs(x), max(abs(y), abs(z)));
            this->x /= largest;
            this->y /= largest;
            this->z /= largest;

            this->x /= len;
            this->y /= len;
            this->z /= len;
        }
    }

    void operator&=(const point3<R> &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    void operator+=(const point3<R> &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
    }

    void operator-=(const point3<R> &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
    }

    void operator*=(R f)
    {
        this->x *= f;
        this->y *= f;
        this->z *= f;
    }

    point3<R> operator*(R f)
    {
        return point3<R>(f * this->x, f * this->y, f * this->z);
    }

    point3<R> operator/(R f)
    {
        return point3<R>(this->x / f, this->y / f, f * this->z / f);
    }

    friend point3<R> operator*(R f, const point3<R> &n)
    {
        return point3<R>(f * n.x, f * n.y, f * n.z);
    }

    friend point3<R> operator/(R f, const point3<R> &n)
    {
        return point3<R>(n.x / f, n.y / f, f * n.z / f);
    }

    void operator/=(R f)
    {
        this->x /= f;
        this->y /= f;
        this->z /= f;
    }

    point3<R> operator+(const point3<R> &other)
    {
        return point3<R>(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    point3<R> operator-(const point3<R> &other)
    {
        return point3<R>(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    bool operator<=(const point3<R> &other)
    {
        return (this->before(other) >= 0);
    }

    bool operator<(const point3<R> &other)
    {
        return (this->before(other) > 0);
    }

    bool operator>(const point3<R> &other)
    {
        return (this->before(other) < 0);
    }

    bool operator>=(const point3<R> &other)
    {
        return (this->before(other) <= 0);
    }

    bool operator==(const point3<R> &other)
    {
        return (this->before(other) == 0);
    }

    R length(point3<R> origin = point3<R>())
    {
        return sqrt((origin.x - this->x) * (origin.x - this->x) + (origin.y - this->y) * (origin.y - this->y) + (origin.z - this->z) * (origin.z - this->z));
    }

    R dot(point3<R> other)
    {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    // dot product operator
    R operator*(point3<R> other)
    {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    point3<R> cross(point3<R> &other)
    {
        return point3<R>(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x);
    }

    // crossproduct operator
    point3<R> operator^(point3<R> &other)
    {
        return point3<R>(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x);
    }

    // O(1) time
    // returns distance square of this point3<R,GEOM_EPS> from point3<R,GEOM_EPS> a
    R dist_square(point3<R> a = point3<R>())
    {
        return (a.x - this->x) * (a.x - this->x) + (a.y - this->y) * (a.y - this->y) + (a.z - this->z) * (a.z - this->z);
    }

    // O(N=3) time
    // projection on line ---p1----p2----
    point3<R> projection_on_line(point3<R> &p1, point3<R> &p2)
    {
        point3<R> norm = p2 - p1;
        // (p1+norm*t).norm=norm.this
        return p1 + (norm * ((this->dot(norm) - norm * p1) / norm.dist_square()));
    }

    // returns 1 if in the segment , 0 if on the line contaning the segment, else -1
    int in_segment(point3<R> &p1, point3<R> &p2)
    {
        int side;
        point3<R> norm = p2 - p1;
        R t = ((this->dot(norm) - norm * p1) / norm.dist_square());
        point3<R> proj = p1 + t * norm;

        if (proj == *this)
        {
            if ((t >= (R)0) && (t <= ((R)1)))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return -1;
        }
    }

    // returns 1 if one line
    int on_line(point3<R> &p1, point3<R> &p2)
    {
        if (p1 == (*this) || (p2 == (*this)))
        {
            return 1;
        }
        else
        {
            R l1 = this->length(p1);
            R l2 = this->length(p2);
            R l12 = p2.length(p1);
            if (abs(l1 + l2 + l12 - 2.0 * max(l1, max(l2, l12))) <= sqrt((R)3.0) * GEOM_EPS)
            {
                return 1;
            }
        }

        return 0;
    }

    // 0 if on the plain, -1 or 1 else depending of the side of the plain
    int on_plain(point3<R> &p1, point3<R> &p2, point3<R> &p3)
    {
        point3<R> v1, v2, v3;
        v1 = p1 - (*this);
        v2 = p2 - (*this);
        v3 = p3 - (*this);
        R volu = v1 * (v2 ^ v3);
        if (abs(volu) <= GEOM_EPS)
        {
            return 0;
        }
        else if (volu > (R)0.0)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    // 1 if one plain
    int in_triangle(point3<R> &a, point3<R> &b, point3<R> &c)
    {
        if (this->on_plain(a, b, c) != 0)
        {
            return -1;
        }
        R A = area(a, b, c);
        R h1 = ((*this) - this->projection_on_line(c, b)).length();
        R h2 = ((*this) - this->projection_on_line(a, c)).length();
        R h3 = ((*this) - this->projection_on_line(a, b)).length();

        R l1 = (c - b).length();
        R l2 = (a - c).length();
        R l3 = (a - b).length();

        R Ap = ((R)0.5) * (l1 * h1 + l2 * h2 + l3 * h3);
        if (abs(A - Ap) > GEOM_EPS)
        {
            return 0;
        }

        return 1;
    }

    friend ostream &operator<<(ostream &os, const point3<R> &n)
    {
        os << "(" << n.x << "," << n.y << "," << n.z << ")";
        return os;
    }

    friend R area(point3<R> &a, point3<R> &b, point3<R> &c)
    {
        point3<R> v1 = a - b;
        point3<R> v2 = c - b;
        point3<R> A = v1 ^ v2;
        return ((R)0.5) * A.length();
    }
};

template <typename R>
bool is_zero(const R &a) { return (a <= GEOM_EPS && a >= -GEOM_EPS); }

template <typename R>
bool sign_of(const R &a)
{
    int sg = 0;
    if (a <= GEOM_EPS)
        sg--;
    if (a >= -GEOM_EPS)
        sg++;
    return sg;
}

template <typename R, int N>
bool is_equal(const point<R, N> &p, const point<R, N> &q)
{
    for (int i = 0; i < N; i++)
    {
        if (!is_zero<R>(p[i] - tp[i]))
        {
            return false;
        }
    }
    return true;
}

template <typename R, int N = 2>
class point
{
public:
    R x[N];

    point() { memset(x, (R)0, sizeof(x)); }
    point(const vector<R> &_x)
    {
        for (int i = 0; i < N; i++)
            this->x[i] = _x[i];
    }
    point(const R _x[N])
    {
        for (int i = 0; i < N; i++)
            this->x[i] = _x[i];
    }
    point(const point<R, N> &_p)
    {
        for (int i = 0; i < N; i++)
            this->x[i] = _p.x[i];
    }

    // returns 1 if this comes before other -1 if other before this and else 0
    int before(const point<R, N> &other)
    {
        for (int i = 0; i < N; i++)
        {
            if (abs(this->x[i] - other.x[i]) < GEOM_EPS)
            {
                continue;
            }
            else if (this->x[i] > other.x[i])
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }

        return 0;
    }
    bool operator<=(const point<R, N> &other) { return (this->before(other) >= 0); }
    bool operator<(const point<R, N> &other) { return (this->before(other) > 0); }
    bool operator>(const point<R, N> &other) { return (this->before(other) < 0); }
    bool operator>=(const point<R, N> &other) { return (this->before(other) <= 0); }
    bool operator==(const point<R, N> &other) { return (this->before(other) == 0); }

    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    void operator+=(const U &f)
    {
        for (int i = 0; i < N; i++)
            this->x[i] += (R)f;
    }
    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    friend point<R, N> operator+(const U &f)
    {
        point<R, N> q;
        for (int i = 0; i < N; i++)
            q.x[i] = this->x[i] + (R)f;

        return q;
    }
    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    friend point<R, N> operator+(const U &f, const point<R, N> &p)
    {
        point<R, N> q;
        for (int i = 0; i < N; i++)
            q.x[i] = p.x[i] + (R)f;

        return q;
    }

    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    void operator-=(const U &f)
    {
        for (int i = 0; i < N; i++)
            this->x[i] -= (R)f;
    }
    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    friend point<R, N> operator-(const U &f)
    {
        point<R, N> q;
        for (int i = 0; i < N; i++)
            q.x[i] = this->x[i] - (R)f;

        return q;
    }
    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    friend point<R, N> operator-(const U &f, const point<R, N> &p)
    {
        point<R, N> q;
        for (int i = 0; i < N; i++)
            q.x[i] = (R)f - p.x[i];

        return q;
    }

    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    void operator*=(const U &f)
    {
        for (int i = 0; i < N; i++)
            this->x[i] *= (R)f;
    }
    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    friend point<R, N> operator*(const U &f)
    {
        point<R, N> q;
        for (int i = 0; i < N; i++)
            q.x[i] = this->x[i] * ((R)f);

        return q;
    }
    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    friend point<R, N> operator*(const U &f, const point<R, N> &p)
    {
        point<R, N> q;
        for (int i = 0; i < N; i++)
            q.x[i] = ((R)f) * p.x[i];

        return q;
    }

    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    void operator/=(const U &f)
    {
        for (int i = 0; i < N; i++)
            this->x[i] /= (R)f;
    }
    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    friend point<R, N> operator/(const U &f)
    {
        point<R, N> q;
        for (int i = 0; i < N; i++)
            q.x[i] = this->x[i] / ((R)f);

        return q;
    }
    template <class U, class = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    friend point<R, N> operator/(const U &f, const point<R, N> &p)
    {
        point<R, N> q;
        for (int i = 0; i < N; i++)
            q.x[i] = ((R)f) / p.x[i];

        return q;
    }

    void operator+=(const point<R, N> &other)
    {
        for (int i = 0; i < N; i++)
            this->x[i] += other.x[i];
    }
    point<R, N> operator+(const point<R, N> &other)
    {
        point<R, N> opt(this->x);
        opt += other;
        return opt;
    }

    void operator-=(const point<R, N> &other)
    {
        for (int i = 0; i < N; i++)
            this->x[i] -= other.x[i];
    }
    point<R, N> operator-(const point<R, N> &other)
    {
        point<R, N> opt(this->x);
        opt -= other;
        return opt;
    }

    R dot(const point<R, N> &other)
    {
        R dt = 0;
        for (int i = 0; i < N; i++)
        {
            dt += this->x[i] * other.x[i];
        }
        return dt;
    }
    R norm_p(R p, bool root = true) const
    {
        R nr = 0;
        for (int i = 0; i < N; i++)
        {
            nr += std::pow(this->x[i], p);
        }
        if (root)
        {
            p = (R)1 / p;
            nr = pow(nr, p);
        }
        return nr;
    }
    R dist_square(const point<R, N> &origin)
    {
        R dist = 0;
        for (int i = 0; i < N; i++)
        {
            dist += (this->x[i] - origin.x[i]) * (this->x[i] - origin.x[i]);
        }
        return dist;
    }

    friend ostream &operator<<(ostream &os, const point<R, N> &n)
    {
        os << "(";
        for (int i = 0; i < N - 1; i++)
        {
            os << n.x[i] << ", ";
        }
        os << n.x[N - 1] << ")";

        return os;
    }
};
