#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FoodItem
{
    char name[100];
    float price;
    char restaurantEmail[100];
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

struct Bill
{
    char customerEmail[100];
    struct FoodItem foodItem;
    int quantity;
    float total;
};

// Function prototypes
void customerSignup();
void restaurantOwnerSignup();
int customerLogin();
int restaurantOwnerLogin();
int verifyEmail(char *email);
int verifyPassword(char *password);
void restaurantOwnerPanel();
void addFoodItem();
void removeFoodItem();
void displayFoodItems(char *restroEmail);
void searchByHotel();
void searchByFood();
void customerPanel();
void generateBill(struct FoodItem *orderedItem, int quantity);
void viewTransactions(char *transactor);
void exit_program();

char customerEmail[100],
    restroEmail[100];

int main()
{
    printf("\n\t****************** WELCOME TO FOOD VENDOR SYSTEM ****************** \n");
    int choice;

    while (1)
    {
        printf("\n1. Customer Signup\n");
        printf("2. Restaurant Owner Signup\n");
        printf("3. Customer Login\n");
        printf("4. Restaurant Owner Login\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf(" %d", &choice);

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
            exit_program();
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
    // Get customer details
    printf("\n\t-------------CUSTOMER SIGNUP  ------------\n");
    while ((getchar()) != '\n')
        ;
    printf("Enter name: ");
    gets(customer.name);

    printf("Enter email: ");
    scanf(" %s", customer.email);

    printf("Enter phone: ");
    scanf(" %s", customer.phone);

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
    scanf(" %s", customer.password);

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
    printf("\n\t------------- RESTAURANT OWNER SIGNUP ------------\n");
    while ((getchar()) != '\n')
        ;
    // Get restaurant owner details
    printf("Enter Restaurant name: ");
    gets(owner.name);

    printf("Enter phone: ");
    scanf(" %s", owner.phone);

    printf("Enter email: ");
    scanf(" %s", owner.email);

    FILE *fp1;
    fp1 = fopen("customers.txt", "r");
    if (fp1 == NULL)
    {
        printf("Error opening file");
        return;
    }
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
    scanf(" %s", owner.password);

    printf("Enter location: ");
    scanf(" %s", owner.location);

    verifyEmail(owner.email);
    verifyPassword(owner.password);

    // Save restaurant owner details to file
    FILE *fp2;
    fp2 = fopen("restaurant_owners.txt", "a");
    if (fp2 == NULL)
    {
        printf("Error opening file");
        return;
    }
    fwrite(&owner, sizeof(struct RestaurantOwner), 1, fp2);
    fclose(fp2);

    printf("Restaurant owner account created successfully!\n");
}

// Restaurant owner login
int restaurantOwnerLogin()
{

    char email[100], password[20];

    struct RestaurantOwner owner;
    printf("\n\t------------- RESTAURANT OWNER LOGIN ------------\n");
    // Input email and password
    printf("\nEnter email: ");
    scanf("%s", email);

    printf("Enter password: ");
    scanf("%s", password);

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

    // Read all restaurant owners from file
    FILE *fp;
    fp = fopen("restaurant_owners.txt", "rb");
    if (fp == NULL)
    {
        printf("Error opening file");
        return;
    }

    while (fread(&owner, sizeof(struct RestaurantOwner), 1, fp))
    {
        // Check if email and password match
        if (strcmp(email, owner.email) == 0 &&
            strcmp(password, owner.password) == 0)
        {
            printf("Login successful!\n");
            strcpy(restroEmail, owner.email);
            // system("clear");
            restaurantOwnerPanel();
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
    printf("\n\t------------- CUSTOMER LOGIN ------------\n");
    // Input email and password
    printf("\nEnter email: ");
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

    if (fp == NULL)
    {
        printf("Error opening file");
        return;
    }
    while (fread(&customer, sizeof(struct Customer), 1, fp))
    {

        // Check if email and password match
        if (strcmp(email, customer.email) == 0 &&
            strcmp(password, customer.password) == 0)
        {
            printf("Login successful!\n");
            strcpy(customerEmail, customer.email);
            // system("clear");
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

void restaurantOwnerPanel()
{
    int choice;

    while (1)
    {
        printf("\n\t****************** RESTAURANT OWNER PANEL ****************** \n");
        printf("\n");
        printf("1. Add Food Item\n");
        printf("2. Remove Food Item\n");
        printf("3. View Food Items\n");
        printf("4. View Transactions\n");
        printf("5. Exit\n");

        printf("Enter your choice : ");
        while ((getchar()) != '\n')
            ;
        scanf(" %d", &choice);

        if (choice == 1)
            addFoodItem();
        else if (choice == 2)
            removeFoodItem();
        else if (choice == 3)
            displayFoodItems(restroEmail);
        else if (choice == 4)
            viewTransactions(restroEmail);
        else if (choice == 5)
            return;
        else
            printf("Invalid choice. Please try again.\n");
    }
}

// Define menu array
void addFoodItem()
{
    char name[100];
    float price;
    printf("\n\t------------- ADD FOOD ITEM ------------\n");
    while ((getchar()) != '\n')
        ;
    printf("Enter food name: ");
    gets(name);

    printf("Enter price: ");
    scanf("%f", &price);

    // Create new food item
    FILE *fp = fopen("menu.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening file");
        return;
    }
    struct FoodItem item;
    strcpy(item.name, name);
    item.price = price;
    strcpy(item.restaurantEmail, restroEmail);

    fwrite(&item, 1, sizeof(struct FoodItem), fp);

    fclose(fp);

    printf("Food item added to file successfully!\n");
}

// Display food items
void displayFoodItems(char *restroEmail)
{
    printf("\n\t------------- FOOD ITEMS ------------\n");
    FILE *fp = fopen("menu.txt", "rb");

    struct FoodItem item;
    int count = 1;

    if (fp == NULL)
    {
        printf("Error opening file");
        return;
    }
    while (fread(&item, sizeof(item), 1, fp))
    {
        if (strcmp(item.restaurantEmail, restroEmail) == 0)
        {
            printf("%d.%s --> %.2f\n", count, item.name, item.price);
            count++;
        }
    }

    fclose(fp);
}

// Remove food item belonging to current owner
void removeFoodItem()
{
    printf("\n\t------------- REMOVE FOOD ITEM ------------\n");
    displayFoodItems(restroEmail);
    int rmv, count = 1;
    struct FoodItem item;
    FILE *fp = fopen("menu.txt", "rb");
    FILE *tmp = fopen("tmp.txt", "a");
    printf("Input option which you want to remove :");
    scanf("%d", &rmv);
    if (fp == NULL && tmp == NULL)
    {
        printf("Error opening file");
        return;
    }
    while (fread(&item, sizeof(item), 1, fp))
    {
        if (!(strcmp(item.restaurantEmail, restroEmail) == 0 && count == rmv))
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
void viewTransactions(char *transactor)
{
    printf("\n\t------------- TRANSACTIONS DETAILS ------------\n");
    int count = 1;
    FILE *fp = fopen("bill.txt", "rb");

    struct Bill txn;
    while (fread(&txn, sizeof(txn), 1, fp))
    {
        if (strcmp(transactor, txn.foodItem.restaurantEmail) == 0 || strcmp(transactor, txn.customerEmail) == 0)
        {
            printf("%d. %s --> %d --> %.2f\n", count, txn.foodItem.name, txn.quantity, txn.total);
        }
        count++;
    }

    fclose(fp);
}

// Customer panel
void customerPanel()
{
    int ch;

    while (1)
    {
        printf("\n\t****************** CUSTOMER PANEL ****************** \n");
        printf("\nCustomer Panel\n");
        printf("1. View Food Items\n");
        printf("2. View Food Items By Hotel\n");
        printf("3. View Order History\n");
        printf("4. Exit\n");
        getchar();
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            searchByFood();
            break;

        case 2:
            searchByHotel();
            break;

        case 3:
            viewTransactions(customerEmail);
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
    printf("\n\t------------- HOTELS  ------------\n");
    int count = 1;
    FILE *fp = fopen("restaurant_owners.txt", "rb");
    int hotel, food, quantity;
    char hotel_name[100];

    struct RestaurantOwner restro;

    if (fp == NULL)
    {
        printf("Error opening file");
        return;
    }
    while (fread(&restro, sizeof(restro), 1, fp))
    {
        printf("\t%d. %s at %s \n", count, restro.name, restro.location);
        count++;
    }

    printf("From which hotel do you want your food being delivered ? (input number) : ");
    scanf("%d", &hotel);

    // finding hotel name from users inputed number
    fseek(fp, (hotel - 1) * sizeof(struct RestaurantOwner), SEEK_SET);
    fread(&restro, sizeof(restro), 1, fp);
    fclose(fp);

    // display food listed in menu of searched hotel
    displayFoodItems(restro.name);
    printf("Which food do you want to have ?(input number) : ");
    scanf("%d", &food);
    printf("Quantity : ");
    scanf("%d", &quantity);

    // finding the food that the user selected and generating bill
    FILE *fpt = fopen("menu.txt", "rb");

    struct FoodItem item;
    int loop = 1;
    if (fpt == NULL)
    {
        printf("Error opening file");
        return;
    }
    while (fread(&item, sizeof(item), 1, fpt))
    {
        if (strcmp(item.restaurantEmail, restroEmail) == 0)
        {
            if (loop == food)
            {
                fclose(fpt);
                generateBill(&item, quantity);
                break;
            }
            loop++;
        }
    }

    fclose(fpt);
}

// display all food items
void searchByFood()
{
    printf("\n\t------------- FOOD AVAILABLE ------------\n");
    int count = 1;
    int ch, quantity;
    FILE *fp = fopen("menu.txt", "rb");

    if (fp == NULL)
    {
        printf("Error opening file");
        return;
    }

    struct FoodItem food;
    while (fread(&food, sizeof(struct FoodItem), 1, fp))
    {
        printf("\t%d. %s --> %f \n", count, food.name, food.price);
        count++;
    }
    printf("Which food do you want to have ?(input number) : ");
    scanf("%d", &ch);
    printf("Quantity : ");
    scanf("%d", &quantity);
    // checking the food
    fseek(fp, (ch - 1) * sizeof(struct FoodItem), SEEK_SET);
    if (fread(&food, sizeof(food), 1, fp) != 1)
    {
        printf("Error reading food item");
    }
    fclose(fp);
    if (fp != NULL)
    {
        generateBill(&food, quantity);
    }
}

// generate bill
void generateBill(struct FoodItem *orderedItem, int quantity)
{
    // Print bill
    printf("\n\t------------- BILL ------------\n");
    printf("Item: %s\n", orderedItem->name);
    printf("Price: %.2f\n", orderedItem->price);
    printf("Total: %.2f\n", (orderedItem->price) * quantity);
    printf("\tThank You for Ordering!! \n");

    // Open bill file and write bill
    FILE *fp = fopen("bill.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening file");
        return;
    }

    struct Bill bill;
    strcpy(bill.customerEmail, customerEmail);
    strcpy(bill.foodItem.name, orderedItem->name);
    bill.foodItem.price = orderedItem->price;
    bill.quantity = quantity;
    bill.total = quantity * (orderedItem->price);
    fclose(fp);
}

void exit_program()
{
    printf("\n\n\t------------- SEE YOU AGAIN ------------\n");
    printf("\tCreated  by:\n");
    printf("\tKIRAN PAUDEL\t(080BCT019)\n");
    printf("\tALIN TIMELSANA\t(080BCT003)\n");
    printf("\tABHISHEK BHATTARAI\t(080BCT001)\n");
    exit(0);
}