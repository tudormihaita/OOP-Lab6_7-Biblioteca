#pragma once
#include <string>
#include "Book.h"
#include "Exceptions.h"

using std::string;

class Validator {
private:

	/*
	* Valideaza id-ul unei carti date
	* @param id - int, numar intreg
	* @return - mesaj de eroare in cazul in care id-ul dat este un numar negativ
	*			string vid in caz contrar
	*/
	string validate_id(const int& id) const;


	/*
	* Valideaza titlul unei carti date
	* @param title - string, titlu de carte
	* @return - mesaj de eroare in cazul in care string-ul dat are mai putin de 2 caractere sau contine caractere speciale invalide
	*			string vid in caz contrar
	*/
	string validate_title(const string& title) const;


	/*
	* Valideaza autorul unei carti date
	* @param author - string, nume de autor
	* @return - mesaj de eroare in cazul in care string-ul dat are mai putin de 2 caractere sau contine caractere speciale invalide
	*			string vid in caz contrar
	*/
	string validate_author(const string& author) const;


	/*
	* Valideaza genul unei carti date
	* @param genre - string, gen de carte
	* @return - mesaj de eroare in cazul in care string-ul dat are mai putin de 2 caractere sau contine caractere speciale invalide
	*			string invalid in caz contrar
	*/
	string validate_genre(const string& genre) const;


	/*
	* Valideaza editura unei carti date
	* @param publisher - string, nume de editura/publicatie
	* @return - mesaj de eroare in cazul in care string-ul dat nu apare in lista de edituri valide
	*			string vid in caz contrar
	*/
	string validate_publisher(const string& publisher) const;

	/*
	* Valideaza anul de aparitie a unei carti date
	* @param year - int, numar intreg
	* @return - mesaj de eroare in cazul in care numarul dat este mai mic decat 1000 sau mai mare decat anul curent
	*			string vid in caz contrar
	*/
	string validate_year(const int& year) const;

public:

	/*
	* Valideaza o carte data prin verificarea tuturor atributelor
	* @param book - entitate de tip Book, o carte data
	* @return -
	* @throws - ValidationException daca cartea introdusa are cel putin un atribut invalid
	*/
	void validate_book(const Book& book) const;
};