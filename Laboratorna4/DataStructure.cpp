#include "DataStructure.h"

DataStructure::DataStructure(int m) : fields(m, 0), mtx(m) {}

int DataStructure::read(int index) {
    std::lock_guard<std::mutex> lock(mtx[index]);
    return fields[index];
}

void DataStructure::write(int index, int value) {
    std::lock_guard<std::mutex> lock(mtx[index]);
    fields[index] = value;
}

std::string DataStructure::toString() {
    std::lock_guard<std::mutex> lock(string_mtx);

    std::stringstream ss;
    ss << "{ ";
    for (size_t i = 0; i < fields.size(); i++) {
        std::lock_guard<std::mutex> lock_field(mtx[i]);
        ss << fields[i];
        if (i + 1 != fields.size()) ss << ", ";
    }
    ss << " }";
    return ss.str();
}
