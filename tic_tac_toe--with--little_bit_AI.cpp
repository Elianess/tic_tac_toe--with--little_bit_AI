//���� ��������-������
/*
(���������)

1)������� ������ ���� ��� ����
2)�������� �� ����� �������
3)���������� ��� ����� ������ 
4)���������� ���� 
5)���� ����� �� ������� � �� ��������� ����� 
� ���� ������ ��� ������������, �� �������� ��� ��� 
6)������� ������� ���� � ������ ����
7)����� ��������� ��� ����������
8)�������� ���� � ������ ��� ����������
9)���������� ���� 
10)�������� ��� ���������
11)���������� ���������� ��� �������� �����
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//���������� ���������
const char X = 'X'; //�������
const char O = 'O'; //�����
const char EMPTY = ' '; //������ ����
const char TIE = 'T'; //����� 
const char NO_ONE = 'N'; //����� �� �������

//���������
void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(const vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);

int main()
{
	setlocale(LC_ALL, "Russian");

	int move;
	const int NUM_SQUARES = 9;

	//������� ������ ���� (���������� ������ ("�����" 9 ���������, ������� ����������� ���������))
	vector<char> board(NUM_SQUARES, EMPTY);

	//����� ������ �� �����
	instructions();

	//���������� ��� ����� ������ (�������� ������)
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;

	//���������� ����� 
	displayBoard(board);

	//���� ����� �� ������� � �� ��������� ����� 
	while (winner(board) == NO_ONE)
	{
		//���� ������ ��� ������������, �� �������� ��� ���
		if (turn == human)
		{
			move = humanMove(board, human);
			board[move] = computer;
		}
		//����� ��������� ��� ����������
		else
		{
			move = computerMove(board, computer);
			board[move] = human;
		}

		//���������� ���� 
		displayBoard(board);

		//�������� ��� ���������
		turn = opponent(turn);
	}

	//����� ����������
	announceWinner(winner(board), computer, human);

	return 0;
}

//�����������
void instructions()
{
	cout << "���������� ����! �������.. ��� ��������-������ ������ ���������� - ����!\n";
	cout << "��������� ���� ��� ������, ��� �� ������� ����.\n";
	cout << "� �� ������� ���� ��������, � ���� ������ �� ������! >:)\n\n";

	cout << " 0 | 1 | 2\n";
	cout << " ---------\n";
	cout << " 3 | 4 | 5\n";
	cout << " ---------\n";
	cout << " 6 | 7 | 8\n\n";

	cout << "�����, ��� ���� �����������.\n\n";
}

//�� ��� ���(��� ������� humanPiece())
char askYesNo(string question)
{
	char responce;
	
	do
	{
		cout << question << "(y/n)";
		cin >> responce;
	} while (responce != 'y' && responce != 'n');

	return responce;
}

//��������� ����. � ���. �����, ��������� ����� �� ����� ����.(����� ��� ����. �������)
int askNumber(string question, int hight, int low)
{
	int number;

	do
	{
		cout << question << " (" << low << " - " << hight << "): ";
		cin >> number;
	} while (number > hight || number < low);

	return number;
}

//���������� ������������, ����� �� �� ������ ������
char humanPiece()
{
	char first = askYesNo("�� ������ ������ ������?");
	if (first == 'y')
	{
		cout<<"\n��� ���� ����, ����� ������ ���.\n";
		return X;
	}
	else
	{
		cout << "\n��.. ��� ������. �� ������� �������������!\n";
		return O;
	}
}

//���������� ������ ������������ � ���������� �� ������������
char opponent(char piece)
{
	if (piece == X)
		return O;
	else
		return X;
}

//����������� �������� ���� 
void displayBoard(const vector<char>& board)
{
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8]<<"\n\n";
}

//�������� ������� ���� � ���������� ����������
char winner(const vector<char>& board)
{
	//���������� ����
	const int WINNING_ROWS[8][3] =
	{
		{0, 1, 2},	// ������� �������
		{3, 4, 5},	// ������� �������
		{6, 7, 8},	// ������ �������

		{0, 3, 6},	// ����� �������
		{1, 4, 7},	// ������� �������
		{2, 5, 8},	// ������ �������

		{0, 4, 8},	// ��������� ����� �� �����
		{2, 4, 6}	// ��������� ������ �� ����
	};

	//��������, �� ������� �� ��� ���-��
	const int TOTAL_ROWS = 8;

	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}
	}

	//���� ��� ����������, ��������� �� �����
	//��������� �������� �� ������ ������
	if (count(board.begin(), board.end(), EMPTY) == 0)
		return TIE;

	//���� ��� ����������, � ��� ������, �� ���������� ����
	return NO_ONE;
}

//�������� ���� � ��������� ��������� �� ������ ���(����� ��� ����. �������)
bool isLegal(const vector<char>& board, int move)
{
	return (board[move] == EMPTY);
}

//���� ���
//�������� ���� � ������, ���������� ����� ������ ����
int humanMove(const vector<char>& board, char human)
{
	int move = askNumber("���� ������ ������? ", (board.size() - 1));

	while (!isLegal(board, move))
	{
		cout << "\n��� ��... ������!\n";
		move = askNumber("���� ������ ������? ", (board.size() - 1));
	}
	cout << "�������.\n";
	return move;
}

//��� ����������
//�������� ���� � ������, ���������� ����� ������ ����
//��� �������� ���� �� ��������, �.�. ����� ����� ����� �������� � �������� ����� ����
//������� � ������, �������� ������ ���������� ��� ��������� 
int computerMove(vector<char> board, char computer)
{
	//��������� ������� �����n������� ���������
	/*
		��� 1
		���� � ���������� ���� ����������� ������� ���,
		������� �������� ��� ������ - ������� ���� ���.
	*/
	unsigned move = 0;
	bool found = false;

	while (!found && move < board.size())
	{
		if (isLegal(board, move))
		{
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}

		if (!found)
			++move;
	}

	/*
		��� 2
		�����, ���� ������� ����� �������� 
		��������� �����, ����������� ���� ���.
	*/
	//������ ������ ������������ � ��������� �������� �� ��� ��� � ������
	//����� �������� ��� ������������, ����� ������ ����� ������
	//���� ��� ������������ �� �������� � ������, �� ���� ������
	//���� ��������, �� ����� ������, � ������� ������ ������� ���������
	if (!found)
	{
		move = 0;
		char human = opponent(computer);

		while (!found && move < board.size())
		{
			if (isLegal(board, move))
			{
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}

			if (!found)
				++move;
		}
	}

	//���� ���� �� ������ ���������� ���, �������� ����������� �������
	/*
		��� 3
		����� ������ ����������� ������ �� ���������� ������.
		����� ������ ������ � ������, ����� ����� �������, 
		��������� ������ �� ����� ������� 
	*/
	if (!found)
	{
		const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
		move = 0;
		unsigned i = 0;

		while (!found && i < board.size())
		{
			move = BEST_MOVES[i];

			if (isLegal(board, move))
				found = true;

			++i;
		}
	}

	//���������� ���� ���������� � ������� ��������� ������
	cout << "...\n����� ����� " << move << endl;
	return move;
}

//�������� ����������, ������, ������� ����� �������� � ������������
void announceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		cout << winner << "'s �������!1\n";
		cout << "�� ����� ����... ������ ������!1\n";
	}

	else if (winner == human)
	{
		cout << winner << "'s �������!1\n";
		cout << "�� � ������� ����� ��� ��������? �� �����...";
	}

	else
	{
		cout << "�����...\n�������, ����� ��� �����?";
	}
}
