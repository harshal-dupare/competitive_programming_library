#include <vector>

template<typename I>
class general_matrix_sequence
{
public:
    std::vector<I> a;
    I n;
    I m;
    I inMOD = (I)10000007;
    std::vector<std::vector<I>> matrix,matrixm;
    std::vector<I> base;
    bool computed;

    general_matrix_sequence(I n, std::vector<std::vector<I>> _matrix, I _m, std::vector<I> base)
    {
        this->n = n;
        this->m = _m;
        this->base = base;
        this->a = base;
        this->matrix = _matrix;
        this->computed = false;
    }

    // O(m^3*log(m))
    void compute_Am()
    {
        if(this->computed)
        {
            return;
        }
        I _m = this->m;
        this->matrixm.assign(this->m, std::vector<I>(this->m, 0));
        std::vector<std::vector<I>> tm = this->matrix,_matrix=this->matrix;
        for (I j = 0; j < _m; j++)
        {
            this->matrixm[j][j] = 1;
        }
        while(_m>0)
        {
            if(_m%2==1)
            {
                tm = this->matrixm;
                this->mm_mult(_matrix,tm,this->matrixm);
            }
            _m>>=1;
            tm = _matrix;
            this->mm_mult(tm,tm,_matrix);
        }

        this->computed=true;
    }

    // O(m^3)
    void mm_mult(std::vector<std::vector<I>> &a, std::vector<std::vector<I>> &b, std::vector<std::vector<I>> &prod)
    {
        prod.assign(a.size(),std::vector<I>(b[0].size()));
        for (I j = 0; j < a.size(); j++)
        {
            for (I k = 0; k < b[0].size(); k++)
            {
                prod[j][k] = 0;
                for (I l = 0; l < a[0].size(); l++)
                {
                    prod[j][k] = (prod[j][k] + (a[j][l] * b[l][k]) % this->inMOD) % this->inMOD;
                }
            }
        }
    }

    // O(log(i)*m^3) time
    I get_ith(I i)
    {
        if (i < this->m)
            return this->base[i];

        std::vector<std::vector<I>> power_matrix = this->matrix;

        // ans matrix is identity matrix at start
        std::vector<std::vector<I>> ans_matrix(this->m, std::vector<I>(this->m, 0));
        for (I j = 0; j < m; j++)
        {
            ans_matrix[j][j] = 1;
        }

        i = i - this->m + 1;

        std::vector<std::vector<I>> temp(this->m, std::vector<I>(this->m));
        while (i > 0)
        {
            if (i % 2 == 1)
            {
                // multiplty the matrix
                this->mm_mult(ans_matrix, power_matrix, temp);
                ans_matrix = temp;
            }

            this->mm_mult(power_matrix, power_matrix, temp);
            power_matrix = temp;

            i >>= 1;
        }

        I ans = 0;
        // A^(i-m+1)[0,...m-1] = [i-m+1,...,i]
        for (I j = 0; j < this->m; j++)
        {
            ans = (ans + (this->base[j] * ans_matrix[this->m-1][j]) % this->inMOD) % this->inMOD;
        }

        return ans;
    }

    // extend till a[k], O(m^3*log(m)+(k-a.size())*m)
    void extend(I k)
    {
        if(k<=a.size()-1)
        {
            return;
        }

        std::vector<I> ta(this->m);
        this->compute_Am();

        // A^m[i,....,i+m-1] = [i+m,....,i+2m-1]
        for(I i=a.size();i<k;i+=m)
        {
            for (I j = 0; j < this->m; j++)
            {
                ta[j] = a[a.size()+j-this->m];
            }

            for(I j=i;j<i+m;j++)
            {
                I ans =0;
                for(I t=0;t<this->m;t++)
                {
                    ans = (ans + (this->matrixm[j-i][t]*ta[t])%this->inMOD)%this->inMOD;
                }
                this->a.push_back(ans);
            }
        }

        return;
    }

};
