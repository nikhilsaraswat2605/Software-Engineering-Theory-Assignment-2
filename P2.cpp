#include <iostream>
#include <list>
#include <vector>

using namespace std;
// customer class
class Customer
{
    string name;            // name of the customer as a string
    int id;                 // ID of the customer as an int
    static int NumCustomer; // just for uniqueness of customer IDs, because this will be declared once only, and will be changed again and again

public:
    Customer(string name = "NA") // constructor
    {
        this->name = name;
        this->id = ++NumCustomer;
    }

    ~Customer() // destructor
    {}
    friend ostream &operator<<(ostream &os, const Customer &cust) // output stream
    {
        os << endl
           << "-----------------------------------------------------------------" << endl
           << "customer id: " << cust.id << ", "
           << "customer name: " << cust.name << " " << endl
           << "-----------------------------------------------------------------" << endl;
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
    string title;              // title of the Product Item as a string
    int id;                    // Id of the Product Item as an int
    static int NumProductItem; // just for uniqueness of ProductItem IDs, because this will be declared once only, and will be changed again and again
    float price;               // price of the Product Item as a floating point number
    int copies;                // number of copies of the Product Item as an int

public:
    ProductItem(string title = "NA", float price = 0) // constructor
    {
        this->title = title;
        this->price = price;
        this->id = ++NumProductItem;
        this->copies = 0;
    }

    ~ProductItem() // destructor
    {}
    friend ostream &operator<<(ostream &os, const ProductItem &pi) // output stream
    {
        os << endl
           << "-----------------------------------------------------------------" << endl
           << "Product id: " << pi.id << ", "
           << "Produt title: " << pi.title << ", "
           << "Produt price: " << pi.price << ", "
           << "Produt copies: " << pi.copies << " " << endl
           << "-----------------------------------------------------------------" << endl;
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
    int id;                    // ID of the order as an int
    static int NumOrder;       // just for uniqueness of Order IDs, because this will be declared once only, and will be changed again and again
    Customer c;                // customer who have ordered this order
    vector<ProductItem> prods; // vector of the product items which have been ordered by the customer c

public:
    Order(Customer &in_c) // constructor
    {
        this->c = in_c;
        this->id = ++NumOrder;
    }

    ~Order() // destructor
    {
        this->c.~Customer();
        this->prods.clear();
    }
    int getid() // for accessing ID of the object
    {
        return this->id;
    }
    friend ostream &operator<<(ostream &os, const Order &o) // output stream
    {
        os << endl
           << "-----------------------------------------------------------------" << endl
           << "Order id: " << o.id << ", "
           << "Customer-> " << o.c << " " << endl
           << "-----------------------------------------------------------------" << endl;
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
    int id;               // ID of Shopping Basket as an int
    static int NumBasket; // just for uniqueness of NumBasket IDs, because this will be declared once only, and will be changed again and again
    Customer c;           // customer who has ordered his orders in this Shopping Basket
    list<Order> orders;   // list of the orders which have been ordered by the customer c

public:
    ShoppingBasket(Customer &in_c) // constructor
    {
        this->c = in_c;
        this->id = ++NumBasket;
    }

    ~ShoppingBasket() // destructor
    {
        this->c.~Customer();
        this->orders.clear();
    }
    friend ostream &operator<<(ostream &os, const ShoppingBasket &sb) // output stream
    {
        os << endl
           << "-----------------------------------------------------------------" << endl
           << "ShopBasket id: " << sb.id << ", "
           << "Customer-> " << sb.c << " " << endl;
        for (auto x : sb.orders)
        {
            os << x << endl;
        }
        os << "-----------------------------------------------------------------" << endl;
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

// initializing all the static variables with 0
int Customer::NumCustomer = 0;
int ProductItem::NumProductItem = 0;
int Order::NumOrder = 0;
int ShoppingBasket::NumBasket = 0;

int main()
{
    // create a customer
    Customer *c = new Customer("Nikhil");
    // create a product
    cout << *c << endl;
    ProductItem *p = new ProductItem("Something");
    // create an Order
    Order *o = new Order(*c);
    // add 10 copies of p to order o
    Order &oref = *o;
    oref = oref + *p * 10;
    // create a shopping basket
    ShoppingBasket *s = new ShoppingBasket(*c);
    ShoppingBasket &shop = *s;
    // added an order in the shop
    shop = shop + oref;

    // deleted an order from the shop
    shop = shop - oref.getid();

    return 0;
}