#ifndef ADDRESSLIST_H
#define ADDRESSLIST_H

#include "Address.h"

class AddressList {
private:
    Address* list;
    int size;

public:
    AddressList(Address* list, int size);

    Address* getList() const;
    int getSize() const;

    Address getAt(int index) const;
};

#endif
