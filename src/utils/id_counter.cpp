#include "Utils.hpp"

namespace Utils {

    int counter(int& id) {
        return id++;
    }

    int counter(int id) {
        return id + 1;
    }
}