#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Records
{
    string occ;
    string word;
};

class unordered_map_ED {
private:
    vector<pair<string,vector<Records> > > hashtable;
    int capacity;
    int size;
    void resize(){
        if(size<capacity)
            return;
        capacity*=2;
        vector<pair<string,vector<Records> > > oldhashtable(hashtable.begin(),hashtable.end());
        hashtable.clear();
        hashtable.resize(capacity);
        for(int i=0;i<oldhashtable.size();i++){
            for(int j=0;j<oldhashtable[i].second.size();j++)
                push(oldhashtable[i].first,oldhashtable[i].second[j]);
        }
    }

    uint64_t hashing(string key){
        uint64_t hash = 0xcbf29ce484222325; // FNV_offset_basis
        while(key.length())
        {
            char mm = key[0];
            key.erase(0,1);

            hash = hash ^ mm;
            hash = hash * 1099511628211; // FNV_prime
        }
        return (hash % capacity);
    }

public:

    unordered_map_ED(){
        size=0;
        capacity=8;
        hashtable.resize(capacity);
    }

    vector<Records> get(string key){
        int it = hashing(key);
        int foundindex = -1;
        while(!hashtable[it].second.empty()){
            if(key == hashtable[it].first){
                foundindex = it;
                break;
            }
            it++;
            if(it==capacity)
                it=0;
        }
        if(foundindex != -1)
            return hashtable[foundindex].second;
        return {};
    }

    void push(string key,Records record){
        int it = hashing(key);
        while(hashtable[it].first != ""){

            if(key == hashtable[it].first)
                break;
            it++;
            if(it == capacity)
                it=0;
        }
        if(hashtable[it].first == ""){

            size++;
            resize();
        }
        hashtable[it].first = key;
        hashtable[it].second.push_back(record);
    }

};

