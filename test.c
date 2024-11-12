#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "WordLadder.c"

bool testCountWords(){

	int test = countWordsOfLength("3test.txt", 3);
	printf(" Testing with valid file/size (simple3.txt, 3)\n");
	if(test != 26)
	{
		printf("  Test FAILED\n");
		return false;
	}
	else
	{
		printf("  Test Passed\n");
	}
	
	printf(" Testing with invalid file\n");
	test = countWordsOfLength("hi.txt", 3);

	if(test != -1)
	{
		printf("  Test FAILED\n");
		return false;
	}
	else
	{
		printf("  Test Passed\n");
		return true;
	}
}

bool testBuildWordArray()
{
	char** words = (char**)malloc(26*sizeof(char*));
	for (int i = 0; i < 26; ++i) {
    words[i] = (char*)malloc(4*sizeof(char));
    }
	
	if (!buildWordArray("3test.txt", words, 26, 3)|| strcmp(words[0], "aim")!=0)
	{
		printf(" Test FAILED\n");
		for(int i=0;i<26;i++)
			{
				free(words[i]);
			}
		free(words);
		return false;
	}
	else
	{
		printf(" Test Passed\n");
	}

	for(int i=0;i<26;i++)
	{
		free(words[i]);
	}
	free(words);

	return true;
}

bool testFindWord()
{
	char** words = (char**)malloc(26*sizeof(char*));
	for (int i = 0; i < 26; ++i) {
    words[i] = (char*)malloc(4*sizeof(char));
    }
	
	buildWordArray("3test.txt", words, 26, 3);

	printf(" Testing with valid word in upper half\n");

	int test = findWord(words, "tye", 0, 25);

	if (test != 25)
	{
		printf("  Test FAILED\n");
		for (int i = 0; i < 26; ++i) 
			{
			free(words[i]);
			}	
		free(words);
		return false;
	}
	else{
		printf("  Test Passed\n");
	}

	printf(" Testing with valid word in lower half\n");

	test = findWord(words, "arm", 0, 25);

	if (test != 1)
	{
		printf("  Test FAILED\n");
		for (int i = 0; i < 26; ++i) 
		{
		free(words[i]);
		}	
		free(words);
		return false;
	}
	else{
		printf("  Test Passed\n");
	}

	printf(" Testing with invalid word\n");

	test = findWord(words, "hello", 0, 25);

	if (test != -1)
	{
		printf("  Test FAILED\n");
		for (int i = 0; i < 26; ++i) 
		{
		free(words[i]);
		}	
		free(words);
		return false;
	}
	else{
		printf("  Test Passed\n");
	}
	for (int i = 0; i < 26; ++i) 
		{
		free(words[i]);
		}	
	free(words);
}

bool testInsertAtFront()
{
	WordNode* ladder;
	char* myWord = (char*)malloc(4);
	char* myWord2 = (char*)malloc(4);
	strcpy(myWord, "arm");
	strcpy(myWord2, "ear");

	insertWordAtFront(&ladder, myWord);
	insertWordAtFront(&ladder, myWord2);

	if(strcmp((*ladder).myWord , "ear") != 0 || strcmp((*ladder).next->myWord , "arm"))
	{
		printf(" Test FAILED\n");
		free((*ladder).next);
		free(ladder);
		free(myWord);
		free(myWord2);
		return false;
	}
	else
	{
		printf(" Test Passed\n");
	}
	
	free((*ladder).next);
	free(ladder);
	free(myWord);
	free(myWord2);
	return true;
}

bool testGetHeight()
{
	WordNode* ladder;
	char* myWord = (char*)malloc(4);
	char* myWord2 = (char*)malloc(4);
	strcpy(myWord, "arm");
	strcpy(myWord2, "ear");

	insertWordAtFront(&ladder, myWord);
	insertWordAtFront(&ladder, myWord2);
	ladder->next->next = NULL;
	int test = getLadderHeight(ladder);

	if(test != 2)
	{
		printf(" Test FAILED\n");
		free((*ladder).next);
		free(ladder);
		free(myWord);
		free(myWord2);
		return false;
	}
	else
	{
		printf(" Test Passed\n");
	}
	
	free((*ladder).next);
	free(ladder);
	free(myWord);
	free(myWord2);
	return true;
}

bool testCopyLadder()
{
	WordNode* ladder;
	char* myWord = (char*)malloc(4);
	char* myWord2 = (char*)malloc(4);
	strcpy(myWord, "arm");
	strcpy(myWord2, "ear");
	bool valid =0;

	insertWordAtFront(&ladder, myWord);
	insertWordAtFront(&ladder, myWord2);
	ladder->next->next = NULL;


	WordNode* newLadder = copyLadder(ladder);
	if( strcmp(newLadder->myWord, "ear") != 0 || strcmp(newLadder->next->myWord, "arm") != 0)
	{
		printf(" Test FAILED\n");
	}
	else
	{
		printf(" Test Passed\n");
		valid=1;
	}

	free((*ladder).next);
	free(ladder);
	free((*newLadder).next);
	free(newLadder);
	free(myWord);
	free(myWord2);
	if(valid)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool testInsertAtBack()
{
	WordNode* ladder;
	LadderNode* myLadder;
	myLadder = NULL;
	char* myWord = (char*)malloc(4);
	char* myWord2 = (char*)malloc(4);
	strcpy(myWord, "arm");
	strcpy(myWord2, "ear");
	bool valid =1;

	insertWordAtFront(&ladder, myWord);
	insertWordAtFront(&ladder, myWord2);

	printf(" Testing with empty ladder\n");
	insertLadderAtBack(&myLadder, ladder);

	if (strcmp(myLadder->topWord->myWord, "ear") != 0)
	{
		printf("  Test FAILED\n");
		valid=0;
	}
	else
	{
		printf("  Test Passed\n");
	}

	printf(" Testing with non-empty ladder\n");
	insertLadderAtBack(&myLadder, ladder->next);

	if (strcmp(myLadder->next->topWord->myWord, "arm") != 0)
	{
		printf("  Test FAILED\n");
		valid=0;
	}
	else
	{
		printf("  Test Passed\n");
	}


	free((*ladder).next);
	free(ladder);
	free((*myLadder).next);
	free(myLadder);
	free(myWord);
	free(myWord2);
	if(valid)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool testPopFront()
{
	WordNode* ladder;
	LadderNode* myLadder;
	myLadder = NULL;
	char* myWord = (char*)malloc(4);
	char* myWord2 = (char*)malloc(4);
	strcpy(myWord, "arm");
	strcpy(myWord2, "ear");
	bool valid =1;

	insertWordAtFront(&ladder, myWord);
	insertWordAtFront(&ladder, myWord2);

	insertLadderAtBack(&myLadder, ladder);
	insertLadderAtBack(&myLadder, ladder->next);

	WordNode* result = popLadderFromFront(&myLadder);

	if(strcmp(result->myWord, "ear") != 0)
	{
		printf(" Test FAILED\n");
		valid =0;
	}
	else
	{
		printf(" Test Passed\n");
	}

	free((*ladder).next);
	free(ladder);
	free(myLadder);
	free(myWord);
	free(myWord2);

	if(valid)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool testFindShortestLadder()
{
	char** words = (char**)malloc(26*sizeof(char*));
	bool* usedWord = (bool*)malloc(26*sizeof(bool));
	for (int i = 0; i < 26; ++i) {
    words[i] = (char*)malloc(4*sizeof(char));
	usedWord[i] = 0;
    }
	bool valid =1;

	buildWordArray("3test.txt", words, 26, 3);
	if (!buildWordArray("3test.txt", words, 26, 3))
	{
		printf(" buildWordArray ERROR\n");
		valid=0;
	}

	printf(" Finding shortest ladder from hop to log.\n");
	WordNode* result = findShortestWordLadder(words, usedWord, 26, 3, "hop", "log");

	if (strcmp(result->myWord, "log") != 0 || strcmp(result->next->myWord, "hog") != 0 || strcmp(result->next->next->myWord, "hop") != 0)
	{
		printf(" Test FAILED\n");
		valid=0;
	}
	else
	{
		printf(" Test Passed");
	}

	for (int i=0;i<26;i++)
	{
		free(words[i]);
	}
	free(usedWord);
	freeLadder(result);
	free(words);

	if (valid)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	printf("Testing wordCount()\n");
	testCountWords();
	printf("Testing buildWordArray()\n");
	testBuildWordArray();
	printf("Testing findWord()\n");
	testFindWord();
	printf("Testing insertAtFront()\n");
	testInsertAtFront();
	printf("Testing getHeight()\n");
	testGetHeight();
	printf("Testing copyLadder()\n");
	testCopyLadder();
	printf("Testing insertLadderAtBack()\n");
	testInsertAtBack();
	printf("Testing popLadderFromFront()\n");
	testPopFront();
	printf("Testing findShortestLadder()\n");
	testFindShortestLadder();
	return 0;
}