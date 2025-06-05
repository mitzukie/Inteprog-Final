#include <iostream>
#include <vector>
#include <map>
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
    map<int, int> items; // productId -> quantity
    vector<Product> catalog;

public:
    void setCatalog(const vector<Product>& products) {
        catalog = products;
    }

    void addProduct(const Product& product, int quantity) {
        if (quantity <= 0)
            throw runtime_error("Quantity must be greater than 0.");
        items[product.getId()] += quantity;
        cout << "Added " << quantity << " of " << product.getName() << " to cart." << endl;
    }

    void removeProduct(int productId) {
        if (items.count(productId) == 0)
            throw runtime_error("Product not in cart.");
        items.erase(productId);
        cout << "Removed product ID " << productId << " from cart." << endl;
    }

    void updateQuantity(int productId, int newQuantity) {
        if (items.count(productId) == 0)
            throw runtime_error("Product not in cart.");
        if (newQuantity <= 0)
            throw runtime_error("Quantity must be greater than 0.");
        items[productId] = newQuantity;
    }

    void showCart() const {
        cout << "\n--- Cart ---" << endl;
        double total = 0;
        for (const auto& item : items) {
            for (const auto& prod : catalog) {
                if (prod.getId() == item.first) {
                    double itemTotal = prod.getPrice() * item.second;
                    cout << prod.getName() << " x" << item.second << " - Php " << itemTotal << endl;
                    total += itemTotal;
                }
            }
        }
        cout << "Total: Php " << total << endl;
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
    
    const map<int, int>& getItems() const {
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
        cout << "Paid Php " << amount << " using Credit Card." << endl;
    }
};

class GcashPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Paid Php " << amount << " using Gcash." << endl;
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
    cout << "\n--- Receipt ---\n";
    cout << "User: " << user.getUsername() << endl;
    cout << "Email: " << user.getEmail() << endl;
    cout << "Shipping Address: " << user.getAddress() << endl;
    cout << "Payment Method: " << paymentMethod << endl;
    cout << "Items Purchased:" << endl;

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
map<string, string> credentials;

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
    if (credentials.find(username) != credentials.end()) {
        throw runtime_error("Username already exists. Please try logging in.");
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
    
   
    credentials[username] = password;
    cout << "Sign-up successful!" << endl;
    
    User* newUser = new User(username);
    newUser->setEmail(email);
    return newUser;
}

User* logIn() {
    cout << "\n--- Log In ---" << endl;
    string username = readNonEmptyLine("Enter your username: ");
    string password = readNonEmptyLine("Enter your password: ");
    if (credentials.find(username) == credentials.end() || credentials[username] != password) {
        throw runtime_error("Invalid username or password.");
    }
    cout << "Log in successful!" << endl;
    return new User(username);
}

int main() {
    try {
        cout << "Welcome! Please choose an option:" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Log In" << endl;
        int authChoice = readInt("Enter choice (1 or 2): ", 1, 2);

        User* user = nullptr;
        if (authChoice == 1) {
            user = signUp();
        } else {
            user = logIn();
        }

        vector<Product> catalog = {
            Product(1, "Laptop", 999.99),
            Product(2, "Mouse", 25.50),
            Product(3, "Keyboard", 45.00)
        };

        Cart cart;
        cart.setCatalog(catalog);

        // Shopping cart interaction
        cart.addProduct(catalog[0], 1);
        cart.addProduct(catalog[1], 2);
        cart.showCart();

        // Shipping details
        string city = readNonEmptyLine("Enter your shipping city: ");
        string province = readNonEmptyLine("Enter your shipping province: ");
        user->setAddress(city + ", " + province);
        cout << "Shipping to: " << user->getAddress() << endl;

        // Process order
        Order order(cart);
        cout << "\nChoose payment method:" << endl;
        cout << "1. Credit Card" << endl;
        cout << "2. Gcash" << endl;
        int paymentChoice = readInt("Enter your choice (1 or 2): ", 1, 2);

        PaymentStrategy* strategy = nullptr;
        string paymentMethod;
        if (paymentChoice == 1) {
            strategy = new CreditCardPayment();
            paymentMethod = "Credit Card";
        } else if (paymentChoice == 2) {
            strategy = new GcashPayment();
            paymentMethod = "Gcash";
        } else {
            throw runtime_error("Invalid payment option.");
        }
        
        order.checkout(strategy);
        delete strategy;

        generateReceipt(*user, cart, paymentMethod);

        delete user;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}