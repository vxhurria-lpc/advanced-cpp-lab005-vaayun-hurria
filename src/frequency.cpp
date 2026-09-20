#include "frequency.h"

#include <stdexcept>
#include <unordered_map>

namespace algorithm_lab {

int mostFrequentNaive(const std::vector<int>& values) {
    if (values.empty()) {
        throw std::invalid_argument("values must not be empty");
    }

    int best_value = values.front();
    int best_count = 0;

    for (std::size_t i = 0; i < values.size(); ++i) {
        int current = values[i];
        int count = 0;
        for (std::size_t j = 0; j < values.size(); ++j) {
            if (values[j] == current) {
                ++count;
            }
        }

        if (count > best_count || (count == best_count && current < best_value)) {
            best_count = count;
            best_value = current;
        }
    }

    return best_value;
}

int mostFrequentEfficient(const std::vector<int>& values) {
    if (values.empty()) {
        throw std::invalid_argument("values must not be empty");
    }

    std::unordered_map<int, int> frequency_map;
    for (int value : values) {
        ++frequency_map[value];
    }

    int best_value = values.front();
    int best_count = 0;

    for (const auto& pair : frequency_map) {
        int current_value = pair.first;
        int current_count = pair.second;

        if (current_count > best_count || (current_count == best_count && current_value < best_value)) {
            best_count = current_count;
            best_value = current_value;
        }
    }

    return best_value;
}

}
