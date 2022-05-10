#include <math.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <chrono>
#include <thread>

#define PRINT_SORT
#include "sort.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::forward_list;
using std::list;
using std::map;
using std::set;
using std::string;
using std::vector;
using namespace std::chrono;

const size_t N = 40;
const char min_num = 'A', max_num = 'Z';

template <typename T>
struct data_t {
    std::vector<T> mas;
    // std::function<void(std::vector<T> &, size_t)> func;
    void (*func)(std::vector<T> &, size_t);
    string name;
    size_t speed;
    long long time = 0;
};

template <typename T>
void run_sort(data_t<T> &data) {
    cout << data.name << endl;

    if (data.mas.size() <= 40) {
        std::for_each(data.mas.begin(), data.mas.end(), [](auto &val) { cout << std::setw(2) << val; });
        cout << endl;
    }

    auto startTime = steady_clock::now();

    data.func(data.mas, data.speed);

    auto endTime = steady_clock::now();

    if (data.mas.size() <= 40) {
        std::for_each(data.mas.begin(), data.mas.end(), [](auto &val) { cout << std::setw(2) << val; });
        cout << endl;
    }

    data.time = duration_cast<milliseconds>(endTime - startTime).count();

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    std::default_random_engine rand_eng;
    std::uniform_int_distribution<> u_ch(min_num, max_num);

    vector<data_t<char>> vec;

    vector<char> mas(N);

    for (size_t i = 0; i != N; ++i) {
        mas[i] = static_cast<char>(u_ch(rand_eng));
        // mas[i] = 'A'/* + i % (max_num - min_num + 1)*/;
    }

    size_t speed = 50;

    vec.push_back(data_t<char>{mas, bubble_sort<char>, "bubble_sort", speed * 40});
    vec.push_back(data_t<char>{mas, shaker_sort<char>, "shaker_sort", speed * 40});
    vec.push_back(data_t<char>{mas, selection_sort<char>, "selection_sort", speed * 2});
    vec.push_back(data_t<char>{mas, insertion_sort<char>, "insertion_sort", speed * 10});
    vec.push_back(data_t<char>{mas, shall_sort<char>, "shall_sort", speed * 10});
    vec.push_back(data_t<char>{mas, quick_sort<char>, "qsort", speed * 1});
    vec.push_back(data_t<char>{mas, merge_sort<char>, "merge_sort", speed * 1});
	vec.push_back(data_t<char>{mas, heap_sort<char>, "heap_sort", speed * 1});

    std::for_each(vec.begin(), vec.end(), run_sort<char>);

    clearConsole();

    for (const auto &str : vec) {
        cout << "Elasped time: " << std::setw(10) << str.time << " " << str.name << endl;
    }

    cin >> speed;

    return 0;
}