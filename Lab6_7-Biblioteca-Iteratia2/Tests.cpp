#pragma once
#include <iostream>
#include <cassert>
#include <functional>
#include "Tests.h"
#include "Validator.h"
#include "Exceptions.h"
#include "Book.h"
#include "Repository.h"
#include "Service.h"


void Tests::run_all_tests() {
	std::cout << "-------------------------------------------\n";
	std::cout << "Ruleaza teste domain...\n";
	run_domain_tests();
	std::cout << "Teste domain trecute cu succes!\n";
	std::cout << "Ruleaza teste validator...\n";
	run_validation_tests();
	std::cout << "Teste validator trecute cu succes!\n";
	std::cout << "Ruleaza teste repository...\n";
	run_repo_tests();
	std::cout << "Teste repository trecute cu succes!\n";
	std::cout << "Ruleaza teste service...\n";
	run_service_tests();
	std::cout << "Teste service trecute cu succes!\n";
	std::cout << "-------------------------------------------\n";
}

void Tests::run_domain_tests() {
	Book book(9, "War and Peace", "Lev Tolstoi", "Nuvela istorica", "Humanitas", 1869);
	assert(book.get_title() == "War and Peace");
	assert(book.get_author() == "Lev Tolstoi");
	assert(book.get_genre() == "Nuvela istorica");
	assert(book.get_publisher() == "Humanitas");
	assert(book.get_year() == 1869);
	assert(book.get_id() == 9);
	assert(book.get_ISBN() == "9ROWL69");

	Book identical_book(11, "War and Peace", "Lev Tolstoi", "Fictiune", "Corint", 1869);
	assert(book == identical_book);

	Book copy_book = book;
	assert(copy_book.get_title() == "War and Peace");
	assert(copy_book.get_author() == "Lev Tolstoi");
	assert(copy_book.get_ISBN() == book.get_ISBN());

	book.set_year(1871);
	assert(book.get_year() == 1871);
	
	book.set_title("In Search of Lost Time");
	assert(book.get_title() == "In Search of Lost Time");

	book.set_author("Marcel Proust");
	assert(book.get_author() == "Marcel Proust");

	book.set_genre("Fictiune");
	assert(book.get_genre() == "Fictiune");

	book.set_publisher("Art");
	assert(book.get_publisher() == "Art");
}

void Tests::run_validation_tests() {
	Validator book_validator;
	Book book(9, "War and Peace", "Lev Tolstoi", "Nuvela istorica", "Humanitas", 1869);
	//std::cout << book.get_ISBN() << "\n";

	book_validator.validate_book(book);

	Book invalid_book(-2, "a","a!!~", "b", "c", 10);
	try {
		book_validator.validate_book(invalid_book);
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.get_error_messages() == "Numar identificare carte invalid, introduceti un numar cuprins intre 0 si 99!\n"
			"Titlu invalid, introduceti un sir de caractere valid!\nNume autor invalid, introduceti un sir de caractere valid!\n"
			"Gen invalid, introduceti un sir de caractere valid!\nEditura invalida, introduceti una dintre editurile prezentate!\n"
			"An invalid, introduceti un numar valid!\n");
	}

}

void Tests::run_repo_tests() {
	BookRepository book_repository;
	assert(book_repository.get_size() == 0);
	Book book1{ 9, "War and Peace", "Lev Tolstoi", "Nuvela istorica", "Corint", 1869 };
	book_repository.add_book(book1);
	assert(book_repository.get_size() == 1);

	Book book2{ 12, "In Search of Lost Time", "Marcel Proust", "Fictiune", "Nemira", 1913};
	book_repository.add_book(book2);
	assert(book_repository.get_size() == 2);

	Book identical_book{ 7, "War and Peace", "Lev Tolstoi", "Biografie", "Art", 1869 };
	try {
		book_repository.add_book(identical_book);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu titlul War and Peace si autorul Lev Tolstoi aparuta in 1869 exista deja in lista!\n");
	}
	assert(book_repository.get_size() == 2);

	DynamicVector<Book> booklist = book_repository.get_all_books();
	assert(booklist.size() == 2);

	string looked_up_ISBN = book1.get_ISBN();
	Book looked_up_book = book_repository.find_book(looked_up_ISBN);
	assert(looked_up_book == book1);

	try {
		Book missing_book = book_repository.find_book("2ROIL15");
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu ISBN-ul 2ROIL15 nu exista in lista!\n");
	}

	book_repository.delete_book(book2);
	assert(book_repository.get_size() == 1);

	try {
		book_repository.delete_book(book2);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu titlul In Search of Lost Time si autorul Marcel Proust aparuta in 1913 nu exista in lista!\n");
	}

	Book updated_book{ 18, "War and Peace", "Lev Tolstoi", "Poveste de razboi", "Litera", 1869 };
	book_repository.update_book(updated_book);
	string updated_ISBN = updated_book.get_ISBN();
	assert(book_repository.find_book(updated_ISBN).get_genre() == "Poveste de razboi");

	try {
		Book missing_book{23,  "To Kill a Mockingbird", "Harper Lee", "Thriller", "Art", 1960};
		book_repository.update_book(missing_book);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu titlul To Kill a Mockingbird si autorul Harper Lee aparuta in 1960 nu exista in lista!\n");
	}
}

void Tests::run_service_tests() {
	BookRepository book_repository;
	Validator book_validator;
	Library book_library{ book_repository, book_validator };

	assert(book_library.get_size() == 0);

	book_library.store_book(23, "To Kill a Mockingbird", "Harper Lee", "Thriller", "Humanitas", 1960);
	book_library.store_book(17, "War and Peace", "Lev Tolstoi", "War story", "Corint", 1869);

	assert(book_library.get_size() == 2);
	DynamicVector<Book> booklist = book_library.get_all_books();
	assert(booklist.size() == 2);

	try {
		book_library.store_book(31, "To Kill a Mockingbird", "Harper Lee", "Roman juridic", "Art", 1960);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu titlul To Kill a Mockingbird si autorul Harper Lee aparuta in 1960 exista deja in lista!\n");
	}

	Book old_book = book_library.update_book("23ROTH60", "Roman juridic", "Corint");
	assert(old_book.get_ISBN() == "23ROTH60");
	assert(book_library.find_book("23ROTH60").get_genre() == "Roman juridic");
	assert(book_library.find_book("23ROTH60").get_publisher() == "Corint");

	try {
		book_library.update_book("19ROIM71", "Roman psihologic", "Arthur");
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu ISBN-ul 19ROIM71 nu exista in lista!\n");
	}

	const Book& deleted_book = book_library.remove_book("17ROWL69");
	assert(deleted_book.get_id() == 17);
	assert(deleted_book.get_ISBN() == "17ROWL69");
	assert(book_library.get_size() == 1);

	try {
		book_library.remove_book("19ROIM71");
	}
	catch (RepoException&) {
		assert(true);
	}

	book_library.remove_book("23ROTH60");
	assert(book_library.get_size() == 0);

	book_library.store_book(14, "In Search of Lost Time", "Marcel Proust", "Fictiune filosofica", "Humanitas", 1890);
	book_library.store_book(67, "The Trial", "Franz Kafka", "Fictiune filosofica", "Art", 1925);
	book_library.store_book(6, "Les Miserables", "Victor Hugo", "Tragedie", "Humanitas", 1862);
	book_library.store_book(19, "The Castle", "Franz Kafka", "Comedie", "Corint", 1926);

	assert(book_library.get_size() == 4);

	Book release_year_filter_book;
	release_year_filter_book.set_year(1900);

	DynamicVector<Book> filtered_books_release_year = book_library.filter_books(&filter_by_release_year, release_year_filter_book);
	assert(filtered_books_release_year.size() == 2);

	//TESTE SORT
	Book genre_filter_book;
	genre_filter_book.set_genre("Fictiune filosofica");

	DynamicVector<Book> filtered_books_genre = book_library.filter_books(&filter_by_genre, genre_filter_book);
	assert(filtered_books_genre.size() == 2);


	DynamicVector<Book> sorted_books_by_title = book_library.sort_books(&compare_by_title, false);
	assert(sorted_books_by_title.at(0).get_title() == "In Search of Lost Time");
	DynamicVector<Book> sorted_books_by_title_reversed = book_library.sort_books(&compare_by_title, true);
	assert(sorted_books_by_title_reversed.at(0).get_title() == "The Trial");

	DynamicVector<Book> sorted_books_by_author = book_library.sort_books(&compare_by_author, false);
	assert(sorted_books_by_author.at(0).get_author() == "Franz Kafka");
	DynamicVector<Book> sorted_books_by_author_reversed = book_library.sort_books(&compare_by_author, true);
	assert(sorted_books_by_author_reversed.at(0).get_author() == "Victor Hugo");

	book_library.store_book(96, "Madame Bovary", "Gustave Flaubert", "Tragedie", "Humanitas", 1862);
	book_library.store_book(12, "The Divine Comedy", "Dante Alighieri", "Drama", "Arthur", 1862);
	book_library.store_book(2, "The Brothers Karamazov", "Fyodor Dostoyevsky", "Tragic", "Humanitas", 1862);

	DynamicVector<Book> sorted_books_by_release_year_and_genre = book_library.sort_books(&compare_by_release_year_and_genre, false);
	assert(sorted_books_by_release_year_and_genre.at(0).get_year() == 1862);
	DynamicVector<Book> sorted_books_by_release_year_and_genre_reversed = book_library.sort_books(&compare_by_release_year_and_genre, true);
	assert(sorted_books_by_release_year_and_genre_reversed.at(0).get_year() == 1926);
}