#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<string>
#include <cstring>
#include <windows.h>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include <conio.h>

using namespace std;

const int N = 9;
int startGame();
void display();


COORD coord = {0, 0};
void gotoxy(int x, int y)
{
COORD coord;
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
coord);
}



bool isSafe(int board[N][N], int row, int col, int num)
{
    // Check if 'num' is already in the same row
    for (int i = 0; i < N; i++)
        if (board[row][i] == num)
            return false;

    // Check if 'num' is already in the same column
    for (int i = 0; i < N; i++)
        if (board[i][col] == num)
            return false;

    // Check if 'num' is already in the same 3x3 box
    int boxRowStart = row - row % 3;
    int boxColStart = col - col % 3;

    for (int i = 0; i < 3; i++)

        for (int j = 0; j < 3; j++)
            if (board[i + boxRowStart][j + boxColStart] == num)
                return false;

    return true;
}


void printBoard(int grid[N][N])
{

    system("cls");
    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU Game!                                 |" << endl;
    cout << "\t\t\t|       Fill in the missing numbers(represented by 0) to solve the puzzle.       |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            if(col == 3 || col == 6)
                cout << " | ";
            cout << grid[row][col] <<" ";
        }
        if(row == 2 || row == 5)
        {
            cout << endl;
            for(int i = 0; i<N; i++)
                cout << "---";
        }
        cout << endl;
    }
}


bool solveSudoku(int board[N][N], int row, int col)
{
    // If all cells are filled, the puzzle is solved
    if (row == N - 1 && col == N)
        return true;

    // Move to the next row if the current column is N
    if (col == N)
    {
        row++;
        col = 0;
    }

    // Skip the cells that already have a value
    if (board[row][col] != 0)
        return solveSudoku(board, row, col + 1);

    // Try filling the current cell with a number from 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(board, row, col, num))
        {
            board[row][col] = num;

            if (solveSudoku(board, row, col + 1))
                return true;

            board[row][col] = 0;
        }
    }
    return false;
}



bool isSolvedCompletely(int grid[N][N])
{
    for (int row = 0; row < N; row++)

        for (int col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return false;

    return true;
}


void playGame(int board[N][N])
{
    int ch;
    int row, col, num;
    while(true)
    {
        printBoard(board);
        cout << endl << endl;
        cout << "Unable to solve? Enter -1 as row, col and num to view the solved sudoku."<<endl;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;
        cout << "Enter number: ";
        cin >> num;

        if(row == -1 || col == -1 || num == -1)
        {
            solveSudoku(board, 0, 0);
            printBoard(board);
            cout << endl;
            cout << "Better luck next time!!!" << endl;
            return;
        }

        if (isSolvedCompletely(board))
            break;
        row--;
        col--;
        if (!isSafe(board, row, col, num))
        {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board[row][col] = num;
    }


    // Check if the user has solved it correctly or not
    bool solved = true;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == 0)
            {
                solved = false;
                break;
            }
        }
    }



    if (solved)
    {
        cout << "Congratulations! You have solved the puzzle." << endl;
        printBoard(board);
    }
    else
    {
        cout << "Puzzle not solved. Better luck next time." << endl;
    }

}



class TowerOfHanoiInterface
{
    int* a;
    int* b;
    int* c;
    int size;
    int nextIndexA;
    int nextIndexB;
    int nextIndexC;

public:

    static int moves;
    int& getSize()
    {
        return size;
    }
    int* getArrayA()
    {
        return a;
    }
    int* getArrayB()
    {
        return b;
    }
    int* getArrayC()
    {
        return c;
    }
    int* getIndexA()
    {
        return &nextIndexA;
    }
    int* getIndexB()
    {
        return &nextIndexB;
    }
    int* getIndexC()
    {
        return &nextIndexC;
    }
    TowerOfHanoiInterface(int n)
    {
        if (n > 0)
        {
            size = n;
        }
        else
        {
            size = 1;
        }
        a = NULL;
        b = NULL;
        c = NULL;
    }
    int swap(char source, char dest)
    {
        int* s;
        int* q;
        int* sourceIndex;
        int* destIndex;
        if (source == 'A')
        {
            sourceIndex = getIndexA();
            s = getArrayA();
        }
        else if (source == 'B')
        {
            sourceIndex = getIndexB();
            s = getArrayB();
        }
        else
        {
            sourceIndex = getIndexC();
            s = getArrayC();
        }
        if (dest == 'A')
        {
            q = getArrayA();
            destIndex = getIndexA();
        }
        else if (dest == 'B')
        {
            q = getArrayB();
            destIndex = getIndexB();
        }
        else
        {
            q = getArrayC();
            destIndex = getIndexC();
        }
        if (*destIndex >= 0 && *destIndex < size && (*sourceIndex - 1) >= 0 && (*sourceIndex - 1) < size)
        {
            if (*sourceIndex == 0)
            {
                return -1;
            }
            else if ((*destIndex - 1 >= 0) && q[*destIndex - 1] <= s[*sourceIndex - 1])
            {
                return 0;
            }
            else
            {
                int temp = q[*destIndex];
                q[*destIndex] = s[*sourceIndex - 1];
                s[*sourceIndex - 1] = temp;
                *sourceIndex = *sourceIndex - 1;
                *destIndex = *destIndex + 1;
                return true;
            }
        }
    }
    void display()
    {
        cout << "\n---------------Towers_Of_Hanoi_Game--------------\n";
        cout << '\n';
        for (int i = size; i >= 0; i--)
        {
            cout << "\t\t";
            for (int j = 0; j < 3; j++)
            {
                if (i == size)
                {
                    cout << ".\t";
                }
                else
                {
                    if (j == 0)
                    {
                        if (a[i] == 0)
                        {
                            cout << ".\t";
                        }
                        else
                        {
                            cout << a[i] << '\t';
                        }
                    }
                    else if (j == 1)
                    {
                        if (b[i] == 0)
                        {
                            cout << ".\t";
                        }
                        else
                        {
                            cout << b[i] << '\t';
                        }
                    }
                    else if (j == 2)
                    {
                        if (c[i] == 0)
                        {
                            cout << ".\t";
                        }
                        else
                        {
                            cout << c[i] << '\t';
                        }
                    }
                }
            }
            cout << '\n';
        }
        cout << "\t ----- ----- -----";
        cout << "\n\t\tA\tB\tC\n";
        cout << "\n------------------------------------------------\n";
    }
    void resetGame()
    {
        if (a && b && c)
        {
            delete a;
            delete b;
            delete c;
            a = NULL;
            b = NULL;
            c = NULL;
        }
        a = new int[size];
        b = new int[size];
        c = new int[size];
        nextIndexA = size;
        nextIndexB = 0;
        nextIndexC = 0;
        int count = size;
        for (int i = 0; i < size; i++)
        {
            a[i] = count;
            count = count - 1;
        }
        for (int i = 0; i < size; i++)
        {
            b[i] = 0;
            c[i] = 0;
        }
        moves = 0;
    }
    virtual void playGame() = 0;
};
class TowerOfHanoiGame :private TowerOfHanoiInterface
{
    bool isGameWin()
    {
        int size = getSize();
        int* c = getArrayC();
        for (int i = 0; i < size; i++)
        {
            if (c[i] == 0)
            {
                return false;
            }
        }
        return true;
    }

public:

    using TowerOfHanoiInterface::getSize;
    TowerOfHanoiGame(int n) :TowerOfHanoiInterface(n)
    {
    }
    void playGame()
    {
        resetGame();
        bool flag = false;
        char source;
        char dest;
        int invalidCheck;
        while (flag == false)
        {
            system("CLS");
            display();
            cout << "\nTotal Moves:\t" << moves;
            cout << '\n';
            cout << "\nEnter Src (A,B,C):\t";
            cin >> source;
            while (source != 'A' && source != 'B' && source != 'C')
            {
                cout << "invalid input";
                cout << "\nEnter Src (A,B,C):\t";
                cin >> source;
            }
            cout << "Enter Dst (A,B,C):\t";
            cin >> dest;
            while (source == dest || (dest != 'A' && dest != 'B' && dest != 'C'))
            {
                cout << "invalid input";
                cout << "\nEnter Dst (A,B,C):\t";
                cin >> dest;
            }
            invalidCheck = swap(source, dest);
            if (invalidCheck != 1)
            {
                if (invalidCheck == 0)
                {
                    cout << "\nWarning!, a bigger number can't be place above on small number\n";
                }
                else
                {
                    cout << "\nInvalid Move from " << source << " to " << dest << "\n";
                }
                system("pause");
            }
            else
            {
                moves = moves + 1;
            }
            flag = isGameWin();
        }
        system("CLS");
        display();
        cout << "Total Moves:\t" << moves;
        cout << "\nCongrats! You Solve The Tower of Hanoi Puzzle in " << moves << " moves\n";
        system("pause");
    }
};


int TowerOfHanoiInterface::moves = 0;


class TowerOfHanoiApp
{
public:
    static void TowerOfHanoiGameApp()
    {
        int size = 3;
        int option;
        TowerOfHanoiGame p(size);


        do
        {
            system("CLS");

            cout << "------------------------------------------------";
            cout << "\n\tWelcome To Tower Of Hanoi Game App\n";
            cout << "\nEnter 1 to Select No of Disks";
            cout << "\nEnter 2 to Start Game";
            cout << "\nEnter 3 to play Random No of Disk (3-7)";
            cout << "\nEnter 0 to exit tower of Hanoi and enter Sudoku menu";
            cout << "\nChoose Option:\t";
            cin >> option;
            if (option == 1)
            {
                cout << "Enter No. Of Disk for Tower Of Hanoi Game: ";
                cin >> size;
                while (size <= 0)
                {
                    cout << "Invalid Input Size Must Be Greater Than Zero\n";
                    cout << "Enter No. Of Disk for Tower Of Hanoi Game: ";
                    cin >> size;
                }
                p.getSize() = size;
            }

            else if (option == 2)
            {
                cout << "\nGame is Starting Now";
                cout << "\nNo of Disks Are:\t" << size << '\n';
                system("pause");
                p.playGame();
            }

            else if (option == 3)
            {
                cout << "\nYour are playing Random Puzzle Game";
                size = 3 + rand() % (7 - 3 + 1);
                p.getSize() = size;
                cout << "\nGame is Starting Now";
                cout << "\nNo of Disks Are:\t" << size << '\n';
                system("pause");
                p.playGame();
            }

            else if (option == 0)
            {
                cout << "\nTowers of Hanoi Game App is Exit Now";
            }

            else
            {
                cout << "\nInvalid Option From User";
            }
        }

        while (option != 0);
    }
};


void welcome1()   //for first welcome page
{
    int j;
    char str[]="\n\n\n\n\n\t\t\t************************WELCOME TO PROJECT OF************************ \n\n\t\t\t**********************Nokesha Marwari***************************" ;
    for(j=0;j<strlen(str);j++)
    {
      usleep(10000);      //usleep takes values in micro-seconds
      cout<<str[j];
    }
    cout<<"\t\t\t\n\nPress any key to continue\n" ;
    getch();
    system("cls");
	gotoxy(25,6);
cout<<"  *------------------*";
}


void welcome()      //welcome page 2
{



cout<<"  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**";
gotoxy(25,7);
cout<<"  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**";
gotoxy(25,8);
cout<<"        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
gotoxy(25,9);
cout<<"        =                 WELCOME                   =";
gotoxy(25,10);
cout<<"        =                   TO                      =";
gotoxy(25,11);
cout<<"        =                  MINI                   =";
gotoxy(25,12);
cout<<"        =                 GAMING                  =";
gotoxy(25,13);
cout<<"        =                 ARCADE                    =";
gotoxy(25,14);
cout<<"        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
gotoxy(25,15);
cout<<"  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**";
gotoxy(25,16);
cout<<"  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**";
gotoxy(28,22);

cout<<" Enter any key to continue.....";
getch();

}


int main()
{
    system("color D7");
    welcome();
    system("cls");
    system("color A4");
    welcome1();
    system("cls");
    srand(time(0));
    system("color E8");
    system("Color E3");
    char a;

    cout<<"WElCOME TO MINI GAMING ARCADE !!"<<endl;
            cout<<endl;
            cout<<endl;


    cout<<"\n\t*******************************Word Search Puzzle Game********************************\n\n"<<endl;

	 char n;
     string name;
     cout<<"Enter your name  :       ";
     getline(cin,name);
     cout<<endl;
     int score=0;


     do
     {
     	system("cls");
     	display();
        score=score+startGame();
        cout<<"Do you want to play again y/n   :   ";
        cin>>n;
        cout<<endl;
     }while(n!='n');


     cout<<name<<"  ";
     cout<<"Your score is   :   "<<score<<endl;
     cout<<"\n\n\t*************************************************************************************\n\n"<<endl;

    TowerOfHanoiApp::TowerOfHanoiGameApp();

    system("cls");

    system("title Sudoku Game");
    system("color B0");

    int board[N][N] =
    {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };


    cout<<endl;
    cout<<endl;
    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU Game!                                 |" << endl;
    cout << "\t\t\t|       Fill in the missing numbers(represented by 0) to solve the puzzle.       |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;

    while (true)
    {

        int choice;
        cout << endl << endl;
        cout << "\t\t[1] Solve the Sudoku" << endl;
        cout << "\t\t[2] Unable to solve? View the solved Sudoku" << endl;
        cout << "\t\t[3] Exit the Mini Arcade" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:

            playGame(board);
            break;

        case 2:

            if (solveSudoku(board, 0, 0))
            {
                cout << "Completely Solved Sudoku is: "<< endl;
                cout << endl << endl;


                for (int row = 0; row < N; row++)
                {

                    for (int col = 0; col < N; col++)
                    {
                        if(col == 3 || col == 6)
                            cout << " | ";
                        cout << board[row][col] <<" ";
                    }

                    if(row == 2 || row == 5)
                    {
                        cout << endl;
                        for(int i = 0; i<N; i++)
                            cout << "---";
                    }

                    cout << endl;

                }
                cout << endl;
                cout << "Better luck next time!!!" << endl;
            }

            else
                cout << "No solution found" << endl;

            break;

        case 3:
            exit(0);
        default:
            cout << "Invalid choice" << endl;

        }
        return 0;
    }
}
int startGame()
{

    int hint;
    string output;
    string a[10]={"html","java","css","kotlin","php","python","ruby","golang","swift","shell"};
    char arr[10][10];

    for(int i=0;i<10;i++)
    {

        for(int j=0;j<10;j++)
        {
            char c;
            int r;
            r= rand() % 26;   // generate a random number
            c= 'a' + r;            // Converting implicitly a character from a-z
            arr[i][j]=c;
        }

    }
    int index=rand()%10;
    output=a[index];

    if(a[index].length()%2==0)
    {
        // checking horizontally

            int row=rand()%10;
            int col=rand()%3;

            for(int i=0;a[index][i]!='\0';i++,col++)
            {
                arr[row][col]=a[index][i];
            }

    }
    else
    {
            //checking vertically

            int row=rand()%3;
            int col=rand()%10;

            for(int i=0;a[index][i]!='\0';i++,row++)
            {
                arr[row][col]=a[index][i];
            }
    }

    for(int i=0;i<10;i++)
    {

        for(int j=0;j<10;j++)
        {
          cout<<" "<<arr[i][j];
          Sleep(90);
        }
        cout<<endl;

    }

    string guess;
	cout<<endl<<"Press 1 for Direct Guess "<<endl;
	cout<<"Press 2 to see Hint and then guess the word	"<<endl;
	label1:
	cout<<"Enter input		:	";
	cin>>hint;
	cout<<endl;


	if(hint==2)
	{
	   cout<<"The Length of the word is  :       ";
       cout<<output.size();
       cout<<endl;
	}

    else if(hint>2)
    {
        cout<<"Invalid input	";
    	goto label1;
    }

    cout<<"Enter word you guess         :       ";
    cin>>guess;
    cout<<endl;

    if(guess==a[index])
    {
        cout<<"Congratulations ! You have guessed correct word  "<<endl;
        return 1;
    }

    else
    {
        cout<<"Sorry ! Your guessed word is incorrect.Try again "<<endl;
        return 0;
    }
}
void display()
{

	cout<<"************************************Word Search Puzzle Game****************************************\n\n"<<endl;
    cout<<"You have to guess the word in this puzzle. For example word in this puzzle can be (html,css,java etc )"<<endl;
    cout<<"(any programming language). You can also take hint from the system"<<endl<<endl;

}

