#pragma once
#include <memory>
#include "sqlite_orm.h"
#include "Records.h"

using namespace sqlite_orm;

auto makeStorage(const std::string& path);
using Storage = decltype(makeStorage(""));

class Database {
public:
    static Database& instance();
    Storage& storage();
private:
    Database();
    std::unique_ptr<Storage> storage_;
};
