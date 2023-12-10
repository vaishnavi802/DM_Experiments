//3. Perform Binning of data.
#include <bits/stdc++.h>
using namespace std;

void binDataByMean(vector<int> &data, int numBins)
{
    // Calculate the mean
    int len = data.size();

    int binsize = len / numBins;
    int ite = 0, sum = 0;

    vector<int> binnedData;
    
    for (int i = 0; i < len; i++)
    {
        sum += data[i];
        if (i && !((i+1)%binsize) && i<=(numBins*binsize)) {
            sum = sum/binsize;
            for (int j=0; j<binsize; j++) {
                binnedData.push_back(sum);
            }
            sum = 0;
            
        }
    }

    int temp = binsize;
    int binctn = 1;
    cout << "Bin 1: " << endl;
    for (int i = 0; i < len; i++)
    {
        if (i && !((i)%binsize) && i < binnedData.size()) {
            binctn++;
            cout << "Bin " << binctn << ": " << endl;
        }
        if (i < binnedData.size()) cout << binnedData[i] << " ";
            else cout << data[i] << " ";
        cout << endl;
    }
    cout << endl;
    
}

int main()
{
    vector<int> data;
    int numBins;
    cout << "Enter Number of Bins: ";
    cin >> numBins;
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
    sort(data.begin(), data.end());
    binDataByMean(data, numBins);
    return 0;
}