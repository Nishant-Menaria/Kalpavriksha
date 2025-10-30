#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct Product
{
    int ID;
    char name[20];
    float price;
    int quantity;
} Product;

int gSize;

Product* addNewProduct(Product *products);
void viewAllProduct(Product *products);
void updateQuantity(Product *products);
void searchByID(Product *products);
void searchByName(Product *products);
int matchCharacter( char firstChar , char secondChar);
void searchByPriceRange(Product *products);
Product* deleteByID(Product *products);

int main()
{
    printf("Enter The Initial number of products :");
    scanf("%d", &gSize);

    Product *products = (Product *)calloc(gSize, sizeof(Product));
    if(products==NULL){
        printf("dynamic memory allocation fails\n");
        exit(1);
    }

    for (int productIndex = 0; productIndex < gSize; productIndex++)
    {
        printf("\n\nEnter initial number of products: %d\n", productIndex + 1);
        printf("Product ID:");
        scanf("%d", &products[productIndex].ID);
        while(getchar()!='\n');
        printf("Product Name:");
        scanf("%19[^\n]",products[productIndex].name);
        printf("Product Price:");
        scanf("%f", &products[productIndex].price);
        printf("Product quantity:");
        scanf("%d", &products[productIndex].quantity);
    }

    int choice;
    
    while (1)
    {

        printf("\n\n========== Inventory Menu ==============\n");
        printf("1. Add New Product\n");
        printf("2. View All Products\n");
        printf("3. Update Quantity\n");
        printf("4. Search Product by ID\n");
        printf("5. Search Product by Name\n");
        printf("6. Search Product by Price Range\n");
        printf("7. Delete Product\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:{
                products=addNewProduct(products);
                break;
            }
            case 2:{
                viewAllProduct(products);
                break;
            }
            case 3:{
                updateQuantity(products);
                break;
            }
            case 4:{
                searchByID(products);
                break;
            }
            case 5:{
                searchByName(products);
                break;
            }
            case 6:{
                searchByPriceRange(products);
                break;
            }
            case 7:{
                products=deleteByID(products);
                break;
            }
            case 8:{
                free(products);
                products=NULL;
                printf("\n\nMemory released successfully. Exiting program...");
                exit(0);
            }
        }
    }
}


Product* addNewProduct(Product *products){

    gSize++;
    products=(Product *)realloc(products ,gSize * sizeof(Product) );
    if(products==NULL){
        printf("Dynamic memory allocation fails\n");
        exit(1);
    }
    printf("\nEnter new product details:");
    printf("\nProduct ID:");
    scanf("%d",&products[gSize-1].ID);
    while(getchar()!='\n');
    printf("Product Name:");
    scanf("%19[^\n]",products[gSize-1].name);
    printf("Product Price:");
    scanf("%f", &products[gSize-1].price);
    printf("Product quantity:");
    scanf("%d", &products[gSize-1].quantity);
    return products;
}

void viewAllProduct(Product *products)
{

    printf("=========== Product List ============\n");
    for (int productIndex = 0; productIndex < gSize; productIndex++)
    {
        printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n", products[productIndex].ID, products[productIndex].name, products[productIndex].price, products[productIndex].quantity);
    }
}

void updateQuantity(Product *products){
    int productID;
    printf("Enter Product ID to update quantity: ");
    scanf("%d",&productID);

    for(int productIndex=0 ; productIndex < gSize ; productIndex++){
        if(products[productIndex].ID == productID){
            printf("Enter new Quantity:");
            scanf("%d",&products[productIndex].quantity);
            printf("Quantity updated successfully!\n");
            return;
        }
    }

    printf("There is not matching product for that product ID\n");
}

void searchByID(Product *products){
    int productID;
    printf("Enter Product ID to search:");
    scanf("%d",&productID);
    for(int productIndex=0 ; productIndex<gSize ; productIndex++){
        if(products[productIndex].ID == productID){
            printf("Product Found: Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n", products[productIndex].ID, products[productIndex].name, products[productIndex].price, products[productIndex].quantity);
            return;
        }
    }
    printf("There is not matching product for that product ID\n");
}

void searchByName(Product *products){
    getchar();
    printf("Enter name to search (partial allowed):");
    char productName[20];
    scanf("%19[^\n]",productName);

    for(int productIndex=0; productIndex < gSize ; productIndex++){
        int productNameIndex=0;
        int targetIndex=0;
        while( productName[productNameIndex] !='\0' && products[productIndex].name[targetIndex]!='\0' ){
            if( matchCharacter(productName[productNameIndex] , products[productIndex].name[targetIndex])){
                productNameIndex++;
                targetIndex++;
            }else{
                break;
            }
        }

        if(productName[targetIndex]=='\0'){
            printf("Product Found: Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n", products[productIndex].ID, products[productIndex].name, products[productIndex].price, products[productIndex].quantity);
            break ;
        }
    }
}

void searchByPriceRange(Product *products){
    int minPrice,maxPrice;
    do{
        printf("Enter minimum price:");
        scanf("%d",&minPrice);
        printf("Enter maximum price:");
        scanf("%d",&maxPrice);
        if(minPrice >= maxPrice)
            printf("Please enter a valid Price range\n");
    }while(minPrice>=maxPrice);

    for(int productIndex = 0 ; productIndex < gSize ; productIndex++){
        if(products[productIndex].price > minPrice && products[productIndex].price < maxPrice){
            printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n", products[productIndex].ID, products[productIndex].name, products[productIndex].price, products[productIndex].quantity);
        }
    }
}

Product* deleteByID(Product *products){
    if(gSize == 0){
        printf("No Product in the List \n");
        return products;
    }
    int productID;
    printf("Enter product ID to delete:");
    scanf("%d",&productID);
    int flag=0;

    for(int productIndex = 0; productIndex < gSize ; productIndex++){
        if(products[productIndex].ID == productID){
            for(int i = productIndex ; i < gSize - 1 ; i++){
                products[i]=products[i+1];
            }
            flag=1;
            break;
        }
    }
    if(flag){
        printf("Product deleted Successfully!\n");
        products=(Product*)realloc(products,sizeof(Product)* (--gSize));
        if(products==NULL){
            printf("Dynamic memory allocation fails\n");
            exit(1);
        }
        return products;
    }else{
        printf("No matching Product for Given Product ID\n");
        return products;
    }
}

int matchCharacter( char firstChar , char secondChar){
    if(firstChar >='A' && firstChar <='Z')
        firstChar+=32;
    else if(secondChar >='A' && secondChar<='Z')
        secondChar+=32;

    return firstChar==secondChar;
}