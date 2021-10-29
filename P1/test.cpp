#include <iostream>
#include <algorithm>
#include <numeric>
#include <chrono>
#include "sort.hpp"
using namespace std;

void timeresult(vector<int> test0, vector<int> test01,vector<int> test02,vector<int> test03,vector<int> test04,vector<int> test05, void (*fp)(std::vector<int> &vector, std::less<int> comp))
{
    auto start = std::chrono::steady_clock::now();
    fp(test0, less<int>());
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::steady_clock::now();
    fp(test01, less<int>());
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::steady_clock::now();
    fp(test02, less<int>());
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::steady_clock::now();
    fp(test03, less<int>());
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::steady_clock::now();
    fp(test04, less<int>());
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::steady_clock::now();
    fp(test05, less<int>());
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";    
}

int main()
{
    srand(42);
    size_t n;
    n = 20;
    vector<int> test0, test1, test2, test3, test4, test5, test6;
    test0.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        test0.push_back((rand() % (10000 - 0 + 1)) - 0);
    }
    test1 = test0;
    test2 = test0;
    test3 = test0;
    test4 = test0;
    test5 = test0;
    test6 = test0;

    vector<int> test01, test11, test21, test31, test41, test51, test61;
    test01.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        test01.push_back((rand() % (10000 - 0 + 1)) - 0);
    }
    test11 = test01;
    test21 = test01;
    test31 = test01;
    test41 = test01;
    test51 = test01;
    test61 = test01;

    vector<int> test02, test12, test22, test32, test42, test52, test62;
    test02.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        test02.push_back((rand() % (10000 - 0 + 1)) - 0);
    }
    test12 = test02;
    test22 = test02;
    test32 = test02;
    test42 = test02;
    test52 = test02;
    test62 = test02;

    vector<int> test03, test13, test23, test33, test43, test53, test63;
    test03.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        test03.push_back((rand() % (10000 - 0 + 1)) - 0);
    }
    test13 = test03;
    test23 = test03;
    test33 = test03;
    test43 = test03;
    test53 = test03;
    test63 = test03;

    vector<int> test04, test14, test24, test34, test44, test54, test64;
    test04.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        test04.push_back((rand() % (10000 - 0 + 1)) - 0);
    }
    test14 = test04;
    test24 = test04;
    test34 = test04;
    test44 = test04;
    test54 = test04;
    test64 = test04;

    vector<int> test05, test15, test25, test35, test45, test55, test65;
    test05.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        test05.push_back((rand() % (10000 - 0 + 1)) - 0);
    }
    test15 = test05;
    test25 = test05;
    test35 = test05;
    test45 = test05;
    test55 = test05;
    test65 = test05;

    auto start = std::chrono::steady_clock::now();
    sort(test0.begin(), test0.end(), less<int>());
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::steady_clock::now();
    sort(test01.begin(), test01.end(), less<int>());
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::steady_clock::now();
    sort(test02.begin(), test02.end(), less<int>());
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::steady_clock::now();
    sort(test03.begin(), test03.end(), less<int>());
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::steady_clock::now();
    sort(test04.begin(), test04.end(), less<int>());
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::steady_clock::now();
    sort(test05.begin(), test05.end(), less<int>());
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";  
    cout << endl;  


    timeresult(test1, test11,test12,test13,test14,test15, bubble_sort);
    cout << endl;


    timeresult(test2, test21,test22,test23,test24,test25, insertion_sort);
    cout << endl;


    timeresult(test3, test31,test32,test33,test34,test35, selection_sort);
    cout << endl;


    timeresult(test4, test41,test42,test43,test44,test45, merge_sort);
    cout << endl;


    timeresult(test5, test51,test52,test53,test54,test55, quick_sort_extra);
    cout << endl;


    timeresult(test6, test61,test62,test63,test64,test65, quick_sort_inplace);
    cout << endl;
}