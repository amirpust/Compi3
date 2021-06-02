#include "BaseObj.hpp"

Type::Type(TYPE t) : t(t) {}

Symbol::Symbol(const ID &id, const Type &t) : id(id), t(t) {}

Symbol::Symbol(const Symbol& _sym) : id(_sym.id), t(_sym.t) {}

SymList::SymList(const vector<Symbol> &symList) : symList(symList) {}

SymList::SymList() : symList() {}
