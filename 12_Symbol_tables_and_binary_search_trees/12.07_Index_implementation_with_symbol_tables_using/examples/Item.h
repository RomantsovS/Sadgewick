#pragma once

#include <cstring>
#include <iostream>

struct Key {
    Key() = default;
    Key(char* val) : m_val(val) {}
    operator char*() { return m_val; }

    char* m_val;
};

Key maxKey = {nullptr};

bool operator<(const Key lhs, const Key rhs) { return strcmp(lhs.m_val, rhs.m_val) < 0; }
bool operator==(const Key lhs, const Key rhs) { return strncmp(lhs.m_val, rhs.m_val,
strlen(lhs.m_val)) == 0; }

std::ostream& operator<<(std::ostream& os, Key& x) {
    os << x.m_val;
    return os;
}

class Item {
   private:
    Key keyval = nullptr;
    float info;

   public:
    Item() = default;
    Item(Key val) : keyval(val) {}
    Key key() const { return keyval; }
    bool null() const { return keyval.m_val == nullptr; }

    void show(std::ostream& os = std::cout) const { os << keyval.m_val << " " << info << std::endl; }
};

std::ostream& operator<<(std::ostream& os, Item& x) {
    x.show(os);
    return os;
}