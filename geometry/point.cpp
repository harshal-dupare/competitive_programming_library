#include <bits/stdc++.h>

using namespace std;

class point
{
public:
    double EPS = 1e-9;
    double x;
    double y;

    point(double x = 0, double y = 0)
    {
        this->x = x;
        this->y = y;
    }

    void set(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    // returns 1 if this comes before other -1 if other before this and else 0
    int before(const point &other)
    {
        if (abs(this->y - other.y) < EPS)
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

    void operator&=(const point &other)
    {
        this->x = other.x;
        this->y = other.y;
    }

    void operator+=(const point &other)
    {
        this->x += other.x;
        this->y += other.y;
    }

    void operator-=(const point &other)
    {
        this->x -= other.x;
        this->y -= other.y;
    }

    void operator*=(double f)
    {
        this->x *= f;
        this->y *= f;
    }

    void operator/=(double f)
    {
        this->x /= f;
        this->y /= f;
    }

    point operator+(const point &other, const point &other1)
    {
        return point(other1.x + other.x, other1.y + other.y);
    }

    point operator-(const point &other, const point &other1)
    {
        return point(other.x - other1.x, other.y - other1.y);
    }

    bool operator<=(const point &other)
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

    double abs(point origin = point(0.0, 0.0))
    {
        return sqrt((origin.x - this->x) * (origin.x - this->x) + (origin.y - this->y) * (origin.y - this->y));
    }

    double dot(point other)
    {
        return this->x * other.x + this->y * other.y;
    }

    double cross(point other)
    {
        return this->x * other.y - this->y * other.x;
    }
    // O(1) time
    // returns distance square of this point from point a
    double dist_square(point &a)
    {
        double d2 = (a.x - this->x) * (a.x - this->x) + (a.y - this->y) * (a.y - this->y);
        return d2;
    }

    // O(1) time
    // Distance from line ---p1----p2----
    double dist_line(point &p1, point &p2)
    {
        double delta = abs((p1.x - p2.x) * (this->y - p1.y) - (this->x - p1.x) * (p1.y - p2.y));
        return delta;
    }

    // O(1) time
    // clockwise
    int span_interior(point &last, point &next)
    {
        double v1x = this->x - last.x;
        double v1y = this->y - last.y;
        double v2x = next.x - this->x;
        double v2y = next.y - this->y;

        double cross_product = v1x * v2y - v1y * v2x;

        if (abs(cross_product) <= EPS)
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
    int in_segment(point &p1, point &p2)
    {
        double delta = (p1.x - p2.x) * (this->y - p1.y) - (this->x - p1.x) * (p1.y - p2.y);

        // not on line
        // OK(delta)
        if (abs(delta) > EPS)
        {
            return -1;
        }

        // if on line then need to check if inside the segment

        int sign_p1x, sign_p2y, sign_p2x, sign_p1y;
        double temp;
        temp = this->x - p1.x;
        if (abs(temp) <= EPS)
            sign_p1x = 0;
        else if (temp > 0)
            sign_p1x = 1;
        else
            sign_p1x = -1;

        temp = this->y - p1.y;
        if (abs(temp) <= EPS)
            sign_p1y = 0;
        else if (temp > 0)
            sign_p1y = 1;
        else
            sign_p1y = -1;

        temp = this->x - p2.x;
        if (abs(temp) <= EPS)
            sign_p2x = 0;
        else if (temp > 0)
            sign_p2x = 1;
        else
            sign_p2x = -1;

        temp = this->y - p2.y;
        if (abs(temp) <= EPS)
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
                // if point is in the segment
                side = 1;
            }
            else
            {
                // if point is not in the segment but on the line
                side = 0;
            }

            return side;
        }
        else if (!(sign_p1y == 0 || sign_p2y == 0))
        {
            int vote_y = sign_p1y * sign_p2y;
            if (vote_y == -1)
            {
                // if point is in the segment
                side = 1;
            }
            else
            {
                // if point is not in the segment but on the line
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
    int on_same_side(point &a, point &p1, point &p2)
    {
        /*
        line is formed by p1 and p2
        (p1x -p2x)(y-p1y) - (x-p1x)(p1y-p2y) = 0 if on line else > 0 or < 0 tells the side of line
        the function returns 1 if both on same side 0 if anyone on the line and -1 if both on different side
        */
        double delta_a = (p1.x - p2.x) * (a.y - p1.y) - (a.x - p1.x) * (p1.y - p2.y);
        double delta_this = (p1.x - p2.x) * (this->y - p1.y) - (this->x - p1.x) * (p1.y - p2.y);
        int sgn_a = 0, sgn_this = 0;
        if (abs(delta_a) <= EPS)
            sgn_a = 0;
        else if (delta_a > 0)
            sgn_a = 1;
        else
            sgn_a = -1;

        if (abs(delta_this) <= EPS)
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
    int in_triangle(point &a, point &b, point &c)
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

    void show()
    {
        cout << "(" << x << "," << y << ") ";
        return;
    }
};

int main()
{

    return 0;
}