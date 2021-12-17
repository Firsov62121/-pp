#include "listCopy.h"
#include <iostream>


node::node(char value, std::shared_ptr<node> other) : value(value), other_node(std::move(other)) {}


size_t node::getSize() const
{
    size_t res = 1;
    auto tmp = next;
    while(tmp)
    {
        tmp = tmp->next;
        ++res;
    }
    return res;
}

std::shared_ptr<node> read()
{
    std::cout << "Введите длину списка: ";
    int n;
    char c;
    std::cin >> n;
    std::cout << "Введите элементы списка через пробел:" << std::endl;
    std::cin >> c;
    std::vector<std::shared_ptr<node>> list(n);
    list[0] = std::make_shared<node>(c);
    for (int i = 0; i < n - 1; ++i)
    {
        std::cin >> c;
        list[i]->next = std::make_shared<node>(c);
        list[i + 1] = list[i]->next;
    }
    std::cout << "Введите кто на кого ссылается:" << std::endl;
    for(int i = 0; i < n; ++i)
    {
        int tmp;
        std::cin >> tmp;
        list[i]->other_node = list[(tmp - 1) % n];
    }
    return list[0];
}

void printList(const std::shared_ptr<const node>& first) //can use get
{
    const node* tmp = first.get();
    while(tmp)
    {
        std::cout << "node.value = " << tmp->value << std::endl;
        if(tmp->next)
            std::cout << "node.next.value = " << tmp->next->value << std::endl;
        tmp->other_node;
        if(tmp->other_node.lock())
            std::cout << "node.other_node = " << tmp->other_node.lock()->value << std::endl;
        tmp = tmp->next.get();
    }
}

std::shared_ptr<node> copyList(std::shared_ptr<node> first)//std::shared_ptr, raii, google_tests//look at weak_tpr
{
    if(!first)
        return nullptr;
    size_t n = first->getSize();
    std::vector<std::shared_ptr<node>> listFromFirst(n);//rename A
    auto p = std::make_shared<node>(first->value);
    auto res = p;
    for(uint i = 0; i < n; ++i)
    {
        auto tmp = first->next;
        p->other_node = first->other_node;
        first->next = p;
        if(i != n - 1)
            p->next = std::make_shared<node>(tmp->value);
        p = p->next;
        listFromFirst[i] = first;
        first = tmp;
    }
    p = res;
    for(uint i = 0; i < n; ++i)
    {
        p->other_node = p->other_node.lock()->next;
        p = p->next;
    }
    for(uint i = 0; i < n - 1; ++i)
    {
        listFromFirst[i]->next = listFromFirst[i + 1];
    }
    listFromFirst[n-1]->next = nullptr;
    return res;
}
