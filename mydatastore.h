#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include <map>
#include <queue>


class MyDataStore : public DataStore {
	public:
		MyDataStore();
		~MyDataStore();

		void addProduct(Product* p);
		void addUser(User* u);

		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);

		void addToCart(std::string username, int search_hit_number);
		void buy(std::string username);
		void view(std::string username);

		
	protected:
		//container for products
		std::vector<Product*> products;

		// container for users
		std::map<std::string, std::queue<Product*> > user_carts;
		std::map<std::string, User* > usernames; // maps username to User*


		std::map<std::string, std::set<Product*> > keywords;

		std::vector<Product*> previous_search;
};

#endif