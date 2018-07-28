#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#define DEFAULT_LIBRARY "library.txt"
#define DEFAULT_CLIENTS "clients.txt"
#define FIELD_LEN 15

using namespace std;

class LibraryItem {
protected:
	string name, year, city, item_type, id, sum;

public:
	string get_id(void) {
		return id;
	}

	string* get_quantity(void) {
		return &sum;
	}

	string get_item_type(void) {
		return item_type;
	}

	void print_short_header(int len) {
		this->LibraryItem::print_header(len);
		cout << setw(len) << "item_type\n";
	}

	void print_short_info(int len) {
		this->LibraryItem::print_info(len);
		cout << setw(len) << item_type << '\n';
	}

	virtual void print_header(int len) {
		cout << setw(len) << "id"
			<< setw(len) << "name"
			<< setw(len) << "year"
			<< setw(len) << "city"
			<< setw(len) << "sum";
	}

	virtual void print_info(int len) {
		cout << setw(len) << id
			<< setw(len) << name
			<< setw(len) << year
			<< setw(len) << city
			<< setw(len) << sum;
	}

	virtual void write_info_to_file(ofstream *F) {
		*F << "//" << item_type << '\n';
		*F << id << '\n';
		*F << name << '\n';
		*F << year << '\n';
		*F << city << '\n';
		*F << sum << '\n';
		return;
	}

	LibraryItem(void) {
		cout << "id: "; cin >> id;
		cout << "name: "; cin >> name;
		cout << "year: "; cin >> year;
		cout << "city: "; cin >> city;
		cout << "sum: "; cin >> sum;
	}

	LibraryItem(ifstream* F) {
		getline(*F, id);
		getline(*F, name);
		getline(*F, year);
		getline(*F, city);
		getline(*F, sum);
	}

	LibraryItem(LibraryItem* rhs) {
		id = rhs->id;
		name = rhs->name;
		year = rhs->year;
		city = rhs->city;
		sum = "1";
		item_type = rhs->item_type;
	}
};
/*===========================================================================*/
/*===========================================================================*/

class Magazine : public LibraryItem {
private:
	string number, publisher, topic;

public:
	void print_header(int len) {
		LibraryItem::print_header(len);
		cout << setw(len) << "number"
			<< setw(len) << "publisher"
			<< setw(len) << "item_type"
			<< setw(len) << "topic";
	}

	void print_info(int len) {
		LibraryItem::print_info(len);
		cout << setw(len) << number
			<< setw(len) << publisher
			<< setw(len) << item_type
			<< setw(len) << topic;
	}

	void write_info_to_file(ofstream *F) {
		this->LibraryItem::write_info_to_file(F);
		*F << number << '\n';
		*F << publisher << '\n';
		*F << topic << '\n';
	}

	Magazine() : LibraryItem() {
		item_type = "magazine";
		cout << "number: "; cin >> number;
		cout << "publisher: "; cin >> publisher;
		cout << "topic: "; cin >> topic;
	}

	Magazine(ifstream* F) : LibraryItem(F) {
		item_type = "magazine";
		getline(*F, number);
		getline(*F, publisher);
		getline(*F, topic);
	}

	Magazine(Magazine* rhs) : LibraryItem((LibraryItem*)rhs) {
		number = rhs->number;
		publisher = rhs->publisher;
		topic = rhs->topic;
	}
};
/*===========================================================================*/
/*===========================================================================*/

class Newspaper : public LibraryItem {
private:
	string number, topic;

public:
	void print_header(int len) {
		LibraryItem::print_header(len);
		cout << setw(len) << "number"
			<< setw(len) << "item_type"
			<< setw(len) << "topic";
	}

	void print_info(int len) {
		LibraryItem::print_info(len);
		cout << setw(len) << number
			<< setw(len) << item_type
			<< setw(len) << topic;
	}

	void write_info_to_file(ofstream *F) {
		this->LibraryItem::write_info_to_file(F);
		*F << number << '\n';
		*F << topic << '\n';
	}

	Newspaper() : LibraryItem() {
		item_type = "newspaper";
		cout << "number: "; cin >> number;
		cout << "topic: "; cin >> topic;
	}

	Newspaper(ifstream* F) : LibraryItem(F) {
		item_type = "newspaper";
		getline(*F, number);
		getline(*F, topic);
	}

	Newspaper(Newspaper* rhs) : LibraryItem((LibraryItem*)rhs) {
		number = rhs->number;
		topic = rhs->topic;
	}
};
/*===========================================================================*/
/*===========================================================================*/

class Book : public LibraryItem {
protected:
	string author, genre, cover;

public:
	void print_header(int len) {
		LibraryItem::print_header(len);
		cout << setw(len) << "genre"
			<< setw(len) << "author"
			<< setw(len) << "item_type"
			<< setw(len) << "cover\n";
	}

	void print_info(int len) {
		LibraryItem::print_info(len);
		cout << setw(len) << genre
			<< setw(len) << author
			<< setw(len) << item_type
			<< setw(len) << cover << endl;
	}

	void write_info_to_file(ofstream *F) {
		this->LibraryItem::write_info_to_file(F);
		*F << author << '\n';
		*F << genre << '\n';
		*F << cover << '\n';
	}

	Book() : LibraryItem() {
		item_type = "book";
		cout << "author: "; cin >> author;
		cout << "genre: "; cin >> genre;
		cout << "cover: "; cin >> cover;
	}

	Book(ifstream* F) : LibraryItem(F) {
		item_type = "book";
		getline(*F, author);
		getline(*F, genre);
		getline(*F, cover);
	}

	Book(Book* rhs) : LibraryItem((LibraryItem*)rhs) {
		author = rhs->author;
		genre = rhs->genre;
		cover = rhs->cover;
	}
};
/*===========================================================================*/
/*===========================================================================*/

class Client {
private:
	string name, phone;
	string id;
	LibraryItem* * items = 0;
	int size = 0;


	void extend_items_array(void) {
		LibraryItem * *tmp = new LibraryItem *[size + 1];
		for (int i = 0; i<size; i++) {
			tmp[i] = items[i];
		}
		delete[] items;
		items = tmp;
		size++;
	}

public:
	string get_id(void) {
		return id;
	}

	bool has_item(string id) {
		for (int i = 0; i<size; i++) {
			if (items[i]->get_id() == id) {
				return true;
			}
		}
		return false;
	}

	void lend_item(LibraryItem* obj) {
		extend_items_array();
		items[size - 1] = obj;
	}

	void return_item(string id) {
		LibraryItem * *tmp = new LibraryItem *[size - 1];
		int index = -1;
		for (int i = 0; i<size; i++) {
			if (items[i]->get_id() == id) {
				index = i;
				break;
			}
		}
		for (int i = 0, j = 0; i<size; i++) {
			if (i != index) {
				tmp[j] = items[i];
				j++;
			}
		}
		delete[] items;
		items = tmp;
		size--;
	}

	void print_items(int len) {
		if (size) {
			items[0]->print_short_header(len);
		}
		for (int i = 0; i<size; i++) {
			items[i]->print_short_info(len);
		}
	}

	void print_short_header(int len) {
		cout << setw(len) << "id: ";
		cout << setw(len) << "name: ";
		cout << setw(len) << "phone: \n";
	}

	void print_short_info(int len) {
		cout << setw(len) << id;
		cout << setw(len) << name;
		cout << setw(len) << phone << '\n';
	}

	void write_items_to_file(ofstream *F) {
		*F << "//client\n";
		*F << name << '\n' << phone << '\n' << id << '\n';
		for (int j = 0; j<size; j++) {
			items[j]->write_info_to_file(F);
		}
		*F << "//end_client\n";
	}

	Client() {
		char tmp[FIELD_LEN + 2];
		cout << "id: "; cin >> id;
		cout << "name: "; cin >> name;
		cout << "phone: "; cin >> phone;
	}

	~Client() {
		for (int i = 0; i<size; i++) {
			delete items[i];
		}
		delete[] items;
	}

	Client(ifstream* F) {
		string line;
		getline(*F, name);
		getline(*F, phone);
		getline(*F, id);
		while (1) {
			getline(*F, line);
			if (line == "//end_client") {
				return;
			}

			extend_items_array();
			if (line == "//book") {
				items[size - 1] = new Book(F);
			}
			else if (line == "//newspaper") {
				items[size - 1] = new Newspaper(F);
			}
			else if (line == "//magazine") {
				items[size - 1] = new Magazine(F);
			}
		}
	}
};
/*===========================================================================*/
/*===========================================================================*/

class Library {
private:
	Client * *clients = 0;
	int clients_size = 0;
	LibraryItem * *library = 0;
	int library_size = 0;


	bool has_item(string id) {
		for (int i = 0; i<library_size - 1; i++) {
			if (library[i]->get_id() == id) {
				return true;
			}
		}
		return false;
	}

	void extend_clients_array(void) {
		Client * *tmp = new Client *[clients_size + 1];
		for (int i = 0; i<clients_size; i++) {
			tmp[i] = clients[i];
		}
		delete[] clients;
		clients = tmp;
		clients_size++;
	}

	void extend_library_array(void) {
		LibraryItem * *tmp = new LibraryItem *[library_size + 1];
		for (int i = 0; i<library_size; i++) {
			tmp[i] = library[i];
		}
		delete[] library;
		library = tmp;
		library_size++;
	}

	/*===========================================================================*/
public:
	void read_clients_from_file(const char *fname) {
		ifstream F;
		F.open(fname);
		string line;
		Client * *tmp = 0;

		while (1) {
			if (F.eof()) {
				F.close();
				return;
			}
			getline(F, line);
			if (line != "//client") {
				F.close();
				return;
			}

			extend_clients_array();
			clients[clients_size - 1] = new Client(&F);
		}
		F.close();
	}

	void write_clients_to_file(const char *fname) {
		ofstream F;
		F.open(fname);

		for (int j = 0; j<clients_size; j++) {
			clients[j]->write_items_to_file(&F);
		}
		F.close();
		return;
	}

	void add_client(void) {
		cout << "making new client...\n";
		extend_clients_array();
		clients[clients_size - 1] = new Client();
	}

	void remove_client(void) {
		string id;
		cout << "id: "; cin >> id;
		int index = -1;
		for (int i = 0; i<clients_size; i++) {
			if (clients[i]->get_id() == id) {
				delete clients[i];
				index = i;
				break;
			}
		}
		if (index == -1) {
			cout << "id not found\n";
			return;
		}
		Client * *tmp = new Client *[clients_size];
		for (int i = 0, j = 0; i<clients_size; i++) {
			if (i != index) {
				tmp[j] = clients[i];
				j++;
			}
		}
		delete[] clients;
		clients = tmp;
		clients_size--;
		cout << " id removed successfully\n";
	}

	void print_all_clients(void) {
		if (clients_size == 0) {
			return;
		}
		clients[0]->print_short_header(FIELD_LEN);
		for (int i = 0; i<clients_size; i++) {
			clients[i]->print_short_info(FIELD_LEN);
		}
	}

	void print_client(void) {
		string id;
		cout << "id: "; cin >> id;
		int index = -1;
		for (int i = 0; i<clients_size; i++) {
			if (clients[i]->get_id() == id) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			cout << "Id not found\n";
			return;
		}
		clients[index]->print_short_header(FIELD_LEN);
		clients[index]->print_short_info(FIELD_LEN);
		clients[index]->print_items(FIELD_LEN);
	}
	/*===========================================================================*/

	void read_library_from_file(const char *fname) {
		ifstream F;
		F.open(fname);
		string line;
		LibraryItem * *tmp = 0;

		while (1) {
			if (F.eof()) {
				break;
			}
			getline(F, line);
			if (line == "//book") {
				extend_library_array();
				library[library_size - 1] = new Book(&F);
			}
			else if (line == "//newspaper") {
				extend_library_array();
				library[library_size - 1] = new Newspaper(&F);
			}
			else if (line == "//magazine") {
				extend_library_array();
				library[library_size - 1] = new Magazine(&F);
			}
			else {
				break;
			}
		}
		F.close();
		return;
	}

	void write_library_to_file(const char *fname) {
		ofstream F;
		F.open(fname);
		for (int i = 0; i<library_size; i++) {
			library[i]->write_info_to_file(&F);
		}
	}

	void add_item(void) {
		extend_library_array();
		string line;
		while (1) {
			cout << "input item_type, please: "; cin >> line;
			for (int i = 0; line[i] = tolower(line[i]); i++);
			if (line == "book") {
				library[library_size - 1] = new Book();
				break;
			}
			else if (line == "magazine") {
				library[library_size - 1] = new Magazine();
				break;
			}
			else if (line == "newspaper") {
				library[library_size - 1] = new Newspaper();
				break;
			}
			cout << "Unknown item\n";
		}

		if (has_item(library[library_size - 1]->get_id())) {
			cout << "Id already exists\n";
			LibraryItem * *tmp = new LibraryItem *[library_size - 1];
			delete library[library_size - 1];
			library_size--;
			for (int i = 0; i<library_size; i++) {
				tmp[i] = library[i];
			}
			delete[] library;
			library = tmp;
			return;
		}
		cout << "Item " << line << " created successfully\n";
	}

	void remove_item(void) {
		string id;
		cout << "id: "; cin >> id;
		int index = -1;
		for (int i = 0; i<library_size; i++) {
			if (library[i]->get_id() == id) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			cout << "Id\ not found\n";
			return;
		}

		LibraryItem * *tmp = new LibraryItem *[library_size - 1];
		for (int i = 0, j = 0; i<library_size; i++) {
			if (i != index) {
				tmp[j] = library[i];
				j++;
			}
		}
		delete library[index];
		delete[] library;
		library = tmp;
		library_size--;
		cout << "Item deleted successfully\n";
	}

	void print_all_items(void) {
		if (library_size == 0) {
			return;
		}
		library[0]->print_short_header(FIELD_LEN);
		for (int i = 0; i<library_size; i++) {
			library[i]->print_short_info(FIELD_LEN);
		}
	}

	void print_item(void) {
		if (library_size == 0) {
			return;
		}
		string id;
		cout << "id: "; cin >> id;
		int index = -1;
		for (int i = 0; i<library_size; i++) {
			if (library[i]->get_id() == id) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			cout << "Id not found\n";
			return;
		}
		library[index]->print_header(FIELD_LEN);
		library[index]->print_info(FIELD_LEN);
	}
	/*===========================================================================*/

	void lend_item(void) {
		string item_id, account_id;
		int account_index = -1, item_index = -1;
		cout << "Account id: "; cin >> account_id;
		cout << "Item id: "; cin >> item_id;
		for (int i = 0; i<clients_size; i++) {
			if (clients[i]->get_id() == account_id) {
				account_index = i;
				break;
			}
		}
		if (account_index == -1) {
			cout << "Account not found\n";
			return;
		}
		for (int i = 0; i<library_size; i++) {
			if (library[i]->get_id() == item_id) {
				item_index = i;
				break;
			}
		}
		if (item_index == -1) {
			cout << "Item not found\n";
			return;
		}

		if (clients[account_index]->has_item(library[item_index]->get_id())) {
			cout << "Item'd already lended\n";
			return;
		}

		string *quantity = library[item_index]->get_quantity();
		int num = atoi(quantity->c_str());
		if (num == 0) {
			cout << "No copies left\n";
			return;
		}
		*quantity = to_string(--num);
		LibraryItem *obj = 0;
		if (library[item_index]->get_item_type() == "book") {
			obj = new Book((Book*)library[item_index]);
		}
		else if (library[item_index]->get_item_type() == "newspaper") {
			obj = new Newspaper((Newspaper*)library[item_index]);
		}
		else if (library[item_index]->get_item_type() == "magazine") {
			obj = new Magazine((Magazine*)library[item_index]);
		}
		clients[account_index]->lend_item(obj);
		cout << "Item lended successfully\n";
	}

	void return_item(void) {
		string item_id, account_id;
		int account_index = -1, item_index = -1;
		cout << "Account id: "; cin >> account_id;
		cout << "Item id: "; cin >> item_id;
		for (int i = 0; i<clients_size; i++) {
			if (clients[i]->get_id() == account_id) {
				account_index = i;
				break;
			}
		}
		if (account_index == -1) {
			cout << "Account not found\n";
			return;
		}
		for (int i = 0; i<library_size; i++) {
			if (library[i]->get_id() == item_id) {
				item_index = i;
				break;
			}
		}
		if (item_index == -1) {
			cout << "Item not found\n";
			return;
		}

		if (clients[account_index]->has_item(item_id)) {
			clients[account_index]->return_item(item_id);
			string *quantity = library[item_index]->get_quantity();
			int tmp = atoi(quantity->c_str());
			*quantity = to_string(++tmp);
			cout << "Item returned\n";
		}
		else {
			cout << "Client didn't lend this item\n";
		}
	}
};
/*===========================================================================*/
/*===========================================================================*/

void interaction_menu(Library* lib) {
	string choise;

	while (1) {
		cout << "****Interaction****\n";
		cout << "1 for lending an item\n";
		cout << "2 for getting back an item\n";
		cout << "3 to get back\n";
		while (1) {
			cout << ">>> "; cin >> choise;
			if (choise == "1") {
				lib->lend_item();
				break;
			}
			else if (choise == "2") {
				lib->return_item();
				break;
			}
			else if (choise == "3") {
				return;
			}
			else {
				cout << "Unrecognised option\n";
				continue;
			}
		}
	}
}


void library_menu(Library* lib, int* argc, char* *argv[]) {
	string choise;

	while (1) {
		cout << "****Library****\n";
		cout << "1 for saving current state\n";
		cout << "2 for adding an item\n";
		cout << "3 for removing an item\n";
		cout << "4 for printing all items\n";
		cout << "5 for printing item by id\n";
		cout << "6 to get back\n";
		while (1) {
			cout << ">>> "; cin >> choise;
			if (choise == "1") {
				if (*argc > 2) {
					lib->write_library_to_file(*argv[1]);
				}
				else {
					lib->write_library_to_file(DEFAULT_LIBRARY);
				}
				break;
			}
			else if (choise == "2") {
				lib->add_item();
				break;
			}
			else if (choise == "3") {
				lib->remove_item();
				break;
			}
			else if (choise == "4") {
				lib->print_all_items();
				break;
			}
			else if (choise == "5") {
				lib->print_item();
				break;
			}
			else if (choise == "6") {
				return;
			}
			else {
				cout << "Unrecognised option\n";
				continue;
			}
		}
	}
}


void clients_menu(Library* lib, int* argc, char* *argv[]) {
	string choise;

	while (1) {
		cout << "****Accounts****\n";
		cout << "1 for saving current state\n";
		cout << "2 for creating an account\n";
		cout << "3 for deleting an account\n";
		cout << "4 for printing all the accounts\n";
		cout << "5 for printing account by id\n";
		cout << "6 to get back\n";
		while (1) {
			cout << ">>> "; cin >> choise;
			if (choise == "1") {
				if (*argc > 2) {
					lib->write_clients_to_file(*argv[2]);
				}
				else {
					lib->write_clients_to_file(DEFAULT_CLIENTS);
				}
				break;
			}
			else if (choise == "2") {
				lib->add_client();
				break;
			}
			else if (choise == "3") {
				lib->remove_client();
				break;
			}
			else if (choise == "4") {
				lib->print_all_clients();
				break;
			}
			else if (choise == "5") {
				lib->print_client();
				break;
			}
			else if (choise == "6") {
				return;
			}
			else {
				cout << "Unrecognised option\n";
				continue;
			}
		}
	}
}


void main_menu(Library* lib, int* argc, char* *argv[]) {
	cout << "Library is successfully loaded\n";
	string choise;

	while (1) {
		cout << "****Main menu****\n";
		cout << "1 for accounts interaction\n";
		cout << "2 for library interaction\n";
		cout << "3 for interaction with clients\n";
		cout << "4 to quit\n";
		while (1) {
			cout << ">>> "; cin >> choise;
			if (choise == "1") {
				clients_menu(lib, argc, argv);
				break;
			}
			else if (choise == "2") {
				library_menu(lib, argc, argv);
				break;
			}
			else if (choise == "3") {
				interaction_menu(lib);
				break;
			}
			else if (choise == "4") {
				return;
			}
			else {
				cout << "Unrecognised option\n";
				continue;
			}
		}
	}
}


int main(int argc, char* argv[]) {
	Library lib;
	if (argc > 2) {
		lib.read_clients_from_file(argv[2]);
		lib.read_library_from_file(argv[1]);
	}
	else {
		lib.read_clients_from_file(DEFAULT_CLIENTS);
		lib.read_library_from_file(DEFAULT_LIBRARY);
	}

	main_menu(&lib, &argc, &argv);
	return 0;
}
