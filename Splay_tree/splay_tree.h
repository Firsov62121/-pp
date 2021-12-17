#include <iostream>
#include <string>
#pragma once

namespace MySplay{

template <typename T>
struct splay_node
{
    splay_node<T>* left;
    splay_node<T>* right;
    splay_node<T>* parent;
    T value;

    splay_node(T value, splay_node* parent = nullptr, 
        splay_node*left = nullptr, splay_node* right = nullptr) : 
        left(left), right(right), parent(parent), value(std::move(value)) {} 

    ~splay_node()
    {
        delete left;
        delete right;
    }

    void printS(char c, uint count, std::ostream& os) const
    {
        for(uint i = 0; i < count; ++i)
            os << c;
    }   

    void print(uint depth) const
    {
        std::cout << value << std::endl;
        if(left != nullptr)
        {
            printS('\t', depth, std::cout);
            std::cout << "left = ";
            left->print(depth + 1);
        }
        if(right != nullptr)
        {
            printS('\t', depth, std::cout);
            std::cout << "right = ";
            right->print(depth + 1);
        }
    }
};

template <typename T>
struct splay_tree
{
private:
    splay_node<T>* root;

    splay_node<T>* get_max_node() const
    {
        if(root == nullptr)
            return root;
        auto u = root;
        while(u->right != nullptr)
        {
            u = u->right;
        }
        return u;
    }

    void merge(splay_tree<T> &other) //other > this
    {
        auto u = get_max_node();
        splay(u);
        if(u == nullptr)
            root = other.root;
        else
            set_child(u, other.root, false);
        other.root = nullptr;
    }

    void set_child(splay_node<T>* parent, splay_node<T>* child, bool left = true)
    {
        if(parent == nullptr)
        {
            root = child;
            if(child != nullptr)
                child->parent = nullptr;
            return;
        }
        if(child == nullptr)
        {
            if(left)
                parent->left = nullptr;
            else
                parent->right = nullptr;
            return;
        }
        if(parent->value > child->value)
            parent->left = child;
        else
            parent->right = child;
        child->parent = parent;
    }

    splay_node<T>* find(const T& value) const
    {
        if(root == nullptr)
        {
            return nullptr;
        }
        auto tmp = root;
        while(true)
        {
            if(tmp->value == value)
                return tmp;
            if(tmp->value > value)
            {
                if(tmp->left == nullptr)
                    return tmp;
                tmp = tmp->left;
            }
            else
            {
                if(tmp->right == nullptr)
                    return tmp;
                tmp = tmp->right;
            }
        }
    }

    void splay(splay_node<T>* u)
    {
        if(u == nullptr)
            return;
        while(u != root)
        {
            splay_node<T>* A = u->parent;
            splay_node<T>* B = A->left == u ? u->right : u->left;
            if(A == root)
            {
                set_child(nullptr, u);
                set_child(A, B, A->left == u);
                set_child(u, A);
                continue;
            }
            splay_node<T>* C = A->parent;
            splay_node<T>* D = C->parent;
            bool s1 = A->left == u;
            bool s2 = C->left == A;
            if((s1 && s2) || (!s1 && !s2))
            {
                set_child(D, u);
                if(s1 && s2)
                {
                    set_child(A, u->right);
                    set_child(C, A->right);
                }
                else
                {
                    set_child(A, u->left, false);
                    set_child(C, A->left, false);
                }
                set_child(u, A);
                set_child(A, C);
            }
            if((s1 && !s2)||(!s1 && s2))
            {
                set_child(D, u);
                if(s1 && !s2)
                {
                    set_child(A, u->right);
                    set_child(C, u->left, false);
                }
                else
                {
                    set_child(A, u->left, false);
                    set_child(C, u->right);
                }
                set_child(u, C);
                set_child(u, A);
            }
        }
    }

public:
    splay_tree(splay_node<T>* root = nullptr) : root(root) 
    {
        if(root != nullptr)
            root->parent = nullptr;
    };

    void remove(const T& value)
    {
        splay_node<T>* u = find(value);
        if(u == nullptr)
            return;
        if(u->value == value)
        {
            splay(u);
            set_child(nullptr, u->left);
            auto st2 = splay_tree(u->right);
            u->right = nullptr;
            u->left = nullptr;
            delete u;
            merge(st2);
        }
    }

    bool contains(const T& value)
    {
        splay_node<T>* tmp = find(value);
        if(tmp == nullptr)
            return false;
        bool res = tmp->value == value;
        splay(tmp);
        return res;//splay, const, refs
    }

    void add(T value)
    {
        auto tmp = find(value);
        if(tmp == nullptr)
        {
            root = new splay_node<T>(value);
            return;
        }
        splay_node<T>* u = tmp;
        if(tmp->value != value)
        {
            u = new splay_node<T>(value);
            set_child(tmp, u);
        }
        splay(u);
    }

    ~splay_tree()
    {
        delete root;
    }

    void print() const
    {
        if(root != nullptr)
            root->print(0);
    }
};
}