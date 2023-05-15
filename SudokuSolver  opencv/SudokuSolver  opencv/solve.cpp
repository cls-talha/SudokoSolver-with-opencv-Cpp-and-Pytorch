#include <vector>
#include <iostream>

// computerphile sudoku solver python code conversion to C++ via chatGPT xDD
class Sudoku_Solver {

private:
    const int N = 9;
    std::vector<int> solve(std::vector<int>& board, int pos) {
        if (pos == N * N) {
            return board;
        }
        int row = pos / N;
        int col = pos % N;
        if (board[pos] != 0) {
            return solve(board, pos + 1);
        }
        for (int num = 1; num <= N; num++) {
            bool is_valid = true;
            // check row
            for (int j = 0; j < N; j++) {
                if (board[row * N + j] == num) {
                    is_valid = false;
                    break;
                }
            }
            // check column
            if (is_valid) {
                for (int i = 0; i < N; i++) {
                    if (board[i * N + col] == num) {
                        is_valid = false;
                        break;
                    }
                }
            }
            // check box
            if (is_valid) {
                int box_row = row - row % 3;
                int box_col = col - col % 3;
                for (int i = box_row; i < box_row + 3; i++) {
                    for (int j = box_col; j < box_col + 3; j++) {
                        if (board[i * N + j] == num) {
                            is_valid = false;
                            break;
                        }
                    }
                }
            }
            if (is_valid) {
                board[pos] = num;
                std::vector<int> result = solve(board, pos + 1);
                if (!result.empty()) {
                    return result;
                }
                board[pos] = 0;
            }
        }
        return {};
    }

public:
    inline std::vector<int> solve_sudoku(std::vector<int>& board) {
        return solve(board, 0);
    }

    bool check_solution(std::vector<int>& solution_arr) {
        for (int i = 0; i < solution_arr.size(); i++) {
            if (solution_arr[i] == 0) {
                return false;
            }
        }
        return true;
    }

    void print_array(std::vector<int>& vec) {
        for (size_t i = 0; i < vec.size(); i++) {
            std::cout << vec[i] << " ";
            if ((i + 1) % 10 == 0) {
                std::cout << '\n';
            }
        }
    }
};
