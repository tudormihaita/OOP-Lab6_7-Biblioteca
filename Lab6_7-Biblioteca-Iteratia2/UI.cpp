#pragma once
#include "UI.h"
#include <iostream>

using std::cout;
using std::cin;
using std::getline;
using std::ws;

int ConsoleUI::read_book_id() {
	int id;
	cin >> id;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw InvalidInputException("Input invalid, introduceti un numar valid!\n");
	}

	return id;
}

string ConsoleUI::read_book_ISBN() {
	string ISBN; getline(cin >> ws, ISBN);
	for (auto& c : ISBN) c = static_cast<char>(toupper(c));
	return ISBN;
}

string ConsoleUI::read_book_title() {
	string title; getline(cin >> ws, title);
	return title;
}

string ConsoleUI::read_book_author(){
	string author; getline(cin >> ws , author);
	return author;
}

string ConsoleUI::read_book_genre() {
	string genre; getline(cin >> ws, genre);
	return genre;
}

string ConsoleUI::read_book_publisher() {
	string publisher; getline(cin >> ws, publisher);
	return publisher;
}

const int ConsoleUI::read_book_release_year(){
	int release_year;
	cin >> release_year;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw InvalidInputException("Input invalid, introduceti un numar valid!\n");	
	}

	return release_year;
}


void ConsoleUI::print_booklist(DynamicVector<Book>& booklist) {
	/*for (const auto& book : booklist) {
		cout << "| " << book.get_ISBN() << " | " << book.get_title() << " | " << book.get_author() << " | " <<
			book.get_genre() << " | " << book.get_publisher() << " | " << book.get_year() << " |\n";
	}*/
	IteratorVector<Book> it = booklist.begin();
	while (it.valid()) {
		const Book& book = it.element();
		cout << "| " << book.get_ISBN() << " | " << book.get_title() << " | " << book.get_author() << " | " <<
			book.get_genre() << " | " << book.get_publisher() << " | " << book.get_year() << " |\n";
		it.next();
	}

	/*for (const Book& book : booklist) {
		cout << "| " << book.get_ISBN() << " | " << book.get_title() << " | " << book.get_author() << " | " <<
			book.get_genre() << " | " << book.get_publisher() << " | " << book.get_year() << " |\n";
	}*/
}


void ConsoleUI::print_menu() {
	cout << "Comenzi disponibile:\n";
	cout << "[help] | [display_books] | [add_book] | [find_book] | [delete_book] | [update_book] | [filter_books] | [sort_books] | [exit] \n";
}


void ConsoleUI::help_commandsUI() {
	cout << "Introduceti comanda pentru care doriti sa vizualizati detalii:\n";
	string cmd;
	cin >> cmd;
	if (cmd == "display_books") {
		cout << "[display_books] - Afiseaza toate cartile introduse in biblioteca\n";
	}
	else if (cmd == "add_book") {
		cout << "[add_book] - Adauga o noua carte in biblioteca, specificand urmatoarele atribute pentru care se respecta anumite reguli:\n";
		cout << "id - Numar de identificare unic pentru carte\n";
		cout << "titlu - Titlul cartii, format doar din litere mici si mari si alte anumite caractere speciale specifice\n";
		cout << "autor - Numele autorului cartii, format doar din litere mici si mari\n";
		cout << "gen - Genul cartii, un sir de caractere valid de lungime minim 2\n";
		cout << "editura -  Editura responsabila de publicarea cartii, facand parte din lista: Art, Aquila, Arthur, Booklet, Corint, Dacia, Humanitas, Litera\n";
		cout << "an - Anul aparitiei cartii, un numar natural valid\n";
	}
	else if (cmd == "find_book") {
		cout << "[find_book] - Cauta o carte existenta in biblioteca, prin specificarea codului unic de inregistrare ISBN\n";
	}
	else if (cmd == "delete_book") {
		cout << "[delete_book] - Sterge o carte deja existenta in biblioteca, prin specificarea codului unic de inregistrare ISBN\n";
	}
	else if (cmd == "update_book") {
		cout << "[update_book] - Modifica genul si editura unei carti, cautata dupa codul unic de inregistrare ISBN\n";
	}
	else if (cmd == "filter_books") {
		cout << "[filter_books] - Afiseaza o lista de carti filtrata dupa unul din criteriile prezentate\n";
	}
	else if (cmd == "sort_books") {
		cout << "[sort_books] - Afiseaza o lista de carti sortate dupa criteriile prezentate\n";
	}
	else {
		cout << "Comanda introdusa este invalida!\n";
	}
}

void ConsoleUI::display_booksUI() {
	DynamicVector<Book> booklist = this->book_service.get_all_books();

	if (booklist.size() == 0) {
		cout << "Nu exista carti adaugate in biblioteca!\n";
	}
	else {
		this->print_booklist(booklist);
		cout << "\n";
	}

}

void ConsoleUI::add_bookUI() {
	string title, author, genre, publisher;
	int id_number, release_year;
	cout << "Introduceti datele specifice unei carti:\n";
	cout << "Introduceti un numar identificator unic pentru care: "; id_number = this->read_book_id();
	cout << "Introduceti titlul cartii: "; title = this->read_book_title();
	cout << "Introduceti autorul cartii: "; author = this->read_book_author();
	cout << "Introduceti genul cartii: "; genre = this->read_book_genre();
	cout << "Introduceti editura cartii: "; publisher = this->read_book_publisher();
	cout << "Introduceti anul aparitiei cartii: "; release_year = this->read_book_release_year();

	this->book_service.store_book(id_number, title, author, genre, publisher, release_year);
	cout << "Carte adaugata cu succes!\n";
}

void ConsoleUI::find_bookUI() {
	if (this->book_service.get_size() == 0) {
		cout << "Nu exista carti introduse in biblioteca, nu se poate efectua cautarea!\n";
		return;
	}

	cout << "Introduceti codul unic de identificare ISBN al cartii cautate: ";
	string ISBN = this->read_book_ISBN();

	Book found_book = this->book_service.find_book(ISBN);
	cout << "Cartea gasita este: \n";

	cout << "| "<< found_book.get_ISBN()<< " | " << found_book.get_title() << " | " << found_book.get_author() << " | " <<
		found_book.get_genre() << " | " << found_book.get_publisher() << " | " <<  found_book.get_year() << " |\n";

	cout << "\n";

}

void ConsoleUI::delete_bookUI(){
	if (this->book_service.get_size() == 0) {
		cout << "Nu exista carti introduse in biblioteca, nu se poate efectua stergerea!\n";
		return;
	}

	cout << "Cartile disponibile pentru stergere sunt urmatoarele: \n";
	
	this->display_booksUI();

	cout << "Introduceti codul unic de identificare ISBN al cartii pe care doriti sa o stergeti: ";
	string ISBN = this->read_book_ISBN();

	Book deleted_book = this->book_service.remove_book(ISBN);
	cout << "A fost stearsa cu succes cartea: \n";

	cout << "| " << deleted_book.get_ISBN() << " | " << deleted_book.get_title() << " | " << deleted_book.get_author() << " | " <<
		deleted_book.get_genre() << " | " << deleted_book.get_publisher() << " | " << deleted_book.get_year() << " |\n";

	cout << "\n";
}

void ConsoleUI::update_bookUI(){
	if (this->book_service.get_size() == 0) {
		cout << "Nu exista carti introduse in biblioteca, nu se poate efectua modificarea!\n";
		return;
	}

	cout << "Cartile disponibile pentru modificare sunt urmatoarele: \n";

	this->display_booksUI();

	cout << "Introduceti codul unic de identificare ISBN pentru cartea pe care doriti sa o modificati: ";
	string ISBN = this->read_book_ISBN();

	cout << "Introduceti genul nou: "; string new_genre = this->read_book_genre();
	cout << "Introduceti editura noua: "; string new_publisher = this->read_book_publisher();
	
	Book old_book = this->book_service.update_book(ISBN, new_genre, new_publisher);

	cout << "A fost modificata cu succes cartea: \n";
	cout << "| " << old_book.get_ISBN() << " | " << old_book.get_title() << " | " << old_book.get_author() << " | " <<
		old_book.get_genre() << " | " << old_book.get_publisher() << " | " << old_book.get_year() << " |\n";

	cout << "\n";
}

void ConsoleUI::filter_booksUI() {
	if (this->book_service.get_size() == 0) {
		cout << "Nu exista carti introduse in biblioteca, nu se poate efectua filtrarea!\n";
		return;
	}
	int filter_type = -1;
	cout << "Introduceti tipul de filtrare dorit: \n";
	cout << "1 - Filtrare carti aparute inainte de anul dat\n";
	cout << "2 - Filtrare carti gen dat\n";

	cin >> filter_type;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Optiune introdusa invalida, nu se poate efectua filtrarea!\n";
		return;
	}

	if (filter_type == 1) {
		cout << "Introduceti anul minim de aparitie a cartilor: ";
		const int release_year_filter = this->read_book_release_year();

		Book book_filter;
		book_filter.set_year(release_year_filter);

		DynamicVector<Book> filtered_books = this->book_service.filter_books(&filter_by_release_year, book_filter);
		if (filtered_books.size() == 0) {
			cout << "Au fost filtrate toate cartile!\n";
			return;
		}
		else {
			cout << "Cartile filtrate dupa anul aparitiei sunt: \n";
			this->print_booklist(filtered_books);
		}
	}
	else if (filter_type == 2) {
		cout << "Introduceti genul de carte pe care doriti sa il filtrati: ";
		string genre_filter = this->read_book_genre();

		Book book_filter;
		book_filter.set_genre(genre_filter);

		DynamicVector<Book> filtered_books = this->book_service.filter_books(&filter_by_genre, book_filter);
		if (filtered_books.size() == 0) {
			cout << "Au fost filtrate toate cartile!\n";
			return;
		}
		else {
			cout << "Cartile filtrate dupa gen sunt: \n";
			this->print_booklist(filtered_books);
		}
	}
	else {
		cout << "Tip filtrare invalid, nu s-a putut efectua filtrarea!\n";
	}
}

void ConsoleUI::sort_booksUI() {
	if (this->book_service.get_size() == 0) {
		cout << "Nu exista carti introduse in biblioteca, nu se poate efectua sortarea!\n";
		return;
	}


	int sort_type = -1;
	cout << "Introduceti tipul de sortare dorit: \n";
	cout << "1 - Sortare dupa titlu\n";
	cout << "2 - Sortare dupa autor\n";
	cout << "3 - Sortare dupa an aparitie si gen\n";

	cin >> sort_type;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Optiune introdusa invalida, nu se poate efectua filtrarea!\n";
		return;
	}

	if (sort_type == 1) {
		char criteria = 'c';
		bool reversed = false;

		cout << "Introduceti criteriul de sortare:\n";
		cout << "c - sortare crescatoare\n";
		cout << "d - sortare descrescatoare\n";

		cin >> criteria;
		if (criteria != 'c' && criteria != 'd') {
			cout << "Criteriu de sortare invalid, nu se poate efectua sortarea!\n";
			return;
		}

		if (criteria == 'c')
			reversed = false;
		else if (criteria == 'd')
			reversed = true;

		DynamicVector<Book> sorted_books = this->book_service.sort_books(&compare_by_title, reversed);

		cout << "Cartile sortate in functie de titlu sunt:\n";
		this->print_booklist(sorted_books);
	}
	else if (sort_type == 2) {
		char criteria = 'c';
		bool reversed = false;

		cout << "Introduceti criteriul de sortare:\n";
		cout << "c - sortare crescatoare\n";
		cout << "d - sortare descrescatoare\n";

		cin >> criteria;
		if (criteria != 'c' && criteria != 'd') {
			cout << "Criteriu de sortare invalid, nu se poate efectua sortarea!\n";
			return;
		}

		if (criteria == 'c')
			reversed = false;
		else if (criteria == 'd')
			reversed = true;

		DynamicVector<Book> sorted_books = this->book_service.sort_books(&compare_by_author, reversed);

		cout << "Cartile sortate in functie de autor sunt:\n";
		this->print_booklist(sorted_books);
	}
	else if (sort_type == 3) {
		char criteria = 'c';
		bool reversed = false;

		cout << "Introduceti criteriul de sortare:\n";
		cout << "c - sortare crescatoare\n";
		cout << "d - sortare descrescatoare\n";

		cin >> criteria;
		if (criteria != 'c' && criteria != 'd') {
			cout << "Criteriu de sortare invalid, nu se poate efectua sortarea!\n";
			return;
		}

		if (criteria == 'c')
			reversed = false;
		else if (criteria == 'd')
			reversed = true;

		DynamicVector<Book> sorted_books = this->book_service.sort_books(&compare_by_release_year_and_genre, reversed);

		cout << "Cartile sortate in functie de an aparitie si gen sunt:\n";
		this->print_booklist(sorted_books);

	}
	else {
		cout << "Tip sortare invalid, nu s-a putut efectua sortarea!\n";;
	}
}

void ConsoleUI::run() {
	this->print_menu();
	bool running = true;
	string cmd;
	while (running) {
		cout << "Introduceti comanda: ";
		cin >> cmd;
		auto exists = this->commands.find(cmd);
		if (cmd == "exit") {
			cout << "Shutting down...\n";
			running = false;
			return;
		}
		if (exists != this->commands.end()) {
			try {
				(this->*commands.at(cmd))();
			}
			catch(ValidationException& ve) {
				cout << ve.get_error_messages();
			}
			catch (RepoException& re) {
				cout << re.get_error_message();
			}
			catch (InvalidInputException& ie) {
				cout << string(ie);
			}
		}
		else {
			cout << "Comanda invalida!\n";
		}
	}
}