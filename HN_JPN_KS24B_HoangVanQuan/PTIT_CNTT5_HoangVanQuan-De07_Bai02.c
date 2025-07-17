#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Operation {
    char url[100];
    char timeStamp[100];
} Operation;

typedef struct Node {
    Operation data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

void init(Stack* s) {
    s->top = NULL;
}

int isEmpty(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, Operation op) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = op;
    newNode->next = s->top;
    s->top = newNode;
}

Operation pop(Stack* s) {
    Operation op = {"", ""};
    if (!isEmpty(s)) {
        Node* temp = s->top;
        op = temp->data;
        s->top = temp->next;
        free(temp);
    }
    return op;
}
Operation peek(Stack* s) {
    if (!isEmpty(s))
        return s->top->data;
    Operation empty = {"", ""};
    return empty;
}

void getCurrentTime(char* buffer) {
    time_t now = time(NULL);
    strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", localtime(&now));
}

int main() {
    Stack backStack, forwardStack;
    init(&backStack);
    init(&forwardStack);

    int choice;
    char url[100];

    while (1) {
        printf("\n——————————— WEB HISTORY ———————————\n");
        printf("1. Truy cập vào trang web mới\n");
        printf("2. Quay lại trang web trước\n");
        printf("3. Đi đến trang web sau nếu từng bị back\n");
        printf("4. In trang web hiện tại\n");
        printf("5. Kết thúc chương trình\n");
        printf("Chọn chức năng: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            printf("Nhập địa chỉ web: ");
            fgets(url, sizeof(url), stdin);
            url[strcspn(url, "\n")] = '\0';

            Operation op;
            strcpy(op.url, url);
            getCurrentTime(op.timeStamp);
            push(&backStack, op);

            while (!isEmpty(&forwardStack))
                pop(&forwardStack);

            printf("Đã truy cập: %s lúc %s\n", op.url, op.timeStamp);

        } else if (choice == 2) {
            if (isEmpty(&backStack)) {
                printf("Không có trang để quay lại.\n");
            } else {
                Operation current = pop(&backStack);
                push(&forwardStack, current);
                if (!isEmpty(&backStack)) {
                    Operation prev = peek(&backStack);
                    printf("Quay lại trang: %s\n", prev.url);
                } else {
                    printf("Không còn trang trước.\n");
                }
            }

        } else if (choice == 5) {
            printf("Đã thoát chương trình.\n");
            break;

        } else {
            printf("Lựa chọn không hợp lệ. Vui lòng chọn 1, 2 hoặc 5.\n");
        }
    }

    return 0;
}
