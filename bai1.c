#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Activity {
    int id;
    char type[20];
    int duration;
    int calories;
    char date[20];
}Activity;
typedef struct Node {
    Activity data;
    struct Node* next;
}Node;

Node* createNode (Activity data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
Node* head = NULL;
void add(){
    Activity activity;
    printf("nhap id hoat dong: ");
    scanf("%d",&activity.id);
    getchar();

    printf("nhap loai hoat dong: ");
    fgets(activity.type,20,stdin);
    activity.type[strcspn(activity.type, "\n")] = '\0';

    printf("Nhap thoi gian thuc hien hoat dong: ");
    scanf("%d",&activity.duration);

    printf("Nhap so calo tieu thu: ");
    scanf("%d",&activity.calories);
    getchar();

    printf("Nhap thoi gian thuc hien: ");
    fgets(activity.date,20,stdin);
    activity.date[strcspn(activity.date,"\n")] = '\0';

    Node* newNode = createNode(activity);

    if (head == NULL) {
        head = newNode;
    }else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    printf("them thanh cong\n");
}

void display() {
    Node* temp = head;
    if (temp == NULL) {
        printf("danh sach trong\n");
        return;
    }
    printf("danh sach hoat dong:\n");
    while (temp != NULL) {
        printf("ID: %d\nLoai hoat dong: %s\nThoi gian hoat dong: %d\nCalo tieu thu: %d\nNgay thuc hien: %s\n",temp->data.id, temp->data.type, temp->data.duration,temp->data.calories,temp->data.date);
        temp = temp->next;
    }
}

void delete(){
    int id;
    printf("nhap id hoat dong muon xoa: ");
    scanf("%d",&id);

    Node* current = head;
    Node* temp = NULL;
    while (current != NULL) {
        if (current->data.id == id) {
            if (temp == NULL) {
                head = current->next;
            }else {
                temp->next = current->next;
            }
            free(current);
            printf("xoa thanh cong");
            return;
        }
        temp = current;
        current = current->next;
    }
    printf("ko co hoat dong nay\n");
}

void update() {
    int id;
    printf("nhap id can cap nhat: ");
    scanf("%d",&id);
    getchar();
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data.id == id) {
            printf("nhap kieu hoat dong: ");
            fgets(temp->data.type,20,stdin);
            temp->data.type[strcspn(temp->data.type, "\n")] = '\0';

            printf("nhap thoi gian thuc hien: ");
            scanf("%d",&temp->data.duration);

            printf("nhap so luong calo tieu thu: ");
            scanf("%d",&temp->data.calories);
            getchar();
            printf("nhap ngay thuc hien: ");
            fgets(temp->data.date,20,stdin);
            temp->data.date[strcspn(temp->data.date, "\n")] = '\0';

            printf("cap nhat thong tin thanh cong\n");
            return;
        }
        temp = temp->next;
    }
    printf("ko co hoat dong nay\n");
}

void sumCalo() {
    char day[20];
    printf("nhap nhap ngay muon tinh luong calo: ");
    fgets(day,20,stdin);
    fflush(stdin);
    int sum = 0;
    Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data.date,day)==0) {
            sum += temp->data.calories;
        }
        temp = temp->next;
    }
    if (sum != 0) {
        printf("luong calo tieu thu: %d\n",sum);
    }else {
        printf("ngay nay ko tieu thu calo\n");
    }
}

void sortByCalo() {
    if (!head || !head->next) return;

    Node *i, *j;
    for (i = head; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data.calories > j->data.calories) {
                Activity temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    printf("sap xep thanh cong.\n");
}

void searchByType() {
    char keyword[20];
    printf("Nhap kieu hoat dong muon tim: ");
    fgets(keyword, 20, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    Node* current = head;
    int found = 0;
    while (current != NULL) {
        if (strstr(current->data.type, keyword)) {
            printf("Tim thay ket qua\nID: %d\nLoai hoat dong: %s\nThoi gian hoat dong: %d\nCalo tieu thu: %d\nNgay thuc hien: %s\n",current->data.id, current->data.type, current->data.duration,current->data.calories,current->data.date);

            found = 1;
        }
        current = current->next;
    }
    if (!found) printf("Khong tim thay !\n");
}

int main() {
    int choice;
    do {
        printf("MENU\n"
               "1. Them hoat dong trong ngay\n"
               "2. Hien thi danh sach hoat dong\n"
               "3. Xoa hoat dong\n"
               "4. Cap nhat thong tin hoat dong\n"
               "5. Thong ke tong calories tieu thu/ngay\n"
               "6. Sap xep hoat dong\n"
               "7. Tim kiem hoat dong\n"
               "8. Thoat\n"
               "Lua chon cua ban: ");
        scanf("%d",&choice);
        getchar();
        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                display();
                break;
            case 3:
                delete();
                break;
            case 4:
                update();
                break;
            case 5:
                sumCalo();
                break;
            case 6:
                sortByCalo();
                break;
            case 7:
                searchByType();
                break;
            case 8:
                printf("thoat chuong trinh");
                return 0;
            default:
                printf("lua chon ko hop le");
        }
    }while (choice != 8);
}