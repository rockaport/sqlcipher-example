#include <iostream>
#include <sqlcipher/sqlite3.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    sqlite3 *database;
    char *errorMessage;
    auto filename = "database.db";
    auto ret = sqlite3_open(filename, &database);

    if (ret != SQLITE_OK) {
        std::cerr << "failed to open database: " << filename
                  << " error: " << sqlite3_errmsg(database) << std::endl;
        sqlite3_close(database);
        exit(ret);
    }

    auto databaseKey = std::string("password");
    ret = sqlite3_key(database, databaseKey.c_str(), databaseKey.length());

    if (ret != SQLITE_OK) {
        std::cerr << "failed to key database: " << filename
                  << " error: " << sqlite3_errmsg(database) << std::endl;
        sqlite3_close(database);
        exit(ret);
    }

    ret = sqlite3_exec(database, "select count(*) from sqlite_master;", nullptr, nullptr, &errorMessage);

    if (ret != SQLITE_OK) {
        std::cerr << "failed to open database after keying error: " << sqlite3_errmsg(database) << std::endl;
        sqlite3_close(database);
        exit(ret);
    }


    ret = sqlite3_exec(database, "create table if not exists sample (id integer primary key, name text not null);",
                       nullptr, nullptr, &errorMessage);

    if (ret != SQLITE_OK) {
        std::cerr << "failed to create table error: " << sqlite3_errmsg(database)
                  << " error: " << errorMessage << std::endl;
        sqlite3_close(database);
        exit(ret);
    }

    ret = sqlite3_exec(database, "insert into sample (name) values ('hello');", nullptr, nullptr, &errorMessage);

    if (ret != SQLITE_OK) {
        std::cerr << "failed to insert into table error: " << sqlite3_errmsg(database)
                  << " error: " << errorMessage << std::endl;
        sqlite3_close(database);
        exit(ret);
    }

    ret = sqlite3_close(database);

    if (ret != SQLITE_OK) {
        std::cerr << "failed to close database error: " << sqlite3_errmsg(database) << std::endl;
        exit(ret);
    }
    return 0;
}