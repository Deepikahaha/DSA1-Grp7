#include <iostream>
#include <cstdlib> // used for random generator and seed for random number generator
// i.e. rand() and srand()
// rand() generates the same sequence but srand() generates different numbers
#include <ctime> //for time(), helps create randomness when used with srand()
#include <chrono> //to calculate time taken to execute

using namespace std;

void toGenerateRandomIntegers(int userInput[], int size){
	srand(time(0)); //seed that is used for random number generation

	for (int i = 0; i < size; i++){
		userInput[i] = rand() % 100 + 1; //generates a number between 1 and 100
	}
}

void toMerge(int userInput[], int left, int mid, int right){
   int lSize = mid - left + 1; // since the index starts from 0 in the left, we add 1 to find the exact size of the splitted part
   int rSize = right - mid; //since right half starts from mid + 1, we don't need to add +1
   
   int leftSortPart[lSize], rightSortPart[rSize]; //making temporary arrays for the left and right parts

   for (int i = 0; i < lSize; i++){
	leftSortPart[i] = userInput[left + i]; //divided according to the main user input size of array
   } 
   for (int i = 0; i< rSize;i++){
	rightSortPart[i] = userInput[mid + 1 + i]; //temporary right sorted part of the original array which starts from mid + 1
   }

   // To merge the two halves back into the original array
   int i = 0, j = 0, k = left; 
   // here "i" is used to compare elements in certain indexes of the left array
    // here "j" is used to compare elements in certain indexes of the right array
    // here "k" is used as the merged final array where the sorted elements are kept    

	while ( i < lSize && j < rSize){  // to make sure the arrays don't exceed their size
    if (leftSortPart[i] < rightSortPart[j]){
		userInput[k] = leftSortPart[i]; // compares the values of right and left sorted arrays and puts the smaller one in merged array
		i++; //increments to compare another value in the left sorted array
	}
	else {
		userInput[k] = rightSortPart[j]; //puts the right part elements to the merged array
		j++; //increments the index and compares the next two elements
	}
	k++; //the size of the merged array keeps on increasing according to the values being put in them
	}

	// there might be cases where both arrays might not have the same size 
	// So, to prevent missing elements from printing after comparision part is exhaused
	// we copy the remaining elements

	while (i < lSize) userInput[k++] = leftSortPart[i++]; //remaining values of left part is put if size is not fulfilled
	while (j < rSize) userInput[k++] = rightSortPart[j++]; //remaining values of right part is put if size is not fulfilled
	
}

void toMergeSort(int userInput[], int left, int right){
if (left<right){
	int mid = (left + right)/2; //used to find the index in the array where the array is split from


	//recursively or continuously makes halves of the array
	toMergeSort(userInput, left, mid);
	toMergeSort(userInput, mid + 1 , right);

    // to merge sorted halves
	toMerge ( userInput, left, mid, right);
}
}
 
void toPrintArray(int userInput[], int size) {
	for (int i = 0; i <size; i++){
		cout << userInput[i] << " ";
	}
}

auto start = chrono::steady_clock::now();

int main() {
	cout << "Enter a number of integers: " << endl;
	//asks user to input the size of the array and fix its size
	int size;
	cin >> size;
	int *userInput = new int[size]; // saves the user input into a dynamically stored array    
	
	//function to generate the random numbers  
	toGenerateRandomIntegers (userInput, size);

    // to print the generated numbers
	cout << "The " << size << " random numbers are: ";
	toPrintArray ( userInput, size );
    cout<< endl;
	
	//performing merge sort on the array
	toMergeSort(userInput, 0, size - 1);
	
	//printing the sorted array
	cout << "The Sorted array of numbers is: ";
	toPrintArray (userInput, size);
    

    //To free the dynamically allocated memory
	delete[] userInput;

cout << "\n";
auto end = chrono::steady_clock::now();
auto diff = end - start;
cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;
return 0;


}