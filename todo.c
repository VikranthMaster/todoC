#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LENGTH 100

void displayMenu()
{
    printf("\nTo-Do List Menu:\n");
    printf("1. Add Task\n");
    printf("2. View Tasks\n");
    printf("3. Remove Task\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

void addTask(char tasks[MAX_TASKS][MAX_LENGTH], int *taskCount)
{
    if (*taskCount >= MAX_TASKS)
    {
        printf("Task list is full! Cannot add more tasks.\n");
        return;
    }
    printf("Enter the task: ");
    getchar();
    scanf("%[^\n]", tasks[*taskCount]);

    int len = strlen(tasks[*taskCount]);
    if (len > 0 && tasks[*taskCount][len - 1] == '\n')
    {
        tasks[*taskCount][len - 1] = '\0';
    }

    (*taskCount)++;
    printf("Task added successfully.\n");
}

void viewTasks(char tasks[MAX_TASKS][MAX_LENGTH], int taskCount)
{
    if (taskCount == 0)
    {
        printf("No tasks to show!\n");
        return;
    }
    printf("\nYour To-Do List:\n");
    for (int i = 0; i < taskCount; i++)
    {
        printf("%d. %s\n", i + 1, tasks[i]);
    }
}

void removeTask(char tasks[MAX_TASKS][MAX_LENGTH], int *taskCount)
{
    if (*taskCount == 0)
    {
        printf("No tasks to remove!\n");
        return;
    }

    int taskNumber;
    printf("Enter the task number to remove: ");
    scanf("%d", &taskNumber);

    if (taskNumber < 1 || taskNumber > *taskCount)
    {
        printf("Invalid task number!\n");
        return;
    }

    for (int i = taskNumber - 1; i < *taskCount - 1; i++)
    {
        strcpy(tasks[i], tasks[i + 1]);
    }

    (*taskCount)--;
    printf("Task removed successfully.\n");
}

void write(char *filename, char tasks[MAX_LENGTH][MAX_TASKS], int taskCount)
{
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "Your To-Do List:\n");
    for (int i = 0; i < taskCount; i++)
    {
        fprintf(fp, "%d. %s\n", i + 1, tasks[i]);
    }

    fclose(fp);
}


int main()
{
    char tasks[MAX_TASKS][MAX_LENGTH];
    int taskCount = 0;
    int choice;
    int num;
    int txt;

    while (1)
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("How many Tasks You want to add: ");
            scanf("%d", &num);
            for (int i = 0; i < num; i++)
            {
                addTask(tasks, &taskCount);
            }
            printf("Do You want to save it to a txt file?(type 1 for yes, 0 for no): ");
            scanf("%d", &txt);
            if (txt == 0)
            {
                printf("Added all tasks");
                break;
            }
            else
            {
                char text[100] = "todo.txt";
                write(text, tasks, taskCount);
                printf("Added successfully to todo.txt file");
            }
        case 2:
            viewTasks(tasks, taskCount);
            break;
        case 3:
            removeTask(tasks, &taskCount);
            char text[100] = "todo.txt";
            write(text, tasks, taskCount);
            printf("Deleted successfully from todo.txt file");
            break;
        case 4:
            printf("Exiting To-Do List. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
