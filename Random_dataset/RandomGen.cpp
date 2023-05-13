#include <fstream>
#include <random>
#include <queue>
#include <vector>
#include <algorithm>

const int dataset = 10;
const int maxLength = 1e6;
const int maxN = 1e6;

bool cmp(int a, int b){
  return a > b;
}

void genTest(int dataset, int maxLength, float maxN){
    std::ofstream fout;
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_int_distribution<int> dist(maxN*(-1),maxN);
    std::vector<int> vec;
    for (int j = 0; j < maxLength; j++){
       vec.push_back(dist(e2));
    }
    std::priority_queue<int> maxq(vec.begin(), vec.end());
    std::priority_queue<int, std::vector<int>, std::greater<int>> minq(vec.begin(), vec.end());
    

    fout.open("../Datasets/input0.txt");
    for (; !maxq.empty(); maxq.pop())
        fout << maxq.top() << "\n";
    fout.close();
    
    fout.open("../Datasets/input1.txt");
    for (; !minq.empty(); minq.pop())
        fout << minq.top() << "\n";
    fout.close();
    for (int i = 2; i < dataset; i++){
        std::shuffle(vec.begin(), vec.end(), e2);
        fout.open("../Datasets/input"+std::to_string(i)+".txt");
        for (int j = 0; j < maxLength; j++){
            fout << std::scientific << vec[j] << "\n";
        }
        fout.close();
    }
}

int main(){
    genTest(dataset,maxLength,maxN);
    return 0;
}
