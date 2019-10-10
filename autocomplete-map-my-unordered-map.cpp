#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "List-ED.h"
#include "unordered_map-ED.h"

using namespace std;

bool ImportFile(const char * filename, List_ED<Records>& records);
void GenerateHashTable(unordered_map_ED &dictionary,const List_ED<Records> &records);
int main(int argc, char ** argv) {
    List_ED<Records> records;
    unordered_map_ED dictionary;   //declaring an unordered map with string keys and list values
    string search;
    stringstream arg2converter(argv[2]);
    stringstream arg3converter(argv[3]);
    int maxNumberOfWords, maxNumberOfCharacters;
    if(!(arg2converter >> maxNumberOfWords))
        maxNumberOfWords = 10;
    if(!(arg3converter >> maxNumberOfCharacters))
        maxNumberOfCharacters = 10;
    ImportFile(argv[1], records);   //saving all pairs from file into records lis
    GenerateHashTable(dictionary,records);
    cout << "Ask me which is most popular! " << endl;
    while(cin)
    {
        cin >> search;
        if(search.size()>maxNumberOfCharacters)
            search=search.substr(0,maxNumberOfCharacters);
        cout << "Top answers for '" << search << "' " << endl;
        int count=0;
        for(const auto x : dictionary.get(search))
        {
            if(count < maxNumberOfWords)
            {                   //is user entered string is a key in map then this code executes
                cout << count+1;
                cout << '\t' << x.word << ' ';
                cout << "(" << x.occ << ")" << endl;
                count++;
            }
        }
        if(count==0)
            cout << "No results" << endl;       //if no key corresponding to the user enter string exists
        cout << "Ask me for another autocomplete. " << endl;
    }
    return 0;
}
bool ImportFile(const char * filename, List_ED<Records>& records)
{
    ifstream fin;
    fin.open(filename);
    if(!fin)
    {
        cout << "No file has been opened";
        return false;
    }
    while(!fin.eof())
    {
        Records r;
        while(isspace(fin.peek()))
        {
            fin.ignore();
        }
        getline(fin, r.occ, '\t');
        getline(fin, r.word, '\n');
        fin.ignore();
        records.push_back(r);
    }
    fin.close();
    return true;
}



void GenerateHashTable(unordered_map_ED &dictionary,const List_ED<Records> &records) {


    for( auto i : records)
    {
        for(int j = 1; j <= i.word.size(); j++)
        {
            dictionary.push(i.word.substr(0, j), i);
        }
    }
}


