#include <sstream>
#include <iomanip>
#include "mydatastore.h"

#include <iostream>

using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
	for (size_t i = 0; i < products.size(); i++)
		delete products[i];
	for (std::map<std::string, User* >::iterator it = usernames.begin(); it != usernames.end(); ++it)
		delete it -> second;
}

void MyDataStore::addProduct(Product* p)
{
	products.push_back(p);

	// adjust keywords
	std::set<std::string> p_keywords = p -> keywords();

	for (set<string>::iterator it = p_keywords.begin(); it != p_keywords.end(); ++it)
	{
		if (keywords.find(*it) == keywords.end())
		{
			set<Product*> prods;
			prods.insert(p);

			keywords[*it] = prods;
		}
		else
		{
			keywords[*it].insert(p);
		}
	}
}

void MyDataStore::addUser(User* u)
{
	queue<Product*> curr_cart;

	user_carts[u -> getName()] = curr_cart;

	usernames[u -> getName()] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	set<Product*> ret;
	ret = keywords[terms[0]];

	if (type == 0) 
	{
		for (size_t i = 1; i < terms.size(); i++)
		{
			ret = setIntersection(ret, keywords[terms[i]]);
		}

	}
	else // OR 
	{
		for (size_t i = 0; i < terms.size(); i++)
		{
			ret = setUnion(ret, keywords[terms[i]]);
		}
	}
	vector<Product*> search_(ret.begin(), ret.end());
	previous_search = search_;

	return search_;
}

void MyDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << endl;
	for (size_t i = 0; i < products.size(); i++)
		products[i]->dump(ofile);
	ofile << "</products>" << endl;

	ofile << "<users>" << endl;
	for (std::map<std::string, User* >::iterator it = usernames.begin(); it != usernames.end(); ++it)
		(it -> second)->dump(ofile);
	ofile << "</users>" << endl;
}

void MyDataStore::view(std::string username)
{
	if (user_carts.find(username) == user_carts.end())
	{
		cout << "Invalid username" << endl;
		return;
	}
	else
	{
		std::queue<Product*> u_cart = user_carts[username];
		int index = 1;
		while (!u_cart.empty())
		{
			cout << "Item " << index << endl;
			index++;
			cout << u_cart.front() -> displayString() << endl;
			u_cart.pop();
		}

	}
}

void MyDataStore::buy(std::string username)
{
	if (user_carts.find(username) == user_carts.end())
	{
		cout << "Invalid username" << endl;
		return;
	}
	std::queue<Product*> u_cart = user_carts[username]; // to iterate through user cart
	User* curr_user = usernames[username]; // current user (corresponding)


	while (!u_cart.empty())
	{
		Product* p = u_cart.front();
		if (p -> getQty() > 0 && curr_user -> getBalance() - p ->getPrice() > 0)
		{
			p -> subtractQty(1);
			curr_user -> deductAmount(p -> getPrice());
			user_carts[username].pop();

		}
		else
		{
			Product* prod_to_end = user_carts[username].front();
			user_carts[username].pop();
			user_carts[username].push(prod_to_end);
		}
		u_cart.pop();
	}
}

void MyDataStore::addToCart(std::string username, int search_hit_number)
{
	
	if (user_carts.find(username) == user_carts.end()
		|| (size_t) search_hit_number > previous_search.size() || search_hit_number < 0){
		cout <<"Invalid request" << endl;
		return;
	}

	user_carts[username].push(previous_search[search_hit_number - 1]);
}