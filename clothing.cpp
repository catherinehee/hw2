

#include <sstream>
#include <iomanip>
#include <iostream>
#include "clothing.h"

#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, 
	std::string size, std::string brand) :
    Product(category, name, price, qty),
		size_(size),
		brand_(brand)
{

}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const
{
	std::set<std::string> ret;

	std::set<std::string> name_keywords = parseStringToWords(name_);
	std::set<std::string> brand_keywords = parseStringToWords(brand_);

	ret.insert(name_keywords.begin(), name_keywords.end());
	ret.insert(brand_keywords.begin(), brand_keywords.end());
	

	return ret;
}

std::string Clothing::displayString() const
{
	string str = name_ + "\nSize: " +size_ + " Brand: " + brand_
		+ "\n" + to_string(price_) + " " + to_string(qty_) + " left.";

	return str;
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << 
		 "\n" << size_ << "\n" << brand_ << endl;
}
