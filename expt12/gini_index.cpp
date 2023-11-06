#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

double calculateGini(string subClass, vector<map<string, string>> data)
{
    double totalRecords = data.size();
    double giniIndex = 1.0;

    unordered_set<string> uniqueValues;

    for (const auto &row : data)
    {
        uniqueValues.insert(row.at(subClass));
    }

    for (const auto &value : uniqueValues)
    {
        double probability = 0.0;
        for (const auto &row : data)
        {
            if (row.at(subClass) == value)
            {
                probability += 1;
            }
        }
        probability /= totalRecords;
        giniIndex -= probability * probability;
    }

    return giniIndex;
}

int main()
{
    vector<map<string, string>> data;

    ifstream file("gini_ip.csv");

    if (!file.is_open())
    {
        perror("Error in opening input file : ");
        return -1;
    }

    string line, word;
    string weekend, weather, parents, money, decision;

    int j = 0;
    while (getline(file, line))
    {
        stringstream str(line);

        getline(str, weekend, ',');
        getline(str, weather, ',');
        getline(str, parents, ',');
        getline(str, money, ',');
        getline(str, decision, ',');

        if (j == 0)
        {
            j++;
            continue;
        }

        map<string, string> row;
        row["Weekend"] = weekend;
        row["Weather"] = weather;
        row["Parents"] = parents;
        row["Money"] = money;
        row["Decision"] = decision;

        data.push_back(row);
    }

    file.close();

    string mainClass = "Decision";
    double giniMainClass = calculateGini(mainClass, data);
    cout << "Main Class Gini Index: " << giniMainClass << endl;


    int maxi=0;
    string subclassMax="";

    for (const auto &subClass : data[0])
    {
        if (subClass.first != mainClass)
        {
            double giniSubClass = calculateGini(subClass.first, data);
            cout << "Gini Index for " << subClass.first << ": " << giniSubClass << endl;

            if (giniSubClass > maxi)
            {
                maxi=giniSubClass;
                subclassMax=subClass.first;
            }
        }

    }

    cout << "Subclass : " << subclassMax << " has maximum gini index. Hence it will be selected as root for splitting";

        // Subclass : Weather has maximum giniIndex . Hence it will be selected as root for splitting.

        return 0;
}
