#include "Database.h"

Database& Database::instance() {
    static Database db;
    return db;
}

Database::Database() {
    storage_ = std::make_unique<Storage>(std::move(makeStorage("recruitment.db")));
    storage_->sync_schema();
}

Storage& Database::storage() { return *storage_; }
