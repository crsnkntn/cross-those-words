#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <ctime>
#include <random>


namespace ScrabbleBot {
    class Crossword2D {
        private:
        size_t board_size_x, board_size_y;
        std::vector<std::string> words;
        std::vector<std::vector<char>> board;
        std::vector<int> dirs {
            1, 0, -1, 0, 0, 1, 0, -1
        };

        public:
        // ctors
        Crossword2D (size_t dim) {
            board_size_x = dim;
            board_size_y = dim;
            board.resize(dim, std::vector<char>(dim));
        }

        
        Crossword2D (size_t dim, std::string file_name) : board_size_x(dim), board_size_y(dim) {
            std::ifstream fin(file_name);
            std::string input;
            while (fin >> input) {
                words.push_back(input);
            }
            fin.close();
            board.resize(dim, std::vector<char>(dim));
            make_board_empty();
        }
        
        // copy assignment
        void operator=(Crossword2D& other) {
            board_size_x = other.board_size_x;
            board_size_y = board_size_x;
            words = other.words;
            make_board_empty();
        }
        
        // dtor
        ~Crossword2D () {
            words.clear();
            board.clear();
        }

        std::vector<std::string>& new_file (std::string file_name) {
            std::ifstream fin(file_name);
            std::string input;
            while (fin >> input) {
                words.push_back(input);
            }
            fin.close();
            make_board_empty();
            return words;
        }

        std::vector<std::vector<char>>& generate_a_crossword () {
            std::queue<std::string> q;
            for (auto s : words) {
                q.push(s);
            }

            // place the first word onto the board
            std::string word = q.front();
            q.pop();
            for (int i = 0; i < word.size(); ++i) {
                board[4 + i][5] = word[i];
            }

            // pop and place words until the queue is empty
            int count = 0;
            while (!q.empty()) {
                if (count > 50) {
                    break;
                }
                word = q.front();
                q.pop();
                bool placed = place_word(word);
                if (!placed)
                    q.push(word);
                    ++count;
            }
            return board;
        }

        private:
        void make_board_empty () {
            for (int i = 0; i < board_size_x; ++i) {
                for (int j = 0; j < board_size_y; ++j) {
                    board[i][j] = ' ';
                }
            }
        }
        
        bool place_word(std::string word) {
            // loop through every position on the board and search for a matching letter
            for (int row = 0; row < board_size_x; ++row) {
                for (int col = 0; col < board_size_y; ++col) {
                    // skip blank squares
                    if (board[row][col] == ' ')
                        continue;
                    for (int c = 0; c < word.size(); ++c) {
                        if (board[row][col] != word[c])
                            continue;
                        
                        // check horizontal
                        if (place_word_horizontally(row, col, c, word))
                            return true;
                        
                        // check vertical
                        if (place_word_vertically(row, col, c, word))
                            return true;
                    }
                }
            }
            return false;
        }

        bool place_word_horizontally (int row, int col, int c, std::string word) {
            // protect against seg faults
            if (col - c - 1 < 0 || col + word.size() - c  + 1 > board_size_x) {
                return false;
            } 

            // check for collisions
            int i = 0;
            if (board[row][col - c - 1] != ' ' || board[row][col + word.size() - c + 1] != ' ')
                return false;
            for (int j = col - c; j < col + word.size() - c; ++j) {
                if (board[row][j] != ' ' && board[row][j] != word[i])
                    return false;
                if (j != col && (board[row + 1][j] != ' ' || board[row - 1][j] != ' '))
                    return false;
                ++i;
            }

            // place the word
            i = 0;
            for (int j = col - c; j < col + word.size() - c; ++j) {
                board[row][j] = word[i];
                ++i;
            }
            return true;
        }

        bool place_word_vertically (int row, int col, int c, std::string word) {
            // protect against seg faults
            if (row - c - 1 < 0 || row + word.size() - c + 1 > board_size_x) {
                return false;
            } 

            // check for collisions
            int i = 0;
            if (board[row - c - 1][col] != ' ' || board[row + word.size() - c + 1][col] != ' ')
                return false;
            for (int j = row - c; j < row + word.size() - c; ++j) {
                if (board[j][col] != ' ' && board[j][col] != word[i])
                    return false;
                if (j != row && (board[j][col + 1] != ' ' || board[j][col - 1] != ' '))
                    return false;
                ++i;
            }

            // place the word
            i = 0;
            for (int j = row - c; j < row + word.size() - c; ++j) {
                board[j][col] = word[i];
                ++i;
            }
            return true;
        }

    };

    void convert_to_word_search (std::vector<std::vector<char>>& matrix) {
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (matrix[i][j] == ' ')
                    matrix[i][j] = char(rand() % 26 + 97);
            }
        }
    }
};