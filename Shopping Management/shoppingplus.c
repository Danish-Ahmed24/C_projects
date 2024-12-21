// Header FIles
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// TEXT color codes
#define RESET "\x1b[0m" // Reset color to default
#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define BRIGHT_BLACK "\x1b[30;1m"   // Bright Black (Gray)
#define BRIGHT_RED "\x1b[31;1m"     // Bright Red
#define BRIGHT_GREEN "\x1b[32;1m"   // Bright Green
#define BRIGHT_YELLOW "\x1b[33;1m"  // Bright Yellow
#define BRIGHT_BLUE "\x1b[34;1m"    // Bright Blue
#define BRIGHT_MAGENTA "\x1b[35;1m" // Bright Magenta
#define BRIGHT_CYAN "\x1b[36;1m"    // Bright Cyan
#define BRIGHT_WHITE "\x1b[37;1m"   // Bright White

// BG color codes
#define BG_BLACK "\x1b[40m"
#define BG_RED "\x1b[41m"
#define BG_GREEN "\x1b[42m"
#define BG_YELLOW "\x1b[43m"
#define BG_BLUE "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN "\x1b[46m"
#define BG_WHITE "\x1b[47m"
#define BG_BRIGHT_BLACK "\x1b[40;1m"   // Bright Black
#define BG_BRIGHT_RED "\x1b[41;1m"     // Bright Red
#define BG_BRIGHT_GREEN "\x1b[42;1m"   // Bright Green
#define BG_BRIGHT_YELLOW "\x1b[43;1m"  // Bright Yellow
#define BG_BRIGHT_BLUE "\x1b[44;1m"    // Bright Blue
#define BG_BRIGHT_MAGENTA "\x1b[45;1m" // Bright Magenta
#define BG_BRIGHT_CYAN "\x1b[46;1m"    // Bright Cyan
#define BG_BRIGHT_WHITE "\x1b[47;1m"   // Bright White

// STYLING text codes
#define BOLD "\x1b[1m"      // Bold text
#define UNDERLINE "\x1b[4m" // Underlined text
#define REVERSED "\x1b[7m"  // Reversed colors (background and text swapped)

// Struct definitions
typedef struct
{
    char username[50];
    char password[50];
    char role[20]; // "customer" or "employee"
} User;
typedef struct
{
    int id;
    char name[50];
    char category[50];
    float price;
    int stock;
    int likes;
    char comment[100];
    int nocomments;
} Product, Product_comment_file;
typedef struct
{
    int productId;
    int quantity;
    float total;
} Sale;
typedef struct
{
    int productId;
    int quantity;
    float total;
} CartItem;

// Globals
User users[100];
int userCount = 0;

Product products[100];
int productCount = 0;

Product_comment_file comments[100];
int commentscount = 0;

Sale sales[100];
int saleCount = 0;

int i, j; // Variables for loops

CartItem *cart = NULL; // Dynamic array for cart items
int cartSize = 0;      // Number of items in the cart
// File paths
const char *userFile = "users.txt";
const char *productFile = "products.txt";
const char *salesFile = "sales.txt";
const char *CommentsFile = "comments.txt";

// Function prototypes
void loadUsers();
void saveUsers();
void loadProducts();
void saveProducts();
void loadSales();
void saveSales();
void loadComments();
void savecomments();
void removeComments(int productId);

int signUp();
int login();
void customerMenu();
void employeeMenu();
void viewProducts();
void addProduct();
void removeProduct();
void addToCart();
void checkout();
void likes();
void addcomments();
void viewcommets();

// Load comments
void loadComments()
{
    FILE *file = fopen(CommentsFile, "r");
    if (file)
    {
        commentscount = 0; // Reset comment count
        while (fscanf(file, "%d %[^\n]", &comments[commentscount].id, comments[commentscount].comment) != EOF)
        {
            commentscount++;
        }
        fclose(file);

        // Update the `nocomments` field for each product
        for (int i = 0; i < productCount; i++)
        {
            products[i].nocomments = 0; // Reset comments count
            for (int j = 0; j < commentscount; j++)
            {
                if (products[i].id == comments[j].id)
                {
                    products[i].nocomments++;
                }
            }
        }
    }
}

// Load users from file
void loadUsers()
{
    FILE *file = fopen(userFile, "r");
    if (file)
    {
        while (fscanf(file, "%s %s %s", users[userCount].username, users[userCount].password, users[userCount].role) != EOF)
        {
            userCount++;
        }

        fclose(file);
    }
}

// Save users to file
void saveUsers()
{
    FILE *file = fopen(userFile, "w");
    if (file)
    {
        for (int i = 0; i < userCount; i++)
        {
            fprintf(file, "%s %s %s\n", users[i].username, users[i].password, users[i].role);
        }
        fclose(file);
    }
}

// Load products from file
void loadProducts()
{
    FILE *file = fopen(productFile, "r");
    if (file)
    {
        while (fscanf(file, "%d %s %s %f %d %d", &products[productCount].id, products[productCount].name,
                      products[productCount].category, &products[productCount].price, &products[productCount].stock, &products[productCount].likes) != EOF)
        {
            productCount++;
        }
        fclose(file);
    }
}

// Save products to file
void saveProducts()
{
    FILE *file = fopen(productFile, "w");
    if (file)
    {
        for (int i = 0; i < productCount; i++)
        {
            fprintf(file, "%d %s %s %.2f %d %d\n", products[i].id, products[i].name, products[i].category,
                    products[i].price, products[i].stock, products[i].likes);
        }
        fclose(file);
    }
}

// Load sales from file
void loadSales()
{
    FILE *file = fopen(salesFile, "r");
    if (file)
    {
        while (fscanf(file, "%d %d %f", &sales[saleCount].productId, &sales[saleCount].quantity, &sales[saleCount].total) != EOF)
        {
            saleCount++;
        }
        fclose(file);
    }
}

// Save sales to file
void saveSales()
{
    FILE *file = fopen(salesFile, "w");
    if (file)
    {
        for (int i = 0; i < saleCount; i++)
        {
            fprintf(file, "%d %d %.2f\n", sales[i].productId, sales[i].quantity, sales[i].total);
        }
        fclose(file);
    }
}

// Sign up a user
int signUp()
{
    User newUser;
    printf(BOLD YELLOW "| Enter username(without spaces use underscores): " RESET);
    scanf("%s", newUser.username);
    printf(BOLD YELLOW "| Enter password: " RESET);
    scanf("%s", newUser.password);
    printf(BOLD YELLOW "| Enter role (customer/employee): " RESET);
    scanf("%s", newUser.role);
    if (strlen(newUser.password) >= 4)
    {

        if (strcmp(newUser.role, "employee") == 0 || strcmp(newUser.role, "customer") == 0)
        {

            for (int i = 0; i < userCount; i++)
            {
                if (strcmp(users[i].username, newUser.username) == 0 || strcmp(users[i].password, newUser.password) == 0)
                {
                    printf(BOLD RED BG_BRIGHT_CYAN "Username or password already exists. Try again.\n" RESET);
                    signUp();
                }
            }

            users[userCount++] = newUser;
            saveUsers();
            printf(BOLD GREEN BG_CYAN "Signup successful!\n" RESET);
            printf(BOLD CYAN "Press any Key to continue..." RESET);
            getchar();
            // fflush(stdin);
            getchar();

            system("cls");
            return 1;
        }
        else
        {
            printf(BOLD RED BG_BRIGHT_CYAN "Invalid Role. Try again.\n" RESET);
            signUp();
        }
    }
    else
    {
        printf(BOLD RED BG_BRIGHT_CYAN "Password must have more than 3 characters. Try again.\n" RESET);
        signUp();
    }
}

// Login a user
int login()
{
    char username[50], password[50];
    printf(BOLD YELLOW "| Enter username: " RESET);
    scanf("%s", username);
    printf(BOLD YELLOW "| Enter password: " RESET);
    scanf("%s", password);
    const char *spinner = "|/-\\";
    for (int i = 0; i < 25; i++)
    {
        printf(BOLD BLUE "\rLoading %c" RESET, spinner[i % 4]);
        fflush(stdout);
        Sleep(100); // Sleep for 0.1 seconds
    }
    printf("\n");
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {

            printf(BOLD GREEN BG_CYAN "Login successful! Welcome, %s.\n" RESET, username);
            printf(BOLD CYAN "Press any Key to continue..." RESET);
            getchar();
            getchar();

            system("cls");
            if (strcmp(users[i].role, "employee") == 0)
            {
                employeeMenu();
            }
            else if (strcmp(users[i].role, "customer") == 0)
            {
                customerMenu();
            }
            return 1;
        }
    }
    Beep(1000, 500);
    printf(BOLD RED BG_CYAN "Invalid username or password. Try again.\n" RESET);
    return 0;
}
// likes
void likes()
{
    int IDLIKE;
    printf(BOLD YELLOW "Enter Product ID: " RESET);
    scanf("%d", &IDLIKE);
    if (IDLIKE <= 0)
    {
        printf(BOLD RED BG_CYAN "ID must be +ve. Try again.\n" RESET);
        likes();
    }
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == IDLIKE)
        {
            products[i].likes++;
            printf(BOLD GREEN BG_CYAN "Liked succesfully...\n" RESET);
            break;
        }
    }
}

void addcomments()
{
    int productId;
    char comment[100];

    printf(BOLD YELLOW "Enter Product ID: " RESET);
    scanf("%d", &productId);
    if (productId <= 0)
    {
        printf(BOLD RED BG_CYAN "Product ID must be +ve.\n" RESET);
        addcomments();
    }
    int found = 0;
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == productId)
        {
            found = 1;

            printf(BOLD YELLOW "| Enter your comment: " RESET);
            getchar();
            fgets(comment, sizeof(comment), stdin);
            comment[strcspn(comment, "\n")] = '\0';

            comments[commentscount].id = productId;
            strcpy(comments[commentscount].comment, comment);
            commentscount++;

            products[i].nocomments++;

            printf(BOLD GREEN BG_CYAN "Comment added successfully.\n" RESET);
            break;
        }
    }

    if (!found)
    {
        Beep(1000, 500);
        printf(BOLD RED BG_CYAN "Product not found.\n" RESET);
    }

    savecomments();
}

void savecomments()
{
    FILE *file = fopen(CommentsFile, "w");
    if (file)
    {
        for (int i = 0; i < commentscount; i++)
        {
            fprintf(file, "%d %s\n", comments[i].id, comments[i].comment);
        }
        fclose(file);
    }
    else
    {
        Beep(1000, 500);
        printf(BOLD RED BG_BRIGHT_CYAN "Error saving comments.\n" RESET);
    }
}

void removeComments(int productId)
{
    for (int i = 0; i < commentscount; i++)
    {
        if (comments[i].id == productId)
        {

            for (int j = i; j < commentscount - 1; j++)
            {
                comments[j] = comments[j + 1];
            }
            commentscount--;
            i--;
        }
    }
    savecomments();
}

void viewcommets()
{
    int opt;
    printf(BOLD YELLOW "Enter ID: " RESET);
    scanf("%d", &opt);
    if (opt <= 0)
    {
        printf(BOLD RED BG_CYAN "ID must be +ve. Try again\n" RESET);
        viewcommets();
    }
    if (comments)
        printf(UNDERLINE BOLD BLUE "\n        Available Comments        \n" RESET);
    int found = 0;
    for (int i = 0; i < commentscount; i++)
    {
        if (comments[i].id == opt)
        {
            found = 1;
            printf(BLUE "| " RESET);
            printf(BOLD GREEN "%s\n" RESET, comments[i].comment);
        }
    }
    if (!found)
    {
        Beep(1000, 500);
        printf(REVERSED "No comments Yet!\n" RESET);
    }
}
// Customer menu
void customerMenu()
{
    const char *spinner = "|/-\\";

    char choice;
    do
    {
        ////
        printf(BOLD GREEN "*************************************\n");
        printf("*     " RESET);
        printf(BOLD BLUE "       Customer Menu      " RESET);
        printf(BOLD GREEN "    *\n");
        printf("*************************************\n" RESET);
        printf(BOLD "1. View Products\n");
        printf("2. Add to Cart\n");
        printf("3. Checkout\n");
        printf("4. Add Like (By ID)\n");
        printf("5. Add comment(By ID)\n");
        printf("6. View comments\n");
        printf("7. Logout\n" RESET);
        printf(BOLD GREEN "*************************************\n" RESET);
        printf(BOLD YELLOW "Enter your choice: " RESET);
        ////

        scanf("%c", &choice);

        switch (choice)
        {
        case '1':
            system("cls");
            viewProducts();
            break;
        case '2':
            system("cls");
            addToCart();
            break;
        case '3':
            system("cls");
            checkout();
            break;
        case '4':
            system("cls");
            likes();
            break;
        case '5':
            system("cls");
            addcomments();
            break;
        case '6':
            system("cls");
            viewcommets();
            break;
        case '7':
            for (int i = 0; i < 25; i++)
            {
                system("cls");

                printf(BOLD BLUE "\rLogging Out %c" RESET, spinner[i % 4]);
                fflush(stdout);
                Sleep(100);
            }
            printf("\n");

            return;
        default:
            Beep(1000, 500);
            printf(BOLD RED BG_CYAN "Invalid choice. Try again.\n" RESET);
            break;
        }
        printf(BOLD CYAN "Press any Key to continue..." RESET);
        getchar();
        getchar();
        system("cls");
    } while (choice != '7');
}

// Employee menu
void employeeMenu()
{
    const char *spinner = "|/-\\";

    char choice;
    do
    {
        ////
        printf(BOLD GREEN "*************************************\n");
        printf("*            " RESET);

        printf(BOLD BLUE "Employee Menu" RESET);
        printf(BOLD GREEN "          *\n");
        //    ******
        printf("*************************************\n" RESET);
        printf(BOLD "1. View Products\n");
        printf("2. Add Product\n");
        printf("3. Remove Product\n");
        printf("4. Logout\n" RESET);
        printf(BOLD GREEN "*************************************\n" RESET);
        printf(BOLD YELLOW "Enter your choice: " RESET);
        ////

        scanf("%c", &choice);

        switch (choice)
        {
        case '1':
            system("cls");
            viewProducts();
            break;
        case '2':
            system("cls");
            addProduct();
            break;
        case '3':
            system("cls");
            removeProduct();
            break;
        case '4':
            for (int i = 0; i < 25; i++)
            {
                printf(BOLD BLUE "\rLogging Out %c" RESET, spinner[i % 4]);
                fflush(stdout);
                Sleep(100);
                system("cls");
            }
            printf("\n");
            return;
        default:
            Beep(1000, 500);

            printf("Invalid choice. Try again.\n");
            break;
        }
        printf(BOLD CYAN "Press any Key to continue..." RESET);
        getchar();
        getchar();
        system("cls");
    } while (choice != '4');
}

// View products
void viewProducts()
{ //////////////////////////////ID   Name    Category    Price   Stock   Likes   Comments\n////
    printf(UNDERLINE BOLD BLUE "\n                        Available Products                      .\n" RESET);
    // printf(BOLD MAGENTA " ID\tName\tCategory\tPrice\tStock\tLikes\tComments\n" RESET);
    printf(BOLD MAGENTA "%-4s %-15s %-15s %-8s %-8s %-8s %s\n", "ID", "Name", "Category", "Price", "Stock", "Likes", "Comments" RESET);

    for (int i = 0; i < productCount; i++)
    {
        printf(BLUE "| " RESET);
        printf(GREEN "%-4d %-15s %-15s %-8.2f %-8d %-8d %d\n" RESET, products[i].id, products[i].name, products[i].category, products[i].price, products[i].stock, products[i].likes, products[i].nocomments);
        // printf("%-4d %-15s %-15s %-8.2f %-8d %-8d %s\n",id, name, category, price, stock, likes, comments);
    }
}

// Add product (employee)
void addProduct()
{
    Product newProduct;
    // printf(BOLD YELLOW "| Enter product ID: " RESET);
    // scanf("%d", &newProduct.id);
    newProduct.id = productCount + 1;
    printf(BOLD YELLOW "Enter product name: " RESET);
    scanf("%s", newProduct.name);
    if (strlen(newProduct.name) > 15)
    {
        printf(BOLD RED BG_CYAN "Product name must be less than 15 characters.\n" RESET);
        addProduct();
    }
    else if (strlen(newProduct.name) < 3)
    {
        printf(BOLD RED BG_CYAN "Product name must be greater than 3 characters.\n" RESET);
        addProduct();
    }
    printf(BOLD YELLOW "Enter category: " RESET);
    scanf("%s", newProduct.category);
    if (strlen(newProduct.category) > 15)
    {
        printf(BOLD RED BG_CYAN "Category must be less than 15 characters.\n" RESET);
        addProduct();
    }
    else if (strlen(newProduct.category) < 3)
    {
        printf(BOLD RED BG_CYAN "Category must be greater than 3 characters.\n" RESET);
        addProduct();
    }
    printf(BOLD YELLOW "Enter price: " RESET);
    scanf("%f", &newProduct.price);
    if (newProduct.price <= 0)
    {
        printf(BOLD RED BG_CYAN "Price must be greater then 0.\n" RESET);
        addProduct();
    }
    printf(BOLD YELLOW "Enter stock quantity: " RESET);
    scanf("%d", &newProduct.stock);
    if (newProduct.stock <= 0)
    {
        printf(BOLD RED BG_CYAN "Stock must be greater then 0.\n" RESET);
        addProduct();
    }
    newProduct.likes = 0;
    newProduct.nocomments = 0;
    newProduct.nocomments = 0;

    products[productCount++] = newProduct;
    saveProducts();
    printf(BOLD GREEN BG_CYAN "Product added successfully.\n" RESET);
}

// Remove product (employee)
void removeProduct()
{
    int id;
    printf(BOLD YELLOW "| Enter product ID to remove: " RESET);
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
        {
            removeComments(id);
            for (int j = i; j < productCount - 1; j++)
            {
                products[j] = products[j + 1];
            }
            productCount--;
            saveProducts();
            printf(BOLD GREEN BG_CYAN "Product removed successfully.\n" RESET);

            return;
        }
    }
    Beep(1000, 500);

    printf(BOLD RED BG_CYAN "Product not found.\n" RESET);
}

// Add to cart (Customer feature)
void addToCart()
{
    int productId, quantity;
    printf(BOLD YELLOW "Enter product ID to add to cart: " RESET);
    scanf("%d", &productId);
    if (productId <= 0)
    {
        printf(RED BG_CYAN "Product ID must be +ve\n" RESET);
        addToCart();
    }

    printf(BOLD YELLOW "| Enter quantity: " RESET);
    scanf("%d", &quantity);
    if (quantity <= 0)
    {
        printf(RED BG_CYAN "Quantity must be more than 0\n" RESET);
        addToCart();
    }
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == productId)
        {
            if (products[i].stock >= quantity)
            {
                cartSize++;
                CartItem *tempCart = realloc(cart, cartSize * sizeof(CartItem));
                if (tempCart == NULL)
                {
                    printf(RED BG_CYAN "Memory allocation failed!\n" RESET);
                    return;
                }
                cart = tempCart;
                cart[cartSize - 1].productId = productId;
                cart[cartSize - 1].quantity = quantity;
                cart[cartSize - 1].total = quantity * products[i].price;

                products[i].stock -= quantity; // Update stock
                saveProducts();
                printf(BOLD BLUE BG_CYAN "Added %d of %s to your cart. Total: %.2f\n" RESET, quantity, products[i].name, quantity * products[i].price);
                // products[i].stock -= quantity;
                // sales[saleCount].productId = productId;
                // sales[saleCount].quantity = quantity;
                // sales[saleCount].total = quantity * products[i].price;
                // saleCount++;
                // saveSales();
                return;
            }
            else
            {
                Beep(1000, 500);
                printf(BOLD RED BG_CYAN "Not enough stock.\n" RESET);
                return;
            }
        }
    }
    Beep(1000, 500);

    printf(BOLD RED BG_CYAN "Product not found.\n" RESET);
}

// Checkout (Customer feature)
// void checkout()
// {
//     float total = 0;
//     printf("Product ID\tQuantity\tTotal\n");
//     for (int i = 0; i < saleCount; i++)
//     {
//         printf(BLUE"| "RESET);
//         printf(BOLD GREEN"%d\t\t%d\t\t%.2f\n"RESET, sales[i].productId, sales[i].quantity, sales[i].total);
//         total += sales[i].total;
//     }
//     printf(BOLD"Total amount to pay: ");
//     printf(GREEN"%.2f\n"RESET, total);
// }
// BOLD GREEN"%d\t\t%d\t\t%.2f\n"RESET
void checkout()
{
    // printf("\nYour Cart:\n");
    printf(BOLD BLUE UNDERLINE "\n       Your Cart        \n" RESET);
    float totalAmount = 0.0;
    printf("Product ID\tQuantity\tTotal\n");
    for (i = 0; i < cartSize; i++)
    {
        printf(BLUE "| " RESET);
        printf(BOLD GREEN "%d\t\t%d\t\t%.2f\n" RESET, cart[i].productId, cart[i].quantity, cart[i].total);
        totalAmount += cart[i].total;
    }
    printf(BOLD "Total amount to pay: ");
    printf(GREEN "%.2f\n" RESET, totalAmount);
    // printf("Total Amount: %.2f\n", totalAmount);
    // Process payment here (just a mockup)
    printf(YELLOW "Proceeding to payment");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".\n" RESET);
    Sleep(500);
    printf(BOLD BLUE BG_CYAN "Payment successful. Thank you for shopping!\n" RESET);

    // Clear the cart
    free(cart);
    cart = NULL;
    cartSize = 0;
}
//////////////////
int main()
{

    loadUsers();
    loadProducts();
    loadSales();
    loadComments();
    const char *spinner = "|/-\\";

    char choice;
    do
    {
        printf(BOLD GREEN "*************************************\n");
        printf("*     " RESET);
        printf(BOLD BLUE "Welcome to the Store Menu" RESET);
        printf(BOLD GREEN "    *\n");
        printf("*************************************\n" RESET);
        printf(BOLD "1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. Exit\n\n" RESET);
        printf(BOLD GREEN "*************************************\n" RESET);
        printf(BOLD YELLOW "Enter your choice: " RESET);
        scanf("%c", &choice);

        switch (choice)
        {
        case '1':
            system("cls");
            signUp();
            fflush(stdin);

            break;
        case '2':
            system("cls");
            login();

            break;
        case '3': // abi yahan par koi animation lagagi
            system("cls");
            for (int i = 0; i < 25; i++)
            {
                printf(BOLD BLUE "\rExiting %c" RESET, spinner[i % 4]);
                fflush(stdout);
                Sleep(100);
            }
            printf("\n");

            break;
        default: // yahan par koi error disigning hogi with sound effects
            system("cls");
            Beep(1000, 500);
            printf(BOLD RED BG_CYAN "Invalid choice. Try again.\n" RESET);
        }
    } while (choice != '3');

    return 0;
}