#pragma once
#include "Service.h"
#include <functional>


void Library::store_book(const int& id, const string& title, const string& author, const string& genre, const string& publisher, const int& year) {
	Book book{ id, title, author, genre, publisher, year };
	this->book_validator.validate_book(book);
	this->book_repository.add_book(book);
}

const DynamicVector<Book>& Library::get_all_books() const noexcept{
	return this->book_repository.get_all_books();
}

const Book& Library::find_book(const string& ISBN) {
	return this->book_repository.find_book(ISBN);
}

const Book Library::remove_book(const string& ISBN) {
	const Book deleted_book = this->book_repository.find_book(ISBN);
	this->book_repository.delete_book(deleted_book);

	return deleted_book;
}

Book Library::update_book(const string& ISBN, const string& genre_updated, const string& publisher_updated) {
	Book old_book = this->book_repository.find_book(ISBN);
	Book updated_book{ old_book.get_id(), old_book.get_title(), old_book.get_author(), genre_updated, publisher_updated, old_book.get_year()};
	this->book_validator.validate_book(updated_book);
	this->book_repository.update_book(updated_book);

	return old_book;
}

int Library::get_size() const noexcept {
	return this->book_repository.get_size();
}


bool filter_by_release_year(const Book& filter_book, const Book& book) noexcept{
	if (book.get_year() < filter_book.get_year())
		return true;
	else
		return false;
}

bool filter_by_genre(const Book& filter_book, const Book& book){
	if (book.get_genre() == filter_book.get_genre())
		return true;
	else
		return false;
}


DynamicVector<Book> Library::filter_books(function<bool(const Book&, const Book&)> filter, const Book& filter_book) {
	DynamicVector<Book> filtered_books;
	DynamicVector<Book> booklist = this->book_repository.get_all_books();
	/*for (const auto& book : this->book_repository.get_all_books()) {
		if (!filter(filter_book, book)) {
			filtered_books.push_back(book);
		}
	}*/
	//for(IteratorVector<Book> it = booklist.begin(); it != booklist.end(); it++)
	IteratorVector<Book> it = booklist.begin();
	while (it.valid()) {
		const Book& book = it.element();
		if (!filter(filter_book, book)) {
			filtered_books.push_back(book);
		}
		it.next();
	}
	return filtered_books;
}

bool compare_by_title(const Book& b1, const Book& b2, bool reversed) {
	if (reversed == false) {
		return (b1.get_title() > b2.get_title());}
	else {
		return (b1.get_title() < b2.get_title());
	}

}

bool compare_by_author(const Book& b1, const Book& b2, bool reversed){
	if (reversed == false) {
		return (b1.get_author() > b2.get_author());}
	else {
		return (b1.get_author() < b2.get_author());
	}
}

bool compare_by_release_year_and_genre(const Book& b1, const Book& b2, bool reversed) {
	if (reversed == false) {
		if (b1.get_year() > b2.get_year())
			return true;
		else if (b1.get_year() < b2.get_year())
			return false;
		//criterii egale, se verifica criteriul secundar
		else if (b1.get_genre() > b2.get_genre())
			return true;
		else
			return false;}
	else {
		if (b1.get_year() < b2.get_year())
			return true;
		else if (b1.get_year() > b2.get_year())
			return false;
		//criterii egale, se verifica criteriul secundar
		else if (b1.get_genre() < b2.get_genre())
			return true;
		else
			return false;
	}
}

DynamicVector<Book> Library::sort_books(function<bool(const Book& b1, const Book& b2, bool reversed)> cmp, bool reversed) {
	DynamicVector<Book> sorted_books{ this->book_repository.get_all_books() };
	int sorted = 0;
	while (!sorted) {
		sorted = 1;
		for (int i = 0; i < sorted_books.size() - 1; i++) {
			if (cmp(sorted_books.at(i), sorted_books.at(i+1), reversed)) {
				sorted = 0;
				Book aux = sorted_books.at(i);
				sorted_books.at(i) = sorted_books.at(i+1);
				sorted_books.at(i+1) = aux;
			}
		}
	}

	return sorted_books;
}