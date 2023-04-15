#pragma once
#include "Service.h"
#include "Exceptions.h"
#include <map>
#include <functional>
#include <limits>

using std::map;

//typedef void (ConsoleUI::*UIMethod)();

class ConsoleUI {
private:
	Library& book_service;
	
	map<string, void(ConsoleUI::*)()> commands = {
		{"help", &ConsoleUI::help_commandsUI},
		{"display_books", &ConsoleUI::display_booksUI},
		{"add_book",&ConsoleUI::add_bookUI},
		{"find_book", &ConsoleUI::find_bookUI},
		{"delete_book", &ConsoleUI::delete_bookUI},
		{"update_book", &ConsoleUI::update_bookUI},
		{"filter_books", &ConsoleUI::filter_booksUI},
		{"sort_books", &ConsoleUI::sort_booksUI}
	};

	int read_book_id();

	string read_book_ISBN();

	string read_book_title();

	string read_book_author();

	string read_book_publisher();

	string read_book_genre();

	const int read_book_release_year();

public:

	ConsoleUI(Library& service) : book_service { service } {};

	ConsoleUI(const ConsoleUI& other) = delete;

	void print_booklist(DynamicVector<Book>& booklist);

	void print_menu();
	  
	void help_commandsUI();

	void display_booksUI();

	void add_bookUI();

	void find_bookUI();

	void delete_bookUI();

	void update_bookUI();

	void filter_booksUI();

	void sort_booksUI();

	void run();
};