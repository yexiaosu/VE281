#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP

#include <vector>
#include <functional>

template <typename T>
void swap_val(std::vector<T> &vector, size_t i, size_t j)
{
    const T tmp = vector[j];
    vector[j] = vector[i];
    vector[i] = tmp;
}

template <typename T, typename Compare = std::less<T>>
void bubble_sort(std::vector<T> &vector, Compare comp = Compare())
{
    // TODO: implement
    // base case
    size_t size = vector.size();
    if (size <= 1)
    {
        return;
    }
    else if (size == 2)
    {
        if (comp(vector[0], vector[1]))
        {
            swap_val(vector, 0, 1);
        }
        return;
    }
    // when size > 2
    for (size_t i = size - 2; i > 0; i--)
    {
        for (size_t j = 0; j <= i; j++)
        {
            if (comp(vector[j + 1], vector[j]))
            {
                swap_val(vector, j, j + 1);
            }
        }
    }
}

template <typename T, typename Compare = std::less<T>>
void insertion_sort(std::vector<T> &vector, Compare comp = Compare())
{
    // TODO: implement
    size_t size = vector.size();
    for (size_t i = 1; i < size; i++)
    {
        size_t j = 0;
        while (j < i && !comp(vector[i], vector[j]))
        {
            j++; // Find the location to insert the value (Think about why we use >= here)
        }
        const T tmp = vector[i]; // Store the value we need to insert
        vector.erase(vector.begin() + i);
        vector.insert(vector.begin() + j, tmp);
    }
}

template <typename T, typename Compare = std::less<T>>
void selection_sort(std::vector<T> &vector, Compare comp = Compare())
{
    // TODO: implement
    // base case
    size_t size = vector.size();
    if (size <= 1)
    {
        return;
    }
    // when size > 1
    for (size_t i = 0; i < size - 1; i++)
    {
        size_t smallest = i;
        for (size_t j = i + 1; j < size; j++)
        {
            if (comp(vector[j], vector[smallest]))
            {
                smallest = j;
            }
        }
        swap_val(vector, i, smallest);
    }
}

template <typename T, typename Compare = std::less<T>>
void merge(std::vector<T> &left, std::vector<T> &right, std::vector<T> &vector, Compare comp = Compare())
{
    // TODO: implement
    size_t i = 0, j = 0, k = 0;
    while (i != left.size() && j != right.size())
    {
        if (!comp(right.at(j), left.at(i)))
        {
            vector[k] = left.at(i);
            i++;
        }
        else
        {
            vector[k] = right.at(j);
            j++;
        }
        k++;
    }
    if ((left.begin() + i) == left.end())
    {
        for (j = j; j < right.size(); j++)
        {
            vector[k] = right.at(j);
            k++;
        }
    }
    else
    {
        for (i = i; i < left.size(); i++)
        {
            vector[k] = left.at(i);
            k++;
        }
    }
}

template <typename T, typename Compare = std::less<T>>
void merge_sort(std::vector<T> &vector, Compare comp = Compare())
{
    // TODO: implement
    if (!comp(vector.back(), vector.front()) && vector.size() <= 2)
    {
        return;
    }
    size_t mid = vector.size() / 2;
    std::vector<T> left(vector.begin(), vector.begin() + mid);
    std::vector<T> right(vector.begin() + mid, vector.end());
    merge_sort(left, comp);
    merge_sort(right, comp);
    merge(left, right, vector, comp);
}

template <typename T, typename Compare = std::less<T>>
size_t partition_extra(std::vector<T> &vector, size_t begin, size_t end, size_t pivotat, Compare comp = Compare())
{
    // TODO: implement
    size_t size = end - begin;
    std::vector<T> new_vec = vector;
    T p_val = vector.at(pivotat);
    size_t i = begin, j = (end - 1);
    for (size_t k = begin + 1; k < begin + size; k++)
    {
        if (comp(p_val, vector.at(k)))
        {
            new_vec.at(j) = vector.at(k);
            j--;
        }
        else
        {
            new_vec.at(i) = vector.at(k);
            i++;
        }
    }
    new_vec.at(i) = p_val;
    vector = new_vec;
    return i;
}

template <typename T, typename Compare = std::less<T>>
void quick_sort_extra_helper(std::vector<T> &vector, size_t begin, size_t end, Compare comp = Compare())
{
    size_t pivotat = begin;
    if ((end - begin) < 2 || begin > end)
    {
        return;
    }
    pivotat = partition_extra(vector, begin, end, pivotat, comp);
    quick_sort_extra_helper(vector, begin, pivotat, comp);
    quick_sort_extra_helper(vector, pivotat + 1, end, comp);
}

template <typename T, typename Compare = std::less<T>>
void quick_sort_extra(std::vector<T> &vector, Compare comp = Compare())
{
    // TODO: implement
    size_t begin = 0, end = vector.size();
    quick_sort_extra_helper(vector, begin, end, comp);
}

template <typename T, typename Compare = std::less<T>>
void find_ij(std::vector<T> &vector, size_t begin, size_t end, const T p_val, size_t &i, size_t &j, Compare comp = Compare())
{
    while (i < end && comp(vector.at(i), p_val))
    {
        i++;
    }
    while (begin < j && !comp(vector.at(j), p_val))
    {
        j--;
    }
    if (i < j)
    {
        swap_val(vector, i, j);
        find_ij(vector, begin, end, p_val, i, j, comp);
    }
    else
    {
        swap_val(vector, begin, j);
    }
}

template <typename T, typename Compare = std::less<T>>
size_t partition_in(std::vector<T> &vector, size_t begin, size_t end, size_t pivotat, Compare comp = Compare())
{
    // TODO: implement

    T p_val = vector.at(pivotat);
    size_t i = begin + 1, j = (end - 1);
    find_ij(vector, begin, end, p_val, i, j, comp);
    return j;
}

template <typename T, typename Compare = std::less<T>>
void quick_sort_inplace_helper(std::vector<T> &vector, size_t begin, size_t end, Compare comp = Compare())
{
    size_t pivotat = begin;
    if ((end - begin) < 2 || begin > end)
    {
        return;
    }
    pivotat = partition_in(vector, begin, end, pivotat, comp);
    quick_sort_inplace_helper(vector, begin, pivotat, comp);
    quick_sort_inplace_helper(vector, pivotat + 1, end, comp);
}

template <typename T, typename Compare = std::less<T>>
void quick_sort_inplace(std::vector<T> &vector, Compare comp = Compare())
{
    // TODO: implement
    size_t begin = 0, end = vector.size();
    quick_sort_inplace_helper(vector, begin, end, comp);
}

#endif //VE281P1_SORT_HPP
