#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_LENGTH 100
#define MEDIUM_SIZE_LENGTH 50

typedef struct {
    int id;
    char title[MAX_SIZE_LENGTH];
    char author[MAX_SIZE_LENGTH];
    char category[MEDIUM_SIZE_LENGTH];
    float price;
} Book;

typedef struct Node {
    Book book;
    struct Node* next;
} Node;

typedef struct DoubleNode {
    Book book;
    struct DoubleNode* prev;
    struct DoubleNode* next;
} DoubleNode;

Node* head = NULL;
DoubleNode* readHead = NULL;
int nextId = 1;

void addBook() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->book.id = nextId++;
    printf("Nhap ten sach: ");
    getchar();
    fgets(newNode->book.title, MAX_SIZE_LENGTH, stdin);
    newNode->book.title[strcspn(newNode->book.title, "\n")] = 0;
    printf("Nhap tac gia: ");
    fgets(newNode->book.author, MAX_SIZE_LENGTH, stdin);
    newNode->book.author[strcspn(newNode->book.author, "\n")] = 0;
    printf("Nhap the loai: ");
    fgets(newNode->book.category, MEDIUM_SIZE_LENGTH, stdin);
    newNode->book.category[strcspn(newNode->book.category, "\n")] = 0;
    printf("Nhap gia sach: ");
    scanf("%f", &newNode->book.price);
    newNode->next = head;
    head = newNode;
    printf("Them sach thanh cong");
}

void displayBooks() {
    Node* current = head;
    if (!current) {
        printf("Danh sach sach trong");
        return;
    }
    printf("Danh sach sach:");
    while (current) {
        printf("ID: %d, Ten: %s, Tac gia: %s, The loai: %s, Gia: %.2f\n",
               current->book.id, current->book.title, current->book.author,
               current->book.category, current->book.price);
        current = current->next;
    }
}

void deleteBook() {
    int id;
    printf("Nhap ID sach can xoa: ");
    scanf("%d", &id);
    Node* current = head;
    Node* prev = NULL;
    while (current && current->book.id != id) {
        prev = current;
        current = current->next;
    }
    if (!current) {
        printf("Khong tim thay sach ");
        return;
    }
    if (prev) {
        prev->next = current->next;
    } else {
        head = current->next;
    }
    free(current);
    printf("Xoa sach thanh cong");
}

void updateBook() {
    int id;
    printf("Nhap ID sach can cap nhap: ");
    scanf("%d", &id);
    Node* current = head;
    while (current && current->book.id != id) {
        current = current->next;
    }
    if (!current) {
        printf("Khong tim thay sach ");
        return;
    }
    printf("Nhap ten sach moi: ");
    getchar();
    fgets(current->book.title, MAX_SIZE_LENGTH, stdin);
    current->book.title[strcspn(current->book.title, "\n")] = 0;
    printf("Nhap tac gia moi: ");
    fgets(current->book.author, MAX_SIZE_LENGTH, stdin);
    current->book.author[strcspn(current->book.author, "\n")] = 0;
    printf("Nhap the loai moi: ");
    fgets(current->book.category, MEDIUM_SIZE_LENGTH, stdin);
    current->book.category[strcspn(current->book.category, "\n")] = 0;
    printf("Nhap gia sach moi: ");
    scanf("%f", &current->book.price);
    printf("Cap nhat sach thanh cong");
}

void markBookAsRead() {
    int id;
    printf("Nhap ID sach da doc: ");
    scanf("%d", &id);
    Node* current = head;
    Node* prev = NULL;
    while (current && current->book.id != id) {
        prev = current;
        current = current->next;
    }
    if (!current) {
        printf("Khong tim thay sach ");
        return;
    }
    DoubleNode* newDoubleNode = (DoubleNode*)malloc(sizeof(DoubleNode));
    newDoubleNode->book = current->book;
    newDoubleNode->next = readHead;
    newDoubleNode->prev = NULL;
    if (readHead) {
        readHead->prev = newDoubleNode;
    }
    readHead = newDoubleNode;
    if (prev) {
        prev->next = current->next;
    } else {
        head = current->next;
    }
    free(current);
    printf("Da danh dau sach doc thanh cong");
}

void sortBooksByPrice() {
    if (!head || !head->next) return;
    Node* sorted = NULL;
    Node* current = head;
    while (current) {
        Node* next = current->next;
        if (!sorted || sorted->book.price >= current->book.price) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next && temp->next->book.price < current->book.price) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head = sorted;
    printf("Da sap xech sach theo gia tang dan");
}

void searchBookByTitle() {
    char title[MAX_SIZE_LENGTH];
    printf("Nhap ten sach can tim: ");
    getchar();
    fgets(title, MAX_SIZE_LENGTH , stdin);
    title[strcspn(title, "\n")] = 0;
    Node* current = head;
    int found = 0;
    while (current) {
        if (strstr(current->book.title, title)) {
            printf("ID: %d, Ten: %s, Tac gia: %s, The loai: %s, Gia: %.2f\n",
                   current->book.id, current->book.title, current->book.author,
                   current->book.category, current->book.price);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("Ko tim thay sach ");
    }
}

void printfMenu(){
    printf("\n--- BOOK MANAGER ---\n");
    printf("1.Them sach\n");
    printf("2.Hien thi danh sach sach\n");
    printf("3.Xoa sach\n");
    printf("4.Cap nhat thong tin sach\n");
    printf("5.Danh dau sach da doc\n");
    printf("6.Sap xep sach theo gia tang dan\n");
    printf("7.Tim kiem sach theo tieu de\n");
    printf("8.Thoat\n");
}


int main() {
    int choice;
    while (choice != 8) {
        printfMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                deleteBook();
                break;
            case 4:
                updateBook();
                break;
            case 5:
                markBookAsRead();
                break;
            case 6:
                sortBooksByPrice();
                break;
            case 7:
                searchBookByTitle();
                break;
            case 8:
                return 0;
            default: printf("Lua chon ko hop le");
        }
    }
}