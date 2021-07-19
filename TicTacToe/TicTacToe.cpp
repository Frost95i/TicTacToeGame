#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>
#include <ctime>
using namespace std;

enum Cell {
	CROSS = 'X',
	ZERO = '0',
	EMPTY = '_'
};

class TicTacToe {
private:
	int x = 0, y = 0;
	int tryX = 0, tryY = 0;
	int tryXHum = 0, tryYHum = 0;
	size_t size = 3;

	Cell whoWin = EMPTY;

	Cell** Field;

	void printField() {
		system("cls");
		for (size_t i = 0; i < size; i++)
		{
			cout << "  " << i + 1;
		}
		cout << endl;
		cout << "  ";
		for (size_t i = 0; i < size; i++)
		{
			cout << " _";
		}
		cout << endl;
		for (size_t i = 0; i < size; i++)
		{
			cout << i + 1 << " |";
			for (size_t j = 0; j < size; j++)
			{
				cout << (char)Field[j][i] << "|";
			}
			cout << endl;
		}

	}
	//=======================================Randomize
	int32_t getRandomNum(int32_t min, int32_t max)
	{
		const static auto seed = chrono::system_clock::now().time_since_epoch().count();
		static mt19937_64 generator(seed);
		uniform_int_distribution<int32_t> dis(min, max);
		return dis(generator);
	}
	//=======================================who play first
	bool whoFirst() {
		int v1;
		v1 = getRandomNum(0, 1000) % 2;
		if (v1 == 0)
		{
			return true;
		}
		else
			return false;
	}
	//=======================================add elements to field
	void addCross(int x, int y) {
		Field[x - 1][y - 1] = CROSS;
	}
	void addZero(int x, int y) {
		Field[x - 1][y - 1] = ZERO;
	}
	//=======================================step PC easy mode
	void stepPC(Cell v) {
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				if (Field[i][j] == EMPTY) {  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					Field[i][j] = v;
					return;
				}
			}
		}
	}
	//=======================================pre win situation
	bool tryWin(Cell v) {
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				if (Field[i][j] == EMPTY) {
					Field[i][j] = v;
					if (isEnd())
						return true;
					else
						Field[i][j] = EMPTY;
				}

			}
		}
		return false;
	}
	//=======================================pre lose sitution 1
	bool tryWinOpp1(Cell v) {
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				if (Field[i][j] == EMPTY) {
					Field[i][j] = v;
					if (isEnd()) {
						x = i;
						y = j;
						Field[i][j] = EMPTY;
						return true;
					}
					else
						Field[i][j] = EMPTY;
				}

			}
		}
		return false;
	}
	//=======================================pre lose sitution 2
	bool tryWinOpp2(Cell v) {
		size_t count = 0;
		if (tryPutHum(v)) {
			for (size_t i = 0; i < size; i++)
			{
				for (size_t j = 0; j < size; j++)
				{
					if (Field[i][j] == EMPTY) {
						Field[i][j] = v;
						if (isEnd()) {

							Field[i][j] = EMPTY;
							count++;
						}
						else
							Field[i][j] = EMPTY;
					}

				}
			}
			Field[tryXHum][tryYHum] = EMPTY;
			if (count > 1) {
				Cell v2;
				if (v == CROSS)
					v2 = ZERO;
				else
					v2 = CROSS;
				Field[tryX][tryY] = EMPTY;
				return centrField(v2);
			}
			else
				return false;
		}
		else
		{
			/*Field[tryXHum][tryYHum] = EMPTY;*/
			return false;
		}

	}
	//=======================================choose side
	bool centrField(Cell v) {
		if (Field[0][1] == EMPTY) {
			Field[0][1] = v;
			return true;
		}
		if (Field[2][1] == EMPTY) {
			Field[2][1] = v;
			return true;
		}
		if (Field[1][0] == EMPTY) {
			Field[1][0] = v;
			return true;
		}
		if (Field[1][2] == EMPTY) {
			Field[1][2] = v;
			return true;
		}
		return false;
	}
	//=======================================choose angle
	bool tryPut(Cell v) {
		if (Field[0][0] == EMPTY) {
			tryX = 0;
			tryY = 0;
			Field[tryX][tryY] = v;
			return true;
		}
		if (Field[0][2] == EMPTY) {
			tryX = 0;
			tryY = 2;
			Field[tryX][tryY] = v;
			return true;
		}
		if (Field[2][0] == EMPTY) {
			tryX = 2;
			tryY = 0;
			Field[tryX][tryY] = v;
			return true;
		}
		if (Field[2][2] == EMPTY) {
			tryX = 2;
			tryY = 2;
			Field[tryX][tryY] = v;
			return true;
		}
		return false;
	}
	//=======================================choose angle +1
	bool tryPutHum(Cell v) {
		if (Field[0][0] == EMPTY) {
			tryXHum = 0;
			tryYHum = 0;
			Field[tryXHum][tryYHum] = v;
			return true;
		}
		if (Field[0][2] == EMPTY) {
			tryXHum = 0;
			tryYHum = 2;
			Field[tryXHum][tryYHum] = v;
			return true;
		}
		if (Field[2][0] == EMPTY) {
			tryXHum = 2;
			tryYHum = 0;
			Field[tryXHum][tryYHum] = v;
			return true;
		}
		if (Field[2][2] == EMPTY) {
			tryXHum = 2;
			tryYHum = 2;
			Field[tryXHum][tryYHum] = v;
			return true;
		}
		return false;
	}
	//=======================================hard mode
	void stepSmartPC(Cell v) {
		//step 0
		if (v == CROSS && Field[2][2] == EMPTY) {
			Field[2][2] = v;
			return;
		}
		if (Field[1][1] == EMPTY && v == ZERO) {
			Field[1][1] = v;
			return;
		}
		if (tryWin(v))
			return;
		//step 1
		Cell v2;
		if (v == CROSS)
			v2 = ZERO;
		else
			v2 = CROSS;
		if (tryWinOpp1(v2)) {
			Field[x][y] = v;
			x = 0;
			y = 0;
			return;
		}

		if (tryPut(v)) {
			if (tryWinOpp2(v2)) {
				//Field[tryX][tryY] = EMPTY;

			}
		}
		else
			stepPC(v);

		//step 2
	/*	tryPut();
		Field[tryX][tryY] = v;
			*/

	}
	//=======================================medium mode
	void stepMediumPC(Cell v) {
		//step 0
		if (Field[1][1] == EMPTY) {
			Field[1][1] = v;
			return;
		}
		if (tryWin(v))
			return;
		//step 1
		Cell v2;
		if (v == CROSS)
			v2 = ZERO;
		else
			v2 = CROSS;
		if (tryWinOpp1(v2)) {
			Field[x][y] = v;
			x = 0;
			y = 0;
			return;
		}

		if (tryPut(v)) {
			return;
		}
		else
			stepPC(v);

	}
	//=======================================end?
	bool isEnd() {

		for (size_t i = 0; i < size; i++)
		{

			if (Field[i][0] == Field[i][1] && Field[i][0] == Field[i][2] && Field[i][0] != EMPTY) {
				whoWin = Field[i][0];
				return true;
			}
			if (Field[0][i] == Field[1][i] && Field[0][i] == Field[2][i] && Field[0][i] != EMPTY) {
				whoWin = Field[0][i];
				return true;
			}
		}
		if (Field[0][0] == Field[1][1] && Field[0][0] == Field[2][2] && Field[0][0] != EMPTY) {
			whoWin = Field[0][0];
			return true;
		}
		if (Field[0][2] == Field[1][1] && Field[0][2] == Field[2][0] && Field[0][2] != EMPTY) {
			whoWin = Field[0][2];
			return true;
		}
		return false;
	}
	//=======================================start game
	void startGame() {

		bool youFirst = whoFirst();
		if (youFirst) {
			cout << "Human play cross" << endl
				<< "PC play zero" << endl;
		}
		else
		{
			cout << "PC play cross" << endl
				<< "Human play zero" << endl;
		}
		system("pause");
		for (size_t i = 0; i < (size * size) / 2; i++)
		{
			if (youFirst) {
				printField();
				cout << "insert x: ";
				int x, y;
				cin >> x;
				cout << "insert y: ";
				cin >> y;
				addCross(x, y);
				if (isEnd())
					break;
				//step PC
				stepPC(ZERO);
				if (isEnd())
					break;
			}
			else {
				//step PC
				stepPC(CROSS);
				if (isEnd())
					break;
				//step human
				printField();
				cout << "insert x: ";
				int x, y;
				cin >> x;
				cout << "insert y: ";
				cin >> y;
				addZero(x, y);
				if (isEnd())
					break;
			}
		}

		if (youFirst && !isEnd()) {
			printField();
			cout << "insert x: ";
			int x, y;
			cin >> x;
			cout << "insert y: ";
			cin >> y;
			addCross(x, y);
		}
		else if (!isEnd()) {
			stepPC(CROSS);
		}
		printField();
		if (isEnd() && youFirst && whoWin == CROSS)
			cout << (char)whoWin << " is Win, HUMAN";
		else if (isEnd() && !youFirst && whoWin == ZERO)
			cout << (char)whoWin << " is Win, HUMAN";
		else if (isEnd() && youFirst && whoWin == ZERO)
			cout << (char)whoWin << " is Win,PC";
		else if (isEnd() && !youFirst && whoWin == CROSS)
			cout << (char)whoWin << " is Win, PC";
		else
			cout << "DROW";
		/*printField();*/
		cin.get();
		cout << endl;

	}

	//smart game ==================================================================
	void startSmartGame() {

		bool youFirst = whoFirst();
		if (youFirst) {  
			cout << "Human play cross" << endl
				<< "PC play zero" << endl;
		}
		else
		{
			cout << "PC play cross" << endl
				<< "Human play zero" << endl;
		}
		
		system("pause");//cin.get();
		for (size_t i = 0; i < (size * size) / 2; i++)
		{
			if (youFirst) {
				printField();
				cout << "insert x: ";
				int x, y;
				cin >> x;
				cout << "insert y: ";
				cin >> y;
				addCross(x, y);
				if (isEnd())
					break;
				//step PC
				stepSmartPC(ZERO);
				if (isEnd())
					break;
			}
			else {
				//step PC
				stepSmartPC(CROSS);
				if (isEnd())
					break;
				//step human
				printField();
				cout << "insert x: ";
				int x, y;
				cin >> x;
				cout << "insert y: ";
				cin >> y;
				addZero(x, y);
				if (isEnd())
					break;
			}
		}

		if (youFirst && !isEnd()) {
			printField();
			cout << "insert x: ";
			int x, y;
			cin >> x;
			cout << "insert y: ";
			cin >> y;
			addCross(x, y);
		}
		else if (!isEnd()) {
			stepSmartPC(CROSS);
		}
		printField();
		if (isEnd() && youFirst && whoWin == CROSS)
			cout << (char)whoWin << " is Win, HUMAN";
		else if (isEnd() && !youFirst && whoWin == ZERO)
			cout << (char)whoWin << " is Win, HUMAN";
		else if (isEnd() && youFirst && whoWin == ZERO)
			cout << (char)whoWin << " is Win,PC";
		else if (isEnd() && !youFirst && whoWin == CROSS)
			cout << (char)whoWin << " is Win, PC";
		else {
			printField();
			cout << "DROW";
		}
		/*printField();*/
		cin.get();
		cout << endl;

	}

	void startMediumGame() {

		bool youFirst = whoFirst(); //whoFirst();
		if (youFirst) {  //!!!! youfirst
			cout << "Human play cross" << endl
				<< "PC play zero" << endl;
		}
		else
		{
			cout << "PC play cross" << endl
				<< "Human play zero" << endl;
		}
		system("pause");
		for (size_t i = 0; i < (size * size) / 2; i++)
		{
			if (youFirst) {
				printField();
				cout << "insert x: ";
				int x, y;
				cin >> x;
				cout << "insert y: ";
				cin >> y;
				addCross(x, y);
				if (isEnd())
					break;
				//step PC
				stepMediumPC(ZERO);
				if (isEnd())
					break;
			}
			else {
				//step PC
				stepMediumPC(CROSS);
				if (isEnd())
					break;
				//step human
				printField();
				cout << "insert x: ";
				int x, y;
				cin >> x;
				cout << "insert y: ";
				cin >> y;
				addZero(x, y);
				if (isEnd())
					break;
			}
		}

		if (youFirst && !isEnd()) {
			printField();
			cout << "insert x: ";
			int x, y;
			cin >> x;
			cout << "insert y: ";
			cin >> y;
			addCross(x, y);
		}
		else if (!isEnd()) {
			stepMediumPC(CROSS);
		}
		printField();
		if (isEnd() && youFirst && whoWin == CROSS)
			cout << (char)whoWin << " is Win, HUMAN";
		else if (isEnd() && !youFirst && whoWin == ZERO)
			cout << (char)whoWin << " is Win, HUMAN";
		else if (isEnd() && youFirst && whoWin == ZERO)
			cout << (char)whoWin << " is Win,PC";
		else if (isEnd() && !youFirst && whoWin == CROSS)
			cout << (char)whoWin << " is Win, PC";
		else {
			printField();
			cout << "DROW";
		}
		/*printField();*/
		cin.get();
		cout << endl;
	}

public:

	TicTacToe() {
		Field = new Cell * [size];
		for (size_t i = 0; i < size; i++)
		{
			Field[i] = new Cell[size];
			for (size_t j = 0; j < size; j++)
			{
				Field[i][j] = EMPTY;
			}
		}
	}

	void startGame(int level) {
		if (level == 0)
			startGame();
		else if (level == 1)
			startMediumGame();
		else
			startSmartGame();
	}
	~TicTacToe() {
		for (int i = 0; i < size; i++)
			delete[] Field[i];

		delete[] Field;
	}
};
int main()
{
	int level = 0;
	cout << "Choose hard or easy: " << endl << "Easy - 0" << endl << "Medium - 1" << endl << "Hard - 2" << endl;
	cin >> level;
	TicTacToe* Game = new TicTacToe();

	Game->startGame(level);
	
	delete Game;

	return 0;
}

//Запрограммировать игру крестики нолики на поле 3х3.Прислать архив всего проекта или ссылку на гит репозиторий.
//Для джуниоров : не обязательно делать крутой искусственный интеллект в игре.Но у вас должны корректно работать
//все основные моменты в игре, как например и главный цикл игры в main.
//Челендж для опытных и продвинутых : сделать решение на поле 4х4 или 5х5 или на динамическом поле, размер 
//которого ввел пользователь.Также можно запросить у пользователя количество фигур необходимое для выигрыша, 3 - 5.