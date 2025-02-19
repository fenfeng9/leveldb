//
// Created by fenfeng9 on 25-2-19.
//
// simple_client.cpp
#include <iostream>
#include <string>

#include "leveldb/db.h"

int main() {
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "./db", &db);

  if (!status.ok()) {
    std::cerr << "Unable to open/create test database './db'" << std::endl;
    std::cerr << status.ToString() << std::endl;
    return -1;
  }

  std::string key;
  std::string value;
  std::string cmd;

  while (true) {
    std::cout << "leveldb> ";
    std::cin >> cmd;

    if (cmd == "set") {
      std::cin >> key >> value;
      status = db->Put(leveldb::WriteOptions(), key, value);
      if (status.ok()) {
        std::cout << "OK" << std::endl;
      } else {
        std::cout << "Error setting value: " << status.ToString() << std::endl;
      }
    } else if (cmd == "get") {
      std::cin >> key;
      status = db->Get(leveldb::ReadOptions(), key, &value);
      if (status.ok()) {
        std::cout << value << std::endl;
      } else {
        std::cout << "Not found" << std::endl;
      }
    } else if (cmd == "del") {
      std::cin >> key;
      status = db->Delete(leveldb::WriteOptions(), key);
      if (status.ok()) {
        std::cout << "OK" << std::endl;
      } else {
        std::cout << "Error deleting key: " << status.ToString() << std::endl;
      }
    } else if (cmd == "exit") {
      break;
    } else {
      std::cout << "Unknown command. Supported commands are: set, get, del, exit" << std::endl;
    }
  }

  delete db;
  return 0;
}