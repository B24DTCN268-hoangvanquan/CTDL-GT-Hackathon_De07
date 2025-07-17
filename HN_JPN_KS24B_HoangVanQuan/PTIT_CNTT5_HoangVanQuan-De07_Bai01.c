#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Order {
    int id;
    char customer[100];
    int status;
    char total[100];
} Order;

typedef struct NodeDouble {
    Order data;
    struct NodeDouble* prev;
    struct NodeDouble* next;
} NodeDouble;

typedef struct NodeSingle {
    Order data;
    struct NodeSingle* next;
} NodeSingle;

NodeDouble* headDouble = NULL;
NodeSingle* headSingle = NULL;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Order createOrder() {
    Order o;
    printf("Nhập mã đơn hàng: ");
    scanf("%d", &o.id);
    clearInputBuffer();
    printf("Nhập tên khách hàng: ");
    fgets(o.customer, sizeof(o.customer), stdin);
    o.customer[strcspn(o.customer, "\n")] = '\0';
    printf("Nhập tổng tiền: ");
    fgets(o.total, sizeof(o.total), stdin);
    o.total[strcspn(o.total, "\n")] = '\0';
    o.status = 0;
    return o;
}

void addOrder() {
    Order o = createOrder();
    NodeDouble* newNode = (NodeDouble*)malloc(sizeof(NodeDouble));
    newNode->data = o;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (headDouble == NULL) {
        headDouble = newNode;
    } else {
        NodeDouble* temp = headDouble;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
    printf("Đã thêm đơn hàng thành công!\n");
}

void displayUnshippedOrders() {
    printf("\nDanh sách đơn hàng:\n");
    NodeDouble* temp = headDouble;
    if (temp == NULL) {
        printf("Không có đơn hàng.\n");
        return;
    }
    while (temp != NULL) {
        printf("ID: %d | Khách hàng: %s | Tổng tiền: %s | Trạng thái: Chưa giao\n",
               temp->data.id, temp->data.customer, temp->data.total);
        temp = temp->next;
    }
}
void displayAllOrders() {
    displayUnshippedOrders();
}

void deleteOrder() {
    int id;
    printf("Nhập ID đơn hàng muốn xoá: ");
    scanf("%d", &id);
    clearInputBuffer();
    NodeDouble* temp = headDouble;
    while (temp != NULL) {
        if (temp->data.id == id) {
            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                headDouble = temp->next;
            if (temp->next != NULL)
                temp->next->prev = temp->prev;
            free(temp);
            printf("Đã xoá đơn hàng có ID %d\n", id);
            return;
        }
        temp = temp->next;
    }
    printf("Không tìm thấy đơn hàng có ID %d trong danh sách chưa giao.\n", id);
}

void updateOrder() {
    int id;
    printf("Nhập ID đơn hàng cần cập nhật: ");
    scanf("%d", &id);

}

void menu() {
    printf("\n——————— ORDER MANAGER ———————\n");
    printf("1. Thêm đơn hàng mới\n");
    printf("2. Hiển thị danh sách đơn hàng\n");
    printf("3. Xoá đơn hàng (theo ID)\n");
    printf("4. Cập nhật thông tin đơn hàng\n");
    printf("5. Đánh dấu đơn hàng đã giao\n");
    printf("6. Sắp xếp đơn hàng theo tổng tiền\n");
    printf("7. Tìm kiếm đơn hàng\n");
    printf("8. Thoát chương trình\n");
    printf("Chọn chức năng: ");
}

int main() {
    int choice;
    do {
        menu();
        scanf("%d", &choice);
        clearInputBuffer();
        switch (choice) {
            case 1:
                addOrder();
                break;
            case 2:
                displayAllOrders();
                break;
            case 3:
                deleteOrder();
                break;
            case 4:
                break;
            case 5:

                break;
            case 8:
                printf("Thoát chương trình...\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
        }
    } while (choice != 8);
    return 0;
}
