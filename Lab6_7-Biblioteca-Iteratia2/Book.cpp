#pragma once
#include <string>
#include "Book.h"

int Book::nr_entities = 0;

string Book::get_ISBN() const {
	return this->ISBN;
}

int Book::get_id() const noexcept {
	return this->id;
}

string Book::get_title() const {
	return this->title;
}

string Book::get_author() const {
	return this->author;
}

string Book::get_genre() const {
	return this->genre;
}

string Book::get_publisher() const {
	return this->publisher;
}

int Book::get_year() const noexcept {
	return this->year;
}


void Book::set_title(const string& new_title) {
	this->title = new_title;
}

void Book::set_author(const string& new_author) {
	this->author = new_author;
}


void Book::set_genre(const string& new_genre) {
	this->genre = new_genre;
}

void Book::set_publisher(const string& new_publisher) {
	this->publisher = new_publisher;
}

void Book::set_year(const int& new_year) noexcept{
	this->year = new_year;
}
