#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TASK_LENGTH 100
#define FILENAME "tasks.txt"

// Define a structure for tasks
typedef struct {
    char description[MAX_TASK_LENGTH];
    int completed;
} Task;

// Global array to store tasks
Task tasks[MAX_TASKS];
int taskCount = 0;

// Function prototypes
void loadTasks();
void saveTasks();
void addTask(const char *description);
void viewTasks();
void markTaskAsCompleted(int taskIndex);
void removeTask(int taskIndex);
void clearAllTasks();
void displayMenu();

int main() {
    int choice, taskIndex;
    char taskDescription[MAX_TASK_LENGTH];

    // Load tasks from file at startup
    loadTasks();

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                printf("Enter task description: ");
                fgets(taskDescription, MAX_TASK_LENGTH, stdin);
                taskDescription[strcspn(taskDescription, "\n")] = 0; // Remove newline
                addTask(taskDescription);
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                viewTasks();
                if (taskCount > 0) {
                    printf("Enter task number to mark as completed: ");
                    scanf("%d", &taskIndex);
                    getchar(); // Consume the newline character
                    markTaskAsCompleted(taskIndex - 1); // Subtract 1 because array is 0-indexed
                }
                break;
            case 4:
                viewTasks();
                if (taskCount > 0) {
                    printf("Enter task number to remove: ");
                    scanf("%d", &taskIndex);
                    getchar(); // Consume the newline character
                    removeTask(taskIndex - 1); // Subtract 1 because array is 0-indexed
                }
                break;
            case 5:
                clearAllTasks();
                break;
            case 6:
                saveTasks();
                printf("Tasks saved. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Load tasks from file
void loadTasks() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No tasks file found. Starting with empty task list.\n");
        return;
    }

    taskCount = 0;
    while (!feof(file) && taskCount < MAX_TASKS) {
        fscanf(file, "%d|", &tasks[taskCount].completed);
        fgets(tasks[taskCount].description, MAX_TASK_LENGTH, file);
        
        // Remove newline character if present
        size_t len = strlen(tasks[taskCount].description);
        if (len > 0 && tasks[taskCount].description[len-1] == '\n') {
            tasks[taskCount].description[len-1] = '\0';
        }
        
        taskCount++;
    }

    fclose(file);
    printf("Loaded %d tasks from file.\n", taskCount);
}

// Save tasks to file
void saveTasks() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error: Could not save tasks to file.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%d|%s\n", tasks[i].completed, tasks[i].description);
    }

    fclose(file);
    printf("Tasks saved successfully!\n");
}

// Add a new task
void addTask(const char *description) {
    if (taskCount >= MAX_TASKS) {
        printf("Error: Task list is full!\n");
        return;
    }

    strcpy(tasks[taskCount].description, description);
    tasks[taskCount].completed = 0; // Not completed by default
    taskCount++;
    printf("Task added successfully!\n");
    saveTasks();
}

// Display all tasks
void viewTasks() {
    if (taskCount == 0) {
        printf("No tasks in the list.\n");
        return;
    }

    printf("\n----- Your To-Do List -----\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. [%c] %s\n", 
               i + 1, 
               tasks[i].completed ? 'X' : ' ', 
               tasks[i].description);
    }
    printf("---------------------------\n\n");
}

// Mark a task as completed
void markTaskAsCompleted(int taskIndex) {
    if (taskIndex < 0 || taskIndex >= taskCount) {
        printf("Invalid task number!\n");
        return;
    }

    tasks[taskIndex].completed = 1;
    printf("Task marked as completed!\n");
    saveTasks();
}

// Remove a task
void removeTask(int taskIndex) {
    if (taskIndex < 0 || taskIndex >= taskCount) {
        printf("Invalid task number!\n");
        return;
    }

    // Shift all elements after the deleted one
    for (int i = taskIndex; i < taskCount - 1; i++) {
        strcpy(tasks[i].description, tasks[i + 1].description);
        tasks[i].completed = tasks[i + 1].completed;
    }

    taskCount--;
    printf("Task removed successfully!\n");
    saveTasks();
}

// Clear all tasks
void clearAllTasks() {
    char confirmation;
    printf("Are you sure you want to clear all tasks? (y/n): ");
    scanf("%c", &confirmation);
    getchar(); // Consume the newline character

    if (confirmation == 'y' || confirmation == 'Y') {
        taskCount = 0;
        printf("All tasks cleared!\n");
        saveTasks();
    } else {
        printf("Operation cancelled.\n");
    }
}

// Display the menu
void displayMenu() {
    printf("\n===== TO-DO LIST MANAGER =====\n");
    printf("1. Add a new task\n");
    printf("2. View all tasks\n");
    printf("3. Mark a task as completed\n");
    printf("4. Remove a task\n");
    printf("5. Clear all tasks\n");
    printf("6. Save and exit\n");
    printf("=============================\n");
}