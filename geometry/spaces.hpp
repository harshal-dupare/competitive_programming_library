#pragma once

#include <bits/stdc++.h>
#include "point.hpp"
#include "convex_hull.hpp"
#include "../algebra/linalg.hpp"

using namespace std;

// if dim = N-1 then its hyperplane
template <typename R, int N = 2>
class affine_space
{
public:
    int dim;
    point<R, N> point_on_plane;
    vector<point<R, N>> vec_in_plane;
    bool has_orthogonal_vecs;

    affine_space(const point<R, N> &_point_on_plane, const vector<point<R, N>> &_vec_in_plane, const bool &_has_orthogonal_vecs = false)
    {
        this->point_on_plane = _point_on_plane;
        this->vec_in_plane = _vec_in_plane;
        this->dim = (int)_vec_in_plane.size();
        this->has_orthogonal_vecs = _has_orthogonal_vecs;
    }

    affine_space(const vector<point<R, N>> &_vec_in_plane, const bool _make_orthogonal = false, const bool _unitize = false)
    {
        this->point_on_plane = _vec_in_plane[0];
        this->dim = (int)_vec_in_plane.size() - 1;
        for (int i = 1; i <= this->dim; i++)
        {
            this->vec_in_plane.push_back(_vec_in_plane[i] - _vec_in_plane[0]);
        }
        this->has_orthogonal_vecs = _make_orthogonal;
        if (_make_orthogonal)
        {
            this->orthogonalize(_unitize);
        }
    }

    void orthogonalize(bool _unitize = false)
    {
        this->has_orthogonal_vecs = true;
        std::vector<linalg::matrix<R, int>> u(dim);
        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < N; j++)
            {
                u[i].a[j][0] = this->vec_in_plane[i][j];
            }
        }

        linalg::gram_schmidt_process(u, _unitize);

        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < N; j++)
            {
                this->vec_in_plane[i][j] = u[i].a[j][0];
            }
        }
    }

    bool spans(const point<I, N> &p)
    {
        if (this->has_orthogonal_vecs)
        {
            point<I, N> tp;
            for (int i = 0; i < dim; i++)
            {
                R cordi = this->vec_in_plane[i].dot(p) / this->vec_in_plane[i].norm_p(2, false);
                tp += cordi * this->vec_in_plane[i];
            }

            return is_equal(tp, p);
        }
        else
        {
            linalg::matrix<R, int> adjm(N, dim + 1);
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < dim; j++)
                {
                    adjm.a[i][j] = this->vec_in_plane[j][i];
                }
                adjm.a[i][dim] = p[i];
            }
            return dim == linalg::rank(adjm);
        }
    }
};

// reference vectro is assumes to be at 0 index
template <typename R, int N = 2>
class convex_space
{
public:
    vector<point<R, N>> vecs;
    bool vecs_are_convex_hull;

    convex_space(const vector<point<R, N>> &_vecs, const _vecs_are_convex_hull = false)
    {
        this->vecs_are_convex_hull = _vecs_are_convex_hull;
        this->vecs = _vecs;
    }

    void sieve_convex_hull()
    {
        this->vecs_are_convex_hull = true;
    }

    vector<R> affine_coordinates(const point<I, N> &p,const bool &use_orthogonal=false, int _p_center = 0)
    {
        vector<R> cord;
        for (int i = 0; i < vecs.size(); i++)
        {
            cord.push_back(this->vecs[i].dot(p) / this->vecs[i].norm_p(2, false));
        }
        return cord;
    }

    bool is_in_space(const point<I, N> &p, const bool &use_orthogonal=false)
    {
        vector<R> cord = this->affine_coordinates(p,use_orthogonal);
        R net = 0;
        for(int i=0;i<cord.size();i++)
        {
            int sg = sign_of(cord[i]);
            if(sg==-1)
            {
                return false;
            }
            net+=cord[i];
        }
        int sg = sign_of(net);
        if(sg>0)
        {
            return false;
        }
        return true;
    }
};