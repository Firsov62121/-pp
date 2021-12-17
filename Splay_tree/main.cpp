#include <iostream>
#include "splay_tree.h"
#include <set>
#include <ctime>
#include <algorithm>
#include <list>
#include <utility>
#include <chrono>

namespace MySplay{

void test1() //first steps
{
    splay_tree<int> st;
    uint n;
    std::cout << "Введите число запросов:" << std::endl;
    std::cin >> n;
    std::cout << "Введите запросы:" << std::endl;
    for(uint i = 0; i < n; ++i)
    {
        char type_of_operation;
        std::cin >> type_of_operation;
        int value;
        std::cin >> value;
        switch (type_of_operation)
        {
        case 'a'://add
            st.add(value);
            break;
        case 's'://search
            std::cout << (st.contains(value) ? "exists" :
                "doesn't exist") << std::endl;
            break;
        case 'r'://remove
            st.remove(value);
            std::cout << "Tried" << std::endl;
        default:
            break;
        }
        st.print();
    }
}

int get_rand(int min = -100, int max = 100) //srand was used before
{ 
    if(max < min)
        std::swap(max, min);
    return min + rand() % (max - min + 1);
}

template<typename T>
void print_buf(std::list<std::pair<int, T>> buf)
{
    for(auto el : buf)
    {
        switch (el.first)
        {
        case 0:
            std::cout << "add " << el.second << std::endl;
            break;
        case 1:
            std::cout << "find " << el.second << std::endl;
        case 2:
            std::cout << "remove " << el.second << std::endl;
        default:
            break;
        }
    }
}

bool test2(uint n = 10, uint k = 10000, int min = -10, int max = 10) //correctness
{
    std::srand(std::time(nullptr));
    bool res = true;
    for(uint i = 0; i < n; ++i)
    {
        splay_tree<int> st;
        std::set<int> s;
        std::list<std::pair<int, int>> buffer;
        for(uint j = 0; j < k; ++j)
        {
            int op = get_rand(0, 3);
            int value = get_rand(min, max);
            buffer.push_back({op, value});
            switch (op)
            {
            case 0:
                st.add(value);
                s.insert(value);
                break;
            case 1:
            {
                bool res1 = s.find(value) != s.end();
                bool res2 = st.contains(value);
                if(res1 != res2)
                {
                    std::cout << "correct = " << res1 << 
                        ", our result = " << res2 << std::endl;
                    print_buf(buffer);
                    res = false;
                }
                break;
            }
            case 2:
                st.remove(value);
                s.erase(value);
                break;
            }
            if(!res)
                break;
        }
        if(!res)
            break;
        std::cout << "test " << i << std::endl;
    }
    return res;
}

ulong getTimeMillis()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

void test3(uint n = 4000000, int min = -10000, int max = 10000) //speed: adding / removing = 2
{
    splay_tree<int> st;
    std::set<int> s;
    std::list<std::pair<int, int>> buffer;
    for(uint i = 0; i < n; ++i)
        buffer.emplace_back(get_rand(0, 4), get_rand(min, max));
    ulong t1 = getTimeMillis();
    for(auto el : buffer)
    {
        switch (el.first)
        {
        case 0:
        case 1:
            s.insert(el.second);
            break;
        case 2:
            s.erase(el.second);
        case 3:
            s.find(el.second);
        default:
            break;
        }
    }
    t1 = getTimeMillis() - t1;
    s.clear();
    ulong t2 = getTimeMillis();
    for(auto& el : buffer)
    {
        switch (el.first)
        {
        case 0:
        case 1:
            st.add(el.second);
            break;
        case 2:
            st.remove(el.second);
        case 3:
            st.contains(el.second);
        default:
            break;
        }
    }
    t2 = getTimeMillis() - t2;
    std::cout << "ideal time = " << t1 << std::endl;
    std::cout << "my time = " << t2 << std::endl;
}

void test4(uint start = 100000, uint stop = 1000000, uint step = 100000)
{
    for(uint n = start; n <= stop; n += step)
    {
        std::cout << "n = " << n << std::endl;
        test3(n);
    }
}
}

int main()
{
    //std::cout << (test2() ? "Correct" : "Wrond") << std::endl;
    //test3();
    //test1();
    //test4();//1.4 faster then std::set
    MySplay::test4();
    return 0;
}