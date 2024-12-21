#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ATTEMPTS 6
#define TOTAL_WORDS 15

// Words and hints combined in a single structure
typedef struct {
    const char* word;
    const char* hint;
} WordHint;

const WordHint wordHints[TOTAL_WORDS] = {
    {"apple", "A fruit that keeps doctors away."},
    {"banana", "A yellow fruit loved by monkeys."},
    {"cherry", "A small red fruit often used in desserts."},
    {"grape", "A small round fruit often used in wines."},
    {"orange", "A citrus fruit known for its vitamin C."},
    {"elephant", "The largest land animal."},
    {"giraffe", "An animal with a long neck."},
    {"lion", "The king of the jungle."},
    {"zebra", "A striped animal found in Africa."},
    {"tiger", "A big cat with stripes."},
    {"keyboard", "A device used for typing."},
    {"laptop", "A portable computer."},
    {"bottle", "Used to hold liquids."},
    {"pencil", "Used for writing."},
    {"table", "A piece of furniture often used for studying."}
};

// Function to randomly select a word and its hint
WordHint getRandomWordAndHint() {
    int index = rand() % TOTAL_WORDS;
    return wordHints[index];
}

// Function to display the hangman based on attempts
void displayHangman(int attempts) {
    const char* hangman[] = {
        "  +---+\n      |\n      |\n      |\n      |\n=========\n",
        "  +---+\n  O   |\n      |\n      |\n      |\n=========\n",
        "  +---+\n  O   |\n  |   |\n      |\n      |\n=========\n",
        "  +---+\n  O   |\n /|   |\n      |\n      |\n=========\n",
        "  +---+\n  O   |\n /|\\  |\n      |\n      |\n=========\n",
        "  +---+\n  O   |\n /|\\  |\n /    |\n      |\n=========\n",
        "  +---+\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n"
    };
    printf("%s", hangman[attempts]);
}

// Function to play the game
void playGame() {
    WordHint chosenWordHint = getRandomWordAndHint();
    const char* wordToGuess = chosenWordHint.word;
    const char* hint = chosenWordHint.hint;
    int wordLength = strlen(wordToGuess);
    char guessedWord[wordLength + 1];
    int attempts = 0;

    // Initialize guessed word with underscores
    memset(guessedWord, '_', wordLength);
    guessedWord[wordLength] = '\0';

    printf("Welcome to Hangman!\n");
    printf("Type '!' at any time to quit the game immediately.\n");

    while (attempts < MAX_ATTEMPTS) {
        displayHangman(attempts);
        printf("Word to Guess: %s\n", guessedWord);

        // Provide hint if only 2 attempts remain
        if (attempts == MAX_ATTEMPTS - 2) {
            printf("Hint: %s\n", hint);
        }


        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);

        int found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (wordToGuess[i] == guess) {
                guessedWord[i] = guess;
                found = 1;
            }
        }

          // Quit condition
        if (guess == '!') {
            printf("You chose to quit the game. Goodbye!\n");
            return;
        }

        if (!found) {
            attempts++;
            printf("Incorrect guess. Attempts remaining: %d\n", MAX_ATTEMPTS - attempts);
        }

        if (strcmp(wordToGuess, guessedWord) == 0) {
            printf("Congratulations! You've guessed the word: %s\n", wordToGuess);
            return;
        }
    }

    displayHangman(attempts);
    printf("You're out of attempts! The word was: %s\n", wordToGuess);
}

int main() {
        char playAgain;
    
        do {
            playGame();
            printf("Do you want to play again? (y/n): ");
            scanf(" %c", &playAgain);
        } while (playAgain == 'y' || playAgain == 'Y');
    
        printf("Thank you for playing Hangman!\n");
        return 0;
}

