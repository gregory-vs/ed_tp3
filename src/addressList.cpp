#include "AddressList.h"

AddressList::AddressList(Address* list, int size) {
    this->list = list;
    this->size = size;
}

Address* AddressList::getList() const {
    return list;
}

int AddressList::getSize() const {
    return size;
}

Address AddressList::getAt(int index) const {
    if (index < 0 || index >= size) {
        return Address();
    }
    return list[index];
}
