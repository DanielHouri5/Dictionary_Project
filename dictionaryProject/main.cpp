#include <iostream>
#include <cstring>
using namespace std;
#define zero 0
#define one 1
#define two 2
#define three 3
#define maxCharsOfWord 81
#define maxCharsOfDefinition 201
#define wordPos 0
#define definitionPos 1
#define lowPosition 0
#define highPosition 1
#define minSmallLetter 'a'
#define maxSmallLetter 'z'
#define minCapitalLetter 'A'
#define maxCapitalLetter 'Z'
#define point '.'
#define space ' '
//********************************************************************************
int dictSize();
void createDict(char**** pDict, int size);
void createWords(char*** pDict, int size);
void createWord(char*** pDict);
void fill(char** pDict, int length, int sign);
void fixAllStrings(char*** dict,char*** lastAddress, int sign);
void fixString(char* dict, int sign);
void mainSort(char*** dict, char** start, char** end, int low, int high, int size);
int quickSort(char*** dict, char** temp1, char** temp2, int low, int high, int size, int signTemp1);
void swapStrings(char** temp1, char** temp2);
int sameWords(char**** dict, int size);
void createNewDict(char**** newDict, char**** dict, int size);
void chooseWord(char*** dict, int size);
void binarySearch(char*** dict, char word[], int low, int high);
void deleteDict(char*** dict, int size);
//********************************************************************************
int main()
{
    int size = dictSize();//Declare the variable 'size' and put a number representing the number of words the user wants the dictionary to have in 'size'.
    char*** dict = nullptr;//Declare a dynamic 3D array 'dict' and initialize it to null.
    createDict(&dict, size);//A call to a function that will insert words into 'dict'.
    int newSize = sameWords(&dict, size);//Declare the variable 'size' and put the value that the function 'sameWords' returns.
    char*** newDict = NULL;//Declare a dynamic 3D array 'newDict' and initialize it to null.
    newDict = new char**[newSize];//Initializes it to be size 'newSize' and initialize each cell in 'newDict' to be of type pointer to pointer (a pointer to an array and each cell in this array points to a string).
    createNewDict(&newDict,&dict, size);//A call to a function that will copy from the old array to the new array all the values that are not marked with null.
    mainSort(newDict, *newDict, *(newDict+newSize-one), zero, newSize-one, newSize);//A call to a function that will sort the array using the efficient quick sort method.
    chooseWord(newDict, newSize);//A call to a function that will ask the user to enter a word and after entering the word will look for it in the array and show him its description if it is found.
    deleteDict(newDict, newSize);//A call to a function that will delete 'newDict' and release all the memory it occupied.
    newDict = NULL;//Put null in 'newDict'.
    deleteDict(dict, size);//A call to a function that will delete 'dict' and release all the memory it occupied.
    dict = NULL;//Put null in 'dict'.
    return 0;
}
//********************************************************************************
/*This function asks the user to choose how many words he wants to be in the
  dictionary and asks repeatedly until a proper value bigger than zero is
  obtained and returns this value at the end of the function.*/
int dictSize()
{
    int size;//Declaration of the variable 'size'.
    do {
        cout << "Please enter the number of words in the dictionary" << endl;
        cin >> size;//Put the entered value into 'size'.
    } while (size <= zero);//Asks repeatedly until a proper value bigger than zero is obtained.
    return size;//The function returns the value of 'size'.
}
//********************************************************************************
/*This function receives the address of a three-dimensional array and its size
  and calls the functions that enter which words and descriptions, standardizes
  and arranges it according to the instructions in the task.*/
void createDict(char****dict, int size)
{
    *dict = new char**[size];//Initializes it to be size 'size' and initialize each cell in 'dict' to be of type pointer to pointer (a pointer to an array and each cell in this array points to a string).
    createWords(*dict, size);//Calling a function that puts words and their description into the 'dict'.
    fixAllStrings(*dict, *dict+size, wordPos);//A call to a function that corrects all the words in the array according to the instructions in the task.
    fixAllStrings(*dict, *dict+size, definitionPos);//A call to a function that corrects all the description of the words in the array according to the instructions in the task.
}
//********************************************************************************
/*This function accepts a three-dimensional array and its size and inserts words
  and their description into it.*/
void createWords(char*** dict, int size)
{
    int index = 0;//Declare the variable index which represents the cell in the array into which the function inserts a word and initialize it to zero.
    fflush(stdin);//Clearing the buffer.
    while (index < size)//The loop will run and the function will continue to insert words and their description into the array until it fill all the cells of the array.
    {
        *(dict+index) = nullptr;//Initialize the cell we are working on at null.
        createWord(dict+index);//A call to a function that will take a word and its description from the user and put them in 'dict'.
        ++index;
    }
}
//********************************************************************************
/*This function receives a three-dimensional array and enters each cell in the
  array and initializes the address found there to point to a dynamic array of
  size 2 that points to addresses of strings and puts the word into the zero
  cell in the array and its description into the one cell.*/
void createWord(char*** dict)
{
    *dict = new char*[two];//Initialize each address of the array to point to a dynamic array of size 2 that points to addresses of strings.
    cout << "Please enter a word:" << endl;//A customized message of a request to insert a word.
    fill(*dict, maxCharsOfWord, wordPos);//A call to a function that will insert the word into the 'dict'.
    cout << "Please enter the definition of the word:" << endl;//A customized message of a request to insert the description of the word.
    fill(*dict, maxCharsOfDefinition, definitionPos);//A call to a function that will insert the word into the 'dict'.
}
//********************************************************************************
/*This function gets the address that is inside each of the cells of 'dict',
  the maximum number of characters that can be inserted (for a word - 80 characters, for a description - 200 characters)
  and the index of the cell in the array of size 2 that points to strings (at index 0 the word will be inserted and at
  index 1 its description will be inserted),and enters each cell the word and its description respectively and corrects
  the word that will take up space in the memory as its exact number of characters.*/
void fill(char** dict, int length, int sign)
{
    char temp[length];//Creating a static array 'temp' of char type that represents the word or description the user will enter.
    cin.getline(temp, length);//Enter the word or description that the user will enter into 'temp'.
    dict[sign] = new char[strlen(temp)+one];//Creating a dynamic array of character type to be the size of the number of characters of the word or description the user entered plus one(for null).
    strcpy(dict[sign], temp);//Copying the word or description that is in the static array 'temp' into the dynamic array
}
//********************************************************************************
/*This recursive function receives a dynamic three-dimensional array, the cell after the last cell in the array and a value representing
  the cell in the array to which the address in the main array points (0 - the word, 1 - the description of the word) and fixes
  the word to have a capital first letter and all other letters to be lowercase letters And if there are other characters, she
  leaves them as they are, and corrects the sentence to have a capital letter in the first letter of the first word in each
  sentence (the first letter of the description and every letter that comes after a period, then a space) and all other letters
  to be lowercase letters, and if there are other characters, she leaves them as they are.*/
void fixAllStrings(char*** dict,char*** lastAddress, int sign)
{
    if (dict == lastAddress)//The function ends when it reaches the cell after the last cell in the array.
        return;
    if (**(*dict+sign) >= minSmallLetter && **(*dict+sign) <= maxSmallLetter)//Checking whether the first letter is a lowercase letter.
        **(*dict+sign) -= (minSmallLetter - minCapitalLetter);//Converting the first letter from lowercase to uppercase.
    fixString(*(*dict+sign)+one, sign);//A call to a function that will fix all other characters in the word or description.
    fixAllStrings(dict+one, lastAddress, sign);//Recursively call this function to move to the next cell to fix the next word or description.
}
//********************************************************************************
/*This function accepts the continuation of the characters in the word or description and a value representing
  whether it is a word or a sentence (0 - word, 1 - sentence) and corrects them accordingly.*/
void fixString(char* dict, int sign)
{
    if (*dict == '\0')//The function will end when it reaches the character null.
        return;
    if (*dict == point && *(dict+one) == space && *(dict+two) >= minSmallLetter && *(dict+two) <= maxSmallLetter)//Checking whether we have reached the beginning of a sentence in the description and the letter is a lowercase letter (a point then a space then a lowercase letter).
    {
        *(dict+two) -= (minSmallLetter - minCapitalLetter);//Converting the first letter from lowercase to uppercase.
        fixString(dict+three, sign);//A recursive call to the function to continue checking and correcting the characters following the first letter in the sentence.
    }
    else//If we don't have reached the beginning of a sentence in the description or the letter is not a lowercase letter (is not a point or then is not a space or then is not a lowercase letter).
    {
        if (*dict == point && *(dict+one) == space)//Checking whether we have reached the end of a sentence and there is a capital letter in the next sentence (a point, then a space, then a capital letter).
            fixString(dict+three, sign);//A recursive call to this function to fix the continuation of the characters that come after the first letter of the next sentence.
        else//If we don't have reached the end of a sentence and there is a capital letter in the next sentence (is not a point or then is not a space).
        {
            if(*dict >= minCapitalLetter && *dict <= maxCapitalLetter)//Checking whether the letter we are checking now is a capital letter.
                *dict += (minSmallLetter - minCapitalLetter);//Correcting this letter to be a lowercase letter.
            fixString(dict+one, sign);//Recursively call this function to continue correcting the remaining characters following the word or description.
        }
    }
}
//********************************************************************************
/*This function receives the dynamic three-dimensional array after the user has entered words and their description
  after they have been corrected by the program and also receives its size, the function marks all words that
  are found more than once in the array except for their first occurrence at about null.
  The function returns the size of the new dict.*/
int sameWords(char**** dict, int size)
{
    int length = 0;//Declare the variable 'length' and initialize it to zero.
    for (int i = 0; i < size-one; ++i)//The function will run on each of the cells of the array and check if there are words in the array equal to the word in this cell.
    {
        if ((*dict)[i][0] != nullptr)//Checking whether the value null has not already been placed in the place of the word we now want to check.
            for (int j = i+1; j < size; ++j)//The function will run every time from the word that is in the place after the word we are checking to the end of the array.
                if ((*dict)[j][0] != nullptr)//Checking whether the value null has not already been placed in the place of the word we now want to check with.
                    if (strcmp((*dict)[i][0], (*dict)[j][0]) == 0)//Checking whether the word we are now checking if there are other such words is equal to the word we want to check with.
                    {
                        (*dict)[j][0] = nullptr;//Put null where the identical word is.
                        ++length;//Counting how many words marked with null.
                    }
    }
    return size - length;//The variable length is equal to the size of the current array minus the number of words we want to delete (the number of words we marked with null).
}
//********************************************************************************
/*This function receives the three-dimensional array we marked,
  and the size of the old array,
  this function creates a new dynamic three-dimensional array,
  inserts into it all the words not marked with null.*/
void createNewDict(char**** newDict, char**** dict, int size)
{
    int index = 0;//Declare the variable index which represents the cell in the array into which the function inserts a word and initialize it to zero.
    for (int i = 0; i < size; ++i)//The loop will run until the end of the array 'dict'.
    {
        if ((*dict)[i][wordPos]  != nullptr)//Checking whether the value in the array was marked with null.
        {
            (*newDict)[index] = new char*[two];//Initialize each address of the array 'newDict' to point to a dynamic array of size 2 that points to addresses of strings.
            (*newDict)[index][wordPos] = new char[strlen((*dict)[i][wordPos]) + one];//Creating a dynamic array of character type to be the size of the number of characters of the word in 'dict' plus one(for null).
            (*newDict)[index][definitionPos] = new char[strlen((*dict)[i][definitionPos]) + one];//Creating a dynamic array of character type to be the size of the number of characters of the definition in 'dict' plus one(for null).
            strcpy((*newDict)[index][wordPos] ,(*dict)[i][wordPos]);//Copying the word from 'dict' to 'newDict'.
            strcpy((*newDict)[index][definitionPos] ,(*dict)[i][definitionPos]);//Copying the definition from 'dict' to 'newDict'.
            ++index;
        }
    }
}
//********************************************************************************
/*This function receives a dynamic three-dimensional array, the value found in its
  first cell, the value found in its last cell, the index of the first cell (0)
  and the index of the last cell (size -1) and the size of the array and sorts it
  using the efficient quick sort method.*/
void mainSort(char*** dict, char** start, char** end, int low, int high, int size)
{
    if (low <= high)//Checking whether the function has not finished sorting the array.
    {
        int help = quickSort(dict, start, end, low, high, size, lowPosition);//Declaring the variable help which represents the index of the cell in the array that we placed in its place and inserting the value returned from the function quickSort into it.
        mainSort(dict, start, *(dict+help-one), low, help-one, size);//A recursive call to this function that will sort the array from the left side to the variable 'help'.
        mainSort(dict, *(dict+help+one), end, help+one, high, size);//A recursive call to this function that will sort the array from the right side to the variable 'help'.
    }
}
//********************************************************************************
/*This function receives a dynamic three-dimensional array, the value found in its first cell,
  the value found in its last cell, the index of the first cell (0) and the index of the last cell (size -1),
  the size of the array and a number indicating whether temp1 is at the beginning of the array or at the end of the array,
  This function places the first element of the array it accepts to be in its place.*/
int quickSort(char*** dict, char** temp1, char** temp2, int low, int high, int size, int signTemp1)
{
    if (low == high)//Checking whether we have finished placing the value of the first cell in the array to be in its place in this array.
        return low;//Returning the index of the cell we placed.
    if (strcmp(*temp1, *temp2) < zero)//Checking whether the word found in temp1 is smaller than the word found temp2.
        if (signTemp1 == lowPosition)//Checking whether temp1 is at the beginning of the array.
            return quickSort(dict, temp1, *(dict+high-one), low, high-one, size, signTemp1);//The recursive function returns with the cell before the current last cell and so with its index.
        else//If temp1 is at the end of the array.
        {
            swapStrings(temp1, temp2);//A call to a function that will switch between the word and its description of temp1 and temp2.
            return quickSort(dict, temp2, *(dict+high-one), low, high-one, size, lowPosition);//The recursive function returns with the cell before the current last cell and so with its index.
        }
    else//If the word found in temp1 is bigger than the word found temp2.
    {
        if (signTemp1 == lowPosition)//Checking whether temp1 is at the beginning of the array.
        {
            swapStrings(temp1, temp2);//A call to a function that will switch between the word and its description of temp1 and temp2.
            return quickSort(dict, temp2, *(dict+low+one), low+one, high, size, highPosition);//The recursive function returns with the cell after the current first cell and so with its index.
        }
        else//If temp1 is at the end of the array.
            return quickSort(dict, temp1, *(dict+low+one), low+one, high, size, signTemp1);//The recursive function returns with the cell after the current first cell and so with its index.
    }
}
//********************************************************************************
/*This function receives two addresses of arrays of size 2 that hold a word and its description, the function
  switches between the words and the descriptions of the arrays.*/
void swapStrings(char** temp1, char** temp2)
{
    char* help1 = *temp1;//Creating a one-dimensional array 'help1' and inserting the word of temp1 into it.
    char* help2 = *(temp1+definitionPos);//Creating a one-dimensional array 'help2' and inserting the definition of temp1 into it.
    *temp1 = *temp2;//Put the word found in temp2 into temp1 instead of its word.
    *(temp1+definitionPos) = *(temp2+definitionPos);//Put the definition found in temp2 into temp1 instead of its definition.
    *temp2 = help1;//Put the word found in help1 into temp2 instead of its word.
    *(temp2+definitionPos) = help2;//Put the definition found in help2 into temp2 instead of its definition.
}
//********************************************************************************
/*This function receives a dynamic 3D array and its size, the function asks the user to enter a word he wants to find,
  calls a function to search for the word and prints the description of the word if it is found and asks the user to enter a word again,
  if it is not found the function will ask the user to enter a word again, The function will repeat the process until the user enters the
  word 'exit' and then terminate the program.*/
void chooseWord(char*** dict, int size)
{
    char word[maxCharsOfWord];//Creating a static one-dimensional array 'word' of char type into which the word the user wants to look up in the dictionary will be inserted
    cout << "Please enter a word:" << endl;
    do {
        cin.getline(word, maxCharsOfWord);//Inserting the word the user entered into the array word.
        if (strcmp(word, "exit") != zero)//Checking whether the entered word is not 'exit'.
        {
            if (*word >= minSmallLetter && *word <= maxSmallLetter)//Checking whether the first letter is a lowercase letter.
                *word -= (minSmallLetter - minCapitalLetter);//Converting the first letter from lowercase to uppercase.
            fixString(word+one, wordPos);//A call to a function that will fix the rest of the characters in the word the user entered.
        }
        if ((strcmp(word, *(dict[wordPos])) < zero || strcmp(word,*(dict[size-one])) > zero) && strcmp(word, "exit") != zero)//Checking whether the word entered by the user is smaller than the first word in the dictionary or larger than the last word in the dictionary and neither 'exit'.
            cout << "This word is not in the dictionary, please try again:" << endl;//Printing an appropriate message.
        else//If the word entered by the user is bigger or equal to the first word in the dictionary and smaller or equal to the last word in the dictionary or its 'exit'.
            if (strcmp(word, "exit") != zero)//Checking whether the word is not 'exit'.
                binarySearch(dict, word, zero, size-one);//A call to a function that will look up the word in the dictionary using the efficient binary search method.
    }
    while(strcmp(word, "exit") != zero);//The loop will continue to run until the user enters the word 'exit'.
}
//********************************************************************************
/*This function receives a dynamic three-dimensional array that is the dictionary, the word it wants to look up in the dictionary,
  an index that represents the beginning of the array and an index that represents the end of the array, the function will search
  for the word in the array and print its description if it is found and if not it will print a corresponding message.*/
void binarySearch(char*** dict, char word[], int low, int high)
{
    if (low > high)//Checking whether the function searched the entire array and did not find the word it was looking for.
    {
        cout << "This word is not in the dictionary, please try again:" << endl;//Printing an appropriate message.
        return ;
    }
    int mid = (low + high)/two;//Declaring the variable middle and placing the index that is the middle of the current array in this variable.
    if (strcmp(word, *(dict[mid])) == zero)//Checking whether the word in the array in which the function is found is equal to the word the function is looking for.
    {
        cout << *(dict[mid]+one) << endl;//Print the description of the found word.
        cout << "Please enter another word:" << endl;//Printing a message is adjusted to insert another word
        return;
    }
    else//If the word in the array in which the function is found is not equal to the word the function is looking for.
    {
        if (strcmp(word, *(dict[mid])) > zero)//Checking if the word the function wants to search for is bigger than the word in the middle of the current array.
            binarySearch(dict, word, mid+one, high);//Recursively calling a function with an initial index equal to the middle of the array plus 1.
        else//Checking if the word the function wants to search for is smaller than the word in the middle of the current array.
            binarySearch(dict, word, low, mid-one);//Recursively calling a function with a final index equal to the middle of the array plus 1.
    }

}
//********************************************************************************
/*This function receives a dynamic 3D array and its size, and deletes it
  and frees all the memory it occupied.*/
void deleteDict(char*** dict, int size)
{
    for (int i = size-one; i >= zero; --i)//The loop ran from the end of the array to its beginning.
    {
        for (int j = 1; j >= zero; --j)//The loop ran from cell one in the array to cell zero.
            delete[]dict[i][j];//The function deletes all the strings (the words and their description) that are in the zero cell and the one cell in the dynamic array of size 2 that is in the cells of the dynamic three-dimensional array.
        delete[]dict[i];//The function deletes all arrays of size 2 that are in the cells of the dynamic 3D array.
    }
    delete[]dict;//The function deletes the dynamic 3D array.
}