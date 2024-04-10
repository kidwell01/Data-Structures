#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;


int main()
{
    ifstream myfile;   
    map<string, int> WordCountMap;    
    string word;

    myfile.open("histogram.txt");   
    if (!myfile)
    {
        cout << "  file cannot not open! " << endl;
        return 1;
    }

    myfile >> word;       
    while (myfile)
    { 
        auto search = WordCountMap.find(word);   
        if (search != WordCountMap.end())
        {
            WordCountMap[word] = search->second + 1; 
        }
        else
        {
            WordCountMap[word] = 1;   
        }

        myfile >> word;   
    }

    
    for (map<string, int>::iterator i = WordCountMap.begin(); i != WordCountMap.end(); ++i)
    {
        cout << i->1 << "\t";
        for (int j = 0; j < i->2; j++)
            cout << "*";
        cout << i->2<< endl;
    }

    
    myfile.close();
    return 0;
}