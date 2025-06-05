#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

class Item{
    private:
        int productID;
        string name;
        int quantity;
        double price;
        string category;
    
    public:
    //Constructor
        Item() : productID(0), name(""), 
        quantity(0), price(0.0), category(""){}

    //Setters
    
    void setProductID(int productID){
        this->productID =  productID;
    }

    void setName(string name){
        this->name = name;
    }

    void setQuantity(int quantity){
        this->quantity = quantity;
    }

    void setPrice(double price){
        this->price = price;
    }

    void setCategory(string catergory){
        this-> category = category;
    }

    //Getters
    
    int getProduct() const {
        return productID;
    }

    string getName() const {
        return name;
    }

    int getQuantity() const {
        return quantity;
    }

    double getPrice() const {
        return price;
    }

    string getCategory() const {
        return category;
    }
    
};

class ItemCategory : public Item{

};

class User{
    private:
        int userID;
        string userName;
        string userEmail;
        static int nextUserID; // static for unique IDs

    public:

    //Setters
        void setUserID(int userID){
            this->userID = userID;
        }

        void setUserName(string userName){
            this->userName = userName;
        }

        void setUserEmail(string userEmail){
            this->userEmail = userEmail;
        }

    //Getters
        int getUserID() const {
            return userID;
        }

        string getUserName() const {
            return userName;
        }

        string getUserEmail() const {
            return userEmail;
        }

    void signup(){
        string tempName;
        string tempEmail;
        cout<<"Enter Full Name(First Name, Last Name) : ";
        getline(cin, tempName);
        cout<<"Enter Email Address (user@email.com) : ";
        getline(cin, tempEmail);

        setUserID(nextUserID);
        nextUserID++;
        setUserName(tempName);
        setUserEmail(tempEmail);
        
    }
};

// Define static member outside the class
int User::nextUserID = 1;

void login(const vector<User>& users){
    string loginName, loginEmail;
    cout << "Enter your name: ";
    getline(cin, loginName);
    cout << "Enter your email: ";
    getline(cin, loginEmail);

    bool isLoginValid = false;
    for (const auto& user : users) {
        if (user.getUserName() == loginName && user.getUserEmail() == loginEmail) {
            isLoginValid = true;
            break;
        }
    }

    if (isLoginValid) {
        cout << "Login successful!" << endl;
    } else {
        cout << "Login failed. User not found." << endl;
    }
}

void testSignup(){
    // TEST USER SIGNUP

    vector<User> users;

    User newUser;
    newUser.signup();
    users.push_back(newUser);

    newUser.signup();
    users.push_back(newUser);

    // TEST DISPLAY USER INFO AFTER SIGNUP

    // Example: print the user ID of the first user
    if (!users.empty()) {
        cout << "User ID: " << users[0].getUserID() << endl;
        cout << users[0].getUserName()<<endl;
        cout<< users[0].getUserEmail()<<endl;


        cout << "User ID: " << users[1].getUserID() << endl;
        cout << users[1].getUserName()<<endl;
        cout<< users[1].getUserEmail()<<endl;
    }
}



int main() {
    vector<User> users;

    // Signup process (add as many users as you want)
    User newUser;
    newUser.signup();
    users.push_back(newUser);

    // You can repeat signup if you want more users
    // newUser.signup();
    // users.push_back(newUser);

    // Login process
    login(users);

    return 0;
}