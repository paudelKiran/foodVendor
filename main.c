/*
Name of Project: Food Vendor System using C
Functionalities: 1. Sign-up & Login
                 2. Validate user (to check password & other details of user, or if user already exists)
                 3. Search by hotel name
                 4. Search by food order
                 5. Cart & Order Confirmation

Concepts used: Modular approach in programming
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <conio.h>

// User details for sign-up
struct userDetail
{
    // int age;
    char name[100];
    char email[100];
    char mobile[10];
    char password[8];
};

// Hotel details & their food details
struct hotelDetails
{
    char hotel_name[100];
    char first_food[50];
    char second_food[50];
    char third_food[50];
    int first, second, third, fourth;
};

// Initialize the hotels & user details
struct hotelDetails hotel[6];
struct userDetail user[100];

// Decalarations of functions
void signup();
void account_check(char *);
int is_valid(char *, char *);
void login();
void cart();
void search_by_hotels();
void search_by_food();
void food_order(int food);
void hotel_initialize();
void hotels(int hotel_choice);

// Gobal initialization of values
int flag = 1, i, j = 0, At = -1, Dot = -1, caps = 0;
int small = 0, special = 0, numbers = 0;
int success = 0, validate, choice;
char temp_name[100], temp_email[100];
char temp_mobile[20];
int total = 0, food_choice, n;
int hotel_choice, search_choice, confirm;
int ch, food, hotel_id;

// Food Ordering system
int main()
{
    // system("cls");
    printf("\n\n\t\tWelcome to our Food Ordering System\n");
    while (1)
    {
        printf("\n1. Sign-up\n2. Login\n3. Exit\n");
        printf("Please enter your choice\n");

        scanf("%d", &choice);

        // switch cases
        switch (choice)
        {
        // for sign-up
        case 1:
            signup();
            break;
        // for login
        case 2:
            login();
            break;
        // for exiting
        case 3:
            exit(4);
        default:
            printf("\n Please enter a valid choice\n");
            break;
        }
    }

    return 0;
}

// function signup
void signup()
{
    char temp_password1[20], temp_password2[20];
    printf("\n\n***********SINGUP************\n\n");

    // clears the input buffer
    while ((getchar()) != '\n')
        ;

    printf("Enter Your name: ");
    scanf("%s", temp_name);

    printf("Enter Your Email: ");
    scanf("%s", temp_email);

    printf("Enter Password: ");
    scanf("%s", temp_password1);

    printf("Confirm Password: ");
    scanf("%s", temp_password2);

    printf("Enter Your Mobile Number: ");
    scanf("%s", temp_mobile);

    // now call validate function
    validate = is_valid(temp_password1, temp_password2);
    if (validate == 1)
    {
        // to check if the user account already exists
        account_check(temp_password1);
    }
}

// Function to check if the account already exists or not
void account_check(char *temp_pass)
{

    FILE *fptr;
    fptr = fopen("userDetails.txt", "a+");
    if (fptr == NULL)
    {
        printf("Sorry! Unable to open the file.");
        fclose(fptr);
        main();
    }
    struct userDetail customer, data;
    int confirm = 0;

    while (fread(&data, sizeof(struct userDetail), 1, fptr))
    {
        if (strcmp(temp_email, data.email) == 0 || strcmp(temp_mobile, data.mobile) == 0)
        {
            printf("\n\nAccount Already Existed. Please try with new credentials. !!");
            fclose(fptr);
            main();
            break;
        }
    }

    // creating new account if it doesn't exist already
    strcpy(customer.name, temp_name);
    strcpy(customer.password, temp_pass);
    strcpy(customer.email, temp_email);
    strcpy(customer.mobile, temp_mobile);
    confirm = fwrite(&customer, sizeof(struct userDetail), 1,
                     fptr);
    fclose(fptr);

    if (confirm == 0)
    {
        printf("Sorry! Unable to write to the file.");
        main();
    }
    else
    {
        printf("\n\nAccount Successfully Created!!\n\n");
        main();
    }
}

// function to validate the user credentials for signing-up
int is_valid(char *temp_password1, char *temp_password2)
{
    // Validating the name
    for (i = 0; temp_name[i] != '\0'; i++)
    {
        if (!((temp_name[i] >= 'a' && temp_name[i] <= 'z') || (temp_name[i] >= 'A' && temp_name[i] <= 'Z') || (temp_name[i] == ' ')))
        {
            printf("\nPlease enter a valid name\n");
            flag = 0;
            return 0;
        }
    }

    if (flag == 1)
    {
        At = -1;
        Dot = -1;

        // validating email Id

        // checking if first char is alphabet only
        if (!((temp_email[0] >= 'a' && temp_email[0] <= 'z') || (temp_email[0] >= 'A' && temp_email[0] <= 'Z')))
        {
            printf("\nPlease enter a valid email address.");
            return 0;
        }

        // checking for the position of '@' and '.'
        for (i = 0; temp_email[i] != '\0'; i++)
        {
            // If character is '@'
            if (temp_email[i] == '@')
            {
                At = i;
            }
            // If character is '.'
            else if (temp_email[i] == '.')
            {
                Dot = i;
            }
        }
        // If '@' or '.' is not present
        if (At == -1 || Dot == -1)
        {
            printf("\nPlease enter a valid email address.");
            return 0;
        }

        // If '.' is present before '@'
        if (At > Dot)
        {
            printf("\nPlease enter a valid email address.");
            return 0;
        }

        // If '.' is present at the end
        if (Dot >= (strlen(temp_email) - 1))
        {
            printf("\nPlease enter a valid email address.");
            return 0;
        }
    }

    // Validating password to check if passwords matches
    if (!strcmp(temp_password1, temp_password2))
    {
        if (!(strlen(temp_password1) == 8))
        {
            printf("\nYour password doesn't meet the criteria.\n Length of the password must be 8.\n");
            return 0;
        }
    }
    else
    {
        printf("\nPasswords does not match.\n");
        return 0;
    }

    // Validating the user mobile no
    if (strlen(temp_mobile) == 10)
    {
        if (temp_mobile[0] == '0')
        {
            printf("\nPlease enter a valid mobile number.\n");
            return 0;
        }
        for (i = 0; i < 10; i++)
        {
            if (temp_mobile[i] >= '0' && temp_mobile[i] <= '9')
            {
                return 1;
            }
            else
            {
                printf("\nPlease enter a valid mobile number.\n");
                return 0;
            }
        }
    }
    else
    {
        printf("\nPlease enter a valid mobile number.\n");
        return 0;
    }
}

// login function
void login()
{
    char login_email[100];
    char login_pass[8] = "hari1234";
    char new_login_pass[8];

    printf("\n\n****************LOGIN*****************\n\n");

    printf("\nEnter Your Email: ");
    scanf("%s", login_email);

    printf("Enter Your Password: ");
    scanf("%s", login_pass);

    printf("%s\t%s", login_pass, login_email);
    FILE *fptr;
    fptr = fopen("userDetails.txt", "r");
    struct userDetail data;
    if (fptr == NULL)
    {
        printf("Sorry! Unable to open the file.");
        return;
    }
    else
    {
        // rewind(fptr);
        while (fread(&data, sizeof(data), 1, fptr) != EOF)
        {
            printf("\nentered ");
            // puts(data.password);
            printf("\n%s\t%s", data.email, data.password);
            if (strcmp(login_email, data.email) == 0 && strcmp(login_pass, data.password) == 0)
            {
                printf("\n%s\t%s", data.email, data.password);
                fclose(fptr);

                printf("\n\nWelcome you have successfully logged in :)\n\n");
                printf("Please select your option");
                printf("\n1. Search by hotel\n2. Search by Food\n3. For exit\n");
                printf("Your choice: ");
                scanf("%d", &search_choice);

                // Based on the user choice call the particular fun
                switch (search_choice)
                {
                case 1:
                    search_by_hotels();
                    break;
                case 2:
                    search_by_food();
                    break;
                case 3:
                    exit(1);
                default:
                    printf("\nPlease Enter the valid choice\n\n");
                    break;
                }
                return;
            }
            else
            {
                fclose(fptr);
                printf("\nInvalid password! Please enter the correct password.\n");
                return;
            }
        }
    }
    fclose(fptr);
    // printf("\nThis account doesn't exists. Please signup to create your account!\n");
    main();
}

//!  more to discover
// Function that initializes the hotels
void hotel_initialize()
{
    // Initialize the structure with foods name & their cost
    strcpy(hotel[1].hotel_name, "Freshers Delight");
    strcpy(hotel[1].first_food, "Veg momo");
    strcpy(hotel[1].second_food, "Pizza");
    strcpy(hotel[1].third_food, "Tandoori Sauce Potato");
    hotel[1].first = 730;
    hotel[1].second = 100;
    hotel[1].third = 195;

    strcpy(hotel[2].hotel_name, "Barbeque Nation");
    strcpy(hotel[2].first_food, "Non veg momos");
    strcpy(hotel[2].second_food, "Noodles");
    strcpy(hotel[2].third_food, "Chicken crispy finger");
    hotel[2].first = 80;
    hotel[2].second = 85;
    hotel[2].third = 380;

    strcpy(hotel[3].hotel_name, "Piccante");
    strcpy(hotel[3].first_food, "Chicken_Biriyani");
    strcpy(hotel[3].second_food, "Prawn");
    strcpy(hotel[3].third_food, "Fish crispy finger");
    hotel[3].first = 700;
    hotel[3].second = 100;
    hotel[3].third = 250;

    strcpy(hotel[4].hotel_name, "Balkh Bukhara");
    strcpy(hotel[4].first_food, "Chicken Biriyani");
    strcpy(hotel[4].second_food, "Cheese momo");
    strcpy(hotel[4].third_food, "Veg chilly momo");
    hotel[4].first = 500;
    hotel[4].second = 120;
    hotel[4].third = 230;

    strcpy(hotel[5].hotel_name, "Hard Rock Cafe");
    strcpy(hotel[5].first_food, "Chicken noodles");
    strcpy(hotel[5].second_food, "Honey potato");
    strcpy(hotel[5].third_food, "French Fires");
    hotel[5].first = 240;
    hotel[5].second = 150;
    hotel[5].third = 190;
}

// Search by hotels function
void search_by_hotels()
{
    hotel_initialize();
    printf("\nPlease Choose the hotel\n");
    printf("1. %s\n2. %s\n3. %s\n4. %s, \n5. %s\n6. Exit", hotel[1].hotel_name, hotel[2].hotel_name, hotel[3].hotel_name, hotel[4].hotel_name, hotel[5].hotel_name);
    printf("\nPlease enter your choice: ");

    scanf("%d", &hotel_choice);

    if (hotel_choice > 6)
    {
        printf("Please Enter the valid choice.\n");
        search_by_hotels();
    }
    else if (hotel_choice == 6)
        exit(1);
    else
        hotels(hotel_choice);
}

// Function to implement the hotel
void hotels(int hotel_choice)
{
    total = 0;
    while (1)
    {
        // Displays the list of foods available in selected hotel
        printf("\nList of foods available in %s\n", hotel[hotel_choice].hotel_name);
        printf("\nFood item---->Price");
        printf("\n1. %s---->Rs: %d", hotel[hotel_choice].first_food, hotel[hotel_choice].first);
        printf("\n2. %s---->Rs: %d", hotel[hotel_choice].second_food, hotel[hotel_choice].second);
        printf("\n3. %s---->Rs: %d", hotel[hotel_choice].third_food, hotel[hotel_choice].third);

        printf("\n4. Cart\n5. Exit");
        printf("\nPlease enter your choice: ");
        scanf("%d", &food_choice);

        // Get the input for no of foods to calculate the total amount.
        if (food_choice == 1)
        {
            printf("Please Enter the Count of %s: ", hotel[hotel_choice].first_food);
            scanf("%d", &n);
            total = total + (n * hotel[hotel_choice].first);
        }
        else if (food_choice == 2)
        {
            printf("Please Enter the Count of %s: ", hotel[hotel_choice].second_food);
            scanf("%d", &n);
            total = total + (n * hotel[hotel_choice].second);
        }
        else if (food_choice == 3)
        {
            printf("Please Enter the Count of %s: ", hotel[hotel_choice].third_food);
            scanf("%d", &n);
            total = total + (n * hotel[hotel_choice].third);
        }

        // Once the user, completed their order, they can go to cart by giving choice as 4.
        else if (food_choice == 4)
        {
            cart();
        }
        else if (food_choice == 5)
        {
            search_by_hotels();
        }
        else
        {
            printf("\nPlease Enter the valid Choice\n\n");
        }
    }
}

// Search by food function
void search_by_food()
{
    total = 0;

    // Initialize all the hotels and their foods
    hotel_initialize();
    while (1)
    {
        printf("\nPlease choose the food you want to eat.");
        printf("\nFood Item----> Price\n");
        printf("\n1. %s----> %d\n2. %s---->%d\n3. %s---->%d", hotel[1].first_food, hotel[1].first, hotel[1].second_food, hotel[1].second, hotel[1].third_food, hotel[1].third);
        printf("\n4. %s---->%d\n5. %s---->%d\n6. %s---->%d", hotel[2].first_food, hotel[2].first, hotel[2].second_food, hotel[2].second, hotel[2].third_food, hotel[2].third);
        printf("\n7. %s---->%d\n8. %s---->%d\n9. %s---->%d", hotel[3].first_food, hotel[3].first, hotel[3].second_food, hotel[3].second, hotel[3].third_food, hotel[3].third);
        printf("\n10. %s---->%d\n11. %s---->%d\n12. %s---->%d", hotel[4].first_food, hotel[4].first, hotel[4].second_food, hotel[4].second, hotel[4].third_food, hotel[4].third);
        printf("\n13. %s---->%d\n14. %s---->%d\n15. %s---->%d", hotel[5].first_food, hotel[5].first, hotel[5].second_food, hotel[5].second, hotel[5].third_food, hotel[5].third);

        // Move to cart
        printf("\n16. Cart");
        // For exit
        printf("\n17. Exit");

        printf("\nPlease Enter Your Choice: ");
        scanf("%d", &food);
        if (food > 17)
        {
            printf("Please Enter a valid choice.\n");
            search_by_food();
        }
        // Moves to the cart functionality
        else if (food == 16)
            cart();
        else if (food == 17)
            return;
        // Call food_order functionality to get the no of foods and to calculate the total amount of the order.
        else
            food_order(food);
    }
}

// Function to implement the food order functionality
void food_order(int food)
{
    if (food >= 1 && food <= 3)
        hotel_id = 1;
    else if (food >= 4 && food <= 6)
        hotel_id = 2;
    else if (food >= 7 && food <= 9)
        hotel_id = 3;
    else if (food >= 10 && food <= 13)
        hotel_id = 4;
    else
        hotel_id = 5;
    if ((food % 3) == 1)
    {
        printf("Please Enter the Count of %s: ", hotel[hotel_id].first_food);
        scanf("%d", &n);
        total = total + (n * hotel[hotel_id].first);
    }
    else if ((food % 3) == 2)
    {
        printf("Please Enter the Count of %s: ", hotel[hotel_id].second_food);
        scanf("%d", &n);
        total = total + (n * hotel[hotel_id].second);
    }
    else if ((food % 3) == 0)
    {
        printf("Please Enter the Count of %s: ", hotel[hotel_id].third_food);
        scanf("%d", &n);
        total = total + (n * hotel[hotel_id].third);
    }
}

// Cart function implimentation
void cart()
{
    printf("\n\n**********Cart**********\n");
    printf("\nYour Total Order Amount is: %d", total);
    printf("\nDo You wish to order? Choose 1. Yes 2. No: ");
    scanf("%d", &ch);
    if (ch == 1)
    {
        printf("\n\nThank for ordering! Your order is confirmed Your Food is on the way.");
        exit(1);
    }
    else if (ch == 2)
    {
        printf("\nDo You want to exit -1 or Go back -0");
        scanf("%d", &confirm);
        if (confirm == 1)
        {

            printf("\n\nOops! Your order is cancelled!! Exiting..");
            printf("Thank You visit again!\n");
            exit(1);
        }
        else
        {
            printf("\n\nThank You\n\n");
            login();
        }
    }
    else
    {
        printf("\n\nPlease Enter the correct choice\n");
        cart();
    }
}