#pragma once
#include <stdlib.h>
#include <memory>

// FIXME : add proper tests, check correctness and pointer and add delete and other methods
namespace rb_tree
{
    using namespace std;
    enum color_enums
    {
        RED_COLOR,
        BLACK_COLOR
    };
    enum child_type_enums
    {
        LEFT_CHILD,
        RIGHT_CHILD,
        NONE_CHILD
    };

    template <typename K, class D>
    class tree;

    template <typename K, class D>
    class node
    {
        K key;
        D data;
        color_enums color;
        shared_ptr<node<K, D>> left;
        shared_ptr<node<K, D>> right;
        shared_ptr<node<K, D>> parent;
        child_type_enums which;

        weak_ptr<tree<K, D>> t;
    };

    template <typename K, class D>
    class tree
    {
    public:
        shared_ptr<node<K, D>> root;
        tree()
        {
            this->root = nullptr;
            return;
        }

        template <typename K, class D>
        friend void l_rotate(weak_ptr<node<K, D>> x)
        {
            weak_ptr<node<K, D>> xp = x->parent;
            weak_ptr<node<K, D>> xrc = x->right;
            weak_ptr<node<K, D>> xrclc = xrc->left;

            if (xp != NULL)
            {
                if (x->which == child_type_enums::LEFT_CHILD)
                {
                    xp->left = xrc;
                    xrc->parent = xp;
                    xrc->which = child_type_enums::LEFT_CHILD;
                }
                if (x->which == child_type_enums::RIGHT_CHILD)
                {
                    xp->right = xrc;
                    xrc->parent = xp;
                    xrc->which = child_type_enums::RIGHT_CHILD;
                }
            }
            else
            {

                xrc->parent = NULL;
                xrc->which = NONE_CHILD;
                x->t->root = xrc;
                xrc->t = x->t;
                x->t = NULL;
            }

            x->parent = xrc;
            xrc->left = x;
            x->which = child_type_enums::LEFT_CHILD;

            if (xrclc != NULL)
            {

                xrclc->parent = x;
                x->right = xrclc;
                xrclc->which = child_type_enums::RIGHT_CHILD;
            }
            else
            {

                x->right = NULL;
            }

            return;
        }

        template <typename K, class D>
        friend void r_rotate(weak_ptr<node<K, D>> x)
        {

            weak_ptr<node<K, D>> xp = x->parent;
            weak_ptr<node<K, D>> xlc = x->left;
            weak_ptr<node<K, D>> xlcrc = xlc->right;

            if (xp != NULL)
            {
                if (x->which == child_type_enums::LEFT_CHILD)
                {
                    xp->left = xlc;
                    xlc->parent = xp;
                    xlc->which = child_type_enums::LEFT_CHILD;
                }
                if (x->which == child_type_enums::RIGHT_CHILD)
                {
                    xp->right = xlc;
                    xlc->parent = xp;
                    xlc->which = child_type_enums::RIGHT_CHILD;
                }
            }
            else
            {

                xlc->parent = NULL;
                xlc->which = NONE_CHILD;
                x->t->root = xlc;
                xlc->t = x->t;
                x->t = NULL;
            }

            x->parent = xlc;
            xlc->right = x;
            x->which = child_type_enums::RIGHT_CHILD;

            if (xlcrc != NULL)
            {

                xlcrc->parent = x;
                x->left = xlcrc;
                xlcrc->which = child_type_enums::LEFT_CHILD;
            }
            else
            {

                x->left = NULL;
            }

            return;
        }

        template <typename K, class D>
        friend void rb_fix(weak_ptr<node<K, D>> x)
        {

            if (x->which == NONE_CHILD)
            {
                x->color = color_enums::BLACK_COLOR;
                return;
            }

            weak_ptr<node<K, D>> xp = x->parent;

            if (xp->color == color_enums::BLACK_COLOR)
            {
                return;
            }
            if (xp->color == color_enums::RED_COLOR)
            {

                weak_ptr<node<K, D>> xg = xp->parent;
                weak_ptr<node<K, D>> xu = NULL;

                if (xp->which == child_type_enums::LEFT_CHILD)
                {
                    xu = xg->right;
                }
                if (xp->which == child_type_enums::RIGHT_CHILD)
                {
                    xu = xg->left;
                }

                if (xu != NULL)
                {
                    if (xu->color == color_enums::RED_COLOR)
                    {
                        xu->color = color_enums::BLACK_COLOR;
                        xp->color = color_enums::BLACK_COLOR;
                        xg->color = color_enums::RED_COLOR;
                        rb_fix(xg);
                        return;
                    }

                    if (xu->color == color_enums::BLACK_COLOR)
                    {

                        if (x->which == child_type_enums::LEFT_CHILD)
                        {

                            if (xp->which == child_type_enums::LEFT_CHILD)
                            {
                                r_rotate(xg);
                                xg->color = color_enums::RED_COLOR;
                                xp->color = color_enums::BLACK_COLOR;
                                return;
                            }
                            if (xp->which == child_type_enums::RIGHT_CHILD)
                            {
                                r_rotate(xp);
                                l_rotate(xg);
                                x->color = color_enums::BLACK_COLOR;
                                xg->color = color_enums::RED_COLOR;
                                return;
                            }
                        }
                        if (x->which == child_type_enums::RIGHT_CHILD)
                        {

                            if (xp->which == child_type_enums::LEFT_CHILD)
                            {
                                l_rotate(xp);
                                r_rotate(xg);
                                x->color = color_enums::BLACK_COLOR;
                                xg->color = color_enums::RED_COLOR;
                                return;
                            }
                            if (xp->which == child_type_enums::RIGHT_CHILD)
                            {
                                l_rotate(xg);
                                xg->color = color_enums::RED_COLOR;
                                xp->color = color_enums::BLACK_COLOR;
                                return;
                            }
                        }
                    }
                }
                else
                {

                    if (x->which == child_type_enums::LEFT_CHILD)
                    {

                        if (xp->which == child_type_enums::LEFT_CHILD)
                        {
                            r_rotate(xg);
                            xg->color = color_enums::RED_COLOR;
                            xp->color = color_enums::BLACK_COLOR;
                            return;
                        }
                        if (xp->which == child_type_enums::RIGHT_CHILD)
                        {
                            r_rotate(xp);
                            l_rotate(xg);
                            x->color = color_enums::BLACK_COLOR;
                            xg->color = color_enums::RED_COLOR;
                            return;
                        }
                    }
                    if (x->which == child_type_enums::RIGHT_CHILD)
                    {

                        if (xp->which == child_type_enums::LEFT_CHILD)
                        {
                            l_rotate(xp);
                            r_rotate(xg);
                            x->color = color_enums::BLACK_COLOR;
                            xg->color = color_enums::RED_COLOR;
                            return;
                        }
                        if (xp->which == child_type_enums::RIGHT_CHILD)
                        {
                            l_rotate(xg);
                            xg->color = color_enums::RED_COLOR;
                            xp->color = color_enums::BLACK_COLOR;
                            return;
                        }
                    }
                }
            }
        }

        template <typename K, class D>
        friend void rb_insert(weak_ptr<tree<K, D>> T, int x)
        {

            weak_ptr<node<K, D>> r;
            weak_ptr<node<K, D>> p;
            int c;
            r = T->root;

            if (T->root == NULL)
            {
                T->root = (node<K, D> *)malloc(sizeof(node<K, D>));
                weak_ptr<node<K, D>> Root;
                Root = T->root;
                Root->key = x;
                Root->right = NULL;
                Root->left = NULL;
                Root->color = color_enums::BLACK_COLOR;
                Root->parent = NULL;
                Root->which = NONE_CHILD;
                Root->t = T;
                return;
            }
            else
            {
                while (r != NULL)
                {
                    p = r;
                    if (r->key > x)
                    {
                        r = r->left;
                        c = -1;
                    }
                    else
                    {
                        r = r->right;
                        c = 1;
                    }
                }

                if (c == 1)
                {
                    p->right = (node<K, D> *)malloc(sizeof(node<K, D>));
                    r = p->right;
                }
                if (c == -1)
                {
                    p->left = (node<K, D> *)malloc(sizeof(node<K, D>));
                    r = p->left;
                }

                r->key = x;
                r->left = NULL;
                r->right = NULL;
                r->color = color_enums::RED_COLOR;
                r->parent = p;

                if (c == 1)
                {
                    r->which = child_type_enums::RIGHT_CHILD;
                }
                if (c == -1)
                {
                    r->which = child_type_enums::LEFT_CHILD;
                }
                r->t = NULL;

                rb_fix(r);
                return;
            }
        }
    };

    template <typename K, class D>
    void inorderwalk(weak_ptr<node<K, D>> r)
    {

        if (r != NULL)
        {
            inorderwalk(r->left);
            printf("(%d,%c)", r->key, r->color);
            inorderwalk(r->right);
            return;
        }
        else
        {
            return;
        }
    }

    template <typename K, class D>
    void postorderwalk(weak_ptr<node<K, D>> r)
    {

        if (r != NULL)
        {
            postorderwalk(r->left);
            postorderwalk(r->right);
            printf("(%d,%c)", r->key, r->color);
            return;
        }
        else
        {
            return;
        }
    }

    template <typename K, class D>
    void preorderwalk(weak_ptr<node<K, D>> r)
    {

        if (r != NULL)
        {
            printf("(%d,%c)", r->key, r->color);
            preorderwalk(r->left);
            preorderwalk(r->right);
            return;
        }
        else
        {
            return;
        }
    }

    template <typename K, class D>
    void printtree(weak_ptr<node<K, D>> r, int c)
    {

        if (r != NULL)
        {
            int i;
            printtree(r->right, c + 1);
            for (i = 0; i < 2 * c; i++)
            {
                printf(" ");
            }
            printf("%d %c", r->key, r->color);
            printf("\n");
            printtree(r->left, c + 1);
        }
        else
        {
            printf("\n");
            return;
        }
    }
}
