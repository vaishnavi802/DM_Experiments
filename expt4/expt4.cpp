#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("exp4_input.csv");
    string line, word;
    string day,level, Routine, playGame,value;
    map<string, int> parent;
    map<string, map<string, int>> child;
    if (!file.is_open())
    {
        perror("Error in opening input file : ");
        return -1;
    }
    int i = 0;
    string childName;
    while (getline(file, line))
    {
        stringstream str(line); //convert a string to a file stream like object 
        getline(str, day, ',');
        getline(str,level,',');
        getline(str, Routine, ',');
        getline(str, playGame, ',');
        getline(str, value, ',');
        int choice;
        if (i == 0)
        {
            i++;
            cout << "Enter Child Column Number : ";
            cin >> choice;
            continue;
        }
        switch (choice)
        {
            case 1:
                childName = day;
                break;
            case 2: 
                childName = level;
                break;
            case 3:
                childName = Routine;
                break;
            case 4:
                childName = value;
                break;
            default:
                childName = Routine;
                break;
        }
        parent[playGame]++;
        child[childName][playGame]++;
    }
    double pos = parent["Yes"], neg = parent["No"];
    double total = pos + neg;
    // cout << pos << " " << neg << "\n";
    double parent_entropy = -((pos / total) * log2(pos / total) + (neg / total) * log2(neg / total));
    cout << "Parent Entropy: " << parent_entropy << "\n";
    double child_entropy = 0;
    for (auto p : child)
    {
        string val = p.first;
        double pR = child[val]["Yes"], nR = child[val]["No"];
        // cout << val << " " << pR << " " << nR << "\n";
        double tR = pR + nR;
        child_entropy += -((pR + nR) / total) * ((pR / tR) * log2(pR / tR) + (nR / tR) * log2(nR / tR));
    }
    cout << "Child Entropy * Their proportion : " << child_entropy << "\n";
    cout << "Info gain : " << parent_entropy - child_entropy << "\n";
    return 0;
}