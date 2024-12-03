#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define asize 500

typedef struct {
    char name[20];
    int age;
    char gender;
    char contact[18];
    char email[39];
} customer;

typedef struct {
    char name[20];
    char contact[18];
    char apnt_date[11];
    float apnt_time;
} apnt;

typedef struct Node {
    customer data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} List;

typedef struct {
    apnt arr[asize];
    int front;
    int rear;
} apntQueue;


int serialnm = 0;
int cnt = 0;

void menu();
customer input();
void list_input(List* list, customer newCustomer);
void print_list(List* list);
void addAppointment(apntQueue* app, apnt tmp[]);
void callByAppointmentSerial(apntQueue* app);
void watchAllSerialNumbers(apntQueue* app);
void sortAppointmentQueue(apntQueue* app);

int main() {
    List* male, *female;
    male = malloc(sizeof(List));
    female = malloc(sizeof(List));

    apntQueue* app;
    app = malloc(sizeof(apntQueue));

    apnt tmp[200];

    male->head = NULL;
    male->tail = NULL;
    female->head = NULL;
    female->tail = NULL;

    app->front = 0;
    app->rear = 0;

    customer newCustomer;

    while (1) {
        int c;
        menu();
        scanf("%d", &c);

        switch (c) {
        case 1:
            newCustomer = input();

            if (newCustomer.gender == 'm' || newCustomer.gender == 'M') {
                list_input(male, newCustomer);
            }
            else {
                list_input(female, newCustomer);
            }
            break;

        case 2:
            print_list(male);
            print_list(female);
            break;

        case 3:
            addAppointment(app, tmp);
            break;

        case 4:
            callByAppointmentSerial(app);
            break;

        case 5:
            watchAllSerialNumbers(app);
            break;

        case 6:
            free(male);
            free(female);
            free(app);
            exit(0);

        default:
            printf("Invalid option.\n");
            break;
        }
    }

    return 0;
}

void menu() {
    printf("\n\n----------------------------------------------------------\n");
    printf("SERVICE MANAGEMENT SYSTEM-(appointment- 500 at once     )  |\n");
    printf("-----------------------------------------------------------|\n");
    printf("1. ADD customer's.                                         |\n");
    printf("2. See all customer's data.                                |\n");
    printf("3. Add Appointment.                                        |\n");
    printf("4. Call by appointment serial.                             |\n");
    printf("5. Watch all customer's serial number.                     |\n");
    printf("6. Exit.                                                   |\n");
    printf("***********************************************************|\n");
    printf(">> ");
}

customer input() {
    customer newCustomer;

    printf("Enter data for new customer:\n\n");
    printf("Customer name: ");
    scanf(" %[^\n]", newCustomer.name);
    printf("Customer age: ");
    scanf("%d", &newCustomer.age);
    printf("Customer gender: (ONLY-(M/F):");
    scanf(" %c", &newCustomer.gender);

    printf("Customer contact number(18 digit): ");
    scanf(" %[^\n]", newCustomer.contact);
    printf("Customer email: ");
    scanf(" %[^\n]", newCustomer.email);

    return newCustomer;
}

void list_input(List* list, customer newCustomer) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = newCustomer;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        newNode->prev = NULL;
    }
    else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void print_list(List* list) {
    Node* current = list->head;

    if (!current) {
        printf("No data has been received.\n");
    }
    else {
        printf("\n\n");
        printf(" ------------------------------------------------------------------------------------------------\n");
        printf("|                                DATA LISTS                                                     |\n");
        printf(" ------------------------------------------------------------------------------------------------\n");
        printf("| %-20s | %-3s | %-6s | %-13s | %-40s |\n", "NAME", "AGE", "GENDER", "CONTACT", "EMAIL");
        printf("--------------------------------------------------------------------------------------------------\n");

        while (current) {
            printf("| %-20s | %-3d | %-6c | %-13s | %-40s |\n", current->data.name, current->data.age, current->data.gender, current->data.contact, current->data.email);
            current = current->next;
        }

        printf(" ------------------------------------------------------------------------------------------------\n");
    }
}

void addAppointment(apntQueue* app, apnt tmp[]) {
    if (cnt >= 199) {
        printf("Appointment queue is full.\n");
        return;
    }

    cnt += 1;

    printf("Name: ");
    scanf(" %[^\n]", tmp[cnt].name);
    printf("Contact: ");
    scanf(" %[^\n]", tmp[cnt].contact);
    printf("Appointment Date:(mm/dd/yyyy) ");
    scanf(" %s", tmp[cnt].apnt_date);
    printf("Time:(24:00) ");
    scanf("%f", &tmp[cnt].apnt_time);

    app->arr[app->rear] = tmp[cnt];
    app->rear = (app->rear + 1) % asize;

    sortAppointmentQueue(app);

    printf("Appointment added successfully!\n");
}

void sortAppointmentQueue(apntQueue* app) {
    int i, j;
    for (i = app->front + 1; i < app->rear; i++) {
        for (j = app->front + 1; j < app->rear; j++) {

            if (strcmp(app->arr[j - 1].apnt_date, app->arr[j].apnt_date) > 0 || (strcmp(app->arr[j - 1].apnt_date, app->arr[j].apnt_date) == 0 && app->arr[j - 1].apnt_time > app->arr[j].apnt_time)) {

                apnt temp = app->arr[j - 1];
                app->arr[j - 1] = app->arr[j];
                app->arr[j] = temp;
            }
        }
    }
}

void callByAppointmentSerial(apntQueue* app) {
    if (app->front == app->rear) {
        printf("No appointments in the queue.\n");
        serialnm = 0;
        return;
    }
    serialnm++;
    printf("\nAppointment Details:\n");
    printf("serial number %d :\n", serialnm);
    printf("Name: %s\n", app->arr[app->front].name);
    printf("Time: %.2f\n", app->arr[app->front].apnt_time);

    app->front = (app->front + 1) % asize;

    printf("\nAppointment served.\n");
}

void watchAllSerialNumbers(apntQueue* app) {
    if (app->front == app->rear) {
        printf("No appointments in the queue.\n");
        return;
    }

    printf("\nAll Serial Numbers:\n");
    printf(" ---------------------------------------------------\n");
    printf("|          APPOINTMENT SERIAL NUMBERS             |\n");
    printf(" ---------------------------------------------------\n");
    for (int i = app->front; i < app->rear; i++) {
        printf("| %-3d | %-20s | %-13s | %-4.2f |\n", i + 1, app->arr[i].name, app->arr[i].apnt_date, app->arr[i].apnt_time);
    }
    printf(" -------------------------------------------------\n");
}
