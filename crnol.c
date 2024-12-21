#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <conio.h>

#pragma warning(disable : 4996)

//Меню
int Menu(int choice, int rows, int cols, int win_count)
{
	system("cls");
	printf("Крестики нолики\n\n");
	printf("%s длина: %d\n", (choice == 0) ? "1) Ввод длины поля <== " : "1) Ввод длины поля  ", rows);
	printf("%s ширина: %d\n", (choice == 1) ? "2) Ввод ширины поля <== " : "2) Ввод ширины поля  ", cols);
	printf("%s количество символов для победы: %d\n", (choice == 2) ? "3) Ввод количества символов для победы <== " : "3) Ввод количества символов для победы  ", win_count);
	printf("%s%s\n", (choice == 3) ? "4) Играть <== " : "4) Играть  ", "");
	printf("%s%s\n", (choice == 4) ? "5) Выход  <== " : "5) Выход ", "");
}

int setLenght() {
	int r;
	while (1) {
		system("cls");
		printf("Введите длину поля (от 3 до 15): ");

		if (scanf("%d", &r) != 1) {
			printf("Неверный ввод, введите только цифры.\n");
			_getch();
			while (getchar() != '\n');
			continue;
		}

		if (r >= 3 && r <= 15) {
			printf("Введенная длина: %d\n", r);
			_getch();
			return r; 
		}
		else {
			printf("Неверный формат длины, введите число от 3 до 15.\n");
			_getch();
		}
	}
}

//Ширина
int setHeight() {
	int r;
	while (1) {
		system("cls");
		printf("Введите ширину поля (от 3 до 15): ");

		if (scanf("%d", &r) != 1) {
			printf("Неверный ввод, введите только цифры.\n");
			_getch();
			while (getchar() != '\n');
			continue;
		}

		if (r >= 3 && r <= 15) {
			printf("Введенная ширина: %d\n", r);
			_getch();
			return r;
		}
		else {
			printf("Неверный формат ширины, введите число от 3 до 15.\n");
			_getch();
		}
	}
}
//Для победы
int setWinCondition(int rows, int cols)
{
	int winCondition;
	int max_size = (cols > rows) ? cols : rows;
	system("cls");

	if (cols > 0 && rows > 0) {
		while (1) {
			printf("Введите количество символов для победы (от 3 до %d): ", max_size);
			scanf("%d", &winCondition);
			if (winCondition >= 3 && winCondition <= max_size)
			{
				printf("Введенное количество символов для победы: %d\n", winCondition);
				_getch();
				return winCondition;
			}
			else {
				printf("Неверное количество символов для победы, введите число от 3 до %d.\n", max_size);
				_getch();
				system("cls");
			}
		}
	}
	else {
		printf("Недостаточно входных данных\n");
		_getch();
		return 0;
	}
}

//обычное поле
int Pole1(int rows, int cols, char poleIsh[][21], char pole[][21])
{
	for (int i = 0; i < cols + 2; i++)
	{
		for (int j = 0; j < rows + 2; j++)
		{

			if (i == 1 && j == 1)
			{
				pole[i][j] = '.';
				poleIsh[i][j] = '*';
				printf("%c", poleIsh[i][j]);
			}

			else if (i == 0 || i == cols + 1)
			{
				pole[i][j] = '#';
				poleIsh[i][j] = pole[i][j];
				printf("%c", poleIsh[i][j]);
			}

			else
			{
				if (j == 0 || j == rows + 1) {
					pole[i][j] = '#';
					poleIsh[i][j] = pole[i][j];
					printf("%c", poleIsh[i][j]);
				}
				else
				{
					pole[i][j] = '.';
					poleIsh[i][j] = pole[i][j];
					printf("%c", poleIsh[i][j]);
				}
			}
		}
		printf("\n");
	}
}

//перемещение
int PoleCursor(int rows, int cols, int posY, int posX, char poleIsh[][21])
{
	for (int i = 0; i < cols + 2; i++)
	{
		for (int j = 0; j < rows + 2; j++)
		{
			if (i == posY && j == posX)
			{
				poleIsh[i][j] = '*';
				printf("%c", poleIsh[i][j]);
			}
			else
			{
				printf("%c", poleIsh[i][j]);
			}
		}
		printf("\n");
	}
}

//с символами 
int PoleTrue(int rows, int cols, char pole[][21])
{
	for (int i = 0; i < cols + 2; i++)
	{
		for (int j = 0; j < rows + 2; j++)
		{
			printf("%c", pole[i][j]);
		}
		printf("\n");
	}
}

//правила
int rules(int win_count)
{
	printf("Для победы: %d\n", win_count);
	printf("Для установки символов нажмите enter\n");
	printf("Для выхода нажмите q\n");
}

//чей ход
int whosTurn(int turn)
{
	if (turn == 1)
	{
		printf("\nХод крестиков\n");
	}
	if (turn == 0)
	{
		printf("\nХод ноликов\n");
	}
}

// проверка на победу
int Win(int rows, int cols, int win_count, char pole[][21], int* flag) {

	int dir[8][2] = { {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1},{1, 0}, {1, 1}, {0, 1} };

	for (int i = 1; i <= cols; i++)
	{
		for (int j = 1; j <= rows; j++)
		{
			if (pole[i][j] == '.')
				continue;
			for (int d = 0; d < 8; d++)
			{
				bool match = true;

				for (int q = 1; q < win_count; q++)
				{
					int newX = i + q * dir[d][0];
					int newY = j + q * dir[d][1];
					if (newX < 1 || newX > cols || newY < 1 || newY > rows || pole[i][j] != pole[newX][newY])
					{
						match = false;
						break;
					}
				}
				if (match) {
					*flag = 1;
					return;
				}
			}
		}
	}
}

// проверка на ничью
int Neutral(int rows, int cols, int win_count, char pole[][21], int* flag)
{
	int all[20][21];
	*flag = 1;

	for (int i = 1; i <= cols; i++)
	{
		for (int j = 1; j <= rows; j++)
		{
			int dir[8] = { 0 };
			int counts[8][2] = { 0 };
			int mainFlag = 1;
			for (int q = 1; q < win_count; q++)
			{
				if (pole[i][j] == '.')
				{
					if (pole[i][j + q] == 'X' || pole[i][j + q] == 'O' || pole[i][j + q] == '#')
					{
						if (pole[i][j + q] == 'X')
							counts[0][0]++;
						if (pole[i][j + q] == 'O')
							counts[0][1]++;
						if ((counts[0][0] > 0 && counts[0][1] > 0) || pole[i][j + q] == '#')
							dir[0] = 1;
					}
					if (pole[i + q][j + q] == 'X' || pole[i + q][j + q] == 'O' || pole[i + q][j + q] == '#')
					{
						if (pole[i + q][j + q] == 'X')
							counts[1][0]++;
						if (pole[i + q][j + q] == 'O')
							counts[1][1]++;
						if ((counts[1][0] > 0 && counts[1][1] > 0) || pole[i + q][j + q] == '#')
							dir[1] = 1;
					}
					if (pole[i + q][j] == 'X' || pole[i + q][j] == 'O' || pole[i + q][j] == '#')
					{
						if (pole[i + q][j] == 'X')
							counts[2][0]++;
						if (pole[i + q][j] == 'O')
							counts[2][1];
						if ((counts[2][0] > 0 && counts[2][1] > 0) || pole[i + q][j] == '#')
							dir[2] = 1;
					}
					if (pole[i + q][j - q] == 'X' || pole[i + q][j - q] == 'O' || pole[i + q][j - q] == '#')
					{
						if (pole[i + q][j - q] == 'X')
							counts[3][0];
						if (pole[i + q][j - q] == 'O')
							counts[3][1];
						if ((counts[3][0] > 0 && counts[3][1] > 0) || pole[i + q][j - q] == '#')
							dir[3] = 1;
					}
					if (pole[i][j - q] == 'X' || pole[i][j - q] == 'O' || pole[i][j - q] == '#')
					{
						if (pole[i][j - q] == 'X')
							counts[4][0]++;
						if (pole[i][j - q] == 'O')
							counts[4][1]++;
						if ((counts[4][0] > 0 && counts[4][1] > 0) || pole[i][j - q] == '#')
							dir[4] = 1;
					}
					if (pole[i - q][j - q] == 'X' || pole[i - q][j - q] == 'O' || pole[i - q][j - q] == '#')
					{
						if (pole[i - q][j - q] == 'X')
							counts[5][0]++;
						if (pole[i - q][j - q] == 'O')
							counts[5][1]++;
						if ((counts[5][0] > 0 && counts[5][1] > 0) || pole[i - q][j - q] == '#')
							dir[5] = 1;
					}
					if (pole[i - q][j] == 'X' || pole[i - q][j] == 'O' || pole[i - q][j] == '#')
					{
						if (pole[i - q][j] == 'X')
							counts[6][0]++;
						if (pole[i - q][j] == 'O')
							counts[6][1]++;
						if ((counts[6][0] > 0 && counts[6][1] > 0) || pole[i - q][j] == '#')
							dir[6] = 1;
					}
					if (pole[i - q][j + q] == 'X' || pole[i - q][j + q] == 'O' || pole[i - q][j + q] == '#')
					{
						if (pole[i - q][j + q] == 'X')
							counts[7][0]++;
						if (pole[i - q][j + q] == 'O')
							counts[7][1]++;
						if ((counts[7][0] > 0 && counts[7][1] > 0) || pole[i - q][j + q] == '#')
							dir[7] = 1;
					}
				}

				if (pole[i][j] != '.' && pole[i][j] != pole[i][j + q] && pole[i][j + q] != '.')
					dir[0] = 1;
				if (pole[i][j] != '.' && pole[i][j] != pole[i + q][j + q] && pole[i + q][j + q] != '.')
					dir[1] = 1;
				if (pole[i][j] != '.' && pole[i][j] != pole[i + q][j] && pole[i + q][j] != '.')
					dir[2] = 1;
				if (pole[i][j] != '.' && pole[i][j] != pole[i + q][j - q] && pole[i + q][j - q] != '.')
					dir[3] = 1;
				if (pole[i][j] != '.' && pole[i][j] != pole[i][j - q] && pole[i][j - q] != '.')
					dir[4] = 1;
				if (pole[i][j] != '.' && pole[i][j] != pole[i - q][j - q] && pole[i - q][j - q] != '.')
					dir[5] = 1;
				if (pole[i][j] != '.' && pole[i][j] != pole[i - q][j] && pole[i - q][j] != '.')
					dir[6] = 1;
				if (pole[i][j] != '.' && pole[i][j] != pole[i - q][j + q] && pole[i - q][j + q] != '.')
					dir[7] = 1;
			}
			mainFlag = (dir[0] * dir[1] * dir[2] * dir[3] * dir[4] * dir[5] * dir[6] * dir[7]);
			all[i][j] = mainFlag;
		}
	}
	for (int i = 1; i <= cols; i++)
	{
		for (int j = 1; j <= rows; j++)
		{
			if (all[i][j] == 0)
			{
				*flag = 0;
			}
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");

	char pole[23][21];
	char pole_symb[23][21];
	int posY = 1;
	int posX = 1;

	int choice = 0;
	int length = 0;
	int height = 0;
	int toWin = 0;

	while (1)
	{
		bool first = true;
		bool game = true;
		bool end = true;

		Menu(choice, length, height, toWin);

		int arr = _getch();

		if (arr >= '1' && arr <= '5')
		{
			choice = arr - '1';
		}
		else if (arr == 224)
		{
			switch (_getch())
			{
			case 72:
				choice = (choice > 0) ? choice - 1 : 4;
				break;
			case 80:
				choice = (choice < 4) ? choice + 1 : 0;
				break;
			}
		}

		else if (arr == '\r')
		{
			switch (choice)
			{
			case 0:
				length = setLenght();
				break;
			case 1:
				height = setHeight();
				break;
			case 2:
				toWin = setWinCondition(length, height);
				break;
			case 3:
				if (length != 0 && height != 0 && toWin != 0)
				{
					if (toWin <= length || toWin <= height)
					{
						system("cls");
						int turn = 1;
						posY = 1;
						posX = 1;
						int flagWin = 0;
						int flagDraw = 0;

						Pole1(length, height, pole, pole_symb);
						rules(toWin);
						whosTurn(turn);

						while (game)
						{
							int move = _getch();
							switch (move)
							{
							case 224:
								move = _getch();
								switch (move)
								{
								case 72: //верх
									pole[posY][posX] = pole_symb[posY][posX];
									if (posY != 1)
									{
										posY -= 1;
									}
									else
									{
										posY = height;
									}
									system("cls");
									PoleCursor(length, height, posY, posX, pole);
									rules(toWin);
									whosTurn(turn);
									break;
								case 80: //низ
									pole[posY][posX] = pole_symb[posY][posX];
									if (posY != height)
									{
										posY += 1;
									}
									else
									{
										posY = 1;
									}
									system("cls");
									PoleCursor(length, height, posY, posX, pole);
									rules(toWin);
									whosTurn(turn);
									break;
								case 75: //лево
									pole[posY][posX] = pole_symb[posY][posX];
									if (posX != 1)
									{
										posX -= 1;
									}
									else
									{
										posX = length;
									}
									system("cls");
									PoleCursor(length, height, posY, posX, pole);
									rules(toWin);
									whosTurn(turn);
									break;
								case 77: //право
									pole[posY][posX] = pole_symb[posY][posX];
									if (posX != length)
									{
										posX += 1;
									}
									else
									{
										posX = 1;
									}
									system("cls");
									PoleCursor(length, height, posY, posX, pole);
									rules(toWin);
									whosTurn(turn);
									break;
								}
								break;
							case 13:
								if (turn == 1)
								{
									if (pole_symb[posY][posX] == '.')
									{
										pole_symb[posY][posX] = 'X';
										turn = 0;
									}

								}
								if (turn == 0)
								{
									if (pole_symb[posY][posX] == '.')
									{
										pole_symb[posY][posX] = 'O';
										turn = 1;
									}

								}
								Win(length, height, toWin, pole_symb, &flagWin);
								Neutral(length, height, toWin, pole_symb, &flagDraw);

								if (flagWin == 1 && turn == 0)
								{
									system("cls");
									PoleTrue(length, height, pole_symb);
									rules(toWin);
									printf("Победа крестиков (для выхода нажмите q)");

									while (end)
									{
										int out1 = _getch();
										if (out1 == 'q')
										{
											Menu(choice, height, length, toWin);
											end = false;
											game = false;
										}
									}
								}
								else if (flagWin == 1 && turn == 1)
								{
									system("cls");
									PoleTrue(length, height, pole_symb);
									rules(toWin);
									printf("Победа ноликов (для выхода нажмите q)");

									while (end)
									{
										int out2 = _getch();
										if (out2 == 'q')
										{
											Menu(choice, height, length, toWin);
											end = false;
											game = false;
										}
									}
								}

								else if (flagDraw == 1)
								{
									system("cls");
									PoleTrue(length, height, pole_symb);
									rules(toWin);
									printf("Ничья (для выхода нажмите q)");

									while (end)
									{
										int out3 = _getch();
										if (out3 == 'q') {
											Menu(choice, height, length, toWin);
											end = false;
											game = false;
										}
									}
								}
								else
								{
									system("cls");
									PoleTrue(length, height, pole_symb);
									rules(toWin);
									whosTurn(turn);
								}
								break;
							case 'q':
								game = false;
								Menu(choice, height, length, toWin);
								break;
							}
						}
					}
				}
				else
				{
					printf("Недостаточно данных");
					_getch();
				}
				break;
			case 4:
				exit(0);
				break;
			}
		}
	}
	return 0;
}