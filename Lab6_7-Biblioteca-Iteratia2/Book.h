#pragma once
#include <string>
#include <iostream>

using std::string;
using std::to_string;


class Book {
private:
	string ISBN;

	int id = 0;
	string title;
	string author;
	string genre;
	string publisher;
	int year = 0;
	
	static int nr_entities;

public:

	//Default Constructor
	Book() = default;

	//Class Constructor
	Book(const int& id, const string& title, const string& author, const string& genre, const string& publisher, const int& year) :
		id { id },
		title{ title },
		author{ author },
		genre{ genre },
		publisher { publisher },
		year{ year } {
		ISBN = to_string(id);
		ISBN += "RO";
		ISBN += this->title.at(0);
		ISBN += this->author.at(0);
		ISBN += to_string(this->year).substr(to_string(this->year).size() - 2);
	};

	//Copy Constructor
	Book(const Book& book) :
		ISBN{ book.ISBN },
		id { book.id },
		title{ book.title },
		author{ book.author },
		genre{ book.genre },
		publisher { book.publisher },
		year{ book.year } {
		//std::cout << "Copy Constructor called here!!\n";
	};

	//Destructor Book
	~Book() = default;

	//Overload operator == pentru verificarea egalitatii dintre 2 carti prin compararea atributelor unice
	bool operator==(const Book& other) const noexcept {
		return this->title == other.title && this->author == other.author && this->year == other.year;
	}

	//Overload operator != pentru verificarea inegalitatii dintre 2 carti prin compararea atributelor unice
	bool operator!=(const Book& other) const noexcept {
		return this->title != other.title || this->author != other.author || this->year != other.year;
	}

	
	//Returneaza ISBN-ul unei carti
	string get_ISBN() const;

	//Returneaza id-ul unei carti
	int get_id() const noexcept;

	//Returneaza titlul unei carti
	string get_title() const;

	//Returneaza autorul unei carti
	string get_author() const;

	//Returneaza genul unei carti
	string get_genre() const;

	//Returneaza editura unei carti
	string get_publisher() const;

	//Returneaza anul aparitiei unei carti
	int get_year() const noexcept;

	//Seteaza titlul unei carti la valoarea string-ului dat
	void set_title(const string& new_title);

	//Seteaza autorul unei carti la valoarea string-ului dat
	void set_author(const string& new_author);

	//Seteaza genul unei carti la valoarea string-ului dat
	void set_genre(const string& new_genre);

	//Seteaza editura uei carti la valorea string-ului dat
	void set_publisher(const string& new_publisher);

	//Seteaza anul aparitiei unei carti la valoarea numarului intreg dat
	void set_year(const int& new_year) noexcept;

};
