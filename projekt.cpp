#include<iostream>
#include<vector>
#include<iomanip>
#include<Windows.h>

using namespace std;

class Tableware { //make class Tableware (Dishes)
protected:
	string name;
	int cost;
public:
	void setName(string name) { this->name = name; }
	string getName() { return name; }
	void setCost(int cost) { this->cost = cost; }
	int getCost() { return cost; }
	Tableware() { name = "\0"; cost = 0; }
	~Tableware() { }
};

class Plate : virtual public Tableware { //make class Plates in class Tableware
protected:
	int size;
public:
	void setSize(int size) { this->size = size; }
	int getSize() { return size; }
	Plate() { size = 0; }
	Plate(int size) {; if (size) throw 1; }
	~Plate() {}
};

class Cutlery : virtual public Tableware { //make class Cutlery in class Tableware
protected:
	int number_in_set;
public:
	void setNumber(int number_in_set) { this->number_in_set = number_in_set; }
	int getNumber() { return number_in_set; }
	Cutlery() { number_in_set = 0; }
};

class Cup : virtual public Tableware { //make class Cup in class Tableware
protected:
	int capacity;
public:
	void setCapacity(int capacity) { this->capacity = capacity; }
	int getCapacity() { return capacity; }
	Cup() { capacity = 0; }
};

class Basket : public Plate, public Cutlery, public Cup { // make class Basket, that contains Plate, Cutlery, Cup
protected:
	int amount;
public:
	Basket() { amount = 0; }
	void setAmount(int amount) { this->amount = amount; }
	int getAmount() { return amount; }
};


vector<Plate> addPlate(vector<Plate> plates, string name, int cost, int size) {
	Plate a;
	a.setName(name);
	a.setCost(cost);
	a.setSize(size);
	plates.push_back(a);
	return plates;
}

vector<Cutlery> addCutlery(vector<Cutlery> cutlers, string name, int cost, int number) {
	Cutlery a;
	a.setName(name);
	a.setCost(cost);
	a.setNumber(number);
	cutlers.push_back(a);
	return cutlers;
}

vector<Cup> addCup(vector<Cup> cups, string name, int cost, int capacity) {
	Cup a;
	a.setName(name);
	a.setCost(cost);
	a.setCapacity(capacity);
	cups.push_back(a);
	return cups;
}

void checkTotalCost(int argument) { // checking Cost of user's Cart
	try { if (argument == 0) throw "You have an empty shopping cart"; }
	catch (const char* message) {
		cout << message ;
		throw;
	}
}

void newexception() { // Memory error
	try { double* p = new double[100]; }
	catch (bad_alloc except) {
		cout << "Exception is appeared" << except.what() << endl;
	}
}


int FillnCheckCin(int parametr) { // input parameter and error checking
	while (true) {
		cin >> parametr;
		if (cin.good() || cin.eof()) {
			return parametr;
		}
		cin.clear();
		cout << "\nWrong input, try again\n";
		cin.ignore(10, '\n');
	}
}

string FillnCheckCin(string parametr) { // input parameter and error checking
	while (true) {
		cin >> parametr;
		if (!cin.bad()) {
			return parametr;
		}
		cin.clear();
		cout << "\nInvalid data entry! Try again\n";
		cin.ignore(10, '\n');
	}
}

void View(vector<Basket> items) { // function to show user's cart
	string type;
	int sp_parametr;
	for (int i = 0; i < items.size(); i++) {
		if (items[i].getSize()) { sp_parametr = items[i].getSize(); type = " with size "; }
		else if (items[i].getNumber()) { sp_parametr = items[i].getNumber(); type = " number in set "; }
		else { sp_parametr = items[i].getCapacity(); type = " volume "; }
		cout << "\n " << i+1 << " | Name:" << setw(20) << items[i].getName() << " | Price: " << setw(12) << items[i].getCost() << " x" << setw(6) << items[i].getAmount()
			<< setw(20) << type << setw(8) << sp_parametr << " | " << setw(9) << items[i].getCost() * items[i].getAmount() << " |";
	}
}

void Find(vector<Basket> items) { // function to find items in user's cart
	string newn = "\0";
	int newc = 0, newa = 0, choice = 0;
	cout << "\Choose an option:" << "\n1. Name of goods" << "\n2. Price" << "\n3. Number of goods" << "\n0. Close\n";
	choice = FillnCheckCin(choice);
	switch (choice) {
	case 1: {
		cout << "\nEnter a name of good:\t";
		newn = FillnCheckCin(newn);
		for (int i = 0; i < items.size(); i++) {
			if (newn == items[i].getName()) {
				cout << "\n| Name:" << setw(20) << items[i].getName() << " | Price: " << setw(25) << items[i].getCost() << " x" << items[i].getAmount() << "|";
			}
		}
		break;
	}
	case 2: {
		cout << "\nEnter a price:\t";
		newc = FillnCheckCin(newc);
		for (int i = 0; i < items.size(); i++) {
			if (newc == items[i].getCost()) {
				cout << "\n| Name:" << setw(20) << items[i].getName() << " | Price: " << setw(25) << items[i].getCost() << " x" << items[i].getAmount() << "|";
			}
		}
		break;
	}
	case 3: {
		cout << "\nEnter a number of goods:\t";
		newa = FillnCheckCin(newa);
		for (int i = 0; i < items.size(); i++) {
			if (newa == items[i].getAmount()) {
				cout << "\n| Name:" << setw(20) << items[i].getName() << " | Price: " << setw(25) << items[i].getCost() << " x" << items[i].getAmount() << "|";
			}
		}
		break;
	}
	case 0: return;
	default: break;
	}
}

void swapp(vector<Basket>& items, int i) { //function that moves to the last position and deletes
	Basket item;
	item.setName(items[i].getName());
	item.setCost(items[i].getCost());
	item.setAmount(items[i].getAmount());
	item.setSize(items[i].getSize());
	item.setNumber(items[i].getNumber());
	item.setCapacity(items[i].getCapacity());
	items[i] = items[i + 1];
	items[i + 1] = item;

}

void Delete(vector<Basket>& items) {//function to delete item using swapp 
	string newn = "\0";
	int newc = 0, newa = 0, choice = 0;
	cout << "\nChoose an option:" << "\n1. Name of good" << "\n2. Price" << "\n3. Number of goods" <<  "\n0. Close\n";
	choice = FillnCheckCin(choice);
	switch (choice) {
	case 1: {
		cout << "\nEnter a name of good:\t";
		newn = FillnCheckCin(newn);
		for (int j = 0; j < items.size(); j++)
			if (items[j].getName() == newn) {
				for (int i = j; i < items.size() - 1; i++) {
					swapp(items, i);
				}
                cout << "\n Deleted.";
				items.pop_back();
			}
		break;
	}
	case 2: {
		cout << "\nEnter a price:\t";
		newc = FillnCheckCin(newc);
		for (int j = 0; j < items.size(); j++)
			if (items[j].getCost() == newc) {
				for (int i = j; i < items.size() - 1; i++) {
					swapp(items, i);
				}
				cout << "\n Deleted.";
				items.pop_back();
			}
			break;
		}
	case 3: {
		cout << "\nEnter a number of goods:\t";
		newa = FillnCheckCin(newa);
		for (int j = 0; j < items.size(); j++)
			if (items[j].getAmount() == newa) {
				for (int i = j; i < items.size() - 1; i++) {
					swapp(items, i);
				}
				cout << "\n Deleted.";
				items.pop_back();
			}
			break;
		}

	case 0: return;
	default: break;
	}
}

void Redact(vector<Basket>& items) { // redacting items in Cart
	int numberstr = 0, choice = 0, newc = 0, newa = 0;
	string newn = "\0";
	View(items);
	cout << "\nChoose a line of receipt to change\t";
	numberstr = FillnCheckCin(numberstr);
	numberstr--;
	while (1) {
		cout << "\nRedacting menu:" << "\n1. Name of good" << "\n2. Price" << "\n3. Number of goods" << "\n0. Close\n";
		choice = FillnCheckCin(choice);
		switch (choice) {
		case 1:
			cout << "\nEnter a new name of good\t";
			newn = FillnCheckCin(newn);
			items[numberstr].setName(newn);
			break;
		case 2:
			cout << "\nEnter a new price\t";
			newc = FillnCheckCin(newc);
			items[numberstr].setCost(newc);
			break;
		case 3:
			cout << "\nEnter a new number of goods\t";
			newa = FillnCheckCin(newa);
			items[numberstr].setAmount(newa);
			break;
		case 0: return;
		default: break;
		}
	}
}

void sortingName(vector<Basket> &items) { // Sort using name of goods
	cout << "\n1. descending\n2. ascending\n";
	int ch = 0, i, j;
	Basket t;
	ch = FillnCheckCin(ch);
	if (ch == 1) {
		for (int i = 1; i < items.size(); i++) {
			t = items[i];
			for (j = i - 1; j >= 0 && t.getName() >items[j].getName(); j--) items[j + 1] = items[j];
			items[j + 1] = t;
		}
	}
	else if (ch == 2) {
		for (int i = 1; i < items.size(); i++) {
			t = items[i];
			for (j = i - 1; j >= 0 && t.getName() < items[j].getName(); j--) items[j + 1] = items[j];
			items[j + 1] = t;
		}
	}
	else cout << "\n";
	return;
}

void sortingCost(vector<Basket>& items) { // Sort using price of goods
	cout << "\n1. descending\n2. ascending\n";
	int ch = 0, i, j;
	Basket t;
	ch = FillnCheckCin(ch);
	if (ch == 1) {
		for (int i = 1; i < items.size(); i++) {
			t = items[i];
			for (j = i - 1; j >= 0 && t.getCost() > items[j].getCost(); j--) items[j + 1] = items[j];
			items[j + 1] = t;
		}
	}
	else if (ch == 2) {
		for (int i = 1; i < items.size(); i++) {
			t = items[i];
			for (j = i - 1; j >= 0 && t.getCost() < items[j].getCost(); j--) items[j + 1] = items[j];
			items[j + 1] = t;
		}
	}
	else cout << "\n";
	return;
}

void sortingAmount(vector<Basket>& items) { // Sort using number of goods
	cout << "\n1. descending\n2. ascending\n";
	int ch = 0, i, j;
	Basket t;
	ch = FillnCheckCin(ch);
	if (ch == 1) {
		for (int i = 1; i < items.size(); i++) {
			t = items[i];
			for (j = i - 1; j >= 0 && t.getAmount() > items[j].getAmount(); j--) items[j + 1] = items[j];
			items[j + 1] = t;
		}
	}
	else if (ch == 2) {
		for (int i = 1; i < items.size(); i++) {
			t = items[i];
			for (j = i - 1; j >= 0 && t.getAmount() < items[j].getAmount(); j--) items[j + 1] = items[j];
			items[j + 1] = t;
		}
	}
	else cout << "\n";
	return;
}

void Sort(vector<Basket>& items) { // function where user can choose how he wants to sort
	int numberstr = 0, newc = 0, newa = 0;
	string newn = "\0";
	cout << "\nSort using:" << "\n1. Name of good" << "\n2. Price" << "\n3. Number of goods" << "\n0. Close\n";
	numberstr = FillnCheckCin(numberstr);
	switch (numberstr) {
	case 1:
		sortingName(items);
		return;
	case 2:
		sortingCost(items);
		return;
	case 3:
		sortingAmount(items);
		return;
	case 0: return;
	default: break;
	}
}


int main() { //int main() where you can choose options what you want to do with cart and items in it

	int ch = 1, number = 0, amount = 0, cost = 0, cost1 = 0, size1 = 0, number1 = 0, capacity1 = 0, tableware_type1 = 0, totalCost = 0;
	string name1 ="\0";
	Plate plate;
	Cutlery cut;
	Cup cup;
	vector<Basket> items;
	vector<Plate> plates;
	vector<Cutlery> cutlers;
	vector<Cup> cups;
	plates = addPlate(plates, "Plate", 100, 20);
	plates = addPlate(plates, "Bowl", 140, 25);
	cutlers = addCutlery(cutlers, "Spoon", 45, 4);
	cutlers = addCutlery(cutlers, "Fork", 45, 4);
	cups = addCup(cups, "Glass", 40, 200);
	cups = addCup(cups, "Cup", 50, 200);

	while (true) {
		cout.setf(ios::internal | ios::boolalpha);
		cout << endl << setw(45) << "MENU:\n";
		cout << setw(45) << "1. Add to the cart\n" << setw(45) << "2. Look at the cart\n" << setw(45) << "3. Clear the cart\n"
			<< setw(45) << "4. Add a new good to the shop\n" << setw(45) << "5. Find in the cart\n" << setw(45) << "6. Delete from the cart\n"
			<< setw(45) << "7. Change a good in the cart\n" << setw(45) << "8. Sort goods in the cart\n" << setw(45) << "0. Close the programm\n";
		ch = FillnCheckCin(ch);
		cout.unsetf(ios::internal);
		switch (ch) {
		case 1: {
			int tableware_type = 0;
			cout << "Choose the type of dishes from the catalogs\n:\n1) Plates\n2) Devices\n3) Glasses\n";
			tableware_type = FillnCheckCin(tableware_type);
			switch (tableware_type) {
			case 1: {
				try { if (plates.size() == 0) throw runtime_error("plates are empty"); }
				catch (runtime_error err) { cout << err.what(); break; }
				cout << "Product list: " << endl << endl;
				for (int i = 0; i < plates.size(); i++) {
					cout << i + 1 << ". " << plates[i].getName() << " with size " << plates[i].getSize() << " \Price: " << plates[i].getCost() << endl;
				}
				number = FillnCheckCin(number);
				try {
					if (number <= 0 || number > plates.size()) {
						throw 1;
					}
					else {
						cout << "\nHow much of " << plates[number - 1].getName() << " you want to buy?\t";
						amount = FillnCheckCin(amount);
						if (amount < 0) throw 'c';
						else {
							cost += plates[number - 1].getCost() * amount;

							Basket item;
							item.setName(plates[number - 1].getName());
							item.setCost(plates[number - 1].getCost());
							item.setAmount(amount);
							item.setSize(plates[number - 1].getSize());
							items.push_back(item);
							cout << "\nGoods were added successfully.";
						}
					}
				}
				catch (int) { cout << "\nError with number"; }
				catch (char) { cout << "\nError with amount"; }
				break;
			}

			case 2: {
				try { if (cutlers.size() == 0) throw runtime_error("cutlers are empty"); }
				catch (runtime_error err) { cout << err.what(); break; }
				cout << "Product list: " << endl << endl;
				for (int i = 0; i < cutlers.size(); i++) {
					cout << i + 1 << ". " << cutlers[i].getName() << " ,quantity in set " << cutlers[i].getNumber() << " \Price: " << cutlers[i].getCost() << endl; 
				}
				number = FillnCheckCin(number);
				try {
					if (number <= 0 || number > cutlers.size()) {
						throw 1;
					}
					else {
						cout << "\nHow much of " << cutlers[number - 1].getName() << " you want to buy?\t";
						amount = FillnCheckCin(amount);
						if (amount < 0) throw 'b';
						else {
							cost += cutlers[number - 1].getCost() * amount;

							Basket item;
							item.setName(cutlers[number - 1].getName());
							item.setCost(cutlers[number - 1].getCost());
							item.setAmount(amount);
							item.setNumber(cutlers[number - 1].getNumber());
							items.push_back(item);
							cout << "\nGoods were added successfully.";
						}
					}
				}
				catch (int) { cout << "\nError with number"; }
				catch (char) { cout << "\nError with amount"; }
				break;
			}

			case 3: {
				try { if (cups.size() == 0) throw runtime_error("cups are empty"); }
				catch (runtime_error err) { cout << err.what(); break; }
				cout << "Product list: " << endl << endl;
				for (int i = 0; i < cups.size(); i++) {
					cout << i + 1 << ". " << cups[i].getName() << " volume " << cups[i].getCapacity() << " \Price: " << cups[i].getCost() << endl;
				}
				number = FillnCheckCin(number);
				try {
					if (number <= 0 || number > cups.size()) {
						throw 1;
					}
					else {
						cout << "\nHow much of " << cups[number - 1].getName() << " you want to buy?\t";
						amount = FillnCheckCin(amount);
						if (amount < 0) throw 'c';
						else {
							cost += cups[number - 1].getCost() * amount;

							Basket item;
							item.setName(cups[number - 1].getName());
							item.setCost(cups[number - 1].getCost());
							item.setAmount(amount);
							item.setCapacity(cups[number - 1].getCapacity());
							items.push_back(item);
							cout << "\nGoods were added successfully.";
						}
					}
				}
				catch (int) { cout << "\nError with number"; }
				catch (...) { cout << "\nError with amount"; }
				break;
			}
			default: cout << "\nError of choosing\n"; break;
			}
			break;
		}

		case 2: {
			View(items);
			totalCost = 0;
			for (int i = 0; i < items.size(); i++)
				totalCost += (items[i].getCost() * items[i].getAmount());
			try { checkTotalCost(totalCost); }
			catch (const char* message) {
				break;
			}
			cout << "\n\n";
			cout << right << setw(50) << "Price of goods in cart:" << totalCost << endl;
			break;
		}
		case 3: {
			items.clear();	break;
		}
		case 4: {
			cout << "\nSelect type of dishes:\n1) Plates\n2) Devices\n3) Glasses\n";
			tableware_type1 = FillnCheckCin(tableware_type1);
			switch (tableware_type1) {
			case 1:
				cout << "\nEnter a name, price and size of good\n";
				name1 = FillnCheckCin(name1);
				cost1 = FillnCheckCin(cost1);
				size1 = FillnCheckCin(size1);
				plate.setName(name1);
				plate.setCost(cost1);
				plate.setSize(size1);
				plates.push_back(plate);
				cout << "\nAdded successfully.";
				break;
			case 2:
				cout << "\nEnter a name, price and number in set of good\n";
				name1 = FillnCheckCin(name1);
				cost1 = FillnCheckCin(cost1);
				number1 = FillnCheckCin(number1);
				cut.setName(name1);
				cut.setCost(cost1);
				cut.setNumber(number1);
				cutlers.push_back(cut);
				cout << "\nAdded successfully.";
				break;
			case 3:
				cout << "\nEnter a name, price and volume of good\n";
				name1 = FillnCheckCin(name1);
				cost1 = FillnCheckCin(cost1);
				capacity1 = FillnCheckCin(capacity1);
				cup.setName(name1);
				cup.setCost(cost1);
				cup.setCapacity(capacity1);
				cups.push_back(cup);
				cout << "\nAdded successfully.";
				break;
			default: break;
			}
			break;
		}

		case 5: {
			Find(items);
			break;
		}

		case 6: {
			Delete(items);
			break;
		}

		case 7: {
			Redact(items);
			break;
		}

		case 8: {
			Sort(items);
			break;
		}

		case 0: return 0;

		default: break;
		}
	}
}
