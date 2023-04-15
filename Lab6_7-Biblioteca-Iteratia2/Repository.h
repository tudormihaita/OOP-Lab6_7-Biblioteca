#pragma once
#include "Book.h"
#include "Exceptions.h"
#include "DynamicVectorTemplate.h"
#include <vector>
#include <algorithm>

using std::vector;


class BookRepository {
private:
	//vector<Book> booklist;
	DynamicVector<Book> booklist;

public:
	//Constructor default Repo
	BookRepository() noexcept = default;

	//Constructor Repo prin copiere, sters pentru a nu permite copierea
	BookRepository(const BookRepository& other) = delete;

	/*
	* Adauga o carte in lista
	* @param book - cartea care se adauga (Book)
	* @return -
	* @throws - RepoException daca o carte cu acelasi titlu, autor si an aparitie 
				exista deja in lista
	*/
	void add_book(const Book& book);

	/*
	* Returneaza o lista cu toate cartile
	* @return - lista cu carti (Booklist)
	*/
	const DynamicVector<Book>& get_all_books() const noexcept;


	//const Book& find_book(const string& title, const string& author, const int& year);

	/*
	* Cauta o carte cu ISBN-ul dat
	* @param ISBN - string, cod unic de identificare a unei carti
	* @return - entitatea Book cu ISBN-ul cautat
	* @throws - RepoException daca nu exista nicio carte cu acel ISBN
	*/
	const Book& find_book(const string& ISBN);
	

	/*
	* Returneaza pozitia pe care se afla in lista o carte cautata
	* @param looked_up_book - entitate Book cautata in lista
	* @return - int, pozitia in lista a cartii cautate
	* @throws - RepoException daca nu exista nicio carte identica cu cea data in lista
	*/
	int get_book_position(const Book& looked_up_book);


	/*
	* Sterge o carte data din lista
	* @param book_to_delete - entitate Book cautata in lista pentru a fi stearsa
	* @return -
	* @throws - RepoException daca nu exista cartea data in lista
	*/
	void delete_book(const Book& book_to_delete);


	/*
	* Modifica genul si editura unei carti date
	* @param book_to_update - entitate Book cautata in lista pentru modificare
	* @return -
	* @throws - RepoException daca cartea data nu exista in lista
	*/
	void update_book(const Book& book_to_update);


	/*
	* Returneaza numarul curent de carti din lista
	* @param -
	* @return - int, lungimea listei de carti (Booklist size)
	*/
	int get_size() const noexcept;


	/*
	* Verifica daca o carte data exista in lista
	* @param book - entitate Book cautata in lista
	* @returns - true daca cartea data exista in lista, false in caz contrar
	*/
	bool exists(const Book& book);

	//Destructor Repo
	~BookRepository() = default;
};
