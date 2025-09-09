#ifndef PALINDROMO_H
#define PALINDROMO_H

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <iterator>

/*
  longest_palindrome_positions(s)
  - Entrada: s (string con el contenido del "archivo de transmisión")
  - Salida: pair (start, end) con posiciones 1-based del palíndromo más largo.
    Si s está vacío devuelve (0,0).
  Implementación: algoritmo de Manacher en tiempo O(n).
*/

inline std::pair<size_t, size_t> longest_palindrome_positions(const std::string &s) {
    size_t n = s.size();
    if (n == 0) return {0, 0};

    // Transformación para Manacher: insertar separadores.
    std::string t;
    t.reserve(n * 2 + 3);
    t.push_back('^');
    t.push_back('#');
    for (char c : s) {
        t.push_back(c);
        t.push_back('#');
    }
    t.push_back('$');

    const size_t m = t.size();
    std::vector<int> p(m, 0);
    int center = 0, right = 0;
    int best_center = 0, best_len = 0;

    for (size_t i = 1; i + 1 < m; ++i) {
        int mirror = 2 * center - (int)i;
        if ((int)i < right)
            p[i] = std::min(right - (int)i, p[mirror]);
        else
            p[i] = 0;

        while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) ++p[i];

        if ((int)i + p[i] > right) {
            center = (int)i;
            right = (int)i + p[i];
        }

        if (p[i] > best_len) {
            best_len = p[i];
            best_center = (int)i;
        }
    }

    int start_t = best_center - best_len;
    int end_t   = best_center + best_len;

    int first_real_t = start_t;
    while (first_real_t <= end_t && t[first_real_t] == '#') ++first_real_t;
    int last_real_t = end_t;
    while (last_real_t >= start_t && t[last_real_t] == '#') --last_real_t;

    if (first_real_t > last_real_t) return {0, 0};

    size_t start_idx = (first_real_t - 2) / 2;
    size_t end_idx   = (last_real_t  - 2) / 2;

    return {start_idx + 1, end_idx + 1}; // 1-based
}

inline std::pair<size_t, size_t> longest_palindrome_positions_ignore_whitespace(const std::string &s) {
    std::string clean;
    std::vector<size_t> mapping; 

    for (size_t i = 0; i < s.size(); ++i) {
        if (!isspace(static_cast<unsigned char>(s[i]))) {
            clean += s[i];
            mapping.push_back(i + 1); // 1-based
        }
    }

    size_t n = clean.size();
    if (n == 0) return {0, 0};

    std::string t;
    t.reserve(n * 2 + 3);
    t.push_back('^');
    t.push_back('#');
    for (char c : clean) {
        t.push_back(c);
        t.push_back('#');
    }
    t.push_back('$');

    const size_t m = t.size();
    std::vector<int> p(m, 0);
    int center = 0, right = 0;
    int best_center = 0, best_len = 0;

    for (size_t i = 1; i + 1 < m; ++i) {
        int mirror = 2 * center - (int)i;
        if ((int)i < right)
            p[i] = std::min(right - (int)i, p[mirror]);
        else
            p[i] = 0;

        while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) ++p[i];

        if ((int)i + p[i] > right) {
            center = (int)i;
            right = (int)i + p[i];
        }

        if (p[i] > best_len) {
            best_len = p[i];
            best_center = (int)i;
        }
    }

    int start_t = best_center - best_len;
    int end_t   = best_center + best_len;

    int first_real_t = start_t;
    while (first_real_t <= end_t && t[first_real_t] == '#') ++first_real_t;
    int last_real_t = end_t;
    while (last_real_t >= start_t && t[last_real_t] == '#') --last_real_t;

    if (first_real_t > last_real_t) return {0, 0};

    size_t start_idx_clean = (first_real_t - 2) / 2; 
    size_t end_idx_clean   = (last_real_t  - 2) / 2; 

    size_t start_orig = mapping[start_idx_clean];
    size_t end_orig   = mapping[end_idx_clean];

    return {start_orig, end_orig};
}


#ifdef PALINDROMO_MAIN
int main() {
    std::string input((std::istreambuf_iterator<char>(std::cin)),
                      std::istreambuf_iterator<char>());

    auto res = longest_palindrome_positions(input);
    std::cout << res.first << " " << res.second << "\n";
    return 0;
}
#endif // PALINDROMO_MAIN

#endif // PALINDROMO_H
