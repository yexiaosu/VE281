//
// Created by wanglan on 2021/7/19.
//

#include <forward_list>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
#include <set>
#include <iostream>

using namespace std;

typedef vector<pair<size_t, size_t>> neighbor;  // {index,weight}
typedef tuple<size_t, size_t, size_t> edge;

class Node {
public:
    bool visited_dj = false;
    neighbor ngh;

    Node() = default;
};

typedef vector<Node> ajLists;
typedef vector<edge> edges;
typedef pair<size_t, size_t> distPair;

class Graph {
protected:
    ajLists pos;  // original direction
    vector<pair<size_t, size_t>> forest;  // {index,size}
    edges edge_list;
    size_t num_node = 0;

    void init_forest() {
        for (size_t i = 0; i < num_node; ++i) {
            forest.at(i) = {i, 1};
        }
    }

    void init_dis() {
        for (size_t i = 0; i < num_node; ++i) {
            forest.at(i) = {UINT32_MAX, i};
        }
    }

    void init_topo() {
        for (size_t i = 0; i < num_node; ++i) {
            forest.at(i) = {0, i};
        }
    }

    size_t find(size_t set) {
        while (set != forest.at(set).first) {
            forest.at(set).first = forest.at(forest.at(set).first).first;
            set = forest.at(set).first;
        }
        return set;
    }

    bool make_union(size_t set1, size_t set2) {
        size_t set1_ast = find(set1);
        size_t set2_ast = find(set2);
        if (set1_ast == set2_ast) {
            return false;
        }
        if (forest.at(set1_ast).second < forest.at(set2_ast).second) {
            forest.at(set1_ast).first = set2_ast;
            forest.at(set2_ast).second = forest.at(set2_ast).second + forest.at(set1_ast).second;
        } else {
            forest.at(set2_ast).first = set1_ast;
            forest.at(set1_ast).second = forest.at(set1_ast).second + forest.at(set2_ast).second;
        }
        return true;
    }

public:
    Graph() = default;

    explicit Graph(const size_t &num) {
        num_node = num;
        pos.resize(num, Node());
        forest.resize(num);
        init_topo();
    }

    ~Graph() = default;

    void add_edge(size_t &start, size_t &end, size_t &weight) {
        pos.at(start).ngh.push_back({end, weight});
        ++forest.at(end).first;
        edge_list.push_back({weight, start, end});
    }

    void sort_edge() {
        sort(edge_list.begin(), edge_list.end());
    }

    bool topo_sort() {
        queue<pair<size_t,size_t>*> topo;
        size_t queue_num = 0;
        for (auto &item:forest) {
            if (item.first == 0) {
                topo.push(&item);
            }
        }
        while (!topo.empty()) {
            pair<size_t,size_t>*now = topo.front();
            for (auto &item:pos.at(now->second).ngh) {
                if (forest.at(item.first).first == 0) {
                    return false;
                }
                --forest.at(item.first).first;
                if (forest.at(item.first).first == 0) {
                    topo.push(&forest.at(item.first));
                }
            }
            queue_num++;
            topo.pop();
        }
        if (queue_num != num_node) {
            return false;
        } else {
            return true;
        }
    }

    size_t MST() {
        size_t mst = 0;
        size_t edge_num = 0;
        init_forest();
        for (auto &item:edge_list) {
            size_t set1 = get<1>(item);
            size_t set2 = get<2>(item);
            if (make_union(set1, set2)) {
                mst = mst + get<0>(item);
                edge_num++;
                if (edge_num == num_node - 1) {
                    return mst;
                }
            }
        }
        return UINT32_MAX;
    }

    size_t Dj(const size_t &source, const size_t &destination) {
        init_dis();
        forest.at(source).first = 0;
        priority_queue<distPair, vector<distPair>, greater<>> remain;
        remain.push(forest.at(source));
        while (!remain.empty()) {
            distPair now = remain.top();
            if (now.second == destination) {
                return now.first;
            }
            if (now.first == UINT32_MAX){
                return UINT32_MAX;
            }
            if (pos.at(now.second).visited_dj) {
                remain.pop();
                continue;
            } else {
                pos.at(now.second).visited_dj = true;
                remain.pop();
                for (auto &item:pos.at(now.second).ngh) {
                    if (!pos.at(item.first).visited_dj) {
                        if (now.first + item.second < forest.at(item.first).first) {
                            forest.at(item.first).first = now.first + item.second;
                            remain.push(forest.at(item.first));
                        }
                    }
                }
            }
        }
        return forest.at(destination).first;
    }
};

int main() {
    size_t num, start, end;
    cin >> num >> start >> end;
    size_t s, e, weight;
    Graph graph(num);
    while (cin >> s) {
        cin >> e >> weight;
        graph.add_edge(s, e, weight);
    }
    graph.sort_edge();
    bool dag = graph.topo_sort();
    size_t len = graph.Dj(start, end);
    size_t mst = graph.MST();
    if (len != UINT32_MAX) {
        cout << "Shortest path length is " << len << endl;
    } else {
        cout << "No path exists!" << endl;
    }
    if (dag) {
        cout << "The graph is a DAG" << endl;
    } else {
        cout << "The graph is not a DAG" << endl;
    }
    if (mst != UINT32_MAX) {
        cout << "The total weight of MST is " << mst << endl;
    } else {
        cout << "No MST exists!" << endl;
    }
}