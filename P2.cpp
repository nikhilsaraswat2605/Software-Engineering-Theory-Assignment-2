#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
// customer class
class Customer
{
    string name;
    int id;
    static int NumCustomer; // just for uniqueness of customer IDs

public:
    Customer(string name = "NA") // constructor
    {
        this->name = name;
        this->id = ++NumCustomer;
    }
    // destructor
    ~Customer() {}
    friend ostream &operator<<(ostream &os, const Customer &cust) // output stream
    {
        os << "customer id: " << cust.id << ", "
           << "customer name: " << cust.name << "\n";
        return os;
    }
    friend istream &operator>>(istream &is, Customer &cust) // input stream
    {
        is >> cust.name;
        return is;
    }
};
// ProductItem class
class ProductItem
{
    string title;
    int id;
    static int NumProductItem; // just for uniqueness of ProductItem IDs
    float price;
    int copies;

public:
    ProductItem(string title = "NA", float price = 0) // constructor
    {
        this->title = title;
        this->price = price;
        this->id = ++NumProductItem;
        this->copies = 0;
    }
    // destructor
    ~ProductItem() {}
    friend ostream &operator<<(ostream &os, const ProductItem &pi) // output stream
    {
        os << "Product id: " << pi.id << ", "
           << "Produt title: " << pi.title << ", "
           << "Produt price: " << pi.price << ", "
           << "Produt copies: " << pi.copies << "\n";
        return os;
    }
    friend istream &operator>>(istream &is, ProductItem &pi) // input stream
    {
        is >> pi.title >> pi.price >> pi.copies;
        return is;
    }
    ProductItem &operator*(int a) // overloading of * operator, here we will add a in number of copies of object
    {
        this->copies += a;
        return *this;
    }
    ProductItem &operator=(const ProductItem &pi) // overloading of = operator
    {
        this->title = pi.title;
        this->id = pi.id;
        this->price = pi.price;
        this->copies = pi.copies;
        return *this;
    }
};
// Order class
class Order
{
    int id;
    static int NumOrder; // just for uniqueness of Order IDs
    Customer c;
    vector<ProductItem> prods;

public:
    Order(Customer &in_c) // constructor
    {
        this->c = in_c;
        this->id = ++NumOrder;
    }
    // destructor
    ~Order() {}
    int getid() // for accessing ID of the object
    {
        return this->id;
    }
    friend ostream &operator<<(ostream &os, const Order &o) // output stream
    {
        os << "Order id: " << o.id << ", "
           << "Customer-> " << o.c << "\n";
        return os;
    }
    friend istream &operator>>(istream &is, Order &o) // input stream
    {
        is >> o.c;
        return is;
    }
    Order &operator+(ProductItem &p) // overloading of + operator, here we will add productItem in the Order object
    {
        this->prods.push_back(p);
        return *this;
    }
    Order &operator=(const Order &o) // overloading of = operator
    {
        this->id = o.id;
        this->c = o.c;
        this->prods = o.prods;
        return *this;
    }
};
// ShoppingBasket class
class ShoppingBasket
{
    int id;
    static int NumBasket; // just for uniqueness of NumBasket IDs
    Customer c;
    list<Order> orders;

public:
    ShoppingBasket(Customer &in_c) // constructor
    {
        this->c = in_c;
        this->id = ++NumBasket;
    }
    // destructor
    ~ShoppingBasket() {}
    friend ostream &operator<<(ostream &os, const ShoppingBasket &sb) // output stream
    {
        os << "Shop id: " << sb.id << ", "
           << "Customer-> " << sb.c << "\n";
        return os;
    }
    friend istream &operator>>(istream &is, ShoppingBasket &sb) // input stream
    {
        is >> sb.c;
        return is;
    }
    ShoppingBasket &operator+(Order &p) // overloading of + operator, here we will add productItem in the ShoppingBasket object
    {
        this->orders.push_back(p);
        return *this;
    }
    ShoppingBasket &operator-(int orderid) // overloading of - operator, here we shall remove the order of particular ID from a ShoppingBasket Object
    {
        auto itr = this->orders.begin();
        for (; itr != this->orders.end(); itr++)
        {
            if (itr->getid() == orderid)
                break;
        }
        if (itr != this->orders.end())
        {
            this->orders.erase(itr);
        }
        return *this;
    }
    ShoppingBasket &operator=(ShoppingBasket const &sb) // overloading of = operator
    {
        this->id = sb.id;
        this->c = sb.c;
        this->orders = sb.orders;
        return *this;
    }
};
// initializing the static variables with 0
int Customer::NumCustomer = 0;
int ProductItem::NumProductItem = 0;
int Order::NumOrder = 0;
int ShoppingBasket::NumBasket = 0;

int main()
{
    // create a customer
    Customer *c = new Customer("Nikhil");
    // create a product
    cout << *c;
    ProductItem *p = new ProductItem("Something");
    // create an Order
    Order *o = new Order(*c);
    // add 10 copies of p to order o
    Order &oref = *o;
    oref = oref + *p * 10;
    // create a shopping basket
    ShoppingBasket *s = new ShoppingBasket(*c);
    ShoppingBasket &shop = *s;
    shop = shop + oref;
    shop = shop - oref.getid();
    return 0;
}