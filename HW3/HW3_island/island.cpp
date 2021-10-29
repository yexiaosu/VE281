//
// Created by wanglan on 2021/7/13.
//
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    size_t size, num_island;
    num_island = 0;
    cin >> size;
    vector<pair<int, bool>> vertex;  // vertex, second = true if it had been visited
    vertex.reserve(size * size);
    vector<vector<int>> arc(size * size);  // arc
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            int val;
            cin >> val;
            if (val != 0){
                val = int(i*size+j);
            }
            vertex.push_back({val, false});
        }
    }
    for (size_t i = 0; i < vertex.size(); ++i) {
        if ((i + 1) % size != 0) {
            arc[i].push_back(int(i+1));
            arc[i + 1].push_back(int(i));
        }
        if (i < size * (size - 1)) {
            arc[i].push_back(int(i+size));
            arc[i + size].push_back(int(i));
        }
    }
    for (size_t i = 0; i < vertex.size(); ++i) {
        if (vertex[i].first != 0 && vertex[i].second == false) {
            std::queue<pair<int, bool>*> bf;
            bf.push(&vertex[i]);
            while (!bf.empty()) {
                pair<int, bool> *now = bf.front();
                now->second = true;
                bf.pop();
                for (size_t j = 0; j < arc[now->first].size(); ++j) {
                    if (vertex[arc[now->first][j]].first != 0 && vertex[arc[now->first][j]].second == false){
                        bf.push(&vertex[arc[now->first][j]]);
                    }
                }
            }
            num_island++;
        }
    }
    cout << num_island << endl;
    return 0;
}