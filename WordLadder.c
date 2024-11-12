//Contents of main.c except for int main()
/*---------------------------------
Program 5: Linked List, Find Shortest Word Ladder
Course: CS 211, Fall 2024, UIC
Description: Program reads set of words from dictionary file, then forms the shortest word ladder between any two
words in dictionary specified by the used using a linked list implementation.
Justin Muci
-----------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;

/*Accepts potential dictionary file in filename, and wordSize specified by user.
Returns the number of words in filename of wordSize length as an integer. Returns -1 if invalid file*/
int countWordsOfLength(char* filename, int wordSize) { 

    FILE* inFile = fopen(filename, "r");
    char tempString[25];
    int count =0;

    if(inFile == NULL)//Invalid file
    {
        return -1;
    }

    while (fscanf(inFile, "%s", tempString)==1)
    {
        if (strlen(tempString) == wordSize)
        {
            count++;
        }
    }

	fclose(inFile);
    return count; 
}

/*Builds dynamic array of c-strings read from filename, and all of length wordSize.
If incorrect number of words are read, return false*/
bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 

	FILE* inFile = fopen(filename, "r");
	int test=0;
	char tempString[25];
	if (inFile ==NULL) //Invalid File
	{
		return false;
	}

	while (fscanf(inFile, "%s", tempString)==1)
	{
		if (strlen(tempString)==wordSize) //Only words of correct length
		{
			strcpy(words[test], tempString);
			test++;
		}
	}

	fclose(inFile);
	if( test != numWords)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/*Searches array of c-strings words for aWord using binary search. loInt represents the lower index,
while hiInd represents the higher index. Returns -1 if word not found. */
int findWord(char** words, char* aWord, int loInd, int hiInd) { 

	if (loInd >hiInd) //Word not found
	{
		return -1;
	}
	int midPt= loInd +(hiInd-loInd)/2;

	if (strcmp(words[midPt], aWord) == 0) //Word found
	{
		return midPt;
	}
	else if(strcmp(words[midPt], aWord) < 0) //Lower half
	{
		findWord(words, aWord, midPt+1, hiInd);
	}
	else if(strcmp(words[midPt], aWord) >0)//Upper half
	{
		findWord(words, aWord, loInd, midPt-1);
	}
}

//Frees dynamically allocated array of c-strings of size numWords
void freeWords(char** words, int numWords) {
	for (int i=0;i<numWords;i++) //Free individual entries
	{
		free(words[i]);
	}

	free(words); //Free whole array
}

//Inserts newWord into the front of WordNode ladder.
void insertWordAtFront(WordNode** ladder, char* newWord) {
	WordNode* node = (WordNode*)malloc(sizeof(WordNode)); //Allocate new node

	(*node).myWord = newWord; //Make new node's word element = to newWord

	(*node).next = *ladder; //Make new node's next element the start of ladder.
	*ladder = node; //Make head new node
	
}

//Traverses through WordNode ladder until NULL is reached. Returns the height of the linked list as an integer
int getLadderHeight(WordNode* ladder) {
	int count=0;
	WordNode* test= ladder; //Temporary pointer to traverse list

	while (test !=NULL)
	{
		count++;
		test= test->next;
	}
	return count;
}

//Copies passed WordNode ladder into new dynamically allocated ladder, and returns the memory address of the new ladder.
WordNode* copyLadder(WordNode* ladder) {

	if (ladder == NULL) ///Empty ladder
	{
		return NULL;
	}
    WordNode* newLadder = (WordNode*)malloc(sizeof(WordNode));
	WordNode* temp = ladder; //Traverse old ladder
    WordNode* newTemp = newLadder; //Traverse new Ladder

	newTemp->myWord = temp->myWord; //Copy first entry
	newTemp->next = NULL;
	while (temp->next != NULL)
	{
		temp = temp->next;
		newTemp->next = (WordNode*)malloc(sizeof(WordNode)); //new Node in newLadder
		newTemp = newTemp->next;
		newTemp->myWord = temp->myWord; //Copy corresponding node in ladder
        newTemp->next = NULL;
	}
	
    return newLadder; 
}

//Frees dynamically allocated WordNode ladder node by node. Dynamically allocated myWord elements are not freed
void freeLadder(WordNode* ladder) {

	WordNode* current = ladder; //Temporary pointer to check ladder->next
    WordNode* temp = NULL; //Temporary pointer to traverse ladder
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
}

//Takes LadderNode list and WordNode newLadder, and adds the newLadder list of strings to the back of the list using the
//topWord element within LadderNode.
void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {

    LadderNode* myLadder= (LadderNode*)malloc(sizeof(LadderNode)); //Allocate LadderNode to be added to back
	myLadder->topWord = newLadder; //Initialize topWord
	myLadder->next = NULL;

	if(*list == NULL) //Empty current list
	{
		*list = myLadder;
	}
	else
	{
		LadderNode* temp = *list; //Traverse LadderNode
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = myLadder; //Append new node
	}

}

//Pops the first node from LadderNode list, and that node's topWord is what is returned as a WordNode*
WordNode* popLadderFromFront(LadderNode** list) {

	if (list == NULL) //Empty list
	{
		return NULL;
	}

	LadderNode* temp = *list;	
	*list = (*list)->next; //Make beginning of list the next node 
	WordNode* topWord = temp->topWord;
	free(temp); //Pop node
    return topWord; //topWord is separaterly allocated to the first LadderNode, so we can still return it after freeing
}

//Frees LadderNode list of WordNode lists.
void freeLadderList(LadderNode* myList) {
	LadderNode* temp = myList;
	while(temp != NULL)
	{
		freeLadder(temp->topWord); //Free topWord element in myList
		myList = myList->next; //Move onto next node
		free(temp); //Free ladderNode
		temp=myList; 
	}
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}

/* Algorithm which finds the shortest word ladder from startWord to finalWord. words array contains numWords
number of words, all of length wordSize. A Breadth-first search is used by building all WordNode lists one height at a time
and adding them to the ladderNode myList. bool usedWord array tests if a word has already been considered as the final
word, and is of size numWords aswell. Once the first valid ladder is found, it is returned.*/
WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {

    LadderNode* myList = NULL;
	WordNode* myLadder = NULL;
    insertWordAtFront(&myLadder, startWord);
	insertLadderAtBack(&myList, myLadder);
	char startWordCopy[wordSize+1];
	char alphabet[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	usedWord[findWord(words, startWord, 0, numWords-1)]=1;


	while (myList != NULL)
	{
		myLadder = popLadderFromFront(&myList);

		for (int i=0; i<wordSize;++i)
		{
			strcpy(startWordCopy, myLadder->myWord);

			for (int j=0;j< 26 ;++j)
			{
				startWordCopy[i] = alphabet[j];
				int test = findWord(words, startWordCopy, 0, numWords-1);
				
				if (test != -1 && !usedWord[test])
				{
					if (strcmp(startWordCopy, finalWord) == 0)
					{
						insertWordAtFront(&myLadder, words[test]);
						freeLadderList(myList);
						return myLadder;
					}
					else
					{
						WordNode* anotherLadder = copyLadder(myLadder);
						insertWordAtFront(&anotherLadder, words[test]);
						insertLadderAtBack(&myList, anotherLadder);
						usedWord[test] = 1;
					}
				}
			}
		}
		freeLadder(myLadder);
	}

	freeLadderList(myList); //No ladder Found
    return NULL;
}

// interactive user-input to set a word; 
//  ensures sure the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}
