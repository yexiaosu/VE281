#include <iostream>
#include <algorithm>
#include "sort.hpp"
using namespace std;

struct point
{
    int x = 0;
    int y = 0;
    int x0 = 0;
    int y0 = 0;
    bool operator<=(const point &b) const
    {
        return ((x - x0) * (b.y - y0) - (y - y0) * (b.x - x0)) >= 0;
    }
    bool operator==(const point &b) const
    {
        return ((x - x0) * (b.y - y0) - (y - y0) * (b.x - x0)) == 0;
    }
};

bool judge_ccw(const point next_t, const point t, const point p)
{
    return (((t.x - next_t.x) * (p.y - next_t.y) - (t.y - next_t.y) * (p.x - next_t.x)) <= 0);
}

int main()
{
    // get input
    int N = 0;
    vector<point> X;
    point p0;
    p0.x = INT32_MAX;
    p0.y = INT32_MAX;
    cin >> N;
    if (N == 0)
    {
        return 0;
    }
    else if (N>0)
    {
        cin >> p0.x>>p0.y;
        N--;
    }
    while (N > 0)
    {
        point p;
        cin >> p.x >> p.y;
        if (p.y < p0.y || (p.y == p0.y && p.x < p0.x))
        {
            X.push_back(p0);
            p0.x = p.x;
            p0.y = p.y;
        }
        else
        {
            X.push_back(p);
        }
        N--;
    }
    // record p0
    for (auto &p : X)
    {
        p.x0 = p0.x;
        p.y0 = p0.y;
    }
    // sort
    sort(X.begin(), X.end(), std::less_equal<point>());
    // only keep the farest among the points with same angle    
    vector<point> X_uni;
    X_uni.reserve(X.size());
    if (X.size() > 1)
    {
        for (auto &p : X)
        {
            if (X_uni.size() == 0)
            {
                X_uni.push_back(p);
            }
            else if ((X_uni.back() == p) && ((p.y > X_uni.back().y) || ((p.y == X_uni.back().y) && (p.x > X_uni.back().x))))
            {
                X_uni.back() = p;
            }
            else if (X_uni.back() == p)
            {
                continue;
            }
            else
            {
                X_uni.push_back(p);
            }
        }
    }

    // Graham
    vector<point> S;
    S.reserve(X.size());
    S.push_back(p0);
    for (auto &p : X_uni)
    {
        while (S.size() > 1 && judge_ccw(S.at(S.size() - 2), S.back(), p))
        {
            S.pop_back();
        }
        if (S.back().x == p.x && S.back().y == p.y)
        {
            continue;
        }
        S.push_back(p);
    }
    // output
    for (auto &p : S)
    {
        cout << p.x << " " << p.y << endl;
    }

    return 0;
}