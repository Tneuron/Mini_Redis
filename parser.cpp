#include <bits/stdc++.h>
#include "json_store.h"
using namespace std;

string set_key(string key, string value){
    lock_guard<mutex> lock(db_mutex);
    db[key]=value;
    saveJson(SNAPSHOT_DB);
    return "OK";
}
string get_val(string key){
    lock_guard<mutex> lock(db_mutex);
    if(db.find(key)==db.end()){
        return "NIL";
    }
    else{
        saveJson(SNAPSHOT_DB);
        return db[key];
    }
}
string del_key(string key){
    lock_guard<mutex> lock(db_mutex);
    if(db.find(key)==db.end()){
        return "NIL";
    }
    else{
        db.erase(key);
        saveJson(SNAPSHOT_DB);
        return "OK";
    }
}

string parseString(string input){
    cout << "> ";
    stringstream ss(input);
    string command, key, value;
    ss >> command >> key >> value;
    if(command=="SET"){
        return set_key(key,value);
    }
    else if(command=="GET"){
        return get_val(key);
    }
    else if(command=="DEL"){
        return del_key(key);
    }
    else if(command=="SAVE"){
        return "SAVED";
    }
    else if(command=="EXIT"){
        return "DONE";
    }
    else{
        return "Invalid Command";
    }
}