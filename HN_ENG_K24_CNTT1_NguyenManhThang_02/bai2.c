#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct GraphicAction {
    char action[100];
    char timeStamp[30];
}GraphicAction;

typedef struct Stack {
    GraphicAction *graphic;
    int top;
    int cap;
}Stack;

Stack* createStack(int cap) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->graphic = (GraphicAction*)malloc(sizeof(GraphicAction)*cap);
    stack->cap = cap;
    stack->top = -1;
    return stack;
}
int isEmpty(Stack *stack) {
    if (stack->top == -1) {
        return 1;
    }
    return 0;
}
void push(Stack *undo, GraphicAction graphic) {
    if (undo->top == undo->cap -1) {
        printf("stack full\n");
        return;
    }
    undo->top++;
    undo->graphic[undo->top] = graphic;
}
GraphicAction pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("stack is empty\n");
    }else {
        stack->top--;
        return stack->graphic[stack->top];
    }
}

void display(Stack *stack) {
    if (isEmpty(stack)) {
        printf("stack trong\n");
        return;
    }
    for (int i= stack->top; i >=0; i--) {
        printf("%s ",stack->graphic[i].action);
        printf("%s ",stack->graphic[i].timeStamp);
        printf("\n");
    }
    printf("\n");
}
int main() {
    int choice;
    Stack *undo = createStack(10);
    Stack *redo = createStack(10);
    do {
        printf("MENU\n"
               "1. DRAW: Thuc hien ve\n"
               "2. UNDO: Hoan tac thao tac gan nhat\n"
               "3. REDO: Phuc hoi thao tac vua undo\n"
               "4. PRINT: Hien thi toan bo thao tac ve\n"
               "5. EXIT: Thoat chuong trinh\n"
               "Lua chon cua ban: ");
        scanf("%d",&choice);
        getchar();
        switch (choice) {
            case 1:
                GraphicAction graphic;
                printf("nhap hanh dong ve: ");
                fgets(graphic.action, 100, stdin);

                printf("nhap thoi gian: ");
                fgets(graphic.timeStamp,30,stdin);

                push(undo,graphic);
                redo = createStack(10);
                break;
            case 2:
                if (isEmpty(undo)) {
                    printf("chua co hanh dong ve nao\n");
                    break;
                }
                GraphicAction swap1 = pop(undo);
                push(redo, swap1);
                break;
            case 3:
                if (isEmpty(redo)) {
                    printf("chua co hanh dong ve nao\n");
                    break;
                }
                GraphicAction swap = pop(redo);
                push(undo, graphic);
                break;
            case 4:
                display(undo);
                break;
            case 5:
                printf("thoat chuong trinh\n");
                return 0;
            default:
                printf("lua chon ko hop le");
        }
    }while (choice != 5);
}