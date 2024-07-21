//Maze Runner Game
#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
#define endl "\n"
#define f(n) for (int i=0; i<n; i++)
#define fj(n) for (int j=0; j<n; j++)
class Game
{
public:
    int location_1,location_2;
    char **matrix;
    char **copy_matrix;
    map<pair<int,int>,int>mp;
    vector<int>gems,obstacles;
    Game();
    void print_map()const;
    void randomize();
    bool check()const;
};
void Game::randomize()
{
    f(10)
    {
        fj(10)
        {
            matrix[i][j]='_';
        }
    }
    vector<int>v(100);
    gems.clear();
    obstacles.clear();
    for (int i=0; i<100; i++)
    {
        v[i]=i+1;
    }
    unsigned seed = std::chrono::system_clock::now()
                    .time_since_epoch()
                    .count();
    shuffle (v.begin(), v.end(), std::default_random_engine(seed));
    for (int i=0; i<46; i++)
    {
        gems.push_back(v[i]);
    }
    for (int i=46; i<61; i++)
    {
        obstacles.push_back(v[i]);
    }
    for (int i=0; i<10; i++)
    {
        for (int j=0; j<10; j++)
        {
            if (i==9 and j==0)
            {
                continue;
            }
            bool flag=false;
            for (int k=0; k<gems.size(); k++)
            {
                if (mp[ {i,j}]==gems[k])
                {
                    matrix[i][j]='$';
                    flag=true;
                    break;
                }
            }
            if (!flag)
            {
                for (int z=0; z<obstacles.size(); z++)
                {
                    if (mp[ {i,j}]==obstacles[z])
                    {
                        matrix[i][j]='#';
                        break;
                    }
                }
            }
        }
    }
    matrix[9][0]='*';
    location_1=9;
    location_2=0;

    int number_of_gems=0;
    f(10)
    {
        fj(10)
        {
            if (matrix[i][j]=='$')
            {
                number_of_gems++;
            }
        }
    }
    if (number_of_gems==46)
    {
        f(10)
        {
            fj(10)
            {
                if (matrix[i][j]=='$')
                {
                    matrix[i][j]='-';
                    f(10)
                    {
                        fj(10)
                        {
                            copy_matrix[i][j]=matrix[i][j];
                        }
                    }
                    return;
                }
            }
        }
    }
    f(10)
    {
        fj(10)
        {
            copy_matrix[i][j]=matrix[i][j];
        }
    }
}
Game::Game()
{
    location_1=9;
    location_2=0;
    matrix=new char *[10];
    for (int i=0; i<10; i++)
    {
        matrix[i]=new char [10];
    }
    copy_matrix=new char *[10];
    for (int i=0; i<10; i++)
    {
        copy_matrix[i]=new char [10];
    }
    int e=1;
    f(10)
    {
        fj(10)
        {
            matrix[i][j]='_';
            mp[make_pair(i,j)]=e++;
        }
    }
    matrix[9][0]='*';
    randomize();
    while (!check())
    {
        randomize();
    }
}
void Game::print_map()const
{
    for (int i=0; i<10; i++)
    {
        cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"  ";
        for (int j=0; j<10; j++)
        {
            cout<<matrix[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
}
bool Game::check()const
{
    if (matrix[9][1]=='#' and matrix[8][0]=='#')
    {
        return false;
    }
    return true;
}
int main()
{
    Game obj;
    int t=0;
    bool played=false;
    char choice;
    bool pressed_another_key_from_the_first_menu=false;
    while (true)
    {
        if (!pressed_another_key_from_the_first_menu)
        {
            cout <<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Press 1 To Show The Map" << endl;
            cout <<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Press 2 To Randomize The Map" << endl;
            cout <<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Press 3 To Start A New Game" << endl;
            cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Press 4 To Exit The Game"<<endl<<endl;
            cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'.';
        }
        choice=_getch();
        if (choice == '1')
        {
            pressed_another_key_from_the_first_menu=false;
            system("cls");
            cout<<endl<<endl<<endl<<endl;
            cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Your map is:"<<endl<<endl;
            if (!played)
            {
                obj.print_map();
            }
            else
            {
                for (int i=0; i<10; i++)
                {
                    cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"  ";
                    for (int j=0; j<10; j++)
                    {
                        cout<<obj.copy_matrix[i][j]<<' ';
                    }
                    cout<<endl;
                }
                cout<<endl;
            }
        }
        else if (choice == '2')
        {
            pressed_another_key_from_the_first_menu=false;
            system("cls");
            cout<<endl<<endl<<endl<<endl;
            obj.randomize();
            while (!obj.check())
            {
                obj.randomize();
            }
            cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Your New Map Is:" << endl<<endl;
            obj.print_map();
        }
        else if (choice=='3')
        {
            pressed_another_key_from_the_first_menu=false;
            bool pressed_another_key=false;
            played=true;
            bool first_press=true;
            system("cls");
            cout<<endl<<endl<<endl<<endl;
            int health=3;
            t++;
            int score=0;
            int moves=0;
            char c;
            if (t>1)
            {
                f(10)
                {
                    fj(10)
                    {
                        obj.matrix[i][j]=obj.copy_matrix[i][j];
                    }
                }
                obj.location_1=9;
                obj.location_2=0;
            }
            cout<<endl<<endl<<endl<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Press ESC At Any Moment While Playing To Exit The Game And Go Back To The menu"<<endl<<endl;
            cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Press s To Start The Game Or x To Exit The Game Or Any Key to Go Back To The Menu: ";
            char choice_to_play;
            choice_to_play=_getch();
            if (choice_to_play=='s')
            {
                system("cls");
                cout<<endl<<endl<<endl<<endl;
                cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<3<<"        Score:"<<0<<"        Moves:"<<0<<endl<<endl;
                obj.print_map();
                while (true)
                {
                    if (first_press)
                    {
                        cout<<endl;
                        cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<" You can use the arrow keys or the aswd keys to play"<<endl<<endl;
                    }
                    c=_getch();
                    if (c == 77 || c == 'd')
                    {
                        first_press=false;
                        if (obj.location_2!=9)
                        {
                            if (obj.matrix[obj.location_1][obj.location_2+1]=='#')
                            {
                                if (health==0)
                                {
                                    cout<<endl<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"  GAME OVER"<< endl<<endl;
                                    break;
                                }
                                else
                                {
                                    system("cls");
                                    health--;
                                    cout<<endl<<endl<<endl<<endl;
                                    cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                    obj.print_map();
                                }
                            }
                            else if (obj.matrix[obj.location_1][obj.location_2+1]=='$')
                            {
                                moves++;
                                score++;
                                system("cls");
                                cout<<endl<<endl<<endl<<endl;
                                cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                obj.matrix[obj.location_1][obj.location_2]='_';
                                obj.location_2++;
                                obj.matrix[obj.location_1][obj.location_2]='*';
                                obj.print_map();
                                if (score==45)
                                {
                                    cout<<endl<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"  YOU WIN!!"<< endl<<endl;
                                    break;
                                }
                            }
                            else
                            {
                                moves++;
                                system("cls");
                                cout<<endl<<endl<<endl<<endl;
                                cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                obj.matrix[obj.location_1][obj.location_2]='_';
                                obj.location_2++;
                                obj.matrix[obj.location_1][obj.location_2]='*';
                                obj.print_map();
                            }
                        }
                    }
                    else if (c == 75 || c == 'a')
                    {
                        first_press=false;
                        if (obj.location_2!=0)
                        {
                            if (obj.matrix[obj.location_1][obj.location_2-1]=='#')
                            {
                                if (health==0)
                                {
                                    cout<<endl<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"  GAME OVER"<< endl<<endl;
                                    break;
                                }
                                else
                                {
                                    system("cls");
                                    health--;
                                    cout<<endl<<endl<<endl<<endl;
                                    cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                    obj.print_map();
                                }
                            }
                            else if (obj.matrix[obj.location_1][obj.location_2-1]=='$')
                            {
                                score++;
                                moves++;
                                system("cls");
                                cout<<endl<<endl<<endl<<endl;
                                cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                obj.matrix[obj.location_1][obj.location_2]='_';
                                obj.location_2--;
                                obj.matrix[obj.location_1][obj.location_2]='*';
                                obj.print_map();
                                if (score==45)
                                {
                                    cout<<endl<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"  YOU WIN!!"<< endl<<endl;
                                    break;
                                }
                            }
                            else
                            {
                                moves++;
                                system("cls");
                                cout<<endl<<endl<<endl<<endl;
                                cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                obj.matrix[obj.location_1][obj.location_2]='_';
                                obj.location_2--;
                                obj.matrix[obj.location_1][obj.location_2]='*';
                                obj.print_map();
                            }
                        }
                    }
                    else if (c == 72 || c == 'w')
                    {
                        first_press=false;
                        if (obj.location_1!=0)
                        {
                            if (obj.matrix[obj.location_1-1][obj.location_2]=='#')
                            {
                                if (health==0)
                                {
                                    cout<<endl<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"  GAME OVER"<< endl<<endl;
                                    break;
                                }
                                else
                                {
                                    system("cls");
                                    health--;
                                    cout<<endl<<endl<<endl<<endl;
                                    cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                    obj.print_map();
                                }
                            }
                            else if (obj.matrix[obj.location_1-1][obj.location_2]=='$')
                            {
                                score++;
                                moves++;
                                system("cls");
                                cout<<endl<<endl<<endl<<endl;
                                cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                obj.matrix[obj.location_1][obj.location_2]='_';
                                obj.location_1--;
                                obj.matrix[obj.location_1][obj.location_2]='*';
                                obj.print_map();
                                if (score==45)
                                {
                                    cout<<endl<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"  YOU WIN!!"<< endl<<endl;
                                    break;
                                }
                            }
                            else
                            {
                                moves++;
                                system("cls");
                                cout<<endl<<endl<<endl<<endl;
                                cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                obj.matrix[obj.location_1][obj.location_2]='_';
                                obj.location_1--;
                                obj.matrix[obj.location_1][obj.location_2]='*';
                                obj.print_map();
                            }
                        }
                    }
                    else if (c == 80 || c == 's')
                    {
                        first_press=false;
                        if (obj.location_1!=9)
                        {
                            if (obj.matrix[obj.location_1+1][obj.location_2]=='#')
                            {
                                if (health==0)
                                {
                                    cout<<endl<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"  GAME OVER"<< endl<<endl;
                                    break;
                                }
                                else
                                {
                                    system("cls");
                                    health--;
                                    cout<<endl<<endl<<endl<<endl;
                                    cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                    obj.print_map();
                                }
                            }
                            else if (obj.matrix[obj.location_1+1][obj.location_2]=='$')
                            {
                                score++;
                                moves++;
                                system("cls");
                                cout<<endl<<endl<<endl<<endl;
                                cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                obj.matrix[obj.location_1][obj.location_2]='_';
                                obj.location_1++;
                                obj.matrix[obj.location_1][obj.location_2]='*';
                                obj.print_map();
                                if (score==45)
                                {
                                    cout<<endl<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"  YOU WIN!!"<< endl<<endl;
                                    break;
                                }
                            }
                            else
                            {
                                moves++;
                                system("cls");
                                cout<<endl<<endl<<endl<<endl;
                                cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Remaining lives:"<<health<<"        Score:"<<score<<"        Moves:"<<moves<<endl<<endl;
                                obj.matrix[obj.location_1][obj.location_2]='_';
                                obj.location_1++;
                                obj.matrix[obj.location_1][obj.location_2]='*';
                                obj.print_map();
                            }
                        }
                    }
                    else if (c==27)
                    {
                        break;
                    }
                    else
                    {

                        first_press=false;
                    }
                }
            }
            else if (choice_to_play=='x')
            {
                cout<<"Are You Sure You Want To Quit The Game?"<<endl<<endl;
                cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Press y To Confirm Or n To Cancel: "<<endl<<endl;
                cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'.';
                int ch;
                ch=_getch();
                while (true)
                {
                    if (ch=='y')
                    {
                        return 0;
                    }
                    else if (ch=='n')
                    {
                        system("cls");
                        break;
                    }
                    else
                    {
                        cout<<"Wrong input!"<<endl<<endl;
                        cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Press y To Confirm Or n To Cancel: "<<endl<<endl;
                        cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'.';
                        ch=_getch();
                    }
                }
            }
            else
            {
                system("cls");
            }
        }
        else if (choice=='4')
        {
            cout<<"Are You Sure You Want To Quit The Game?"<<endl<<endl;
            cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Press y To Confirm Or n To Cancel: "<<endl<<endl;
            cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'.';
            int ch;
            ch=_getch();
            while (true)
            {
                if (ch=='y')
                {
                    return 0;
                }
                else if (ch=='n')
                {
                    system("cls");
                    break;
                }
                else
                {
                    cout<<"Wrong input!"<<endl<<endl;
                    cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"Press y To Confirm Or n To Cancel: "<<endl<<endl;
                    cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'.';
                    ch=_getch();
                }
            }
        }
        else
        {
            pressed_another_key_from_the_first_menu=true;
        }
    }
    return 0;
}
