#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "products.dat"

typedef struct {
    int id;
    char name[20];
    float price;
    int stock;
} Product;

void showMenu();

void addProduct();

void updateProduct();

void getProducts();

void deleteProduct();

int main() {
    showMenu();
    return 0;
}

void showMenu() {
    int choice;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1 - Add Product\n");
        printf("2 - Update Product Stock\n");
        printf("3 - List Products\n");
        printf("4 - Delete Product\n");
        printf("5 - Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
                getProducts();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid selection. Please try again.\n");
        }
    }
}

void addProduct() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (!file) {
        printf("Failed to open file!");
        return;
    }

    Product p;

    printf("Enter product ID: ");
    scanf("%d", &p.id);
    printf("Enter product name: ");
    scanf("%s", p.name);
    printf("Enter product price: ");
    scanf("%f", &p.price);
    printf("Enter product stock: ");
    scanf("%d", &p.stock);

    if (fwrite(&p, sizeof(Product), 1, file) == 1) {
        printf("Product added successfully!\n");
    } else {
        printf("Error occurred while adding the product.\n");
    }

    fclose(file);
}

void updateProduct() {
    FILE *file = fopen(FILE_NAME, "rb+");
    if (!file) {
        printf("Failed to open file!");
        return;
    }

    Product p;
    int id, found = 0;

    printf("Enter product ID to update: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(Product), 1, file)) {
        if (p.id == id) {
            found = 1;

            printf("Enter new stock value: ");
            scanf("%d", &p.stock);

            fseek(file, -sizeof(Product), SEEK_CUR);

            if (fwrite(&p, sizeof(Product), 1, file) == 1) {
                printf("Product stock updated successfully!\n");
            } else {
                printf("Error while updating the product.\n");
            }

            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }

    fclose(file);
}

void getProducts() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("Failed to open file!");
        return;
    }

    Product p;
    int id, found = 0;

    printf("Enter product ID to search (0 for all): ");
    scanf("%d", &id);

    if (id == 0) {
        while (fread(&p, sizeof(Product), 1, file)) {
            printf("ID: %d | Name: %s | Price: %.2f | Stock: %d\n", p.id, p.name, p.price, p.stock);
            found++;
        }
    } else {
        while (fread(&p, sizeof(Product), 1, file)) {
            if (p.id == id) {
                printf("ID: %d | Name: %s | Price: %.2f | Stock: %d\n", p.id, p.name, p.price, p.stock);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }

    fclose(file);
}

void deleteProduct() {
    FILE *file = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!file || !temp) {
        printf("Failed to open files!");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    Product p;
    int id, found = 0;

    printf("Enter product ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(Product), 1, file)) {
        if (p.id == id) {
            found = 1;
            continue;
        }

        fwrite(&p, sizeof(Product), 1, temp);
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove(FILE_NAME);
        rename("temp.dat", FILE_NAME);
        printf("Product deleted successfully.\n");
    } else {
        remove("temp.dat");
        printf("Product not found.\n");
    }
}
