//
// Created by wanglan on 2021/7/13.
//

#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ofstream out;
    out.open("case5.txt");
    srand(7777);
    int num= rand() % 100 + 1;
    out << num << endl;
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < num; ++j) {
            out << rand()%2 << " ";
        }
        out << endl;
    }
    out.close();
    return 0;
}