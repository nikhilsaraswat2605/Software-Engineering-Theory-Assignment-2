#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
class Customer
{
    string name;
    int id;
    static int NumCustomer;

public:
    Customer(string name = "NA")
    {
        this->name = name;
        this->id = ++NumCustomer;
    }
    ~Customer() {}
    friend ostream &operator<<(ostream &os, const Customer &cust)
    {
        os << "customer id: " << cust.id << ", "
           << "customer name: " << cust.name << "\n";
        return os;
    }
    friend istream &operator>>(istream &is, Customer &cust)
    {
        is >> cust.name;
        return is;
    }
};
class ProductItem
{
    string title;
    int id;
    static int NumProductItem;
    float price;
    int copies;

public:
    ProductItem(string title = "NA", float price = 0)
    {
        this->title = title;
        this->price = price;
        this->id = ++NumProductItem;
        this->copies = 0;
    };
    ~ProductItem() {}
    friend ostream &operator<<(ostream &os, const ProductItem &pi)
    {
        os << "Product id: " << pi.id << ", "
           << "Produt title: " << pi.title << ", "
           << "Produt price: " << pi.price << ", "
           << "Produt copies: " << pi.copies << "\n";
        return os;
    }
    friend istream &operator>>(istream &is, ProductItem &pi)
    {
        is >> pi.title >> pi.price >> pi.copies;
        return is;
    }
    ProductItem &operator*(int a)
    {
        this->copies += a;
        return *this;
    }
    ProductItem &operator=(const ProductItem &pi)
    {
        this->title = pi.title;
        this->id = pi.id;
        this->price = pi.price;
        this->copies = pi.copies;
        return *this;
    }
};
class Order
{
    int id;
    static int NumOrder;
    Customer c;
    vector<ProductItem> prods;

public:
    Order(Customer &in_c)
    {
        this->c = in_c;
        this->id = ++NumOrder;
    }
    ~Order() {}
    int getid()
    {
        return this->id;
    }
    friend ostream &operator<<(ostream &os, const Order &o)
    {
        os << "Order id: " << o.id << ", "
           << "Customer-> " << o.c << "\n";
        return os;
    }
    friend istream &operator>>(istream &is, Order &o)
    {
        is >> o.c;
        return is;
    }
    Order &operator+(ProductItem &p)
    {
        this->prods.push_back(p);
        return *this;
    }
    Order &operator=(const Order &o)
    {
        this->id = o.id;
        this->c = o.c;
        this->prods = o.prods;
        return *this;
    }
};
class ShoppingBasket
{
    int id;
    static int NumBasket;
    Customer c;
    list<Order> orders;

public:
    ShoppingBasket(Customer &in_c)
    {
        this->c = in_c;
        this->id = ++NumBasket;
    }
    ~ShoppingBasket() {}
    friend ostream &operator<<(ostream &os, const ShoppingBasket &sb)
    {
        os << "Shop id: " << sb.id << ", "
           << "Customer-> " << sb.c << "\n";
        return os;
    }
    friend istream &operator>>(istream &is, ShoppingBasket &sb)
    {
        is >> sb.c;
        return is;
    }
    ShoppingBasket &operator+(Order &p)
    {
        this->orders.push_back(p);
        return *this;
    }
    ShoppingBasket &operator-(int orderid)
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
    ShoppingBasket &operator=(ShoppingBasket const &sb)
    {
        this->id = sb.id;
        this->c = sb.c;
        this->orders = sb.orders;
        return *this;
    }
};
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