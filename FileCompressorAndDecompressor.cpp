#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class File
{
private:
    string data;
    string compressedData;
    string decompressedData;

    string runLengthEncode(const string &enteredData)
    {
        string encodedData;
        int length = enteredData.length();
        for (int i = 0; i < length; i++)
        {
            int count = 1;
            while (i < length - 1 && enteredData[i] == enteredData[i + 1])
            {
                count++;
                i++;
            }
            encodedData += enteredData[i];
            encodedData += to_string(count);
        }
        return encodedData;
    }

    string runLengthDecode(const string &enteredData)
    {
        string decodedData;
        int length = enteredData.length();
        for (int i = 0; i < length; i++)
        {
            char ch = enteredData[i];
            i++;
            int count = enteredData[i] - '0';
            for (int j = 0; j < count; j++)
            {
                decodedData += ch;
            }
        }
        return decodedData;
    }

public:
    void CompressData()
    {
        cout << "Enter the data to compress: ";
        getline(cin, data);
        compressedData = runLengthEncode(data);
        cout << "Compressed Data: " << compressedData << endl;

        string outputFile;
        cout << "Enter the name of the output file to save compressed data: ";
        getline(cin, outputFile);
        ofstream outFile(outputFile, ios::app);

        if (outFile)
        {
            if (outFile.tellp() != 0)
            {
                outFile << "\n";
            }
            outFile << "Compressed data:\n"
                    << compressedData << endl;
            outFile.close();
            cout << "Compressed data has been written to " << outputFile << endl;
        }
        else
        {
            cout << "Unable to open the output file!" << endl;
        }
    }

    void DecompressData()
    {
        cout << "Enter the data to decompress: ";
        getline(cin, compressedData);
        decompressedData = runLengthDecode(compressedData);
        cout << "Decompressed Data: " << decompressedData << endl;

        string outputFile;
        cout << "Enter the name of the output file to save decompressed data: ";
        getline(cin, outputFile);
        ofstream outFile(outputFile, ios::app);

        if (outFile)
        {
            if (outFile.tellp() != 0)
            {
                outFile << "\n";
            }
            outFile << "Decompressed data:\n"
                    << decompressedData << endl;
            outFile.close();
            cout << "Decompressed data has been written to " << outputFile << endl;
        }
        else
        {
            cout << "Unable to open the output file!" << endl;
        }
    }
};

int main()
{
    File file;
    int choice;
    do
    {
        cout << "=================== Menu ===================\n1. Compress Data\n2. Decompress Data\n3. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            file.CompressData();
            break;
        case 2:
            file.DecompressData();
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
