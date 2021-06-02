#include "BaseObj.hpp"

Type::Type(TYPE t) : t(t) {}

bool Type::operator==(const Type rhs) const {
    return t == rhs.t;
}

bool Type::operator==(const TYPE rhs) const {
    return t == rhs;
}

bool Type::operator!=(const Type rhs) const {
    return !(rhs == *this);
}

bool Type::operator!=(const TYPE rhs) const {
    return !(*this == rhs);
}

string Type::getStr() const {
    return typeStr[(int)(t)];
}


Symbol::Symbol(const ID &id, const Type &t) : id(id), t(t) {}

Symbol::Symbol(const Symbol& _sym) : id(_sym.id), t(_sym.t) {}

SymList::SymList(const vector<Symbol> &symList) : symList(symList) {}

SymList::SymList() : symList() {}
