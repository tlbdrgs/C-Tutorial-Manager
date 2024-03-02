#pragma once
#include "tutorial.h"
#include<vector>
template <typename TElem>
class Dynamic_vector
{
private:
    std::vector<TElem> data;
public:
    Dynamic_vector() = default;
    int get_size() const;
    TElem get_item(int index) const;
    void add_item(const TElem& item);
    void update_item(int index, const TElem& updated_item);
    void remove_item(int index);
};