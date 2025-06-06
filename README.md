Miras, Mike 
Pua, Brixx

Inteprog_Final.cpp
HOW TO USE

Signup/Login Screen
enter 1 to signup
enter 2 to login (cannot login if no existing users)

Main Menu
enter 1 to display available products
enter 2 to add/update shipping information
enter 3 to view cart
enter 4 to sign out/exit program

Product Catalog Display
After entering 1 on the main menu, users are show the product catalog which contains the product ID, name, and price.
In this screen, users can enter y/Y to add items to their cart, and n/N to exit the product catalog.
Should users enter y/Y, they are prompted to enter the product ID and quantity to add to cart. Afterwards, they are prompted
whether or not they want to add more items to cart.

Shipping Information Menu
if there is no existing shipping info, users are prompted to first enter the city of their shipping address, and then the province.
if there is existing shipping info, users are prompted to:
enter 1 to update shipping info
enter 2 to remove shipping info
enter 3 to cancel operation

View Cart
the view cart function displays the user's current cart.
Users are then prompted to:
enter 1 to remove/update item quantity
enter 2 to proceed to checkout
enter 3 to go back to main menu

upon entering 1, users must again enter either 1 to remove an item or 2 to update item quantity.

upon entering 2, users proceed to checkout. 
If there is no existing shipping info, users are prompted to add a shipping address before proceeding. 
Otherwise, users are prompted to choose their payment method/strategy:
enter 1 to choose Credit Card
enter 2 to choose GCash
enter 3 for Cash on Delivery

afterwards, a receipt is generated containing the username, user email, shipping address, and a summary of their purchase

Sign Out/Exit
upon entering 4 on the main menu, users are asked whether to sign out (enter 1) or exit the program (enter 2).
Should users sign out, they are brought back to the initial Signup/Login Screen.
