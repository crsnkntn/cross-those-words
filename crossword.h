#pragma once

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <ctime>
#include <random>

class Crossword2D {
    private:
        size_t board_size_x, board_size_y;
        std::vector<std::string> words;
        std::vector<std::vector<char>> board;
        std::vector<int> dirs {
            1, 0, -1, 0, 0, 1, 0, -1
        };

    public:
        Crossword2D (size_t dim);

        Crossword2D (size_t dim, std::string file_name);
            
        // copy assignment
        void operator=(Crossword2D& other);
            
        // dtor
        ~Crossword2D ();

        std::vector<std::string>& new_file (std::string file_name);

        std::vector<std::vector<char>>& generate_a_crossword ();

        private:
        void make_board_empty ();
        
        bool place_word(std::string word);

        bool place_word_horizontally (int row, int col, int c, std::string word);

        bool place_word_vertically (int row, int col, int c, std::string word);
    };

extern void convert_to_word_search (std::vector<std::vector<char>>& matrix);
