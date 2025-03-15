#include <iostream>
#include <cstdlib> // used for random generator and seed for random number generator
// i.e. rand() and srand()
// rand() generates the same sequence but srand() generates different numbers
#include <ctime> //for time(), helps create randomness when used with srand()
#include <chrono> //to calculate time taken to execute

using namespace std;

// Function to generate random numbers between 1 and 100
void toGenerateRandomIntegers(int userInput[], int size){
    srand(time(0)); // Seed the random number generator with the current time used for random number generation
    for (int i = 0; i < size; i++){
        userInput[i] = rand() % 100 + 1; // Generate a random number and store it in the array
    }
}

// Function to print the array elements
void toPrintArray(int userInput[], int size) {
    for (int i = 0; i < size; i++){
        cout << userInput[i] << " ";
    }
    cout << endl;
}

// Function to merge two sorted halves of an array
void toMerge(int userInput[], int left, int mid, int right){
    int lSize = mid - left + 1;  // since the index starts from 0 in the left, we add 1 to find the exact size of the splitted part
    int rSize = right - mid;  //since right half starts from mid + 1, we don't need to add +1
    int leftSortPart[lSize], rightSortPart[rSize];

    // Copy elements to temporary arrays
    for (int i = 0; i < lSize; i++) {
        leftSortPart[i] = userInput[left + i];//divided according to the main user input size of array
    }
    for (int i = 0; i < rSize; i++) {
        rightSortPart[i] = userInput[mid + 1 + i]; //temporary right sorted part of the original array which starts from mid + 1
    }

    int i = 0, j = 0, k = left;
    // Merge the two sorted halves back into the main array
    while (i < lSize && j < rSize){
        if (leftSortPart[i] < rightSortPart[j])
            userInput[k++] = leftSortPart[i++];
        else
            userInput[k++] = rightSortPart[j++];
    }
    while (i < lSize) userInput[k++] = leftSortPart[i++];
    while (j < rSize) userInput[k++] = rightSortPart[j++];
}

// Function to perform Merge Sort
void toMergeSort(int userInput[], int left, int right){
    if (left < right){
        int mid = (left + right)/2; // Find the middle index
        toMergeSort(userInput, left, mid); // Sort left half
        toMergeSort(userInput, mid + 1, right); // Sort right half
        toMerge(userInput, left, mid, right); // Merge the sorted halves
    }
}

// Function to perform Selection Sort
void toSelectionSort(int userInput[], int size){
    for (int i = 0; i < size - 1; i++){
        int minIndex = i; // Assume the first element is the smallest
        for (int j = i + 1; j < size; j++){
            if (userInput[j] < userInput[minIndex]) minIndex = j; // Find the smallest element
        }
        swap(userInput[i], userInput[minIndex]); // Swap the smallest element to its correct position
    }
}

// Function to perform QuickSort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high], i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) swap(arr[++i], arr[j]);
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to perform Interpolation Search
int interpolationSearch(int arr[], int n, int key) {
    int start = 0, end = n - 1;
    while (start <= end && key >= arr[start] && key <= arr[end]) {
        int pos = start + ((key - arr[start]) * (end - start)) / (arr[end] - arr[start]);
        if (pos < start || pos > end) return -1;
        if (arr[pos] == key) return pos; // If key is found, return the index
        if (arr[pos] < key) start = pos + 1; // Search in the right half
        else end = pos - 1; // Search in the left half
    }
    return -1; // Return -1 if not found
}

int main() {
    // Loop to execute three sorting/searching algorithms one after another
    for (int i = 0; i < 3; i++) {
        // Display the algorithm name
        // This line sets the 'algo' string based on the value of 'i'
// If i == 0, 'algo' is "Merge Sort"
// If i == 1, 'algo' is "Selection Sort"
// Otherwise, for i == 2, 'algo' is "Interpolation Search"
        string algo = (i == 0) ? "Merge Sort" : (i == 1) ? "Selection Sort" : "Interpolation Search";
        cout << algo << "\nEnter a number of integers: ";
        int size;
        cin >> size;
        int *userInput = new int[size]; // Dynamically allocate array
        toGenerateRandomIntegers(userInput, size); // Generate random numbers

        cout << "Generated Numbers: ";
        toPrintArray(userInput, size);

        auto start = chrono::steady_clock::now(); // Start timing

        if (i == 0) {
            toMergeSort(userInput, 0, size - 1); // Perform Merge Sort
        } else if (i == 1) {
            toSelectionSort(userInput, size); // Perform Selection Sort
        } else {
            quickSort(userInput, 0, size - 1); // Sort using QuickSort before searching
            cout << "Sorted Numbers: ";
            toPrintArray(userInput, size);
            cout << "Enter a number to search: ";
            int key;
            cin >> key;
            int index = interpolationSearch(userInput, size, key); // Perform Interpolation Search
            if (index != -1) cout << "Element found at index: " << index << endl;
            else cout << "Element not found!" << endl;
        }

        if (i != 2) {
            cout << "Sorted Numbers: ";
            toPrintArray(userInput, size); // Print sorted array for sorting algorithms
        }

        auto end = chrono::steady_clock::now(); // End timing
        auto diff = end - start;
        cout << chrono::duration<double, milli>(diff).count() << " ms" << endl << endl; // Display execution time

        delete[] userInput; // Free allocated memory
    }
    return 0;
}