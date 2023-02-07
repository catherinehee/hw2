#include <sstream>
#include <iomanip>
#include "movie.h"

#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, 
	std::string genre, std::string rating) :
    Product(category, name, price, qty),
		genre_(genre),
		rating_(rating)
{

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{

	std::set<std::string> ret;
	std::set<std::string> name_keywords = parseStringToWords(name_);

	ret.insert(name_keywords.begin(), name_keywords.end());
	ret.insert(convToLower(genre_));

	return ret;
}

std::string Movie::displayString() const
{
	string str = name_ + "\nGenre: " + genre_ + " Rating: " + rating_
		+ "\n" + to_string(price_) + " " + to_string(qty_) + " left.";

	return str;
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
		<< "\n" << genre_ << "\n" << rating_ << endl;
}