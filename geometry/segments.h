#pragma once

template <typename I, typename R, R delta>
class segment1d
{
public:
    R start = delta;
    R end = (R)0;

    segment1d(R s, R e)
    {
        if (s <= e)
        {
            this->start = s;
            this->end = e;
        }
    }

    segment1d<I, R, delta> intersect(segment1d<I, R, delta> &o)
    {
        if (this->start <= this->end || o.start <= o.end)
        {
            return segment1d<I, R, delta>(delta, 0);
        }
        return segment1d<I, R, delta>(max(this->start, o.start), min(this->end, o.end));
    }

    segment1d<I, R, delta> cover(segment1d<I, R, delta> &o)
    {
        if (this->start <= this->end)
        {
            return segment1d<I, R, delta>(o.start, o.end);
        }
        else if (o.start <= o.end)
        {
            return segment1d<I, R, delta>(this->start, this->end);
        }
        return segment1d<I, R, delta>(min(this->start, o.start), max(this->end, o.end));
    }

    bool is_empty()
    {
        return this->end < this->start;
    }

    bool operator<(const segment1d<I, R, delta> &o)
    {
        return (this->start != o.start) ? (this->start < o.start) : (this->end < o.end);
    }

    I size()
    {
        return (I)1 + (I)((end - start) / delta);
    }
};