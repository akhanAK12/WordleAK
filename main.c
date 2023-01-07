//  wordleGuessSecretWord.c
//  Have the program do the guessing to discover the secret wordle word.
//
//  Author: Dale Reed, 11/6/22
//  System: CLion and XCode
//
//  Links to wordle dictionary words at:
//    https://www.reddit.com/r/wordle/comments/s4tcw8/a_note_on_wordles_word_list/
/*  Running the program looks like:
        Using file wordsLarge.txt with 12947 words. 
        -----------------------------------------------------------
        
        enter a secret word or just r to choose one at random: dream
        Trying to find secret word: 
               d r e a m 
        
            1. s o r e s 
                   * *   
            2. s e r e r 
                 * *     
            3. r a r e r 
               * *   *   
            4. r a r e e 
               * *   *   
            5. s a r e e 
                 * * *   
            6. p a r e r 
                 * * *   
            7. c a r e r 
                 * * *   
            8. b a r e r 
                 * * *   
            9. f a r e r 
                 * * *   
           10. D a r e r 
                 * * *   
           11. D e a r e 
                 * * *   
           12. D e b A r 
                 *     * 
           13. D R E A r 
                       * 
           14. D R E A d 
                         
           15. D R E A M 
                         
        Got it!

     ... and then it runs two more times ...
 */
#include <stdio.h>    // for printf(), scanf()
#include <stdlib.h>   // for exit( -1)
#include <string.h>   // for strcpy
#include <assert.h>   // for assert() sanity checks
#include <ctype.h>    // for toupper()
#include <time.h>     // for time()

// Declare globals
#define WORD_LENGTH 5     // All words have 5 letters, + 1 NULL at the end when stored
#define WORDS_FILE_NAME "wordsLarge.txt"
//#define WORDS_FILE_NAME  "wordsTiny.txt"
#define MAX_NUMBER_OF_WORDS 12947   // Number of words in the full set of words file
#define true 1   // Make boolean logic easier to understand
#define false 0  // Make boolean logic easier to understand

typedef struct wordCount wordCountStruct;
struct wordCount{
    char word[ WORD_LENGTH + 1];   // The word length plus NULL
    int score;                     // Score for the word
};


//-----------------------------------------------------------------------------------------
// Read in words from file into array.  We've previously read the data file once to
// find out how many words are in the file.
void readWordsFromFile(
            char fileName[],        // Filename we'll read from
            wordCountStruct *words, // Array of words where we'll store words we read from file
            int *wordCount)          // How many words.  Gets updated here and returned
{
    FILE *inFilePtr  = fopen(fileName, "r");  // Connect logical name to filename
    assert( inFilePtr != NULL);               // Ensure file open worked correctly

    // Read each word from file and store into array, initializing the score for that word to 0.
    char inputString[ 6];
    *wordCount = 0;
    while( fscanf( inFilePtr, "%s", inputString) != EOF) {
        strcpy( words[ *wordCount].word, inputString);
        words[ *wordCount].score = 0;
        (*wordCount)++;
    }

    // Close the file
    fclose( inFilePtr);
} // end readWordsFromFile(..)


//-----------------------------------------------------------------------------------------
// Comparator for use in built-in qsort(..) function.  Parameters are declared to be a
// generic type, so they will match with anything.
// This is a two-part comparison.  First the scores are compared.  If they are the same,
// then the words themselves are also compared, so that the results are in descending
// order by score, and within score they are in alphabetic order.
int compareFunction( const void * a, const void * b) {
    // Before using parameters we have cast them into the actual type they are in our program
    // and then extract the numerical value used in comparison
    int firstScore = ((wordCountStruct *) a)->score;
    int secondScore = ((wordCountStruct *) b)->score;

    // If scores are different, then that's all we need for our comparison.
    if (firstScore != secondScore) {
        // We reverse the values, so the result is in descending vs. the otherwise ascending order
        // return firstScore - secondScore;   // ascending order
        return secondScore - firstScore;      // descending order
    }
    else {
        // Scores are equal, so check words themselves, to put them in alphabetical order
        return strcmp( ((wordCountStruct *)a)->word,  ((wordCountStruct *)b)->word );
    }
} //end compareFunction(..)


// -----------------------------------------------------------------------------------------
// Find a secret word
void findSecretWord(
        wordCountStruct allWords[],    // Array of all the words
        int wordCount,                  // How many words there are in allWords
        char secretWord[])              // The word to be guessed
{
  // Allocate space for the computer guess (holds the word with the guess the computer generated)
    char computerGuess[ 6] = "soare"; 
    char copyComputerGuess[6]; 
    char copySecretWord[6];
    int isTrue = 0; 
  wordCountStruct CopyallWords[wordCount];
    printf("Trying to find secret word: \n");
    // Display secret word with a space between letters, to match the guess words below.
    printf("       ");
    for( int i=0; i<WORD_LENGTH; i++) {
        printf("%c ", secretWord[ i]);
    }
    printf("\n");
    printf("\n");
    
    for(int i = 0; i < wordCount; i++)
      {
          strcpy(CopyallWords[i].word,allWords[i].word);
      }
  
    // Loop until the word is found
    int guessNumber = 1;
    int index = 0; 
    char correctSpot[6] = "$$$$$"; //will store in the Capital letter meaning there is a match at the smae index
    char wrongSpot[6] = "&&&&&"; //will store in the Capital letter meaning there is a match at the smae index
    while(isTrue == 0) {
      //make a copy of each array
       strcpy(correctSpot, "$$$$$"); 
       strcpy(wrongSpot, "&&&&&"); 
       strcpy(copyComputerGuess, computerGuess);
       strcpy(copySecretWord, secretWord); 
      
       //printf("%c", computerGuess); 
       printf("%5d. ", guessNumber);
        for(int i = 0; i < WORD_LENGTH; i++)
          {
           if(copySecretWord[i] != copyComputerGuess[i])
           {
             printf("%c ", copyComputerGuess[i]); //print the character if it is not an exact match
           }
            else{
              //toupper(copyComputerGuess[i]);
              char temp = toupper(copyComputerGuess[i]); 
              correctSpot[i] = copyComputerGuess[i]; //save the letter and index of where both the characters are in the same index and captalize it 
              printf("%c ", temp); 
              
              copySecretWord[i] = ' '; 
              copyComputerGuess[i] = ' '; 
            }
          }
      printf("\n"); 
      if(strcmp(computerGuess,secretWord) == 0){
        printf("GOT IT!\n"); 
        isTrue = 1; 
        break; 
    }

      printf("       "); 
     // char displayCharacter = ' '; 
      for(int i = 0; i < WORD_LENGTH; i++)
        {
          //setting the display character to ''
           char displayCharacter = ' '; 
          for(int j = 0; j < 5; j++)
            {
              if(copySecretWord[j] == copyComputerGuess[i] && copySecretWord[j] != ' ' && i != j) //if character is in the secret word, but not in the same indec
              {
               
                wrongSpot[i] = copyComputerGuess[i]; //save letter and index of where character is not in the same index
                displayCharacter = '*'; 
                break;
              }
              
            }
           printf("%c ", displayCharacter); 
         
        }
      printf("\n");

      for(int j = 0; j < WORD_LENGTH; j++)
        {
          //check to see if letter is uppercase 
          if(isupper(copyComputerGuess[j]))
          {
           for(int p = 0; p < wordCount; p++)
            {
              for(int k = 0; k < 5; k++) //delete all the words that don't contain the UPPER CASE word
              { 
                //looping thru all the words in allWords and looping thru each letter in each word
                if(CopyallWords[p].word[k] != correctSpot[k]) 
                {
                  strcpy(CopyallWords[p].word, ""); //space out all the words that dont't contain the captial letter at the specific index
                }
              }
            }
          }
           
        }

      //delete all words that contain the letter that's in the word but not in the right index(letter with *)
      for(int i = 0; i < wordCount; i++)
      {
          for(int j = 0; j < 5; j++)
          {
              if(CopyallWords[i].word[j] == wrongSpot[j])
              {
                strcpy(CopyallWords[i].word, ""); 
              }
              if(CopyallWords[i].word[j] == tolower(copyComputerGuess[j]) && CopyallWords[i].word[j] != wrongSpot[j])
              {
                strcpy(CopyallWords[i].word, ""); 
              }
          }
      }
      int count = 0;
      int count1 = 0;
  
      for(int p = 0; p < wordCount; p++)
        {
   
          for(int k = 0; k < WORD_LENGTH; k++)
            {
              for(int index = 0; index < WORD_LENGTH; index++)
                {
                  if(copyComputerGuess[k] == CopyallWords[p].word[index] && islower(copyComputerGuess[k]) != 0)//trying to delete all the words that are lowercased and not asterick letter from the previous computerGuess 
                  {
                    int check = false; 
                     for(int i = 0; i < WORD_LENGTH; i++)
                      {
                       //check to see if there is asterik word in the computers guess, if so set check to true 
                        if(CopyallWords[p].word[index] == wrongSpot[i])
                        {
                          check = true;         
                        }
                      }
                    if(check == false)
                    {
                      int secondflag = false;
                      for(int L = 0; L < WORD_LENGTH; L++)
                      {
                        if(CopyallWords[p].word[index] == correctSpot[L]){
                          secondflag = true; //set flag to true when a word in the file contain an uppercase letter 
                        }
                      }
                      if(secondflag == false)
                      {
                        strcpy(CopyallWords[p].word, "");
                      }
                    }
                  }
                }
            }
        }


      //go thru the allWords array and find the first word in the array that isn't spaced out
      for(int i = 0; i < wordCount; i++)
      {
        if(strcmp(CopyallWords[i].word,"") != 0)
        {
          strcpy(computerGuess, CopyallWords[i].word);
          break; 
        }
      }
      
        // Update guess number
        guessNumber++;
    } //end for( int i...)
  for(int i = 0; i < wordCount; i++)
  {
      if(strcmp(allWords[i].word,secretWord) == 0){
        allWords[i].score = guessNumber;
      }
    }
} //end findSecretWord


// -----------------------------------------------------------------------------------------
int main() {
    char wordsFileName[81];                   // Stores the answers file name
    strcpy(wordsFileName, WORDS_FILE_NAME);   // Set the filename, defined at top of program.
    srand( (unsigned) time( NULL));           // Seed the random number generator to be current time
    // Declare space for all the words, of a maximum known size.
    wordCountStruct allWords[ MAX_NUMBER_OF_WORDS];
    // Start out the wordCount to be the full number of words.  This will decrease as
    //    play progresses each time through the game.
    int wordCount = 0;
    // The secret word that the computer will try to find, plus the return character from fgets.
    char secretWord[ WORD_LENGTH + 1];
    char userInput[ 81];                // Used for menu input of secret word

    // Read in words from file, update wordCount and display information
    readWordsFromFile( wordsFileName, allWords, &wordCount);
    printf("Using file %s with %d words. \n", wordsFileName, wordCount);

    // Run the word-guessing game three times
    for( int i=0; i<3; i++) {
        // Reset secret Word
        strcpy( secretWord, "");
        // Display prompt
        printf("-----------------------------------------------------------\n");
        printf("\n");
        printf("Enter a secret word or just r to choose one at random: ");
        scanf(" %s", userInput);
        // Eliminate the return character at end or userInput if it is there
        int length = (int) strlen( userInput);
        if( userInput[ length] == '\n') {
            userInput[ length] = '\0';
        }
        strcpy( secretWord, userInput);   // Store the secret word from user input
                //strcpy( secretWord, allWords[i].word); 
        // If input was 'r' then choose a word at random.
        if( strlen( secretWord) <= 1) {
            // Randomly select a secret word to be guessed.
            int randomIndex = rand() % wordCount;
            strcpy( secretWord, allWords[ randomIndex].word);
        }
        
        // Run the game once with the current secret word
        findSecretWord( allWords, wordCount, secretWord);
    }

  qsort(allWords, MAX_NUMBER_OF_WORDS, sizeof(wordCountStruct), compareFunction);
    for(int i = 0; i < wordCount-1; i++){
      if(allWords[i].score >= 15){
        printf("%s %d \n", allWords[i].word,allWords[i].score);
      }
      if(strcmp(allWords[i].word,"zymic") == 0){
        break;
      }
    }
    printf("Done\n");
    printf("\n");
    return 0;
} // end main()