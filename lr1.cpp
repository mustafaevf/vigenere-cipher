#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


vector<unsigned char> stringToUnsignedChar(const string& key) {
	vector<unsigned char> ucharVector;

	for (char c : key) {
		ucharVector.push_back(static_cast<unsigned char>(c));
	}

	return ucharVector;
}

vector<vector<unsigned char>> getTable(){
	vector<vector<unsigned char>> result(256, vector<unsigned char>(256));;
	int k = 0;
	int k1 = 0;

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (k == 256)
				k = 0;
			result[i][j] = k;
			k++;
		}
		k1++;
		k = k1;
	}
	return result;
}

void decode(unsigned char& symbol, unsigned char& key_s) {
	ofstream file("decode.txt", ios::app);
	if (!file.is_open()) {
		cout << "File error opened";
		return;
	}
	vector<vector<unsigned char>> table = getTable();
	
	int key_position;
	int symbol_position;
	for (int j = 0; j < 256; j++) {
		if ((int)table[(int)key_s][j] == (int)symbol) {
			symbol_position = j;
		}
	}

	file << table[0][symbol_position];
}

void encode(unsigned char& symbol, unsigned char& key_s) {
	ofstream file("result.txt", ios::app);
	if (!file.is_open()) {
		cout << "File error opened";
		return;
	}
	vector<vector<unsigned char>> table = getTable();
	char result;
	int symbol_position;
	int key_position;
	for (int j = 0; j < 256; j++) {
		if ((int)table[0][j] == (int)symbol) {
			symbol_position = j;
			
		}
	}
	for (int i = 0; i < 256; i++) {
		if ((int)table[i][0] == (int)key_s) {
			key_position = i;
			
		}
	}


	file << table[key_position][symbol_position];
}


void getSymbolFromFile(const string& filename, string& key, void(*f)(unsigned char&, unsigned char&)) {
	unsigned char symbol;
	ifstream file(filename, ios::binary);
	file >> noskipws; 

	if (!file.is_open()) {
		cout << "File error opened";
		return;
	}
	file >> noskipws;
	int i = 0;
	vector<unsigned char>key_vector = stringToUnsignedChar(key);
	while (!file.eof()) {
		file >> symbol;
		//cout << symbol;
		
		//static_cast<unsigned char>(key_s);
		f(symbol, key_vector[i]);
		i++;
		if (key_vector.size() == i)
			i = 0;
	}
	cout << "Cool";
	return;
}


int main(int argc, char argv[])
{
	setlocale(0, "rus");

	cout << "1) Зашифровать\n2) Расшифровать\n3) Взломать ключ" << endl;
	int point;
	for (;;) {
		cout << "Выберите: ";
		cin >> point;
		if (point == 1) {
			string filename;
			string key;
			cout << "Введите название файла, который надо зашифровать: ";
			cin >> filename;
			cout << "Введите ключ, которым надо зашифровать: ";
			cin >> key;
			getSymbolFromFile(filename, key, encode);
		}
		else if (point == 2) {
			string filename;
			string key;
			
			cout << "Введите название файла, который надо расшифровать: ";
			cin >> filename;
			cout << "Введите ключ, которым надо расшифровать: ";
			cin >> key;
			getSymbolFromFile(filename, key, decode);
		}
		else if (point == 3) {
			int sub_point;
			cin >> sub_point;
		}
		else {
			cout << "1 или 2\n";
		}
	}

	return 0;
}
