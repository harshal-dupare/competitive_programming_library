
template<typename I>
class newtons_formula
{
public:
    vector<I> a;
    vector<I> p;
    vector<I> e;
    I n;

    newtons_formula(I n)
    {
        this->n = n;
        this->p = vector<I>(this->n, 0);
        this->e = vector<I>(this->n, 0);
    }

    newtons_formula(vector<I> a)
    {
        this->a = a;
        this->n = a.size();
        this->p = vector<I>(this->n, 0);
        this->e = vector<I>(this->n, 0);
    }

    /*
    formula
    p[k] = a[0]^k+a[1]^k+...
    e[i]=a[0]*..*a[i]+a[1]*...*a[i+1] (sum of product of i numbers taken at a time)
    e[0]=1
    i*e[i] = e[i-1]p[1]-e[i-1]p[2]+...
    */
    // O( k*(n+k) ) time | O(n) space
    void compute(int k, I inMOD = 10000009)
    {
        vector<I> temp(n, 1);
        for (int j = 0; j < k; j++)
        {
            for (int i = 0; i < this->n; i++)
            {
                this->p[j] = (this->p[j] + temp[i]) % inMOD;
                temp[i] = (temp[i] * this->a[i]) % inMOD;
            }
        }

        for (int j = 0; j < k; j++)
        {
            for (int i = j - 1; i >= 0; i--)
            {
                I sgn = -1;
                if ((j - i) % 2 == 1)
                    sgn = 1;

                this->e[j] = (this->e[j] + inMOD + (sgn) * ((this->e[i] * this->p[j - i]) % inMOD) )% inMOD;
            }
            if(j==0) this->e[j] = 1;
            else
            {
                this->e[j]/=j;
            }
        }
    }
};
