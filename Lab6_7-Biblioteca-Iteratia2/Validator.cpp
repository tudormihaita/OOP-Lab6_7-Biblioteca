#pragma once
#include <string>
#include <vector>
#include <regex>
#include "Validator.h"

using std::string;
using std::regex;

string Validator::validate_id(const int& id) const{
	if (id < 0 || id > 100)
		return "Numar identificare carte invalid, introduceti un numar cuprins intre 0 si 99!";
	else
		return "";}

string Validator::validate_title(const string& title) const{
	regex invalid_characters("[0-9;'=~^`?|/+<>,@#]+");
	if (title.length() < 2 || regex_search(title, invalid_characters))
		return "Titlu invalid, introduceti un sir de caractere valid!";
	else
		return "";}

string Validator::validate_author(const string& author) const{
	regex invalid_characters("[0-9:;'=~^!`?|/.+<>,@#]+");
	if (author.length() < 2 || regex_search(author,invalid_characters))
		return "Nume autor invalid, introduceti un sir de caractere valid!";
	else
		return "";}

string Validator::validate_genre(const string& genre) const{
	regex invalid_characters("[0-9;'=~^!`?|/.+<>,@#]+");
	if (genre.length() < 2 || regex_search(genre, invalid_characters))
		return "Gen invalid, introduceti un sir de caractere valid!";
	else
		return "";}

string Validator::validate_publisher(const string& publisher) const {
	regex invalid_characters("[();'=~^!`?|/.+<>,@#]+");

	if (publisher.length() < 2 || regex_search(publisher, invalid_characters))
		return "Editura invalida, introduceti un sir de caractere valid!";
	else
		return "";
}

string Validator::validate_year(const int& year) const{
	if (year <= 1000 || year > 2023)
		return "An invalid, introduceti un numar valid!";
	else
		return "";
}

void Validator::validate_book(const Book& book) const{
	vector<string> errors;
	if (validate_id(book.get_id()).length() > 0)
		errors.push_back(validate_id(book.get_id()));
	if(validate_title(book.get_title()).length() > 0)
		errors.push_back(validate_title(book.get_title()));
	if(validate_author(book.get_author()).length() > 0)
		errors.push_back(validate_author(book.get_author()));
	if (validate_genre(book.get_genre()).length() > 0)
		errors.push_back(validate_genre(book.get_genre()));
	if (validate_publisher(book.get_publisher()).length() > 0)
		errors.push_back(validate_publisher(book.get_publisher()));
	if (validate_year(book.get_year()).length() > 0)
		errors.push_back(validate_year(book.get_year()));

	if (errors.size() > 0)
		throw ValidationException(errors);
}