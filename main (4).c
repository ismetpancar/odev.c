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
        printf("1 - urun ekleme\n");
        printf("2 - urun guncelleme\n");
        printf("3 - urun lıste\n");
        printf("4 - urun sılme\n");
        printf("5 - cıkıs\n");

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
                printf("cıkıs yapılıyor...\n");
                exit(0);
            default:
                printf("Invalid selection. Tekrar deneyın.\n");
        }
    }
}

void addProduct() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (!file) {
        printf("dosya acılamadı.");
        return;
    }

    Product p;

    printf("urun id gir: ");
    scanf("%d", &p.id);
    printf("urun ismi gir: ");
    scanf("%s", p.name);
    printf("urun fiyat gir: ");
    scanf("%f", &p.price);
    printf("urun stok gir : ");
    scanf("%d", &p.stock);

    if (fwrite(&p, sizeof(Product), 1, file) == 1) {
        printf("urun basarıyla eklendi.\n");
    } else {
        printf("urun eklenirken hata olustu.\n");
    }

    fclose(file);
}

void updateProduct() {
    FILE *file = fopen(FILE_NAME, "rb+");
    if (!file) {
        printf("dosya acılamadı.");
        return;
    }

    Product p;
    int id, found = 0;

    printf("güncellestirmek icin urun ıd sı girin: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(Product), 1, file)) {
        if (p.id == id) {
            found = 1;

            printf("yeni miktari girin: ");
            scanf("%d", &p.stock);

            fseek(file, -sizeof(Product), SEEK_CUR);

            if (fwrite(&p, sizeof(Product), 1, file) == 1) {
                printf("urunler basarıyla guncellendi:\n");
            } else {
                printf("guncellenirken hata olustu.\n");
            }

            break;
        }
    }

    if (!found) {
        printf("urun bulunamadi.\n");
    }

    fclose(file);
}

void getProducts() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("dosya acilamadi.");
        return;
    }

    Product p;
    int id, found = 0;

    printf("sorgulamak icin ıd girin: ");
    scanf("%d", &id);

    if (id == 0) {
        while (fread(&p, sizeof(Product), 1, file)) {
            printf("ID: %d | isim: %s | fiyat: %.2f | Stok: %d\n", p.id, p.name, p.price, p.stock);
            found++;
        }
    } else {
        while (fread(&p, sizeof(Product), 1, file)) {
            if (p.id == id) {
                printf("ID: %d | isim: %s | fiyat: %.2f | Stok: %d\n", p.id, p.name, p.price, p.stock);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("urun bulunamadi.\n");
    }

    fclose(file);
}

void deleteProduct() {
    FILE *file = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!file || !temp) {
        printf("dosya acilamadi!");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    Product p;
    int id, found = 0;

    printf("silinecek urunun id si girin: ");
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
        printf("urun basariyla silindi.\n");
    } else {
        remove("temp.dat");
        printf("urun bulunamadi.\n");
    }
}