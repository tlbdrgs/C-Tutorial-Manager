#include "Dynamic_vector.h"
#include<vector>

template <typename TElem>
int Dynamic_vector<TElem>::get_size() const {
	return data.size();
}

template <typename TElem>
TElem Dynamic_vector<TElem>::get_item(int index) const {
	return data[index];
}

template <typename TElem>
void Dynamic_vector<TElem>::add_item(const TElem& item) {
	data.push_back(item);
}

template <typename TElem>
void Dynamic_vector<TElem>::update_item(int index, const TElem& updated_item)
{
	data[index] = updated_item;
}

template <typename TElem>
void Dynamic_vector<TElem>::remove_item(int index) {
	data.erase(data.begin() + index);
}


template class Dynamic_vector<Tutorial>;