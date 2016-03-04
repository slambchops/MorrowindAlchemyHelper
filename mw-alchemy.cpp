#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using namespace std;

#define INGREDIENTS_FILE "mw-ingredients.info"

int main(int argc, char *argv[])
{
    bool found;
    ifstream in;
    int ingrNum;
    map<string, vector<string> > ingrList;
    map<string, vector<string> >::iterator it;
    string effect, line, key;
    vector<string> tokens;

    if (argv[1] == NULL)
    {
        effect = "blind";
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            if (argv[i] != NULL)
            {
                effect += argv[i];
                if (i < (argc-1))
                {
                    effect += " ";
                }
            }

        }
    }

    cout << "Trying to find ingredients for " << effect << "TEST\n";

    //Open the ingredients file
    in.open(INGREDIENTS_FILE);
    if (in.fail())
    {
        cout << "Could not open " << INGREDIENTS_FILE;
        return -1;
    }

    //create map of ingredients and their properties
    while (!in.eof())
    {
        //Get a line from the text file. This first line will be the key
        //(aka ingredient name)
        getline(in, key);
        transform(key.begin(), key.end(), key.begin(), ::tolower);
        //Now get the next line, which will be the first effect
        getline(in, line);
        //Loop through all the effects and store them until empty line is found
        while (!line.empty())
        {
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            //Put the effect into the vector
            ingrList[key].push_back(line);
            //Get a new line
            getline(in, line);
        }
        key.clear();
        line.clear();
    }

    for (it = ingrList.begin(); it != ingrList.end(); it++)
    {
        ingrNum = ingrList[it->first].size();
        for (int i = 0; i < ingrNum; i++)
        {
            if (effect.compare(ingrList[it->first][i]) == 0)
            {
                cout << it->first << "\n";
            }
        }
    }

    return 0;
}
