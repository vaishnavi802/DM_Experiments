#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class ExcelSheet
{
public:
    vector<vector<string>> data;
    int max_row;

    ExcelSheet(string file_name)
    {
        ifstream file(file_name);
        string line;
        while (getline(file, line))
        {
            vector<string> row;
            size_t pos = 0;
            string token;
            while ((pos = line.find(",")) != string::npos)
            {
                token = line.substr(0, pos);
                row.push_back(token);
                line.erase(0, pos + 1);
            }
            row.push_back(line);
            data.push_back(row);
        }
        max_row = data.size(); // Set max_row here
    }

    string cell_value(int row, int col)
    {
        return data[row][col];
    }
};

// Function for finding correlation
double find_correlation(ExcelSheet &sheet_obj, int tid1, int tid2)
{
    int tid1_count = 0;
    int tid2_count = 0;
    int total_common_count = 0;

    for (int j = 1; j <= 7; ++j)
    {
        if (sheet_obj.cell_value(tid1, j) == "Y")
        {
            tid1_count += 1;
        }

        if (sheet_obj.cell_value(tid2, j) == "Y")
        {
            tid2_count += 1;
        }

        if (sheet_obj.cell_value(tid1, j) == "Y" && sheet_obj.cell_value(tid2, j) == "Y")
        {
            total_common_count += 1;
        }
    }

    if (tid1_count == 0 || tid2_count == 0)
    {
        return 0;
    }

    return static_cast<double>(total_common_count) / (tid1_count * tid2_count);
}


int main()
{
    ExcelSheet sheet_obj("exp9_input.csv");

    // number of transactions
    int n = 5; 

    vector<vector<string>> data;

    for (int i = 0; i < n; ++i) 
    {
        cout << "i = " << i << endl;
        for (int j = i + 1; j < n; ++j)
        {
            double ans = find_correlation(sheet_obj, i + 1, j + 1);
            string verdict;

            if (ans == 0)
            {
                verdict = "No relationship between entities";
            }
            else if (ans < 0)
            {
                verdict = "Negative correlation";
            }
            else if (ans > 0)
            {
                verdict = "Positive correlation";
            }
            else
            {
                verdict = "Not defined";
            }

            cout << "Correlation ratio " << i + 1 << " & " << j + 1 << " = " << ans << " " << verdict << endl;

            vector<string> row = {to_string(i + 1), to_string(j + 1), to_string(ans), verdict};
            data.push_back(row);
        }
    }

    ofstream output_file("exp9_output.csv");
    if (!output_file.is_open())
    {
        cout << "Error: Unable to open output file" << endl;
        return 1; // Return an error code
    }

    output_file << "item 1 with tid,item 2 with tid,Correlation coefficient,Type of correlation" << endl;

    for (const auto &row : data)
    {
        for (const auto &col : row)
        {
            output_file << col << ",";
        }
        output_file << endl;
    }

    output_file.close();

    return 0;
}