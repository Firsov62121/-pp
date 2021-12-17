#include <iostream>
#include <chrono>

#include "myTestFuncs.h"

bool test(size_t n, bool needCheck)
{
    std::vector<std::shared_ptr<node>> list(n);
    std::vector<size_t> links(n);
    for(size_t i = 0; i < n; ++i)
    {
        links[i] = std::rand() % n;
        list[i] = std::make_shared<node>((char)(std::rand() % 256));
        if(i > 0)
            list[i - 1]->next = list[i];
    }
    for(size_t i = 0; i < n; ++i)
        list[i]->other_node = list[links[i]];
    auto first2 = copyList(list[0]);
    auto first = list[0];
    bool res = true;
    if(!needCheck)
    {
        return true;
    }
    if(first2->getSize() != n)
    {
        res = false;
    }
    if(res)
    {
        std::vector<std::shared_ptr<node>> list2(n); //changed, was node**
        auto tmp = first2;
        for(size_t i = 0; i < n; ++i)
        {
            list2[i] = tmp;
            if(tmp->value != list[i]->value)
            {
                res = false;
                break;
            }
            tmp = tmp->next;
        }
        if(res)
        {
            for(size_t i = 0; i < n; ++i)
            {
                if(list2[i]->other_node.lock() != list2[links[i]])
                {
                    res = false;
                    break;
                }
            }
        }
    }
    if(!res)
    {
        for(size_t i = 0; i < n; ++i)
            std::cout << links[i] << " ";
        std::cout << std::endl;
    }
    return res;
}

void test2()
{
    std::cout << "Введите число тестов:";
    int n; 
    std::cin >> n;
    std::srand(time(nullptr));
    bool res = true;
    for(int i = 0; i < n; ++i)
    {
        if(!test(i + 1, true))
        {
            res = false;
            std::cout << "Test# " << i << " wrong!" << std::endl;
            break;
        }
    }
    if(res)
        std::cout << "All test comlited!" << std::endl;
}

void test3()
{
    auto list = read();
    printList(list);
    auto list2 = copyList(list);
    printList(list2);
}

ulong getTimeMillis()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

void test4(size_t start, size_t stop, size_t step)
{
    for (size_t n = start; n <= stop; n += step)
    {
        ulong ms = getTimeMillis();
        bool res = test(n, false);
        ulong ms2 = getTimeMillis();
        std::cout << "n = " << n << std::endl;
        std::cout << "res = " << res << std::endl;
        std::cout << "start = " << ms << std::endl;
        std::cout << "finish = " << ms2 << std::endl;
        std::cout << "finish - start = " << ms2 - ms << std::endl;
        std::cout << "tan(L) = " << (double)(ms2 - ms) / n << std::endl << std::endl;
        
    }
}