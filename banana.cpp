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
    
    public:

        int nextUserID = 1; //counter for unique userid

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

int main(){

//  TEST USER SIGNUP

    vector<User> users;

    User newUser;
    newUser.signup();
    users.push_back(newUser);

    newUser.signup();
    users.push_back(newUser);

//*/

//*     TEST DISPLAY USER INFO AFTER SIGNUP

    // Example: print the user ID of the first user
    if (!users.empty()) {
        cout << "User ID: " << users[0].getUserID() << endl;
        cout << users[0].getUserName()<<endl;
        cout<< users[0].getUserEmail()<<endl;


         cout << "User ID: " << users[1].getUserID() << endl;
        cout << users[1].getUserName()<<endl;
        cout<< users[1].getUserEmail()<<endl;
    }
//*/

}