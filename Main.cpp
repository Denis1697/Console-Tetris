#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "Consolelib.h"
using namespace std;

//перечисления для удобопонимания
enum Coordinates { X = 1, Y = 2 };
enum MoveDirection { Down = 0, Left = 1, Right = 2 };
enum Rotation { horizontal = 0, vertical = -1, R1 = 1, R2 = 2, R3 = 3, R4 = 4 };
enum Figures { Quad = 0, Line = 1, El = 2, Inel = 3, Lght = 4, Bght = 5, Dck = 6 };

struct Player
{
	char Name[50];
	int Score;
};

//prototypes
int Menu();
void Exit();
int GoodBye();
void ScoresOut();

//graphics
void DrawMainMenu();
void DrawGoodBye();
void DrawRectangle(int x1, int y1, int x2, int y2);
void RedrawField();
void CLRSCR();
void DrawConfigure();
void DrawNFWindow();
void DrawNextFigure(int nextFigure);
void DrawInformation();
void DrawPause();
void DeletePause();
void DrawScores(int len);

//commonfunctions
void Set(int block);
void FieldOut();
void IncreaseCoordinates(int coordinates, int increase);
bool IsOnBottom();
bool IsOutOfBorders(int direction);
int IsCrossesFigureWhileMotion(int direction);
int Motion(int currentFigure);
int Move(MoveDirection direction);
void Set(int block);
void Rotate(int currentFigure);
void FindFilledLine();
void CellsDown(int i);
int Game();
int Menu();
int Pause();
void ScoreOut();
void EmptyField();
int Configures();
void CopyFigureToBuffer(int figure);
void ClearBuffer();
void FastDrop();
void EnterNickAndScore(int Score);
//LINE
int AddLine();
bool LineIsOutOfBordersWhileRotate(int rotation);
bool LineCrossesFigureWhileRotate(int rotation);
void ChangeLineCoordsTo(int rotation);
//QUAD
int AddQuad();
//EL
int AddEL();
bool ELIsOutOfBordersWhileRotate(int rotation);
bool ELCrossesFigureWhileRotate(int rotation);
void ChangeELCoordsTo(int rotation);
//INEL
int AddINEL();
bool INELIsOutOfBordersWhileRotate(int rotation);
bool INELCrossesFigureWhileRotate(int rotation);
void ChangeINELCoordsTo(int nextRotation);
//LGHT
int AddLGHT();
bool LGHTIsOutOfBordersWhileRotate(int rotation);
bool LGHTCrossesFigureWhileRotate(int rotation);
void ChangeLGHTCoordsTo(int rotation);
//BGHT
int AddBGHT();
bool BGHTIsOutOfBordersWhileRotate(int rotation);
bool BGHTCrossesFigureWhileRotate(int rotation);
void ChangeBGHTCoordsTo(int rotation);
//DCK
int AddDCK();
bool DCKIsOutOfBordersWhileRotate(int rotation);
bool DCKCrossesFigureWhileRotate(int rotation);
void ChangeDCKCoordsTo(int nextRotation);

bool GameOver = false;
static int xi[4];
static int yi[4];
static int score = 0;
int dx, dy;
int currentRotation;
const int x = 16; 
const int y = 20; 
static int speed = 15;
int ShowNextFigure = 1;

int Field[y][x] = { 0 };
int SQRT[2][2] = { {1, 1},
                   {1, 1} };
int LINE[4][3] = { {1, 0, 0},
                   {1, 0, 0},
	               {1, 0, 0},
                   {1, 0, 0} };
int EL[3][3] = { {1, 1, 1},
				 {1, 0, 0},
				 {0, 0, 0} };
int INEL[3][3] = { {1, 1, 1},
                  {0, 0, 1},
                  {0, 0, 0} };
int LGHT[3][3] = { {1, 1, 0},
                   {0, 1, 1},
                   {0, 0, 0} };
int BGHT[3][3] = { {0, 1, 1},
				   {1, 1, 0},
				   {0, 0, 0}, };
int DCK[3][3] = { {1, 1, 1},
                  {0, 1, 0},
                  {0, 0, 0} };
int BUFFER[4][4] = { 0 };

void main()
{
	srand(unsigned(time(NULL)));
	ShowCursor(false);

	while (true)
	{
		DrawMainMenu();
		switch (Menu())
		{
		case 0:
			if(!Game());
			{
				CLRSCR();
				EmptyField();
				GameOver = false;
			}
			break;
		case 1:
			Configures();
			break;
		case 2:
			DrawInformation();
			break;
		case 3:
			ScoresOut();
			break;
		case 4:
			Exit();
		}
	}
	
}

int Configures()
{
	DrawConfigure();

	const int Enter = 13;
	int items = 2;
	int currentMenuItem = 0;
	int chosenItem;

	do
	{
		

		switch (ShowNextFigure)
		{
		case 1:
			WriteStr(66, 15, "ON ");
			ChangeTextAttr(66, 15, White, Cyan, 3);
			break;
		case 0:
			WriteStr(66, 15, "OFF");
			ChangeTextAttr(66, 15, White, Cyan, 3);
			break;
		}

		ChangeTextAttr(58, 16 + currentMenuItem, Black, Yellow, 4);

		chosenItem = _getch();

		if (chosenItem == Enter)
		{
			switch (currentMenuItem)
			{
			case 0:
				ShowNextFigure = 1;
				break;
			case 1:
				ShowNextFigure = 0;
				break;
			case 2:
				CLRSCR();
				return 0;
			}
		}

		if (chosenItem == 0 || chosenItem == 0xE0)
		{
			chosenItem = _getch();

			ChangeTextAttr(58, 16 + currentMenuItem, White, Cyan, 4);
			switch (chosenItem)
			{
			case 71:		// Home
				currentMenuItem = 0;
				break;
			case 72:		//Up
				if (currentMenuItem == 0)
					currentMenuItem = items;
				else
					currentMenuItem -= 1;
				break;
			case 79:		// End
				currentMenuItem = items;
				break;
			case 80:		//Down
				if (currentMenuItem == items)
					currentMenuItem = 0;
				else
					currentMenuItem += 1;
				break;
			}
		}

	} while (true);
	
}
int Menu()
{
	DrawMainMenu();
	const int Enter = 13;
	int items = 4;
	int currentMenuItem = 0;
	int chosenItem;

	do
	{
		ChangeTextAttr(52, 14 + currentMenuItem, Black, Yellow, 12);

		chosenItem = _getch();

		if (chosenItem == Enter)
		{
			switch (currentMenuItem)
			{
			case 0:
				return 0;
			case 1:
				return 1;
			case 2:
				return 2;
			case 3:
				return 3;
			case 4:
				return 4;
			}
		}

		if (chosenItem == 0 || chosenItem == 0xE0)
		{
			chosenItem = _getch();

			ChangeTextAttr(52, 14 + currentMenuItem, White, Cyan, 12);
			switch (chosenItem)
			{
			case 71:		// Home
				currentMenuItem = 0;
				break;
			case 72:		//Up
				if (currentMenuItem == 0)
					currentMenuItem = items;
				else
					currentMenuItem -= 1;
				break;
			case 79:		// End
				currentMenuItem = items;
				break;
			case 80:		//Down
				if (currentMenuItem == items)
					currentMenuItem = 0;
				else
					currentMenuItem += 1;
				break;
			}
		}

	} while (true);
}
int Game()
{
	CLRSCR();

	int currentFigure;
	int nextFigure = rand() % 7;

	do
	{
		currentFigure = nextFigure;
		nextFigure = rand() % 7;

		switch (ShowNextFigure)
		{
		case 1:
			DrawNFWindow();
			DrawNextFigure(nextFigure);
			break;
		case 0:
			break;
		}	

		switch (currentFigure)
		{
		case Quad:
			AddQuad();
			break;
		case Line:
			AddLine();
			break;
		case El:
			AddEL();
			break;
		case Inel:
			AddINEL();
			break;
		case Lght:
			AddLGHT();
			break;
		case Bght:
			AddBGHT();
			break;
		case Dck:
			AddDCK();
			break;
		}
		
		switch (Motion(currentFigure))
		{
		case 1:
			FindFilledLine();
			break;
		case 2:
			EmptyField();
			CLRSCR();
			score = 0;
			continue;
		case 3:
			EmptyField();
			CLRSCR();
			score = 0;
			return 0;
		}
	} while (!GameOver);

	EnterNickAndScore(score);

	return 0;
}

void EnterNickAndScore(int Score)
{
	char nick[50];

	WriteStr(30, 12, "Enter your nick:");
	
	GotoXY(47, 12);
	
	cin >> nick;

	FILE *sc = fopen("Scores.txt", "ab");

	int len = (strlen(nick) + 1);

	fwrite(&len, sizeof(len), 1, sc);
	fwrite(nick, sizeof(char), len, sc);

	len = Score; 

	fwrite(&len, sizeof(len), 1, sc); 

	fclose(sc);
}
void Exit()
{
	CLRSCR();
	if (GoodBye())
	{
		CLRSCR();
		GotoXY(0, 0);
		exit(0);
	}
	else
	{
		CLRSCR();
		return;
	}
	
}
void Status(char key)
{
	switch (key)
	{
	case 13:
		//FastDrop()
		return;
	case 27:
		//Quit()?
		break;
	case 32:
		//Pause()
		break;
	}
	
}
int GoodBye()
{
	DrawGoodBye();
	const int Enter = 13;
	int items = 1;
	int currentMenuItem = 0;
	int chosenItem;

	do
	{
		ChangeTextAttr(52, 15 + currentMenuItem, Black, Yellow, 13);

		chosenItem = _getch();

		if (chosenItem == Enter)
		{
			switch (currentMenuItem)
			{
			case 0:
				return 1;
			case 1:
				return 0;
			}
		}

		if (chosenItem == 0 || chosenItem == 0xE0)
		{
			chosenItem = _getch();

			ChangeTextAttr(52, 15 + currentMenuItem, White, Cyan, 13);
			switch (chosenItem)
			{
			case 71:		// Home
				currentMenuItem = 0;
				break;
			case 72:		//Up
				if (currentMenuItem == 0)
					currentMenuItem = items;
				else
					currentMenuItem -= 1;
				break;
			case 79:		// End
				currentMenuItem = items;
				break;
			case 80:		//Down
				if (currentMenuItem == items)
					currentMenuItem = 0;
				else
					currentMenuItem += 1;
				break;
			}
		}

	} while (true);
}
int Pause()
{
	DrawPause();

	const int Enter = 13;
	int items = 2;
	int currentMenuItem = 0;
	int chosenItem;

	do
	{
		ChangeTextAttr(32, 14 + currentMenuItem, Black, Yellow, 12);

		chosenItem = _getch();

		if (chosenItem == Enter)
		{
			switch (currentMenuItem)
			{
			case 0:
				DeletePause();
				return 0;
			case 1:
				CLRSCR();
				return 1;
			case 2:
				CLRSCR();
				return 2;
			}
		}

		if (chosenItem == 0 || chosenItem == 0xE0)
		{
			chosenItem = _getch();

			ChangeTextAttr(32, 14 + currentMenuItem, White, Black, 12);
			switch (chosenItem)
			{
			case 71:		// Home
				currentMenuItem = 0;
				break;
			case 72:		//Up
				if (currentMenuItem == 0)
					currentMenuItem = items;
				else
					currentMenuItem -= 1;
				break;
			case 79:		// End
				currentMenuItem = items;
				break;
			case 80:		//Down
				if (currentMenuItem == items)
					currentMenuItem = 0;
				else
					currentMenuItem += 1;
				break;
			}
		}

	} while (true);
}
void ScoresOut()
{
	int size = 500;

	Player *playa = new Player[size];

	memset(playa, 0, sizeof(playa));

	FILE *f = fopen("Scores.txt", "rb");

	int number = 0;
	int len = 0;
	char tmp[12];
	
	while (!feof(f)) 
	{
		fread(&len, sizeof(len), 1, f);
		fread(&tmp, sizeof(char), len, f);

		strcpy(playa[number].Name, tmp);

		fread(&len, sizeof(len), 1, f);

		playa[number].Score = len;

		number++;
	}

	number -= 1;

	for (int k = number - 1; k >= 0; k--)
	{
		for (int j = 0; j < k; j++)
		{
			if (playa[j].Score < playa[j + 1].Score)
			{
				Player tmp = playa[j];
				playa[j] = playa[j + 1];
				playa[j + 1] = tmp;
			}
		}
	}

	DrawScores(number);

	for (int j = 0; j < number; j++)
	{
		GotoXY(52, 14 + j);
		printf("%d. %s - %d", j + 1, playa[j].Name, playa[j].Score);
		ChangeTextAttr(52, 14 + j, White, Cyan, 18);
	}

	while (!_kbhit())
		if (_getch() == 13)
		{
			CLRSCR();
			return;
		}			
		else
			continue;
	
}
//graphics functions
void DrawMainMenu()
{
	WriteStr(52, 14, "Start game");
	WriteStr(52, 15, "Configures");
	WriteStr(52, 16, "Information");
	WriteStr(52, 17, "Scores");
	WriteStr(52, 18, "Quit game");

	WriteChar(49, 13, 201);
	WriteChars(50, 13, 205, 15);
	WriteChar(65, 13, 187);

	for (int i = 0; i < 5; i++)
	{
		WriteChar(49, 14 + i, 186);
	}

	WriteChar(49, 19, 200);
	WriteChars(50, 19, 205, 15);
	WriteChar(65, 19, 188);

	for (int i = 0; i < 5; i++)
	{
		WriteChar(65, 14 + i, 186);
	}

	DrawRectangle(49, 13, 66, 19);
}
void DrawGoodBye()
{
	CLRSCR();

	WriteStr(52, 14, "Are you sure?");
	WriteStr(57, 15, "Yes");
	WriteStr(57, 16, "No");

	WriteChar(51, 13, 201);
	WriteChars(52, 13, 205, 13);
	WriteChar(65, 13, 187);

	for (int i = 0; i < 3; i++)
	{
		WriteChar(51, 14 + i, 186);
	}

	WriteChar(51, 17, 200);
	WriteChars(52, 17, 205, 13);
	WriteChar(65, 17, 188);

	for (int i = 0; i < 3; i++)
	{
		WriteChar(65, 14 + i, 186);
	}

	DrawRectangle(51, 13, 66, 17);
	system("pause");
}
void DrawConfigure()
{
	CLRSCR();

	WriteStr(51, 14, "Show next figure?");
	WriteStr(50, 15, "Current status: ");
	
	WriteStr(58, 16, "Yes");
	WriteStr(58, 17, "No");
	WriteStr(58, 18, "Back");

	WriteChar(49, 13, 201);
	WriteChars(50, 13, 205, 19);
	WriteChar(69, 13, 187);

	for (int i = 0; i < 5; i++)
	{
		WriteChar(49, 14 + i, 186);
	}

	WriteChar(49, 19, 200);
	WriteChars(50, 19, 205, 19);
	WriteChar(69, 19, 188);

	for (int i = 0; i < 5; i++)
	{
		WriteChar(69, 14 + i, 186);
	}

	DrawRectangle(49, 13, 70, 19);
}
void DrawNFWindow()
{

	WriteChar(30, 2, 201);
	WriteChars(31, 2, 205, 10);
	WriteChar(41, 2, 187);

	for (int i = 0; i < 4; i++)
	{
		WriteChar(30, 3 + i, 186);
	}

	WriteChar(30, 7, 200);
	WriteChars(31, 7, 205, 10);
	WriteChar(41, 7, 188);

	for (int i = 0; i < 4; i++)
	{
		WriteChar(41, 3 + i, 186);
	}
}
void DrawNextFigure(int nextFigure)
{
	ClearBuffer();

	CopyFigureToBuffer(nextFigure);
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (BUFFER[i][j] == 0)
			{
				ChangeTextAttr(35 + j, 3 + i, Black, Black, 1);
				continue;
			}				
			ChangeTextAttr(35 + j, 3 + i, Blue, Blue, 1);
		}
	}

	

}
void DrawInformation()
{
	CLRSCR();

	WriteStr(51, 14, "The game of Tetris");
	WriteStr(51, 15, "Done by Baghin Denis");
	WriteStr(53, 16, "^ - rotate");
	WriteStr(53, 17, "< - move left");
	WriteStr(53, 18, "> - move right");
	WriteStr(52, 19, "\\/ - move down");
	WriteStr(52, 20, "Space - fast drop");
	WriteStr(59, 22, "Back");

	WriteChar(49, 13, 201);
	WriteChars(50, 13, 205, 21);
	WriteChar(71, 13, 187);

	for (int i = 0; i < 9; i++)
	{
		WriteChar(49, 14 + i, 186);
	}

	WriteChar(49, 23, 200);
	WriteChars(50, 23, 205, 21);
	WriteChar(71, 23, 188);

	for (int i = 0; i < 9; i++)
	{
		WriteChar(71, 14 + i, 186);
	}

	DrawRectangle(49, 13, 72, 23);
	ChangeTextAttr(59, 22, Black, Yellow, 4);

	cout << flush;

	while (!_kbhit())
		continue;
	if (_getch() == 13)
		CLRSCR();
}
void DrawPause()
{
	WriteStr(32, 14, "Resume");
	WriteStr(32, 15, "Reset");
	WriteStr(32, 16, "Back to menu");

	WriteChar(30, 13, 201);
	WriteChars(31, 13, 205, 15);
	WriteChar(46, 13, 187);

	for (int i = 0; i < 3; i++)
	{
		WriteChar(30, 14 + i, 186);
	}

	WriteChar(30, 17, 200);
	WriteChars(31, 17, 205, 15);
	WriteChar(46, 17, 188);

	for (int i = 0; i < 3; i++)
	{
		WriteChar(46, 14 + i, 186);
	}
}
void DeletePause()
{
	for (int i = 0; i < 5; i++)
	{
		ChangeTextAttr(30, 13 + i, Black, Black, 23);
	}
}
void DrawScores(int len)
{
	CLRSCR();
	
	WriteChar(49, 13, 201);
	WriteChars(50, 13, 205, 21);
	WriteChar(71, 13, 187);

	for (int i = 0; i < len + 1; i++)
	{
		WriteChar(49, 14 + i, 186);
	}

	WriteChar(49, 15 + len, 200);
	WriteChars(50, 15 + len, 205, 21);
	WriteChar(71, 15 + len, 188);

	for (int i = 0; i < len + 1; i++)
	{
		WriteChar(71, 14 + i, 186);
	}

	DrawRectangle(49, 13, 72, 15 + len);

	WriteStr(59, 14 + len, "Back");
	ChangeTextAttr(59, 14 + len, Black, Yellow, 4);
}
void DrawRectangle(int x1, int y1, int x2, int y2)
{
	for (; y1 <= y2; y1++)
	{
		ChangeTextAttr(x1, y1, White, Cyan, x2 - x1);
	}
}
void CLRSCR()
{
	system("cls");
}
void RedrawField()
{
	ChangeTextAttr(9, 1, Green, Green, x + 1);
	ChangeTextAttr(9, y + 2, Green, Green, x + 1);

	for (int i = 1; i <= y + 1; i++)
		ChangeTextAttr(9, i, Green, Green, 1);

	for (int i = 1; i <= y + 2; i++)
		ChangeTextAttr(x + 10, i, Green, Green, 1);

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (Field[i][j] == 3)
				ChangeTextAttr(10 + j, i + 2, Blue, Blue, 1);

			else if (Field[i][j] == 1)
				ChangeTextAttr(10 + j, i + 2, Green, Cyan, 1);
			else if (Field[i][j] == 0)
				ChangeTextAttr(10 + j, i + 2, Black, Black, 1);
		}
	}
}

//common functions
void Set(int block)
{
	for (int i = 0; i < 4; i++)
	{
		Field[yi[i]][xi[i]] = block;
	}
}
void IncreaseCoordinates(int coordinates, int increase)
{
	switch (coordinates)
	{
	case X:
		for (int i = 0; i < 4; i++)
			xi[i] += increase;
		break;
	case Y:
		for (int i = 0; i < 4; i++)
			yi[i] += increase;
		break;
	}
}
bool IsOnBottom()
{
	for (int i = 0; i < 4; i++)
		if (yi[i] + 1 >= y)
			return true;
	return false;
}
bool IsOutOfBorders(int direction)
{
	switch (direction)
	{
	case -1:
		for (int i = 0; i < 4; i++)
			if (xi[i] - 1 == -1)
				return true;
		return false;
	case 1:
		for (int i = 0; i < 4; i++)
			if (xi[i] + 1 == x)
				return true;
		return false;
	case 2:
		for (int i = 0; i < 4; i++)
			if (yi[i] + 1 == y)
				return true;
		return false;
	}
}
int IsCrossesFigureWhileMotion(int direction)
{
	switch (direction)
	{
	case -1:
		for (int i = 0; i < 4; i++)
			if (Field[yi[i]][xi[i] - 1] == 3)
				return -1;
		return 0;
	case 1:
		for (int i = 0; i < 4; i++)
			if (Field[yi[i]][xi[i] + 1] == 3)
				return 1;
		return 0;
	case 2:
		for (int i = 0; i < 4; i++)
			if (Field[yi[i] + 1][xi[i]] == 3)
				return 2;
		return 0;
	}
}
int Move(MoveDirection direction)
{
	switch (direction)
	{
	case Down:
		if (IsOnBottom() || IsCrossesFigureWhileMotion(2))
		{
			Set(3);
			return 3;
		}
		else
		{
			Set(0);
			IncreaseCoordinates(Y, +1);
			Set(1);
		}
		break;
	case Left:
		if (IsCrossesFigureWhileMotion(-1) || IsOutOfBorders(-1))
			return 0;
		else
		{
			Set(0);
			IncreaseCoordinates(X, -1);
			Set(1);
		}
		break;
	case Right:
		if (IsCrossesFigureWhileMotion(1) || IsOutOfBorders(1))
			return 0;
		else
		{
			Set(0);
			IncreaseCoordinates(X, +1);
			Set(1);
		}
		break;
	}
}
int Motion(int currentFigure)
{
	int pause;
	cout << flush;

	char key;

	do
	{
		int time = 0;

		while (time <= speed)
		{
			
			if (score > 100)
				if (score % 100 == 0)
					speed -= 1;

			ScoreOut();
			RedrawField();
			Sleep(1);

			if (_kbhit())
			{
				key = _getch();
				switch (key) //72 ^		75 <	 77 >	  80 \/		32 - space		27 - esc	13 - enter
				{
				case 32:
					FastDrop();
					continue;
				case 27:
					if ((pause = Pause()) == 1)
						return 2;
					else if (pause == 2)
						return 3;
					else if (pause == 0)
						continue;
					break;
				case 72:
					Rotate(currentFigure);
					break;
				case 75:
					Move(Left);
					break;
				case 77:
					Move(Right);
					break;
				case 80:
					if (Move(Down) == 3)
						return 1;
					break;
				default:
					cout << flush;
					break;
				}
			}
			time++;
		}
		time = 0;
		if (Move(Down) == 3)
			return 1;
	} while (dy < y);
}
void Rotate(int currentFigure)
{
	switch (currentRotation)
	{
		case horizontal:
		{
			switch (currentFigure)
			{
			case Line:
			{
				if (LineIsOutOfBordersWhileRotate(currentRotation) || LineCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;

				Set(0);
				ChangeLineCoordsTo(vertical);
				Set(1);
				currentRotation = vertical;
			}
			break;
			case Lght:
			{
				if (LGHTIsOutOfBordersWhileRotate(currentRotation) || LGHTCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeLGHTCoordsTo(vertical);
				Set(1);
				currentRotation = vertical;
			}
			break;
			case Bght:
			{
				if (BGHTIsOutOfBordersWhileRotate(currentRotation) || BGHTCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeBGHTCoordsTo(vertical);
				Set(1);
				currentRotation = vertical;
			}
			break;
			}
		}
		break;
		case vertical:
		{
			switch (currentFigure)
			{
			case Line:
			{
				if (LineIsOutOfBordersWhileRotate(currentRotation) || LineCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;

				Set(0);
				ChangeLineCoordsTo(horizontal);
				Set(1);
				currentRotation = horizontal;
			}
			break;
			case Lght:
			{
				if (LGHTIsOutOfBordersWhileRotate(currentRotation) || LGHTCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeLGHTCoordsTo(horizontal);
				Set(1);
				currentRotation = horizontal;
			}
			break;
			case Bght:
			{
				if (BGHTIsOutOfBordersWhileRotate(currentRotation) || BGHTCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeBGHTCoordsTo(horizontal);
				Set(1);
				currentRotation = horizontal;
			}
			break;
			}
		}
		break;
		case R1:
		{
			switch (currentFigure)
			{
			case El:
			{
				if (ELIsOutOfBordersWhileRotate(currentRotation) || ELCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeELCoordsTo(R2);
				Set(1);
				currentRotation = R2;
				break;
			}
			case Inel:
			{
				if (INELIsOutOfBordersWhileRotate(currentRotation) || INELCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeINELCoordsTo(R2);
				Set(1);
				currentRotation = R2;
			}
			break;
			case Dck:
			{
				if (DCKIsOutOfBordersWhileRotate(currentRotation) || DCKCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeDCKCoordsTo(R2);
				Set(1);
				currentRotation = R2;
			}
			break;
			}
		}
		break;
		case R2:
		{
			switch (currentFigure)
			{
			case El:
			{
				if (ELIsOutOfBordersWhileRotate(currentRotation) || ELCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeELCoordsTo(R3);
				Set(1);
				currentRotation = R3;
			}
			break;
			case Inel:
			{
				if (INELIsOutOfBordersWhileRotate(currentRotation) || INELCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeINELCoordsTo(R3);
				Set(1);
				currentRotation = R3;
			}
			break;
			case Dck:
			{
				if (DCKIsOutOfBordersWhileRotate(currentRotation) || DCKCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeDCKCoordsTo(R3);
				Set(1);
				currentRotation = R3;
				
			}
			break;
			}
		}
		break;
		case R3:
		{
			switch (currentFigure)
			{
			case El:
			{
				if (ELIsOutOfBordersWhileRotate(currentRotation) || ELCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeELCoordsTo(R4);
				Set(1);
				currentRotation = R4;
				break;
			}
			case Inel:
			{
				if (INELIsOutOfBordersWhileRotate(currentRotation) || INELCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeINELCoordsTo(R4);
				Set(1);
				currentRotation = R4;
				break;
			}
			case Dck:
			{
				if (DCKIsOutOfBordersWhileRotate(currentRotation) || DCKCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeDCKCoordsTo(R4);
				Set(1);
				currentRotation = R4;
			}
			break;
			}
		}
		break;
		case R4:
		{
			switch (currentFigure)
			{
			case El:
			{
				if (ELIsOutOfBordersWhileRotate(currentRotation) || ELCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeELCoordsTo(R1);
				Set(1);
				currentRotation = R1;
				break;
			}
			case Inel:
			{
				if (INELIsOutOfBordersWhileRotate(currentRotation) || INELCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeINELCoordsTo(R1);
				Set(1);
				currentRotation = R1;
				break;
			}
			case Dck:
			{
				if (DCKIsOutOfBordersWhileRotate(currentRotation) || DCKCrossesFigureWhileRotate(currentRotation) || IsOnBottom())
					return;
				Set(0);
				ChangeDCKCoordsTo(R1);
				Set(1);
				currentRotation = R1;
			}
			break;
			}
		}
		break;
	}
}
void FieldOut()
{

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			GotoXY(10 + j, 2 + i);
			cout << Field[i][j];
		}
	}
}
void FindFilledLine()
{
	bool Was0 = false;

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (Field[i][j] == 0)
				Was0 = true;
		}
		if (!Was0)
			CellsDown(i);
		Was0 = false;
	}
}
void CellsDown(int Y)
{
	for (int j = x - 1; j >= 0; j--)
			Field[Y][j] = 0;

	for (int k = Y; k > 0; k--)
	{
		for (int z = 0; z < x; z++)
		{
			if (Field[k][z] == 0)
			{
				if (Field[k - 1][z] == 3)
				{
					Field[k - 1][z] = 0;
					Field[k][z] = 3;
				}
			}
		}
	}

	score += 10;

}
void ScoreOut()
{
	GotoXY(32, 9);
	cout << "Score: " << score;
}
void EmptyField()
{
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			Field[i][j] = 0;
}
void CopyFigureToBuffer(int figure)
{
	switch (figure)
	{
	case 0:
	{
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				BUFFER[i][j] = SQRT[i][j];
	}		
	break;
	case 1:
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
				BUFFER[i][j] = LINE[i][j];
	}
	break;
	case 2:
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				BUFFER[i][j] = EL[i][j];
	}
	break;
	case 3:
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				BUFFER[i][j] = INEL[i][j];
	}
	break;
	case 4:
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				BUFFER[i][j] = LGHT[i][j];
	}
	break;
	case 5:
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				BUFFER[i][j] = BGHT[i][j];
	}		
	break;
	case 6:
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				BUFFER[i][j] = DCK[i][j];
	}
	break;
	}

}
void ClearBuffer()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			BUFFER[i][j] = 0;
}
void FastDrop()
{
	while (true)
	{
		Move(Down);
		RedrawField();
		if (IsOnBottom() || IsCrossesFigureWhileMotion(2))		
			return;
	}
	
}

//LINE
int AddLine()
{
	int num = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Field[i][j + 5] == 3)
			{
				GameOver = true;
				return 0;
			}

			if (LINE[i][j] == 0)
				continue;
			else
			{
				Field[i][j + 5] = LINE[i][j];
				xi[num] = j + 5;
				yi[num] = i;
				num++;				
			}

		}
	}
	currentRotation = vertical;
	return 1;
}
bool LineIsOutOfBordersWhileRotate(int rotation)
{
	switch (rotation)
	{
	case vertical:
		if(xi[0] + 3 >= x)
				return true;
		return false;
	case horizontal:
		if (yi[0] + 3 >= y)
			return true;
		return false;
	}
}
bool LineCrossesFigureWhileRotate(int rotation)
{
	switch (rotation)
	{
	case vertical:
		for (int i = 0; i < 4; i++)
			if (Field[yi[0]][xi[0] + i] == 3)
				return true;
		return false;
	case horizontal:
		for (int i = 0; i < 4; i++)
			if (Field[yi[0] + i][xi[0]] == 3)
				return true;
		return false;
	}
}
void ChangeLineCoordsTo(int rotation)
{
	switch (rotation)
	{
	case vertical:
		for (int i = 1; i < 4; i++)
		{
			xi[i] = xi[0];
			yi[i] = yi[i - 1] + 1;
		}
		break;
	case horizontal:
		for (int i = 1; i < 4; i++)
		{
			yi[i] = yi[0];
			xi[i] = xi[i - 1] + 1;
		}
		break;
	}
}

//QUAD
int AddQuad()
{
	int num = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (Field[i][j + 5] == 3)
			{
				GameOver = true;
				return 0;
			}

			else
			{
				Field[i][j + 5] = SQRT[i][j];
				xi[num] = j + 5;
				yi[num] = i;
				num++;
			}
		}
	}
	return 1;
}

//EL
int AddEL()
{
	int num = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Field[i][j + 5] == 3)
			{
				GameOver = true;
				return 0;
			}

			if (EL[i][j] == 0)
				continue;
			else
			{
				Field[i][j + 5] = EL[i][j];
				xi[num] = j + 5;
				yi[num] = i;
				num++;
			}

		}
	}
	currentRotation = R1;
	return 1;
}
bool ELIsOutOfBordersWhileRotate(int rotation)
{
	switch (rotation)
	{
	case R1:
		return (yi[0] + 2 >= y || xi[0] - 1 <= 0);
	case R2:
		return (xi[0] - 2 <= 0 || yi[0] - 1 <= 0);
	case R3:
		return (yi[0] - 2 <= 0 || xi[0] + 1 >= x);
	case R4:
		return (xi[0] + 2 >= x || yi[0] + 1 >= y);
	}
}
bool ELCrossesFigureWhileRotate(int rotation)
{
	switch (rotation)
	{
	case R1:
		return (Field[yi[0] + 2][xi[0]] == 3 || Field[yi[0]][xi[0] - 1] == 3);
	case R2:
		return (Field[yi[0]][xi[0] - 2] == 3 || Field[yi[0] - 1][xi[0]] == 3);
	case R3:
		return (Field[yi[0] - 2][xi[0]] == 3 || Field[yi[0]][xi[0] + 1] == 3);
	case R4:
		return (Field[yi[0]][xi[0] - 2] == 3 || Field[yi[0] + 1][xi[0]] == 3);
	}
}
void ChangeELCoordsTo(int rotation)
{
	switch (rotation)
	{
	case R1:
		xi[0] = xi[0];
		xi[1] = xi[0] + 1;
		xi[2] = xi[1] + 1;
		xi[3] = xi[0];

		yi[0] = yi[0];
		yi[1] = yi[0];
		yi[2] = yi[0];
		yi[3] = yi[0] + 1;
		break;
	case R2:
		xi[0] = xi[0];
		xi[1] = xi[0];
		xi[2] = xi[1];
		xi[3] = xi[2] - 1;

		yi[0] = yi[0];
		yi[1] = yi[0] + 1;
		yi[2] = yi[1] + 1;
		yi[3] = yi[0];
		break;
	case R3:
		xi[0] = xi[0];
		xi[1] = xi[0] - 1;
		xi[2] = xi[1] - 1;
		xi[3] = xi[0];

		yi[0] = yi[0];
		yi[1] = yi[0];
		yi[2] = yi[0];
		yi[3] = yi[0] - 1;
		break;
	case R4:
		xi[0] = xi[0];
		xi[1] = xi[0];
		xi[2] = xi[0];
		xi[3] = xi[0] + 1;

		yi[0] = yi[0];
		yi[1] = yi[0] - 1;
		yi[2] = yi[1] - 1 ;
		yi[3] = yi[0];
		break;
	}
}

//INEL
int AddINEL()
{
	int num = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Field[i][j + 5] == 3)
			{
				GameOver = true;
				return 0;
			}

			if (INEL[i][j] == 0)
				continue;
			else
			{				
				Field[i][j + 5] = INEL[i][j];
				xi[num] = j + 5;
				yi[num] = i;
				num++;
			}

		}
	}
	currentRotation = R1;
	return 1;
}
bool INELIsOutOfBordersWhileRotate(int rotation)
{
	switch (rotation)
	{
	case R1:
		return (xi[0] - 1 <= 0 || yi[0] + 2 >= y);
	case R2:
		return (xi[0] - 2 <= 0 || yi[0] - 1 <= 0);
	case R3:
		return (xi[0] + 1 >= x || yi[0] - 2 <= 0);
	case R4:
		return (xi[0] + 2 >= x || yi[0] + 1 >= y);
	}
}
bool INELCrossesFigureWhileRotate(int rotation)
{
	switch (rotation)
	{
	case R1:
		return (Field[yi[0] + 2][xi[0]] == 3 || Field[yi[0]][xi[0] - 1] == 3);
	case R2:
		return (Field[yi[0] - 1][xi[0]] == 3 || Field[yi[0]][xi[0] - 2] == 3);
	case R3:
		return (Field[yi[0] - 2][xi[0]] == 3 || Field[yi[0]][xi[0] + 1] == 3);
	case R4:
		return (Field[yi[0] + 1][xi[0]] == 3 || Field[yi[0]][xi[0] + 2] == 3);
	}
}
void ChangeINELCoordsTo(int nextRotation)
{
	switch (nextRotation)
	{
	case R1:
		xi[0] = xi[0];
		xi[1] = xi[0] + 1;
		xi[2] = xi[1] + 1;
		xi[3] = xi[2];

		yi[0] = yi[0];
		yi[1] = yi[0];
		yi[2] = yi[0];
		yi[3] = yi[0] + 1;
		break;
	case R2:
		xi[0] = xi[0];
		xi[1] = xi[0];
		xi[2] = xi[0];
		xi[3] = xi[0] - 1;

		yi[0] = yi[0];
		yi[1] = yi[0] + 1;
		yi[2] = yi[1] + 1;
		yi[3] = yi[2];
		break;
	case R3:
		xi[0] = xi[0];
		xi[1] = xi[0] - 1;
		xi[2] = xi[1] - 1;
		xi[3] = xi[2];

		yi[0] = yi[0];
		yi[1] = yi[0];
		yi[2] = yi[0];
		yi[3] = yi[0] - 1;
		break;
	case R4:
		xi[0] = xi[0];
		xi[1] = xi[0];
		xi[2] = xi[0];
		xi[3] = xi[1] + 1;

		yi[0] = yi[0];
		yi[1] = yi[0] - 1;
		yi[2] = yi[1] - 1;
		yi[3] = yi[2];
		break;
	}
}

//LGHT
int AddLGHT()
{
	int num = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Field[i][j + 5] == 3)
			{
				GameOver = true;
				return 0;
			}

			if (LGHT[i][j] == 0)
				continue;
			else
			{
				Field[i][j + 5] = LGHT[i][j];
				xi[num] = j + 5;
				yi[num] = i;
				num++;
			}

		}
	}
	currentRotation = horizontal;
	return 1;
}
bool LGHTIsOutOfBordersWhileRotate(int rotation)
{
	switch (rotation)
	{
	case horizontal:
		return (yi[0] + 2 >= y || xi[0] - 1 <= 0);
	case vertical:
		return (xi[0] + 2 >= x);
	}
}
bool LGHTCrossesFigureWhileRotate(int rotation)
{
	switch (rotation)
	{
	case horizontal:
		return (Field[yi[0] + 2][xi[0]] == 3 || Field[yi[0]][xi[0] - 1] == 3);
	case vertical:
		return (Field[yi[0]][xi[0] + 2] == 3);
	}
}
void ChangeLGHTCoordsTo(int rotation)
{
	switch (rotation)
	{
	case horizontal:
		xi[0] = xi[0];
		xi[1] = xi[0] + 1;
		xi[2] = xi[1];
		xi[3] = xi[2] + 1;

		yi[0] = yi[0];
		yi[1] = yi[0];
		yi[2] = yi[0] + 1;
		yi[3] = yi[2];
		break;
	case vertical:	
		xi[0] = xi[0];
		xi[1] = xi[0];
		xi[2] = xi[0] - 1;
		xi[3] = xi[2];

		yi[0] = yi[0];
		yi[1] = yi[0] + 1;
		yi[2] = yi[1];
		yi[3] = yi[2] + 1;
		break;
	}
}

//BGHT
int AddBGHT()
{
	int num = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Field[i][j + 5] == 3)
			{
				GameOver = true;
				return 0;
			}

			if (BGHT[i][j] == 0)
				continue;
			else
			{
				Field[i][j + 5] = BGHT[i][j];
				xi[num] = j + 5;
				yi[num] = i;
				num++;
			}

		}
	}

	ChangeBGHTCoordsTo(horizontal);

	currentRotation = horizontal;
	return 1;
}
bool BGHTIsOutOfBordersWhileRotate(int rotation)
{
	switch (rotation)
	{
	case horizontal:
		return (xi[0] + 1 >= x );
	case vertical:
		return (xi[0] - 1 <= 0 );
	}
}
bool BGHTCrossesFigureWhileRotate(int rotation)
{
	switch (rotation)
	{
	case horizontal:
		return (Field[yi[0]][xi[0] + 1] == 3);
	case vertical:
		return (Field[yi[0]][xi[0] - 1] == 3);
	}
}
void ChangeBGHTCoordsTo(int rotation)
{
	switch (rotation)
	{
	case horizontal:
		xi[0] = xi[1];
		xi[1] = xi[1] - 1;
		xi[2] = xi[1];
		xi[3] = xi[2] - 1;

		yi[0] = yi[0];
		yi[1] = yi[0];
		yi[2] = yi[0] + 1;
		yi[3] = yi[2];
		break;
	case vertical:
		xi[0] = xi[0];
		xi[1] = xi[0];
		xi[2] = xi[0] + 1;
		xi[3] = xi[2];

		yi[0] = yi[0];
		yi[1] = yi[0] + 1;
		yi[2] = yi[1];
		yi[3] = yi[2] + 1;
		break;
	}
}

//DCK
int AddDCK()
{
	int num = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Field[i][j + 5] == 3)
			{
				GameOver = true;
				return 0;
			}

			if (DCK[i][j] == 0)
				continue;
			else
			{
				Field[i][j + 5] = DCK[i][j];
				xi[num] = j + 5;
				yi[num] = i;
				num++;
			}

		}
	}
	currentRotation = R1;
	return 1;
}
bool DCKIsOutOfBordersWhileRotate(int rotation)
{
	switch (rotation)
	{
	case R1:
		return (xi[0] - 1 <= 0 || yi[0] + 2 >= y);
	case R2:
		return (xi[0] - 2 <= 0 || yi[0] - 1 <= 0);
	case R3:
		return (xi[0] + 1 >= x || yi[0] - 2 <= 0);
	case R4:
		return (xi[0] + 2 >= x || yi[0] + 1 >= y);
	}
}
bool DCKCrossesFigureWhileRotate(int rotation)
{
	switch (rotation)
	{
	case R1:
		return (Field[yi[0]][xi[0] - 1] == 3 || Field[yi[0] + 2][xi[0]] == 3);
	case R2:
		return (Field[yi[0]][xi[0] - 2] == 3 || Field[yi[0] - 1][xi[0]] == 3);
	case R3:
		return (Field[yi[0]][xi[0] + 1] == 3 || Field[yi[0] - 2][xi[0]] == 3);
	case R4:
		return (Field[yi[0]][xi[0] + 2] == 3 || Field[yi[0] + 1][xi[0]] == 3);
	}
}
void ChangeDCKCoordsTo(int nextRotation)
{
	switch (nextRotation)
	{
		case R1:
		xi[0] = xi[0];
		xi[1] = xi[0] + 1;
		xi[2] = xi[1] + 1;
		xi[3] = xi[1];

		yi[0] = yi[0];
		yi[1] = yi[0];
		yi[2] = yi[0];
		yi[3] = yi[0] + 1;
		break;
	case R2:
		xi[0] = xi[0];
		xi[1] = xi[0];
		xi[2] = xi[0];
		xi[3] = xi[0] - 1;

		yi[0] = yi[0];
		yi[1] = yi[0] + 1;
		yi[2] = yi[1] + 1;
		yi[3] = yi[1];
		break;
	case R3:
		xi[0] = xi[0];
		xi[1] = xi[0] - 1;
		xi[2] = xi[1] - 1;
		xi[3] = xi[1];

		yi[0] = yi[0];
		yi[1] = yi[0];
		yi[2] = yi[0];
		yi[3] = yi[0] - 1;
		break;
	case R4:
		xi[0] = xi[0];
		xi[1] = xi[0];
		xi[2] = xi[0];
		xi[3] = xi[0] + 1;

		yi[0] = yi[0];
		yi[1] = yi[0] + 1;
		yi[2] = yi[1] + 1;
		yi[3] = yi[1];
		break;
	}
}