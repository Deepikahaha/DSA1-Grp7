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

//function that puts the values into an array to perform selection sort
void toSelectionSort(int userInput[], int size){
  for (int i = 0; i < size - 1; i++){ //this outer loop goes through each element of the array and updates the minimum value 
//we then need to find the smallest element in the unsorted list
       int minIndex = i;
       for (int j = i + 1; j < size; j++){ //this inner loop looks for the smallest element in the unsorted indexes using comparision 

            if (userInput[j] < userInput[minIndex]){
                minIndex = j; // if condition is true, value is swapped
            }
       }  
       //Then swapping the smallest element that was found with the first element of the unsorted section
       swap(userInput[i],userInput[minIndex]);
    }

  }

  void toPrintArray(int userInput[], int size) {
	for (int i = 0; i <size; i++){
		cout << userInput[i] << " ";
	}
}

auto start = chrono::steady_clock::now();

int main(){
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
	
    //putting the user input values into the selection sort function
    toSelectionSort(userInput, size);
	
	//printing the sorted array
	cout << "The Sorted array of numbers is: ";
	toPrintArray (userInput, size);
 
cout << "\n";
auto end = chrono::steady_clock::now();
auto diff = end - start;
cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;
return 0;


}