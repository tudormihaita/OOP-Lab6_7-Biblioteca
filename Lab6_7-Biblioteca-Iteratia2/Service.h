#pragma once
#include "Repository.h"
#include "Validator.h"
#include <functional>

using std::function;

//typedef bool (*CompareFct)(const Carte&, const Carte&, bool reversed);
//typedef bool (*FilterFct)(const Carte&, const Carte&);

class Library {
private:
	BookRepository& book_repository;
	Validator& book_validator;

public:
	//Constructor default Service
	Library() = default;

	//Constructor Service
	Library(BookRepository& repo, Validator& validator) noexcept:
		book_repository{ repo }, book_validator{ validator } {};

	//Constructor Service prin copiere, sters pentru a nu permite copierea
	Library(const Library& other) = delete;


	/*
	* Creeaza o carte cu atributele date, o valideaza si o adauga in lista de carti
	* @param id - int, title - string, author - string, genre - string, publisher - string, release_year - int
	* @return -
	* @throws - RepoException daca cartea creata cu atributele date exista deja in lista
	*			ValidationException daca cel putin unul dintre atributele introduse este invalid
	*/
	void store_book(const int& id, const string& title, const string& author, const string& genre, const string& publisher, const int& year);


	/*
	* Returneaza o lista cu toate cartile introduse in biblioteca
	* @return - lista cu toate cartile disponibile in biblioteca
	*/
	const DynamicVector<Book>& get_all_books() const noexcept;


	/*
	* Cauta o carte in biblioteca identificata prin codul unic ISBN
	* @param ISBN - string, cod de identificare unic pentru carti
	* @return - cartea cautata in cazul in care aceasta exista
	* @throws - RepoException daca cartea cautata nu exista in biblioteca
	*/
	const Book& find_book(const string& ISBN);


	/*
	* Cauta o carte in biblioteca prin codul unic ISBN si o elimina din lista daca aceasta exista
	* @param ISBN - string, cod de identificare unic pentru carti
	* @return - cartea stearsa in cazul in care aceasta a fost identificata cu succes
	* @throws - RepoException daca cartea cautata pentru stergere nu exista in lista
	*/
	const Book remove_book(const string& ISBN);


	/*
	* Cauta o carte in biblioteca prin codul unic ISBN si modifica valorile pentru gen si editura la noile valori date, daca acestea sunt valide
	* @param ISBN - string, cod de identificare unic pentru carti, genre_updated - noua valoare pentru genul cartii, publisher_updated - noua valoarea pentru editura cartii
	* @return - cartea gasita, inainte de modificare, daca aceasta a fost identificata cu succes
	* @throws - RepoException daca cartea cautata pentru modificare nu exista in lista
	*			ValidationException - daca valorile noi specificare pentru gen si editura nu sunt valide
	*/
	Book update_book(const string& ISBN, const string& genre_updated, const string& publisher_updated);


	/*
	* Returneaza numarul de carti disponibile in biblioteca
	* @return - int, dimensiunea listei de carti din biblioteca
	*/
	int get_size() const noexcept;

	/*
	* Returneaza o lista de carti filtrata corespunzator dupa criteriul specificat
	* @param filter - pointer la o functie de comparare a cartilor cu criteriul de filtrare, filter_book - entitate de tip Book creata conform
	*				criteriilor de filtrare, astfel incat sa fie comparata cu cartile din bilbioteca
	* @return - lista de carti filtrate corespunzator
	*/
	DynamicVector<Book> filter_books(function<bool(const Book&, const Book&)> filter, const Book& filter_book);


	/*
	* Returneaza o lista de carti sortata corespunzator dupa criteriile specificate
	* @parm cmp - pointer la o functie de comparare prin care se verifica indeplinirea relatiei de sortare dintre entitatile listei de carti din biblioteca
	*			  reversed - bool, specificator de sortare crescatoare sau descrescatoare
	* @return - lista de carti sortate corespunzator
	*/
	DynamicVector<Book> sort_books(function<bool(const Book& b1, const Book& b2, bool reversed)> cmp, bool reversed);

	//Destructor Service
	~Library() = default;

	//Functie de verificare a relatiei de filtrare dupa anul aparitiei
	friend bool filter_by_release_year(const Book& filter_book, const Book& book) noexcept;

	//Functie de verificare a relatiei de filtrare dupa genul cartii
	friend bool filter_by_genre(const Book& filter_book, const Book& book);

	//Functie de comparare a titlurilor cartilor pentru sortare dupa titlu
	friend bool compare_by_title(const Book& b1, const Book& b2, bool reversed);

	//Functie de comparare a autorilor cartilor pentru sortare dupa autor
	friend bool compare_by_author(const Book& b1, const Book& b2, bool reversed);

	//Functie de comparare a anul aparitiei si a genului cartilor pentru sortare dupa an+gen
	friend bool compare_by_release_year_and_genre(const Book& b1, const Book& b2, bool reversed);
};

bool filter_by_release_year(const Book& filter_book, const Book& book) noexcept;

bool filter_by_genre(const Book& filter_book, const Book& book);

bool compare_by_title(const Book& b1, const Book& b2, bool reversed);

bool compare_by_author(const Book& b1, const Book& b2, bool reversed);

bool compare_by_release_year_and_genre(const Book& b1, const Book& b2, bool reversed);

/*auto filter_lambda = [](const Book& filter_book, const Book& book) -> bool {
	if (book.get_year() >= filter_book.get_year())
		return true;
	else
		return false;
};*/