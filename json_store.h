#ifndef JSON_STORE_H
#define JSON_STORE_H

#include <bits/stdc++.h>
#include <mutex>
using namespace std;

#define SNAPSHOT_DB "snapshot_db.json"
extern map<string,string> db;
extern mutex db_mutex;

void checkJson(const string &filename);
void loadJson(const string &filename);
void saveJson(const string &filename);

#endif
