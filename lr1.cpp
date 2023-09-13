#include <iostream>
#include <vector>
#include <string>


using namespace std;



vector <vector<unsigned char>> generateTable() {
	vector<vector<unsigned char>> result (26, vector<unsigned char> (26));
	
	int k = 0;
	int k1 = 0;

	for(int i = 97; i < 122; i++) 
	{
		for (int j = 97; j < 122; j++)
		{
			if (k == 26)
				k = 0;
			result[i][j] = k;
			k++;
		}
		k1++;
		k = k1;
	
	}
	

	return result;
}


string decode(string text, string key, const vector<vector<unsigned char>> &table) {
	string result = "";

	vector<int> text_arr;
	vector<int> key_arr;


	for (unsigned char ch : text)
		text_arr.push_back((int)ch);

	for (unsigned char ch : key)
		key_arr.push_back((int)ch);

	int i = 0;

	while (key_arr.size() != text_arr.size()) {
		key_arr.push_back(key_arr[i]);
		i++;
	}
	
	for (int i = 0; i < key_arr.size(); i++) {
		
		for (int k = 0; k < table.size(); k++) {
			int key_pos = 0;
			if (key_arr[i] == table[k][0]) {
				key_pos = k;
				for (int j = 0; j < table[0].size(); j++) {
					if (text_arr[i] == table[key_pos][j]) {
						result += table[0][j];
					}

				}
			}
				
		}
	}


	return result;
}

string encode(string text, string key, const vector<vector<unsigned char>> &table) {
	string result = "";
	vector<int> text_arr;
	vector<int> key_arr;
	for (unsigned char ch : text)
		text_arr.push_back((int)ch);

	for (unsigned char ch : key)
		key_arr.push_back((int)ch);

	int i = 0;
	while (key_arr.size() != text_arr.size()) {
		key_arr.push_back(key_arr[i]);
		i++;
	}
	
	for (int i = 0; i < text_arr.size(); i++) {
		int symbol = text_arr[i];
		int symbol_pos = 0;
		int key = key_arr[i];
		int key_pos = 0;
		for (int k = 1; k < table[0].size(); k++) {
			if (symbol == table[0][k])
				symbol_pos = k;
		}
		for (int k = 1; k < table.size(); k++) {
			if (key == table[k][0])
				key_pos = k;
		}
		result += table[key_pos][symbol_pos];
	}
	
	return result;
}


int main(int argc, char argv[])
{
	setlocale(0, "rus");
	/*cout << "Выберите действие" << endl;
	cout << "1. Зашифровать" << endl;
	cout << "2. Расшифровать" << endl;
	for (;;) {
		int menu_point;
		cin >> menu_point;
	}*/
	vector<vector<unsigned char>> table = generateTable();
	/*int i = 0;
	for (auto ch : ) {
		cout << ch[i];
		i++;
	}*/
	cout << encode("abcd", "abcd", table) << endl;
	cout << decode("abcd", "abcd", table) << endl;
	
}

