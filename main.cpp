#include "crossword.h"
#include "crossword.cpp"

int main () {
    size_t crossword_size = 30;
    Crossword2D crossword_maker(crossword_size);
    std::ifstream files("word_bank.txt");
    std::string file_name;
    while (files >> file_name) {
        std::ofstream fout_c(file_name.substr(0, file_name.size() - 4) + "_crossword.txt");
        std::ofstream fout_w(file_name.substr(0, file_name.size() - 4) + "_wordsearch.txt");
        crossword_maker.new_file(file_name);
        auto v = crossword_maker.generate_a_crossword();
        auto v_w = v;
        convert_to_word_search(v_w);
        for (int row = 0; row < v.size(); ++row) {
            for (int col = 0; col < v[row].size(); ++col) {
                fout_c << v[row][col] << ' ';
                fout_w << v_w[row][col] << ' ';
            }
            fout_c << '\n';
            fout_w << '\n';
        }
        fout_c << std::endl;
        fout_w << std::endl;
        fout_c.close();
        fout_w.close();
    }
    return 1;
}