
template <typename I>
class stable_matching
{
public:
    I n;
    vector<vector<I>> women;
    vector<vector<I>> men;
    vector<vector<I>> wpartner;
    vector<vector<I>> mpartner;
    
    // input preferences must be in reverse
    stable_matching(I n, vector<vector<I>> men, vector<vector<I>> &womenp)
    {
        this->n = n;
        this->men = men;
        this->women = vector<vector<I>>(n, vector<I>(n));
        for (I i = 0; i < n; i++)
        {
            for (I j = 0; j < n; j++)
            {
                this->women[i][womenp[i][j]] = j;
            }
            reverse(this->men[i].begin(), this->men[i].end());
        }
        this->wpartner = vector<vector<I>>(n, vector<I>(0));
        // ok("created")
    }

    void match()
    {
        vector<bool> pool(this->n, true);
        I inpool = this->n;
        while (inpool > 0)
        {
            // make all the proposals
            for (I man = 0; man < this->n; man++)
            {
                if (!pool[man])
                    continue;

                I best_women = this->men[man][this->men[man].size() - 1];
                this->men[man].pop_back();
                // propose the best women
                this->wpartner[best_women].push_back(man);
                pool[man]=false;
                inpool--;
            }

            for (I i = 0; i < this->n; i++)
            {
                if (this->wpartner[i].size() > 1)
                {
                    auto best_man = this->wpartner[i].begin();
                    for (auto man = this->wpartner[i].begin() + 1; man != this->wpartner[i].end(); man++)
                    {
                        if (this->women[i][(*man)] < this->women[i][(*best_man)])
                        {
                            pool[*best_man]= true;
                            inpool++;
                            best_man = man;
                        }
                        else
                        {
                            pool[*man]=true;
                            inpool++;
                        }
                    }
                    // this->wpartner[i].clear();
                    // this->wpartner[i].push_back((*best_man));
                    this->wpartner[i] = vector<I>(1,(*best_man));
                }
            }
            // ok("pool created")
        }
    }

    void show_matching()
    {
        for (I i = 0; i < this->n; i++)
        {
            cout << i << ": " << this->wpartner[i][0] << endl;
        }
    }
};