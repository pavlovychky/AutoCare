#include "OrderStorage.h"
#include <cstdio>

void ProductStorage::addProduct(const Product &product)
{
        FILE* file = fopen(PRODUCT_FILE, "ab");
    if (file == NULL) return;

    fwrite(&product, sizeof(Product), 1, file);
    fclose(file);
}

int ProductStorage::getAllProducts(Product products[], int maxCount)
{
     FILE* file = fopen(PRODUCT_FILE, "rb");
    if (file == NULL) return 0;

    int count = 0;

    while (count < maxCount &&
           fread(&products[count], sizeof(Product), 1, file) == 1) {
        count++;
    }

    fclose(file);
    return count;
}

bool ProductStorage::findProductById(int id, Product &result)
{
    FILE* file = fopen(PRODUCT_FILE, "rb");
    if (file == NULL) return false;

    Product temp;

    while (fread(&temp, sizeof(Product), 1, file) == 1) {
        if (temp.id == id) {
            result = temp;
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

bool ProductStorage::updateProduct(const Product &updatedProduct)
{
    FILE* file = fopen(PRODUCT_FILE, "rb+");
    if (file == NULL) return false;

    Product temp;

    while (fread(&temp, sizeof(Product), 1, file) == 1) {
        if (temp.id == updatedProduct.id) {
            fseek(file, -sizeof(Product), SEEK_CUR);
            fwrite(&updatedProduct, sizeof(Product), 1, file);
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

bool ProductStorage::deleteProduct(int id_prod)
{
    FILE* file = fopen(PRODUCT_FILE, "rb");
    if (file == NULL) return false;

    FILE* tempFile = fopen("data/temp.dat", "wb");
    if (tempFile == NULL) {
        fclose(file);
        return false;
    }

    Product temp;
    bool deleted = false;

    while (fread(&temp, sizeof(Product), 1, file) == 1) {
        if (temp.id != id_prod) {
            fwrite(&temp, sizeof(Product), 1, tempFile);
        } else {
            deleted = true;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(PRODUCT_FILE);
    rename("data/temp.dat", PRODUCT_FILE);

    return deleted;
}
