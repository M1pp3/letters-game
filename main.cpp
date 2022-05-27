//POP_2018_12_19_projekt_1_Penkal_Michal_EIT_2_176001 Code::Blocks 17.12
#include <iostream>
#include <cstdlib>
#include <ctime>// funkcja srand
#include <cctype>   // wieksze, mniejsze
#include <iomanip>// format tablicy
#include <limits> //do zapobiegania bledom wpisywania

using namespace std;
// stale okreslajace maksymalne liczby do wykorzytania w grze
const int Max_width = 100;
const int Max_height = 100;
const int Max_letters = 20;

//stale dla przykladowej gry
const int Example_w = 5;
const int Example_h = 3;
const int Example_l = 3;
const char Example_board [Example_h][Example_w] = {'c', 'a', 'c', 'b', 'c',
                                                   'a', 'b', 'c', 'b', 'b',
                                                   'c', 'b', 'c', 'a', 'c',};       // to jest przykladowa tablica gry
// poszczegolne ruchy w przykladowej grze
const char Example_move1 = 'a';
const char Example_move2 = 'c';
const char Example_move3 = 'b';

//struktora  gry
struct Game
{
    int width, height;
    int letters;
    int capital;
    char board[Max_height][Max_width];//te stale to maksymalnu rozmiar tablicy
};
//funkcja inicjujaca gre
void InitGame(Game &g, int w, int h, int l) //przypisuje otrzymane wartosci struktorze
{
    g.width = w;
    g.height = h;
    g.letters = l;
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            g.board[i][j] = 'a' + rand() %g.letters; // okresla literki biorace udzial w grze (a to 97)
        }
    }
    g.board[0][0] = toupper(g.board[0][0]); // to zmienia pierwsza litere na wielka
    g.capital = 1;
}

void DisplayGame(Game g)
{
/* cout << (char)201;
 for(int i = 0; i < (g.width * 2) + 1; i++)
 {
     cout << (char)0xCD;
 }
 cout << (char)187 << endl;*/
 for(int i = 0; i < g.height; i++)
 {
     //cout << (char)0xBA;
     for(int j = 0; j < g.width; j++)
     {
         cout<< setw(2) << g.board[i][j]; // wyswietla tablice gry
     }
    // cout << " " << (char)0xBA;
     cout << endl;
 }
 cout << (char)0xc8;
 for(int i = 0; i < (g.width * 2) + 1; i++)
 {
     cout << (char)0xCD;
 }
 cout << (char)188 << endl;
}
void MakeMove(Game &g, char m)// game jest przekazywane przez referencje poniewaz jej wartosci zmieniaja sie wewnatrz tej funkcji
{
    cout << "zamiana wyroznionych liter na: " << char(toupper(m)) <<  endl;
    if(tolower(m) < 'a' || tolower(m) >= 'a' + g.letters)
    {
        cout << "bledny znak" << endl;
        cout << "podaj poprawna literke (od " << 'a' << " do " << char('a'+ g.letters - 1) <<" )" << endl; // tu musi byc char bo inaczej wypisze liczbe
        cout << endl;
        return;
    }
    for(int i = 0; i < g.height; i++)
    {
        for(int j = 0; j < g.width; j++)
        {
            if(isupper(g.board[i][j]))
            {
                g.board[i][j] = toupper(m);
                if(j + 1 < g.width && g.board[i][j + 1] == tolower(m)) // to jest sasiad z prawej
                {
                    g.board[i][j + 1] = toupper(m);
                }
                if(j - 1 >= 0 && g.board[i][j - 1] == tolower(m)) // to jest sasiad z lewej
                {
                    g.board[i][j - 1] = toupper(m);
                }
                if(i + 1 < g.height && g.board[i + 1][j] == tolower(m)) // to jest sasiad z dolu
                {
                    g.board[i + 1][j] = toupper(m);
                }
                if(i - 1 >= 0 && g.board[i - 1][j] == tolower(m)) // to jest sasiad z gory
                {
                    g.board[i - 1][j] = toupper(m);
                }
            }
        }
    }
    // tutaj zlicza wielkie litery zeby sprawdzic czy gra sie nie skonczyla
     int quantity = 0;
     for(int i = 0; i < g.height; i++)
     {
         for(int j = 0; j < g.width; j++)
         {
             if(isupper(g.board[i][j]))
             {
                 quantity += 1;
             }
         }
     }
     g.capital = quantity;
}


void InitExampleGame(Game &g)
{
    g.width = Example_w;
    g.height = Example_h;
    g.letters = Example_l;
    for(int i = 0; i < Example_h; i++)
    {
        for(int j = 0; j < Example_w; j++)
        {
            g.board[i][j] = Example_board[i][j];
        }
    }
    g.board[0][0] = toupper(g.board[0][0]);
    g.capital = 1;
}

void ShowHelp()
{
    Game g;
    InitExampleGame(g);
    DisplayGame(g);
    cout << "Wyswietlono plansze na ktorej bedzie odbywac sie gra." << endl;
    cout << "Chcemy zamienic jak najwiecej literek jednoczesnie. Sprobojmy zmienic wielkie litery na 'A'" << endl;
    cout << endl;
    MakeMove(g, Example_move1);
    DisplayGame(g);
    cout << endl;
    cout << "Jak widac zmienily sie wszystkie male 'a' graniczace z wielka litera." << endl;
    cout << "gramy dalej i probujemy wybrac optymalny ruch." << endl;
    cout << endl;
    MakeMove(g, Example_move2);
    DisplayGame(g);
    cout << endl;
    cout << "Analogicznie jak poprzednim razem widzimy ze wszystkie male c graniczace z A zmienily sie na wielkie. " << endl;
    cout << endl;
    MakeMove(g, Example_move3);
    DisplayGame(g);
    cout << endl;
    cout << "..........................." << endl;
}

bool Finished(Game g)
{
    if(g.capital != g.width * g.height) // warunek kiedy gra dobiega konca
    {
        return false;
    }
    else
    {
        return true;
    }
}

void exit()
{
    cout << "koniec gry";
}
int main()
{
    srand(time(NULL)); // potrzebne do uzycia rand
    string game;
    char m;

    const string nazwa = "ZAMIANA LITEREK";
    cout << nazwa << endl;
    cout << endl;
    cout << endl;
    cout << "Gra przeznaczona jest dla jednej osoby, odbywa sie na planszy wypelninej malymi literkami."<< endl;
    cout << "Jedynie litera w lewym gornym rogu jest wielka." << endl;
    cout << "Gracz ma mozliwosc zmiany wielkich liter na dowolne inne litery biorace udzial w grze." << endl;
    cout << "Mala litera zmienia sie na wielka, gdy przy niej jest taka sama litera rozniaca sie wielkoscia" << endl;
    cout << "Gracz konczy gre, jesli zmieni wszystkie litery na wielkie." << endl;
    cout << endl;
    int start = 0; // zapewnia wlaczenie sie while
    while(start != 2)           //to jest petla ktora trzyma konsole tak dlugo az sam nie zdecyduje o wyjsciu
    {
        cout << "MENU" << endl;
        cout << "1. nowa gra" << endl;
        cout << "2. wyjdz z gry" << endl;
        cout << "3. pomoc" << endl;
        cout << endl;
        cout << "wybierz opcje: ";
        while(!(cin >> start))//aby start na pewno byl liczba
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "wybrano nieistniejaca opcje" << endl;
            cout << "wybierz opcje: ";
        }
        cout << "..........................." << endl;
        // tutaj koniec menu
        int w;
        int h;
        int l;
        // podejmowanie wyboru z menu
        switch(start)
        {
        case 1:
            {
                cout << "Podaj szerokosc tablicy (nie wieksza od " << Max_width << ") : ";
                while(!(cin >> w) || w > Max_width || w < 0)       //petle zabezpieczajace przed bledami
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "bledne dane" << endl;
                    cout << "wprowadz poprawne dane: ";
                }

                cout << "Podaj wysokosc tablicy (nie wieksza od " << Max_height << ") : ";


                while(!(cin >> h) || h > Max_height || h < 0)
                {
                    cin.clear(); // te 2 linijki potrzebne aby nie mozna bylo wpisac liter i znakow
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "bledne dane" << endl;
                    cout << "wprowadz poprawne dane: ";
                }
                cout << "Podaj ilosc literek(nie wieksza od " << Max_letters << ") : ";

                while(!(cin >> l) || l > Max_letters || l < 0)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "bledne dane" << endl;
                    cout << "wprowadz poprawne dane: ";
                }
                cout << endl;

                Game g;
                InitGame(g, w, h, l);// przekazuje do funkcji uprzednio pobrane liczby
                DisplayGame(g);
                while(!Finished(g))
                {
                // tutaj wybiera sie litere na jaka chce dokonac zamiany
                    cout << endl;
                    cout << "Zmien wielkie litery na: ";
                    cin >> m;
                    cout << endl;
                    MakeMove(g, m);
                    DisplayGame(g);
                }
                cout << "=======" << endl;
                cout << "WYGRANA!" << endl;
                cout << "=======" << endl;
                cout << "..........................." << endl;
            }
        break;
        case 2:
            {
               exit();
               return 0;
            }
        break;
        case 3:
            {
                ShowHelp();
            }
        break;
        default:        // w przypadku wybrania czegos z poza 1,2,3
        cout<<"Wybrano nieistniejaca opcje" << endl;
        cout << endl;
        break;
        }
    }
    return 0;
}
