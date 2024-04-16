#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structs to hold customer and restaurant owner details
struct FoodItem
{
    char name[100];
    float price;
    char restaurantName[100];
};

struct Customer
{
    char name[100];
    char phone[20];
    char email[100];
    char password[20];
};

struct RestaurantOwner
{
    char name[100];
    char phone[20];
    char email[100];
    char password[20];
    char location[100];
};

// Function prototypes
void customerSignup();
void restaurantOwnerSignup();
int customerLogin();
int restaurantOwnerLogin();
int verifyEmail(char *email);
int verifyPassword(char *password);
void restaurantOwnerPanel(char *restroName);
void addFoodItem(char *restroName);
void removeFoodItem(char *restroName);
void displayFoodItems(char *restroName);
void searchByHotel();
void searchByFood();
void customerPanel();

int main()
{

    int choice;

    while (1)
    {
        printf("1. Customer Signup\n");
        printf("2. Restaurant Owner Signup\n");
        printf("3. Customer Login\n");
        printf("4. Restaurant Owner Login\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            customerSignup();
            break;
        case 2:
            restaurantOwnerSignup();
            break;
        case 3:
            customerLogin();
            break;
        case 4:
            restaurantOwnerLogin();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Invalid choice\n");
        }
    }

    return 0;
}

int verifyEmail(char *email)
{
    // Check if email contains @ and .
    char *atSign = strchr(email, '@');
    char *dot = strchr(email, '.');
    if (atSign != NULL && dot != NULL)
    {
        if (atSign < dot)
        {
            return 1;
        }
        else
        {
            printf("Please input email according to email criteria.");
            return 0;
        }
    }
    else
    {
        printf("Not a valid email.");
    }
    return 0;
}

// Verify password
int verifyPassword(char *password)
{
    // Check if password is between 6 to 20 characters
    if (strlen(password) >= 8 && strlen(password) <= 20)
    {
        return 1;
    }
    return 0;
}

// Customer signup
void customerSignup()
{

    struct Customer customer, readCustomer;
    printf("\n\n");
    // Get customer details
    while ((getchar()) != '\n')
        ;
    printf("Enter name: ");
    gets(customer.name);
    while ((getchar()) != '\n')
        ;
    printf("Enter phone: ");
    scanf("%s", customer.phone);
    while ((getchar()) != '\n')
        ;
    printf("Enter email: ");
    scanf("%s", customer.email);
    while ((getchar()) != '\n')
        ;

    // Check if email already exists
    FILE *fp;
    fp = fopen("customers.txt", "r");
    while (fread(&readCustomer, sizeof(struct Customer), 1, fp))
    {
        if (strcmp(customer.email, readCustomer.email) == 0)
        {
            printf("Email already exists!");
            return;
        }
    }
    fclose(fp);

    printf("Enter password: ");
    scanf("%s", customer.password);

    // Validate email and password
    verifyEmail(customer.email);
    verifyPassword(customer.password);

    // Save customer details to file
    fp = fopen("customers.txt", "a");
    fwrite(&customer, sizeof(struct Customer), 1, fp);
    fclose(fp);

    printf("Customer account created successfully!\n");
}

// Restaurant owner signup
void restaurantOwnerSignup()
{

    struct RestaurantOwner owner, readOwner;

    // Get restaurant owner details
    printf("Enter Restaurant name: ");
    scanf("%s", owner.name);
    while ((getchar()) != '\n')
        ;

    printf("Enter phone: ");
    scanf("%s", owner.phone);

    printf("Enter email: ");
    scanf("%s", owner.email);

    FILE *fp1;
    fp1 = fopen("customers.txt", "r");
    while (fread(&readOwner, sizeof(struct Customer), 1, fp1))
    {
        if (strcmp(owner.email, readOwner.email) == 0)
        {
            printf("Email already exists!");
            return;
        }
    }
    fclose(fp1);

    printf("Enter password: ");
    scanf("%s", owner.password);

    printf("Enter location: ");
    scanf("%s", owner.location);

    verifyEmail(owner.email);
    verifyPassword(owner.password);

    // Save restaurant owner details to file
    FILE *fp2;
    fp2 = fopen("restaurant_owners.txt", "a");
    fwrite(&owner, sizeof(struct RestaurantOwner), 1, fp2);
    fclose(fp2);

    printf("Restaurant owner account created successfully!\n");
}

// Restaurant owner login
int restaurantOwnerLogin()
{

    char email[100], password[20];

    struct RestaurantOwner owner;

    // Input email and password
    printf("Enter email: ");
    scanf("%s", email);

    printf("Enter password: ");
    scanf("%s", password);

    // Read all restaurant owners from file
    FILE *fp;
    fp = fopen("restaurant_owners.txt", "rb");

    while (fread(&owner, sizeof(struct RestaurantOwner), 1, fp))
    {
        // Check if email and password match
        if (strcmp(email, owner.email) == 0 &&
            strcmp(password, owner.password) == 0)
        {
            printf("Login successful!\n");
            system("cls");
            restaurantOwnerPanel(owner.name);
            fclose(fp);
            return 1;
        }
    }
    printf("Invalid credentials.\n");
}

// Customer login
int customerLogin()
{

    char email[100], password[20];

    struct Customer customer;

    // Input email and password
    printf("Enter email: ");
    scanf("%s", email);

    printf("Enter password: ");
    scanf("%s", password);

    // Verify email
    if (!verifyEmail(email))
    {
        printf("Invalid email!\n");
        return 0;
    }

    // Verify password
    if (!verifyPassword(password))
    {
        printf("Invalid password!\n");
        return 0;
    }

    // Read all customers from file
    FILE *fp;
    fp = fopen("customers.txt", "rb");

    while (fread(&customer, sizeof(struct Customer), 1, fp))
    {

        // Check if email and password match
        if (strcmp(email, customer.email) == 0 &&
            strcmp(password, customer.password) == 0)
        {
            printf("Login successful!\n");
            system("cls");
            customerPanel();
            fclose(fp);
            return 1;
        }
    }

    printf("Invalid credentials!\n");

    fclose(fp);
    return 0;
}

// Restaurant owner panel

void restaurantOwnerPanel(char *restroName)
{
    int choice;

    while (1)
    {
        printf("\n\n");
        printf("1. Add Food Item\n");
        printf("2. Remove Food Item\n");
        printf("3. View Orders and Transactions\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addFoodItem(restroName);
            break;
        case 2:
            removeFoodItem(restroName);
            break;
        case 3:
            displayFoodItems(restroName);
            break;
        case 4:
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

// Define menu array
void addFoodItem(char *restroName)
{
    char name[100];
    float price;
    while ((getchar()) != '\n')
        ;
    printf("Enter food name: ");
    gets(name);

    printf("Enter price: ");
    scanf("%f", &price);

    // Create new food item
    FILE *fp = fopen("menu.txt", "a");
    struct FoodItem item;
    strcpy(item.name, name);
    item.price = price;
    strcpy(item.restaurantName, restroName);

    fwrite(&item, 1, sizeof(struct FoodItem), fp);

    fclose(fp);

    printf("Food item added to file successfully!\n");
}

// Display food items
void displayFoodItems(char *restroName)
{
    printf("\n\n");
    FILE *fp = fopen("menu.txt", "rb");

    struct FoodItem item;
    int count = 1;
    while (fread(&item, sizeof(item), 1, fp))
    {
        if (strcmp(item.restaurantName, restroName) == 0)
        {
            printf("%d.%s --> %.2f\n", count, item.name, item.price);
            count++;
        }
    }

    fclose(fp);
}

// Remove food item belonging to current owner
void removeFoodItem(char *restroName)
{
    printf("\n\n");
    displayFoodItems(restroName);
    int rmv, count = 1;
    struct FoodItem item;
    FILE *fp = fopen("menu.txt", "rb");
    FILE *tmp = fopen("tmp.txt", "a");
    printf("Input option which you want to remove :");
    scanf("%d", &rmv);

    while (fread(&item, sizeof(item), 1, fp))
    {
        if (!(strcmp(item.restaurantName, restroName) == 0 && count == rmv))
        {
            fwrite(&item, 1, sizeof(item), tmp);
        }
        count++;
    }

    fclose(fp);
    fclose(tmp);
    remove("menu.txt");
    rename("tmp.txt", "menu.txt");
}

// View transactions
// void viewTransactions()
// {
//     FILE *fp = fopen("transactions.txt", "r");

//     struct Transaction txn;
//     while (fread(&txn, sizeof(txn), 1, fp))
//     {
//         printf("Customer: %s, Food: %s, Price: %.2f\n",
//                txn.customerName, txn.foodName, txn.price);
//     }

//     fclose(fp);
// }
// Search food items by hotel

// Customer panel
void customerPanel()
{
    int choice;

    while (1)
    {
        printf("\nCustomer Panel\n");
        printf("1. View Food Items\n");
        printf("2. View Food Items By Hotel\n");
        printf("3. View Orders\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            searchByFood();
            break;

        case 2:
            searchByHotel();
            break;

        case 3:
            viewTransactions();
            break;

        case 4:
            return;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

// choose hotel and show food menu of it
void searchByHotel()
{
    printf("\nHotels listed are:");
    int count = 1;
    FILE *fp = fopen("restaurant_owner.txt", "rb");
    int hotel;
    char hotel_name[100];

    struct RestaurantOwner item;
    while (fread(&item, sizeof(item), 1, fp))
    {
        printf("\t%d. %s at %s \n", count, item.name, item.location);
        count++;
    }

    printf("From which hotel do you want your food being delivered ? (input number) : ");
    scanf("%d", &hotel);

    // finding hotel name from users inputed number
    rewind(fp);
    count = 1;
    while (fread(&item, sizeof(item), 1, fp))
    {
        if (count == hotel)
        {
            strcpy(hotel_name, item.name);
        }
        count++;
    }

    fclose(fp);

    // search food listed in menu of searched hotel
    displayFoodItems(hotel_name);
}

// display all food items
void searchByFood()
{
    printf("\nFoods available right now are:\n");
    int count = 1;
    FILE *fp = fopen("menu.txt", "rb");
    int food;

    struct FoodItem item;
    while (fread(&item, sizeof(item), 1, fp))
    {
        printf("\t%d. %s --> %s -->%s \n", count, item.name, item.price, item.restaurantName);
        count++;
    }
    printf("Which food do you want to have ?(input number) : ");
    scanf("%d", &food);

    fclose(fp);
}
