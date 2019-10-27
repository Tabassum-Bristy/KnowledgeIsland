#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTION 200

struct Question
{
    char statement[256];
    char option1[256];
    char option2[256];
    char option3[256];
    char option4[256];
    int correct;
};

struct Question easy[MAX_QUESTION], medium[MAX_QUESTION], hard[MAX_QUESTION];
int total_easy, total_medium, total_hard;

int used[MAX_QUESTION];

void initiate_question();
void start_quiz(char type[], struct Question question[], int total_question);
int next_index();

int main()
{

    initiate_question();

    // set screen color
    system("COLOR 2F");

    int choice;

    do
    {
        puts("Welcome to Knowledge Island");
        puts("Select a difficulty to get started");
        puts("\t1. Easy");
        puts("\t2. Medium");
        puts("\t3. Hard");
        puts("\t4. Exit");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        srand(time(NULL));

        system("CLS");

        switch(choice)
        {
        case 1:
            start_quiz("Easy", easy, total_easy);
            break;
        case 2:
            start_quiz("Medium", medium, total_medium);
            break;
        case 3:
            start_quiz("Hard", hard, total_hard);
            break;
        default:
            // flash invalid input
            fflush(stdin);
        }

    }while(choice != 4);

    return 0;
}


void start_quiz(char type[], struct Question question[], int total_question)
{
    int i, ans, marks = 0;
    char input[255];

    memset(used, 0, sizeof(used));

    printf("%s Quiz Started\n", type);
    puts("=================");
    // change it later
    for(i=0; i<10; i++)
    {
        int index;
        do {
            index = next_index(total_question);
        } while(used[index] != 0);

        printf("Ques-%d. %s\n", i+1, question[index].statement);
        printf("\t1. %s\n", question[index].option1);
        printf("\t2. %s\n", question[index].option2);
        printf("\t3. %s\n", question[index].option3);
        printf("\t4. %s\n", question[index].option4);

        while(1) {
            printf("Enter your answer (1/2/3/4): ");

            // flash previous input
            fflush(stdin);

            gets(input);
            ans = atoi(input);

            if(ans < 1 || ans > 4 ) {
                puts("Invalid answer! Try again!");
            }
            else {
                break;
            }
        }

        if(ans == question[index].correct){
            marks = marks + 1;
            puts("Correct!");
        }
        else {
            printf("Wrong Answer! Correct Answer: %d\n", question[index].correct);
        }
        used[index] = 1;
    }
    puts("====================================");
    printf("Your total Mark is %d\n", marks);

    system("PAUSE");
    system("CLS");
}



void initiate_question()
{
    FILE *easyFile, *mediumFile, *hardFile;
    int i;

    // load easy file
    easyFile = fopen("easy.txt", "r");
    if(easyFile == NULL) {
        puts("ERROR LOADING DATABASE");
        return 0;
    }
    // load total number of easy questions
    fscanf(easyFile, "%d\n", &total_easy);

    // loop through the file and read questions
    for(i=0; i<total_easy; i++) {
        fgets(easy[i].statement, 255, easyFile);
        fgets(easy[i].option1, 255, easyFile);
        fgets(easy[i].option2, 255, easyFile);
        fgets(easy[i].option3, 255, easyFile);
        fgets(easy[i].option4, 255, easyFile);
        fscanf(easyFile, "%d\n", &easy[i].correct);
    }

    fclose(easyFile);

    // load medium file
    mediumFile = fopen("medium.txt", "r");
    if(mediumFile == NULL) {
        puts("ERROR LOADING DATABASE");
        return 0;
    }
    // load total number of easy questions
    fscanf(mediumFile, "%d\n", &total_medium);

    // loop through the file and read questions
    for(i=0; i<total_medium; i++) {
        fgets(medium[i].statement, 255, mediumFile);
        fgets(medium[i].option1, 255, mediumFile);
        fgets(medium[i].option2, 255, mediumFile);
        fgets(medium[i].option3, 255, mediumFile);
        fgets(medium[i].option4, 255, mediumFile);
        fscanf(mediumFile, "%d\n", &medium[i].correct);
    }

    fclose(mediumFile);

    // load hard file
    hardFile = fopen("hard.txt", "r");
    if(hardFile == NULL) {
        puts("ERROR LOADING DATABASE");
        return 0;
    }
    // load total number of easy questions
    fscanf(hardFile, "%d\n", &total_hard);

    // loop through the file and read questions
    for(i=0; i<total_hard; i++) {
        fgets(hard[i].statement, 255, hardFile);
        fgets(hard[i].option1, 255, hardFile);
        fgets(hard[i].option2, 255, hardFile);
        fgets(hard[i].option3, 255, hardFile);
        fgets(hard[i].option4, 255, hardFile);
        fscanf(hardFile, "%d\n", &hard[i].correct);
    }
    fclose(hardFile);

}


int next_index(int total)
{
    return rand()%total;
}





