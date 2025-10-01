#include <bits/stdc++.h>
#include <mutex>
#include "json_store.h"

using namespace std;

map<string, string> db;
mutex db_mutex;

void checkJson(const string &filename){
    ifstream fin(filename);
    if(!fin.good()){
        ofstream fout(filename);
        fout << "{}" << endl;
        fout.close();
        cout << "No SNAPSHOT DB previously existed, creating a new JSON DB: " << filename << endl;
    }
}

void loadJson(const string &filename){
    ifstream fin(filename);
    if(!fin.is_open()){
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string content((istreambuf_iterator<char>(fin)), {});
    fin.close();
    int pos=0;
    while(true){
        int keyStart=content.find('"', pos);
        if(keyStart==string::npos) break;
        int keyEnd=content.find('"', keyStart+1);
        int valStart=content.find('"', keyEnd+1);
        int valEnd=content.find('"', valStart+1);
        string key=content.substr(keyStart+1, keyEnd-keyStart-1);
        string val=content.substr(valStart+1, valEnd-valStart-1);
        db[key]=val;
        pos=valEnd+1;
    }
    cout << "Loaded DB from " << filename << endl;

}

void saveJson(const string &filename){
    ofstream fout(filename);
    if(!fout.is_open()){
        cout << "Error opening file: " << filename << endl;
        return;
    }
    fout << "{" << endl;
    for(auto it=db.begin(); it!=db.end(); it++){
        cout << it->first << " " << it->second << endl;
        fout << "  \"" << it->first << "\": \"" << it->second << "\"";
        if(next(it)!=db.end()){
            fout << ",";
        }
        fout << endl;
    }
    fout << "}" << endl;
    fout.close();
    cout << "Database saved to " << filename << endl;
}

