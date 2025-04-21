#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LEN 100
#define MAX_RESPONSE_LEN 256
#define MAX_QUERY 100

// ------------ Trie Data Structure ------------

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord;
} TrieNode;

TrieNode* getNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void insert(TrieNode* root, const char* word) {
    TrieNode* curr = root;
    for (int i = 0; word[i]; i++) {
        if (!isalpha(word[i])) continue;
        int index = tolower(word[i]) - 'a';
        if (!curr->children[index])
            curr->children[index] = getNode();
        curr = curr->children[index];
    }
    curr->isEndOfWord = 1;
}

int min(int a, int b, int c) {
    if (a < b && a < c) return a;
    if (b < c) return b;
    return c;
}

// ------------ Edit Distance ------------

int editDistance(const char* a, const char* b) {
    int m = strlen(a), n = strlen(b);
    int dp[m + 1][n + 1];
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
        }
    return dp[m][n];
}

// ------------ Dictionary and Responses ------------

const char* dictionary[] = {
    "hello", "hi", "name", "how", "are", "you", "what", "your", "weather", "today", "fine", "bye",
    "is", "i", "am", "good", "doing", "help", "can", "do", "who", "where", "time", "date"
};
const int dictSize = sizeof(dictionary) / sizeof(dictionary[0]);

const char* knownQuestions[] = {
    "hello",
    "hi",
    "what is your name",
    "how are you",
    "bye",
    "how is the weather today",
    "what can you do",
    "who are you"
};
const char* responses[] = {
    "Hi there!",
    "Hello!",
    "I am a chatbot written in C.",
    "I'm doing well. How about you?",
    "Goodbye! Have a great day!",
    "The weather is quite pleasant today.",
    "I can answer your questions and autocorrect spelling mistakes!",
    "I'm your helpful assistant."
};

// ------------ Utility Functions ------------

void preprocess(char* str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

void autocorrect(TrieNode* root, char* word, char* correctedWord) {
    int minDist = 1000;
    strcpy(correctedWord, word); // fallback
    for (int i = 0; i < dictSize; i++) {
        int dist = editDistance(word, dictionary[i]);
        if (dist < minDist) {
            minDist = dist;
            strcpy(correctedWord, dictionary[i]);
        }
    }
}

void autocorrectSentence(TrieNode* root, char* sentence, char* corrected) {
    char* token = strtok(sentence, " ");
    corrected[0] = '\0';
    while (token) {
        char correctedWord[MAX_WORD_LEN];
        autocorrect(root, token, correctedWord);
        strcat(corrected, correctedWord);
        strcat(corrected, " ");
        token = strtok(NULL, " ");
    }
    if (strlen(corrected) > 0 && corrected[strlen(corrected) - 1] == ' ')
        corrected[strlen(corrected) - 1] = '\0'; // remove last space
}

const char* getResponse(const char* input) {
    for (int i = 0; i < sizeof(knownQuestions)/sizeof(knownQuestions[0]); i++) {
        if (strcmp(input, knownQuestions[i]) == 0)
            return responses[i];
    }
    return "Sorry, I don't understand that.";
}

// ------------ Main Function ------------

int main() {
    TrieNode* root = getNode();
    for (int i = 0; i < dictSize; i++)
        insert(root, dictionary[i]);

    char input[MAX_QUERY], inputCopy[MAX_QUERY], corrected[MAX_QUERY];
    printf("ChatBot (type 'exit' to quit):\n");

    while (1) {
        printf("You: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // remove newline
        strcpy(inputCopy, input);
        preprocess(inputCopy);

        if (strcmp(inputCopy, "exit") == 0)
            break;

        autocorrectSentence(root, inputCopy, corrected);

        printf("Autocorrected: %s\n", corrected);  // Optional: debug

        const char* response = getResponse(corrected);
        printf("Bot: %s\n", response);
    }
return 0;
}
