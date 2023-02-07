#include <sstream>
#include <iomanip>
#include "book.h"
#include <string>

#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, 
	std::string ISBN, std::string author) :
    Product(category, name, price, qty),
		ISBN_(ISBN),
		author_(author)
{

}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
	std::set<std::string> ret;
	std::set<std::string> name_keywords = parseStringToWords(name_);
	std::set<std::string> author_keywords = parseStringToWords(author_);

	ret.insert(name_keywords.begin(), name_keywords.end());
	ret.insert(author_keywords.begin(), author_keywords.end());

	ret.insert(ISBN_);
	return ret;
}

std::string Book::displayString() const
{
	std::string str = name_ + "\nAuthor: " +author_ + " ISBN: " + ISBN_
		+ "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
	return str;
}
void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << 
			"\n" << author_<< endl;
}



