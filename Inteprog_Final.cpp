#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <stdexcept>
#include <cctype>

using namespace std;

// ----------------------------- Product Class -----------------------------
class Product {
private:
    int id;
    string name;
    double price;

public:
    Product(int pid, const string& pname, double pprice)
        : id(pid), name(pname), price(pprice) {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
};

// ----------------------------- User Class -----------------------------
class User {
private:
    string username;
    string email;       
    string address;

public:
    User(const string& uname) : username(uname) {}

    string getUsername() const { return username; }
    
    void setEmail(const string& userEmail) {
        email = userEmail;
    }
    
    string getEmail() const {
        return email;
    }

    void setAddress(const string& addr) {
        address = addr;
    }

    string getAddress() const {
        return address;
    }
};

// ----------------------------- Cart Class -----------------------------
class Cart {
private:
    vector<pair<int, int>> items; // pair<productId, quantity>
    vector<Product> catalog;

public:
    void setCatalog(const vector<Product>& products) {
        catalog = products;
    }

    void addProduct(const Product& product, int quantity) {
        if (quantity <= 0)
            throw runtime_error("Quantity must be greater than 0.");
        bool found = false;
        for (auto& item : items) {
            if (item.first == product.getId()) {
                item.second += quantity;
                found = true;
                break;
            }
        }
        if (!found) {
            items.push_back({product.getId(), quantity});
        }
        cout<< "Added "<<quantity<<" of "<<product.getName()<<" to cart."<<endl;
    }

    void removeProduct(int productId) {
        auto it = std::remove_if(items.begin(), items.end(),
            [productId](const pair<int, int>& item) { return item.first == productId; });
        if (it == items.end())
            throw runtime_error("Product not in cart.");
        items.erase(it, items.end());
        cout<<"Removed product ID "<<productId<<" from cart."<<endl;
    }

    void updateQuantity(int productId, int newQuantity) {
        if (newQuantity <= 0)
            throw runtime_error("Quantity must be greater than 0.");
        bool found = false;
        for (auto& item : items) {
            if (item.first == productId) {
                item.second = newQuantity;
                found = true;
                break;
            }
        }
        if (!found)
            throw runtime_error("Product not in cart.");
    }

    void showCart() const {
        cout << "\n--- Cart ---" << endl;
        double total = 0;
        for (const auto& item : items) {
            for (const auto& prod : catalog) {
                if (prod.getId() == item.first) {
                    double itemTotal = prod.getPrice() * item.second;
                    cout <<"ID: "<<prod.getId()
                         <<" | " <<prod.getName()
                         << " x" <<item.second
                         << " - Php " <<itemTotal<<endl;
                    total += itemTotal;
                }
            }
        }
        cout<<"Total: Php "<<total<<endl;
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& item : items) {
            for (const auto& prod : catalog) {
                if (prod.getId() == item.first)
                    total += prod.getPrice() * item.second;
            }
        }
        return total;
    }

    bool isEmpty() const {
        return items.empty();
    }

    // For receipt generation
    const vector<pair<int, int>>& getItems() const {
        return items;
    }

    const vector<Product>& getCatalog() const {
        return catalog;
    }
};

// ----------------------------- Payment Strategy (Interface) -----------------------------
class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() = default;
};

class CreditCardPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout<<"Paid Php "<<amount<<" using Credit Card."<<endl;
    }
};

class GcashPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout<<"Paid Php "<<amount<<" using Gcash."<<endl;
    }
};

class CashOnDeliver : public PaymentStrategy {
    public:
        void pay(double amount) override {
            cout<<"Please pay "<<amount<<" upon delivery."<<endl;
        }
};

// ----------------------------- Order Class -----------------------------
class Order {
private:
    Cart& cart;

public:
    Order(Cart& c) : cart(c) {}

    void checkout(PaymentStrategy* strategy) {
        if (cart.isEmpty())
            throw runtime_error("Cart is empty. Add items before checkout.");
        double total = cart.calculateTotal();
        strategy->pay(total);
        cout << "Checkout complete. Thank you for your purchase!" << endl;
    }
};

// ----------------------------- Receipt Generation -----------------------------
void generateReceipt(const User& user, const Cart& cart, const string& paymentMethod) {
    cout<<"\n--- Receipt ---\n";
    cout<<"User: "<<user.getUsername()<<endl;
    cout<<"Email: "<<user.getEmail()<<endl;
    cout<<"Shipping Address: "<<user.getAddress()<<endl;
    cout<<"Payment Method: "<<paymentMethod<<endl;
    cout<<"Items Purchased:"<<endl;

    double grandTotal = 0;
    for (const auto& entry : cart.getItems()) {
        int productId = entry.first;
        int quantity = entry.second;
        for (const auto& prod : cart.getCatalog()) {
            if (prod.getId() == productId) {
                double itemTotal = prod.getPrice() * quantity;
                cout << "- " << prod.getName() << " x" << quantity << " - Php " << itemTotal << endl;
                grandTotal += itemTotal;
                break;
            }
        }
    }
    cout << "\nTotal: Php " << grandTotal << endl;
    cout << "---------------------" << endl;
}

// ----------------------------- Input Utility Functions -----------------------------
int readInt(const string& prompt, int minValue, int maxValue) {
    int choice;
    while (true) {
        cout << prompt;
        if (cin >> choice && choice >= minValue && choice <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        } else {
            cout << "Invalid input. Please enter a number between " << minValue << " and " << maxValue << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string readNonEmptyLine(const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "Input cannot be empty. Please try again." << endl;
        }
    } while (input.empty());
    return input;
}

// ----------------------------- Email Validation Function -----------------------------
bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    if (atPos == string::npos || atPos == 0 || atPos == email.size() - 1)
        return false;
    size_t dotPos = email.find('.', atPos);
    if (dotPos == string::npos || dotPos == email.size() - 1)
        return false;
    return true;
}

// ----------------------------- User Authentication -----------------------------
struct Credential {
    string username;
    string password;
    string email;
};

vector<Credential> credentials;

bool isValidCredential(const string& input) {
    return input.length() >= 3;
}

// Sign-up function with validations (username, password, and email)
User* signUp() {
    cout << "\n--- Sign Up ---" << endl;
    string username = readNonEmptyLine("Enter a username (min. 3 characters): ");
    if (!isValidCredential(username)) {
        throw runtime_error("Username must be at least 3 characters long.");
    }
    // Check if username exists
    for (const auto& cred : credentials) {
        if (cred.username == username) {
            throw runtime_error("Username already exists. Please try logging in.");
        }
    }
    string password = readNonEmptyLine("Enter a password (min. 3 characters): ");
    if (!isValidCredential(password)) {
        throw runtime_error("Password must be at least 3 characters long.");
    }
    
    string email;
    while (true) {
        email = readNonEmptyLine("Enter your email address: ");
        if (isValidEmail(email))
            break;
        cout << "Invalid email format. Please try again." << endl;
    }
    
    credentials.push_back({username, password, email});
    cout << "Sign-up successful!" << endl;
    
    User* newUser = new User(username);
    newUser->setEmail(email);
    return newUser;
}

User* logIn() {
    cout << "\n--- Log In ---" << endl;
    string username = readNonEmptyLine("Enter your username: ");
    string password = readNonEmptyLine("Enter your password: ");
    for (const auto& cred : credentials) {
        if (cred.username == username && cred.password == password) {
            cout << "Log in successful!" << endl;
            User* user = new User(username);
            user->setEmail(cred.email);
            return user;
        }
    }
    throw runtime_error("Invalid username or password.");
}

void displayCatalog(const vector<Product>& catalog) {
    cout << "\n--- Product Catalog ---" << endl;
    for (const auto& product : catalog) {
        cout << "ID: " << product.getId()
             << " | Name: " << product.getName()
             << " | Price: Php " << product.getPrice() << endl;
    }
}

void promptAndSetShippingAddress(User* user) {
    string city = readNonEmptyLine("Enter your shipping city: ");
    string province = readNonEmptyLine("Enter your shipping province: ");
    user->setAddress(city + ", " + province);
    cout << "Shipping to: " << user->getAddress() << endl;
}

void mainMenu(){
    cout<<"-------------------------------------------\n";
    cout<<"1. Display Products.\n";
    cout<<"2. Add/Update Shipping Information.\n";
    cout<<"3. View Cart. \n";
    cout<<"4. Sign Out/Exit \n";
    cout<<"-------------------------------------------\n";
}


int main() {
    try {
        User* user = nullptr;
        while (true) { // Outer loop: allows re-authentication after sign out
            // Authentication loop
            while (user == nullptr) {
                cout << "Welcome! Please choose an option:" << endl;
                cout << "1. Sign Up" << endl;
                cout << "2. Log In" << endl;
                int authChoice = readInt("Enter choice (1 or 2): ", 1, 2);

                if (authChoice == 1) {
                    signUp();
                    cout << "You may now log in with your new credentials.\n";
                } else {
                    if (credentials.empty()) {
                        cout << "No users exist yet. Please sign up first.\n";
                    } else {
                        user = logIn();
                    }
                }
            }

            vector<Product> catalog = {
                Product(1, "Laptop", 999.99),
                Product(2, "Mouse", 25.50),
                Product(3, "Keyboard", 45.00)
            };

            Cart cart;
            cart.setCatalog(catalog);

            // Main Menu Loop
            bool shopping = true;
            while (shopping) {
                mainMenu();
                int menuChoice = readInt("Choose an option: ", 1, 4);

                switch (menuChoice) {
                    case 1: {
                        displayCatalog(catalog);

                        string addChoice;
                        while (true) {
                            cout << "\nWould you like to add an item to your cart? (y/n): ";
                            getline(cin, addChoice);
                            if (addChoice == "y" || addChoice == "Y") {
                                int prodId = readInt("Enter Product ID to add: ", 1, (int)catalog.size());
                                int qty = readInt("Enter quantity: ", 1, 100);

                                // Find product by ID
                                bool found = false;
                                for (const auto& prod : catalog) {
                                    if (prod.getId() == prodId) {
                                        cart.addProduct(prod, qty);
                                        found = true;
                                        break;
                                    }
                                }
                                if (!found) {
                                    cout << "Product not found.\n";
                                }

                            } else if (addChoice == "n" || addChoice == "N") {
                                break;
                            } else {
                                cout << "Invalid input. Please enter 'y' or 'n'.\n";
                            }
                        }
                        break;
                    }
                    case 2: {
                        cout << "\n--- Shipping Information ---\n";
                        string currentAddress = user->getAddress();
                        if (currentAddress.empty()) {
                            promptAndSetShippingAddress(user);
                        } else {
                            cout << "Current shipping address: " << currentAddress << endl;
                            cout << "1. Update shipping information\n";
                            cout << "2. Remove shipping information\n";
                            cout << "3. Cancel\n";
                            int shipChoice = readInt("Choose an option: ", 1, 3);
                            if (shipChoice == 1) {
                                promptAndSetShippingAddress(user);
                            } else if (shipChoice == 2) {
                                user->setAddress("");
                                cout << "Shipping information removed.\n";
                            } else {
                                cout << "No changes made.\n";
                            }
                        }
                        break;
                    }
                    case 3: {
                        bool inCartMenu = true;
                        while (inCartMenu) {
                            cart.showCart();
                            cout << "\nCart Options:\n";
                            cout << "1. Remove an item\n";
                            cout << "2. Proceed to Checkout\n";
                            cout << "3. Back to Main Menu\n";
                            int cartChoice = readInt("Choose an option: ", 1, 3);

                            switch (cartChoice) {
                                case 1: {
                                    cout << "\nWould you like to (1) Remove an item or (2) Update item quantity? ";
                                    int action = readInt("Enter 1 to remove, 2 to update quantity: ", 1, 2);
                                    int prodId = readInt("Enter Product ID: ", 1, (int)catalog.size());
                                    if (action == 1) {
                                        try {
                                            cart.removeProduct(prodId);
                                        } catch (const exception& e) {
                                            cout << e.what() << endl;
                                        }
                                    } else if (action == 2) {
                                        int newQty = readInt("Enter new quantity: ", 1, 100);
                                        try {
                                            cart.updateQuantity(prodId, newQty);
                                            cout << "Quantity updated.\n";
                                        } catch (const exception& e) {
                                            cout << e.what() << endl;
                                        }
                                    }
                                    break;
                                }
                                case 2: {
                                    // Proceed to checkout
                                    if (cart.isEmpty()) {
                                        cout << "Your cart is empty. Add items before checking out.\n";
                                        break;
                                    }
                                    // Check for shipping address
                                    if (user->getAddress().empty()) {
                                        cout << "No shipping address found.\n";
                                        promptAndSetShippingAddress(user);
                                    }

                                    Order order(cart);
                                    cout << "\nChoose payment method:" << endl;
                                    cout << "1. Credit Card" << endl;
                                    cout << "2. Gcash" << endl;
                                    cout << "3. Cash On Delivery" << endl;
                                    int paymentChoice = readInt("Enter your choice (1, 2, or 3): ", 1, 3);

                                    PaymentStrategy* strategy = nullptr;
                                    string paymentMethod;
                                    if (paymentChoice == 1) {
                                        strategy = new CreditCardPayment();
                                        paymentMethod = "Credit Card";
                                    } else if (paymentChoice == 2) {
                                        strategy = new GcashPayment();
                                        paymentMethod = "Gcash";
                                    } else if (paymentChoice == 3) {
                                        strategy = new CashOnDeliver();
                                        paymentMethod = "Cash On Delivery";
                                    } else {
                                        throw runtime_error("Invalid payment option.");
                                    }

                                    order.checkout(strategy);
                                    delete strategy;
                                    generateReceipt(*user, cart, paymentMethod);
                                    inCartMenu = false;
                                    cart = Cart();
                                    break;
                                }
                                case 3:
                                    inCartMenu = false;
                                    break;
                            }
                        }
                        break;
                    }
                    case 4: {
                        cout << "Would you like to:\n";
                        cout << "1. Sign Out (return to login/signup)\n";
                        cout << "2. Exit the program\n";
                        int exitChoice = readInt("Enter your choice (1 or 2): ", 1, 2);
                        if (exitChoice == 1) {
                            cout << "Signing out...\n";
                            shopping = false; // Exit main menu loop
                        } else {
                            cout << "Exiting the program. Thank you for visiting!\n";
                            delete user;
                            return 0;
                        }
                        break;
                    }
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            }

            delete user;
            user = nullptr; // This will restart the authentication loop
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}