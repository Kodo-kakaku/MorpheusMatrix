#include "../lib/matrix.h"
#include <iostream>

int main() {
    constexpr int SIZE = 10;
    mtx::Matrix<int, 0> matrix;

    for (size_t i = 0; i < SIZE; ++i){
        matrix[i][i] = i; // main diagonal
    }

    for(size_t i = 0; i < SIZE; ++i){
        matrix[SIZE - i - 1][ i ] = matrix[i][i]; // secondary diagonal
    }

    // print matrix
    for (size_t i = 1; i < SIZE - 1; ++i){
        for (size_t ii = 1; ii < SIZE - 1; ++ii){
            std::cout << matrix[i][ii] << " ";
        }

        std::cout << std::endl;
    }

    // size of matrix
    std::cout << matrix.size() << std::endl;

    // print occupied cells
    for (auto c : matrix){
        int x, y, v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
}