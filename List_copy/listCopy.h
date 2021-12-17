#pragma once
#include <vector>
#include <memory>
struct node
{
    char value;
    std::shared_ptr<node> next;
    std::weak_ptr<node> other_node;

    node(char value, std::shared_ptr<node> other = nullptr);

    size_t getSize() const;
};

std::shared_ptr<node> copyList(std::shared_ptr<node> first);
std::shared_ptr<node> read();
void printList(const std::shared_ptr<const node>& first);