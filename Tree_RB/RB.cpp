#include <bits/stdc++.h>
#include "RBTree.h"
using namespace std;

const int dataset = 10;

ofstream fout;
ifstream fin;

int main() {
    for (int i = 0; i < dataset; i++){
        RBTree<int> rbt;
        fout.open("../Output/RBT_height.txt", std::ios_base::app);
        fin.open("../Datasets/input"+std::to_string(i)+".txt");
        for (int j = 0; j < 1e6; j++){
            int x; 
            fin >> x;
            rbt.insertValue(x);
        }
        int height = rbt.maxDepth();
        fout << height << "\n";
        cout << "Height of RBT tree: " << height << "\n";
        fin.close();
        fout.close();
    }
    return 0;
}
