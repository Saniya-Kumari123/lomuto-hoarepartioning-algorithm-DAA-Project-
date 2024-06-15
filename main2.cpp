#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
// Function prototypes
int LomutoPartition(vector<int> &A, int l, int r, int &iterations);
int HoarePartition(vector<int> &A, int l, int r, int &iterations);
int QuickselectLomuto(vector<int> &A, int l, int r, int k, int &iterations);
int QuickselectHoare(vector<int> &A, int l, int r, int k, int &iterations);
void runPartitionAlgorithm(const string &filename, const string &algo);
void runQuickselectAlgorithm(const string &filename, const string &algo, int k);




int main()
{
    while (true)
    {
        string filename;
        int algo_choice;
        int k = 0;
        char choice;

        cout << "Enter the filename to read the numbers from (without extension): ";
        cin >> filename;
        filename += ".txt";

        cout << "Choose the algorithm to run:\n";
        cout << "1. Lomuto\n";
        cout << "2. Hoare\n";
        cout << "3. QuickselectLomuto\n";
        cout << "4. QuickselectHoare\n";
        cout << "5. Exit\n";
        cin >> algo_choice;

        string algo;
        switch (algo_choice)
        {
        case 1:
            algo = "Lomuto";
            break;
        case 2:
            algo = "Hoare";
            break;
        case 3:
            algo = "QuickselectLomuto";
            cout << "Enter the value of k: ";
            cin >> k;
            break;
        case 4:
            algo = "QuickselectHoare";
            cout << "Enter the value of k: ";
            cin >> k;
            break;
        case 5:
            cout << "Exiting the program." << endl;
            return 0;
        default:
            cout<<"Invalid algorithm choice!" << endl;
            continue;
        }

        if (algo == "Lomuto" || algo == "Hoare")
        {
            runPartitionAlgorithm(filename, algo);
        }
        else if (algo == "QuickselectLomuto" || algo == "QuickselectHoare")
        {
            runQuickselectAlgorithm(filename, algo, k);
        }

        cout << "Do you want to continue? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y')
        {
            break;
        }
    }
    return 0;
}

// Lomuto partition implementation
int LomutoPartition(vector<int> &A, int l, int r, int &iterations)
{
    int pivot = A[r];
    int i = l - 1;
    for (int j = l; j < r; j++)
    {
        iterations++;
        if (A[j] < pivot)
        {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

// Hoare partition implementation
int HoarePartition(vector<int> &A, int l, int r, int &iterations)
{
    int pivot = A[l + (r - l) / 2];
    int i = l - 1, j = r + 1;
    while (true)
    {
        do
        {
            i++;
            iterations++;
        } while (A[i] < pivot);
        do
        {
            j--;
            iterations++;
        } while (A[j] > pivot);
        if (i >= j)
            return j;
        swap(A[i], A[j]);
    }
}

// Quickselect using Lomuto partition
int QuickselectLomuto(vector<int> &A, int l, int r, int k, int &iterations)
{
    if (l == r)
        return A[l];
    int pivotIdx = LomutoPartition(A, l, r, iterations);
    int length = pivotIdx - l + 1;
    if (k < length)
        return QuickselectLomuto(A, l, pivotIdx - 1, k, iterations);
    else if (k > length)
        return QuickselectLomuto(A, pivotIdx + 1, r, k - length, iterations);
    else
        return A[pivotIdx];
}

// Quickselect using Hoare partition
int QuickselectHoare(vector<int> &A, int l, int r, int k, int &iterations)
{
    if (l == r)
        return A[l];
    int pivotIdx = HoarePartition(A, l, r, iterations);
    int length = pivotIdx - l + 1;
    if (k < length)
        return QuickselectHoare(A, l, pivotIdx, k, iterations);
    else if (k > length)
        return QuickselectHoare(A, pivotIdx + 1, r, k - length, iterations);
    else
        return A[pivotIdx];
}

void runPartitionAlgorithm(const string &filename, const string &algo)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Error opening file " << filename << endl;
        return;
    }

    vector<int> numbers;
    int number;
    while (inFile >> number)
    {
        numbers.push_back(number);
    }
    inFile.close();

    int iterations = 0;

    auto start = chrono::high_resolution_clock::now();

    if (algo == "Lomuto")
    {
        LomutoPartition(numbers, 0, numbers.size() - 1, iterations);
    }
    else if (algo == "Hoare")
    {
        HoarePartition(numbers, 0, numbers.size() - 1, iterations);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << duration.count() << endl;

    ofstream outFile(algo + ".txt", ios::app);
    if (!outFile)
    {
        cerr << "Error opening output file" << endl;
        return;
    }
    outFile << numbers.size() << "|" << fixed << setprecision(15) << duration.count() << "|" << iterations << "\n";
    outFile.close();
}

void runQuickselectAlgorithm(const string &filename, const string &algo, int k)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Error opening file " << filename << endl;
        return;
    }

    vector<int> numbers;
    int number;
    while (inFile >> number)
    {
        numbers.push_back(number);
    }
    inFile.close();

    int iterations = 0;

    auto start = chrono::high_resolution_clock::now();

    if (algo == "QuickselectLomuto")
    {
        QuickselectLomuto(numbers, 0, numbers.size() - 1, k - 1, iterations);
    }
    else if (algo == "QuickselectHoare")
    {
        QuickselectHoare(numbers, 0, numbers.size() - 1, k - 1, iterations);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << duration.count() << endl;

    ofstream outFile(algo + ".txt", ios::app);
    if (!outFile)
    {
        cerr << "Error opening output file" << endl;
        return;
    }
    outFile << numbers.size() << "|" << fixed << setprecision(15) << duration.count() << "|" << iterations << "\n";
    outFile.close();
}
