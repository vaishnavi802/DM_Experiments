#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> 

using namespace std;

struct Data {
    string className;
    string category;
    int count;
};

int main() {
    vector<Data> data; 
    ifstream file("input.csv"); 
    if (!file.is_open()) {
        cerr << "Error in opening input file." << endl;
        return 1;
    }
    string line;
    while (getline(file, line)) {
        if (line.find("Class,Category,Count") != string::npos) {
            continue;
        }
        istringstream iss(line);
        string className, category, countStr;
        getline(getline(getline(iss, className, ','), category, ','), countStr, ',');
        Data entry;
        entry.className = className;
        entry.category = category;
        entry.count = stoi(countStr);
        data.push_back(entry);
    }

    vector<string> classes;
    vector<string> categories;

    for (const auto& entry : data) {
        if (find(classes.begin(), classes.end(), entry.className) == classes.end()) {
            classes.push_back(entry.className);
        }

        if (find(categories.begin(), categories.end(), entry.category) == categories.end()) {
            categories.push_back(entry.category);
        }
    }

    vector<vector<int>> counts(classes.size(), vector<int>(categories.size(), 0));

    for (const auto& entry : data) {
        int classIndex = distance(classes.begin(), find(classes.begin(), classes.end(), entry.className));
        int categoryIndex = distance(categories.begin(), find(categories.begin(), categories.end(), entry.category));
        counts[classIndex][categoryIndex] = entry.count;
    }

    vector<int> rowSums(classes.size(), 0);
    vector<int> colSums(categories.size(), 0);

    for (size_t i = 0; i < classes.size(); ++i) {
        for (size_t j = 0; j < categories.size(); ++j) {
            rowSums[i] += counts[i][j];
            colSums[j] += counts[i][j];
        }
    }

    vector<vector<double>> tWeights(classes.size(), vector<double>(categories.size()));
    vector<vector<double>> dWeights(classes.size(), vector<double>(categories.size()));

    for (size_t i = 0; i < classes.size(); ++i) {
        for (size_t j = 0; j < categories.size(); ++j) {
            tWeights[i][j] = (double)counts[i][j] / rowSums[i] * 100;
            dWeights[i][j] = (double)counts[i][j] / colSums[j] * 100;
        }
    }
    cout << "T-Weights:\n";
    for (size_t i = 0; i < tWeights.size(); ++i) {
        for (size_t j = 0; j < tWeights[i].size(); ++j) {
            cout << classes[i] << ", " << categories[j] << " (T-Weight): " << tWeights[i][j] << "%" << endl;
        }
    }

    cout << "\nD-Weights:\n";
    for (size_t i = 0; i < dWeights.size(); ++i) {
        for (size_t j = 0; j < dWeights[i].size(); ++j) {
            cout << classes[i] << ", " << categories[j] << " (D-Weight): " << dWeights[i][j] << "%" << endl;
        }
    }

    return 0;
}
