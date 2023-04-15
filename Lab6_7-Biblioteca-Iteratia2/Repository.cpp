#pragma once
#include "Repository.h"
#include <vector>
#include <algorithm>


int BookRepository::get_size() const noexcept {
	//return static_cast<int>(this->booklist.size());
	return this->booklist.size();
}

bool BookRepository::exists(const Book& book) {
	for (const Book& _book : this->booklist) {
		if (_book.get_title() == book.get_title() && _book.get_author() == book.get_author() && _book.get_year() == book.get_year())
			return true;
	}

	return false;
}


const Book& BookRepository::find_book(const string& ISBN) {
	for (const Book& _book : this->booklist) {
		if (_book.get_ISBN() == ISBN) {
			return _book;
		}
	}
	throw RepoException("Cartea cu ISBN-ul " + ISBN + " nu exista in lista!\n");
}

int BookRepository::get_book_position(const Book& looked_up_book) {

	//vector<Book>::iterator it = find(this->booklist.begin(), this->booklist.end(), looked_up_book);
	IteratorVector<Book> it = this->booklist.find(this->booklist.begin(), this->booklist.end(), looked_up_book);

	//const int pos = static_cast<int>(distance(this->booklist.begin(), it));
	const int pos = this->booklist.distance(this->booklist.begin(), it);

	if (it != this->booklist.end())
		return pos;
	else
		throw RepoException("Cartea cu titlul " + looked_up_book.get_title() + " si autorul " + looked_up_book.get_author() + " aparuta in " 
			+ to_string(looked_up_book.get_year()) + " nu exista in lista!\n");}


void BookRepository::add_book(const Book& book) {
	if (exists(book)) {
		throw RepoException("Cartea cu titlul " + book.get_title() + " si autorul " + book.get_author() + 
			" aparuta in " + to_string(book.get_year()) + " exista deja in lista!\n");
	}
	//this->booklist.push_back(book);
	this->booklist.push_back(book);
}

const DynamicVector<Book>& BookRepository::get_all_books() const noexcept{
	/*vector<Book> all_books;
	for (const Book& book : this->booklist) {
		all_books.push_back(book);
	}

	return all_books;*/

	return this->booklist;
}

void BookRepository::delete_book(const Book& book_to_delete) {
	try {
		const int pos_to_delete = get_book_position(book_to_delete);
		//this->booklist.erase(this->booklist.begin() + pos_to_delete);
		this->booklist.erase(pos_to_delete);
	}
	catch (const RepoException& e) {
		throw RepoException(e);}

	/*vector<Book>::iterator it = find(this->booklist.begin(), this->booklist.end(), book_to_delete);
	if (it != this->booklist.end())
		this->booklist.erase(std::remove(this->booklist.begin(), this->booklist.end(), book_to_delete), this->booklist.end());
	else
		throw RepoException("Cartea cu titlul " + book_to_delete.get_title() + " si autorul " + book_to_delete.get_author() + " aparuta in "
			+ to_string(book_to_delete.get_year()) + " nu exista in lista!\n")*/;
}

void BookRepository::update_book(const Book& updated_book) {
	try {
		const int pos_to_update = get_book_position(updated_book);
		this->booklist.at(pos_to_update) = updated_book;

	}
	catch (const RepoException& e) {
		throw RepoException(e);}
}