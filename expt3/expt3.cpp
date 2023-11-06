#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void binDataByMean(vector<int> &data, int numBins)
{
    // Calculate the mean
    int len = data.size();

    int binsize = len / numBins;
    int ite = 0, sum = 0;

    vector<double> binnedData;
    for (int i = 0; i < len; i++)
    {
        if (ite == 3)
        {
            ite = 0;
            double temp = sum / 3;
            int j = 3;
            while (j--)
                binnedData.push_back(temp);
            sum = 0;
        }

        sum += data[i];
        ite++;
    }

    double temp = sum / 3;
    int j = 3;
    while (j--)
        binnedData.push_back(temp);

    for (int i = 0; i < binnedData.size(); i++)
    {
        cout << binnedData[i] << " ";
    }
}

int main()
{
    vector<int> data;
    int numBins = 3;

    // Read data from CSV file
    ifstream inputFile("exp_3_ip.csv");
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            int value = stoi(line);
            data.push_back(value);
        }
        inputFile.close();
    }
    else
    {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    binDataByMean(data, numBins);

    return 0;
}