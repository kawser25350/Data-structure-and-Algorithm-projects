#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    char title[50];
    char description[1000];
    char due_date[12];
    char status[20];
    struct Task* next;
    struct Task* prev;
};

struct TaskManager {
    struct Task* head;
};

void priority(struct TaskManager* manager);
void Menu(struct TaskManager* manager);
void add_task(struct TaskManager* manager);
void search_task(struct TaskManager* manager);
void remove_expired_tasks(struct TaskManager* manager);
void update_task_status(struct TaskManager* manager);
void display_all_tasks(struct TaskManager* manager);
void duedate_sort(struct TaskManager* manager);
void status_sort(struct TaskManager* manager);

int main() {
    struct TaskManager manager;
    manager.head = NULL;
    Menu(&manager);

    return 0;
}

void add_task(struct TaskManager* manager) {
    struct Task* new_task = (struct Task*)malloc(sizeof(struct Task));

    printf("\nEnter task title: ");
    scanf(" %[^\n]", new_task->title);

    printf("Enter task description: ");
    scanf(" %[^\n]", new_task->description);

    printf("Enter due date (MM/DD/YYYY): ");
    scanf(" %11[^\n]", new_task->due_date);

    printf("Enter task status: ");
    scanf(" %[^\n]", new_task->status);

    new_task->next = manager->head;
    new_task->prev = NULL;

    if (manager->head != NULL) {
        manager->head->prev = new_task;
    }

    manager->head = new_task;

    printf("Task added successfully!\n\n");
}

void search_task(struct TaskManager* manager) {
    if (manager->head == NULL) {
        printf("\n\nfound no data in list.\n");
    } else {
        printf("\n\n");
        char search_title[50];
        printf("Enter task title to search: ");
        scanf(" %[^\n]", search_title);

        struct Task* current = manager->head;

        while (current != NULL) {
            if (strcmp(current->title, search_title) == 0) {
                printf("\n-----Task Found:------\n");
                printf("Title: %s\n", current->title);
                printf("Description: %s\n", current->description);
                printf("Due Date: %s\n", current->due_date);
                printf("Status: %s\n", current->status);
                return;
            }
            current = current->next;
        }

        printf("--Task with title '%s' not found.--\n", search_title);
    }
}

void remove_expired_tasks(struct TaskManager* manager) {
    if (manager->head == NULL) {
        printf("\nfound no data in list.\n");
    } else {
        char inputDate[12];
        printf("Enter date to check for expired tasks (MM/DD/YYYY): ");
        scanf(" %11[^\n]", inputDate);

        struct Task* current = manager->head;
        struct Task* prev = NULL;

        while (current != NULL) {
            if (strcmp(current->due_date, inputDate) < 0) {
                if (prev == NULL) {
                    manager->head = current->next;
                    if (current->next != NULL) {
                        current->next->prev = NULL;
                    }
                } else {
                    prev->next = current->next;
                    if (current->next != NULL) {
                        current->next->prev = prev;
                    }
                }

                free(current);
                current = prev == NULL ? manager->head : prev->next;
            } else {
                prev = current;
                current = current->next;
            }
        }

        printf("Expired tasks removed.\n");
    }
}

void update_task_status(struct TaskManager* manager) {
    if (manager->head == NULL) {
        printf("\nfound no data in list.\n");
    } else {
        char search_title[50];
        printf("Enter task title to update status: ");
        scanf(" %[^\n]", search_title);

        struct Task* current = manager->head;

        while (current != NULL) {
            if (strcmp(current->title, search_title) == 0) {
                printf("Enter new task status: ");
                scanf(" %[^\n]", current->status);
                printf("Task status updated successfully!\n");
                return;
            }
            current = current->next;
        }

        printf("Task with title '%s' not found.\n", search_title);
    }
}

void display_all_tasks(struct TaskManager* manager) {
    if (manager->head == NULL) {
        printf("\nfound no data in list.\n");
    } else {
        printf("\nALL TASK:\n");
        struct Task* current = manager->head;

        while (current != NULL) {
            printf("\nTitle: %s\n", current->title);
            printf("Description: %s\n", current->description);
            printf("Due Date: %s\n", current->due_date);
            printf("Status: %s\n", current->status);
            printf("\n");
            current = current->next;
        }
    }
}

void duedate_sort(struct TaskManager* manager) {
    int swapped = 1;
    struct Task* temp;

    while (swapped) {
        swapped = 0;
        struct Task* current = manager->head;
        struct Task* prev = NULL;

        while (current != NULL && current->next != NULL) {
            if (strcmp(current->due_date, current->next->due_date) > 0) {

                temp = current->next;
                current->next = temp->next;
                temp->next = current;
                temp->prev = prev;

                if (prev == NULL) {
                    manager->head = temp;
                    manager->head->prev = NULL;
                } else {
                    prev->next = temp;
                }

                swapped = 1;
            }

            prev = (swapped == 0) ? current : prev;
            current = current->next;
        }
    }
}

void status_sort(struct TaskManager* manager) {
    int swapped;
    struct Task* temp;

    do {
        swapped = 0;
        struct Task* current = manager->head;

        while (current->next != NULL) {
            if (strcmp(current->status, current->next->status) > 0) {

                temp = current->next;
                current->next = temp->next;
                temp->next = current;
                temp->prev = current->prev;

                if (current == manager->head) {
                    manager->head = temp;
                    manager->head->prev = NULL;
                } else {
                    struct Task* prev = manager->head;
                    while (prev->next != current) {
                        prev = prev->next;
                    }
                    prev->next = temp;
                }

                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

void priority(struct TaskManager* manager) {
    if (manager->head == NULL) {
        printf("\nNO data in list.\n");
    } else {
        int c1;
        while (1) {
            printf("\n------------------------------------------\n");
            printf("Handling Priority Menu:\n");
            printf("**************\n");
            printf("1. Short the list by due date (MM/DD/YYYY)\n");
            printf("2. Sort the list by task status\n");
            printf("3. Back to the main menu\n");
            printf("**************\n");
            printf(">> ");

            scanf("%d", &c1);

            if (c1 == 1) {
                duedate_sort(manager);
                printf("\n---Sorted by due date.---\n");
            } else if (c1 == 2) {
                status_sort(manager);
                printf("\nsorted by status.\n");
            } else if (c1 == 3) {
                Menu(manager);
                printf("\nReturn to the main menu.\n");
            } else {
                printf("INVALID INPUT.\n");
            }
        }
    }
}

void Menu(struct TaskManager* manager) {
    int choice;

    while (1) {
        printf("\n----------------------------------------\n");
        printf("Task Management System Menu:\n");
        printf("**************\n");
        printf("1. Add a New Task\n");
        printf("2. Search for a Task\n");
        printf("3. Remove Expired Tasks\n");
        printf("4. Update Task Status\n");
        printf("5. Display All Tasks\n");
        printf("6. Handling priority(sub-MENU)\n");
        printf("0. Exit\n");
        printf("**************\n");

        printf(">>");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_task(manager);
                break;
            case 2:
                search_task(manager);
                break;
            case 3:
                remove_expired_tasks(manager);
                break;
            case 4:
                update_task_status(manager);
                break;
            case 5:
                display_all_tasks(manager);
                break;
            case 6:
                priority(manager);
                break;
            case 0:
                printf("Exit_......\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }
}
