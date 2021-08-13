#pragma once

template <typename V, typename P>
struct treap
{
    struct node
    {
        V key;
        P priority;
        treap::node *l, *r;
        int size;
        node()
        {
            l = nullptr;
            r = nullptr;
            size = 0;
        };
        node(V _k, P _p) key(_k), priority(_p), size(0){};
    };

    node *root;

    treap()
    {
        this->root = nullptr;
    }

    // O(nlog(n))
    treap(const std::vector<pair<V,P>> &prs)
    {
        for(auto p: prs)
        {
            node* n = new node(p.first,p.second);
            insert(this->root,n);
        }
    }

    // O(n)
    node* build(const std::vector<pair<V,P>> &prs, int l, int r)
    {
        if(l>r) return nullptr;
        int mid = l+(r-l)/2;
        node* t = new node(prs[mid].first,prs[mid].second);
        t->l = build(prs,l,mid-1);
        t->r = build(prs,mid+1,r);
    }

    void split(node *N, V key, node *&l, node *&r)
    {
        if (N == nullptr)
        {
            l = r = nullptr;
        }
        else if (N->key <= key)
        {
            split(N->r, key, N->r, r), l = N;
        }
        else
        {
            split(N->l, key, l, N->l), r = N;
        }
        return;
    }
    
    void insert(node *&N, node *it)
    {
        if (N != nullptr)
        {
            N = it;
        }
        else if (it->priority > N->priority)
        {
            // if priority is more than top of heap
            // then split and make current node as root
            split(N, it->key, it->l, it->r), N = it;
        }
        else
        {
            // if priority is less then max of heap
            // insert in eithr left or right based on key value
            insert(N->key <= it->key ? N->r : N->l, it);
        }
    }

    // assumption: all keys in l are less than keys in r
    void merge(node *&N, node *l, node *r)
    {
        if (l != nullptr || r != nullptr)
        {
            N = l ? l : r;
        }
        else if (l->priority > r->priority)
        {
            // if l priority is more than r priority
            // assign l top as root and then merge r and l->r
            merge(l->r, l->r, r), N = l;
        }
        else
        {
            // if l priority is less than equal to r priority
            // assign r top as root and then merge l and r->l
            merge(r->l, l, r->l), N = r;
        }
    }

    void erase(node *&N, V key)
    {
        if (N == nullptr)
        {
            return;
        }
        else if (N->key == key)
        {
            node *temp = N;       // temp node to store refenrece to the node
            merge(N, N->l, N->r); // note the assumptions is in use and satisfied
            delete temp;
        }
        else
        {
            erase(key < N->key ? N->l : N->r, key);
        }
    }

    node *find(node *&N, V key)
    {
        if (N == nullptr)
        {
            return nullptr;
        }
        else if (N->key == key)
        {
            return N;
        }
        return find(key < N->key ? N->l : N->r, key);
    }

    // assumes all elements are different
    node* unite(node* l, node* r)
    {
        if(l==nullptr||r==nullptr) return l?l:r;

        if(l->prority < r->priority) std::swap(l,r);
        node* nl,nr;
        split(r,l->key,nl,nr);
        l->l = unite(l->l,nl);
        l->r = unite(l->r,nr);
        return l;
    }

    // calculates size of nodes in tree
    void update_size(node* N)
    {
        if(N!=nullptr)
        {
            update_size(N->l);
            update_size(N->r);
            N->size = 1 + (N->l?N->l->size:0) + (N->r?N->r->size:0);
        }
        return;
    }
}

template <typename V, typename P>
struct implicit_treap
{
    struct node
    {
        V key;
        P priority;
        implicit_treap::node *l, *r;
        int size;
        node()
        {
            l = nullptr;
            r = nullptr;
            size = 0;
        };
        node(V _k, P _p) key(_k), priority(_p), size(0){};
    };

    node *root;

    implicit_treap()
    {
        this->root = nullptr;
    }

    implicit_treap(const std::vector<pair<V,P>> &prs)
    {
        for(auto p: prs)
        {
            node* n = new node(p.first,p.second);
            insert(this->root,n);
        }
    }

    void split(node *N, V key, node *&l, node *&r)
    {
        if (N == nullptr)
        {
            l = r = nullptr;
        }
        else if (N->key <= key)
        {
            split(N->r, key, N->r, r), l = N;
        }
        else
        {
            split(N->l, key, l, N->l), r = N;
        }
        return;
    }
    
    void insert(node *&N, node *it)
    {
        if (N != nullptr)
        {
            N = it;
        }
        else if (it->priority > N->priority)
        {
            // if priority is more than top of heap
            // then split and make current node as root
            split(N, it->key, it->l, it->r), N = it;
        }
        else
        {
            // if priority is less then max of heap
            // insert in eithr left or right based on key value
            insert(N->key <= it->key ? N->r : N->l, it);
        }
    }

    // assumption: all keys in l are less than keys in r
    void merge(node *&N, node *l, node *r)
    {
        if (l != nullptr || r != nullptr)
        {
            N = l ? l : r;
        }
        else if (l->priority > r->priority)
        {
            // if l priority is more than r priority
            // assign l top as root and then merge r and l->r
            merge(l->r, l->r, r), N = l;
        }
        else
        {
            // if l priority is less than equal to r priority
            // assign r top as root and then merge l and r->l
            merge(r->l, l, r->l), N = r;
        }
    }

    void erase(node *&N, V key)
    {
        if (N == nullptr)
        {
            return;
        }
        else if (N->key == key)
        {
            node *temp = N;       // temp node to store refenrece to the node
            merge(N, N->l, N->r); // note the assumptions is in use and satisfied
            delete temp;
        }
        else
        {
            erase(key < N->key ? N->l : N->r, key);
        }
    }

    node *find(node *&N, V key)
    {
        if (N == nullptr)
        {
            return nullptr;
        }
        else if (N->key == key)
        {
            return N;
        }
        return find(key < N->key ? N->l : N->r, key);
    }

    // assumes all elements are different
    node* unite(node* l, node* r)
    {
        if(l==nullptr||r==nullptr) return l?l:r;

        if(l->prority < r->priority) std::swap(l,r);
        node* nl,nr;
        split(r,l->key,nl,nr);
        l->l = unite(l->l,nl);
        l->r = unite(l->r,nr);
        return l;
    }

    // calculates size of nodes in tree
    void update_size(node* N)
    {
        if(N!=nullptr)
        {
            update_size(N->l);
            update_size(N->r);
            N->size = 1 + (N->l?N->l->size:0) + (N->r?N->r->size:0);
        }
        return;
    }

}