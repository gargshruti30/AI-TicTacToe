#include<iostream>
#include<vector>
#include<climits>
using namespace std ;
bool row(vector<vector<char>>board,int chance)
{
    if(chance==1)
    {
        if(board[0][1]=='X'&&board[0][2]=='X'&&board[0][0]=='X')
            return true;
        if(board[1][1]=='X'&&board[1][2]=='X'&&board[1][0]=='X')
            return true;
        if(board[2][1]=='X'&&board[2][2]=='X'&&board[2][0]=='X')
            return true;
        return false;
    }
    else
    {
        if(board[0][1]=='O'&&board[0][2]=='O'&&board[0][0]=='O')
            return true;
        if(board[1][1]=='O'&&board[1][2]=='O'&&board[1][0]=='O')
            return true;
        if(board[2][1]=='O'&&board[2][2]=='O'&&board[2][0]=='O')
            return true;
        return false;

    }
}
bool column(vector<vector<char>>board,int chance)
{
    if(chance==1)
    {
        if(board[0][0]=='X'&&board[1][0]=='X'&&board[2][0]=='X')
            return true;
        if(board[0][1]=='X'&&board[1][1]=='X'&&board[2][1]=='X')
            return true;
        if(board[0][2]=='X'&&board[1][2]=='X'&&board[2][2]=='X')
            return true;
        return false;
    }
    else
    {
        if(board[0][0]=='O'&&board[1][0]=='O'&&board[2][0]=='O')
            return true;
        if(board[0][1]=='O'&&board[1][1]=='O'&&board[2][1]=='O')
            return true;
        if(board[0][2]=='O'&&board[1][2]=='O'&&board[2][2]=='O')
            return true;
        return false;
    }
}
bool diagonal(vector<vector<char>>board,int chance)
{
    if(chance==1)
    {
        if(board[0][0]=='X'&&board[1][1]=='X'&&board[2][2]=='X')
            return true;
        if(board[2][0]=='X'&&board[1][1]=='X'&&board[0][2]=='X')
            return true;
        return false;
    }
    else
    {
        if(board[0][0]=='O'&&board[1][1]=='O'&&board[2][2]=='O')
            return true;
        if(board[2][0]=='O'&&board[1][1]=='O'&&board[0][2]=='O')
            return true;
        return false;
    }
}
int check(vector<vector<char>>board)
{
    if(row(board,1)||column(board,1)||diagonal(board,1))
    {
        return 1;
    };
    if(row(board,0)||column(board,0)||diagonal(board,0))
    {
        return 0;
    };
    return 2;///tie
}
int move(vector<vector<char>>&board,int chance,int a)
{
    if(chance==1)
    {
        if(board[a/3][a%3]=='_')
        {
            board[a/3][a%3]='X';
            return 1;
        }

        else
        {
            cout<<"WRONG MOVE";
            return 0;
        }
    }
    if(chance==0)
    {
        if(board[a/3][a%3]=='_')
        {
            board[a/3][a%3]='O';
            return 1;
        }

        else
        {
            cout<<"WRONG MOVE"<<endl;
            return 0;
        }
    }
}
int player(vector<vector<char>>&board)
{
    int a;
    cout<<"ENTER THE POSITION OF THE MOVE IN NO 0-8"<<endl;
    cin>>a;
    int valid=move(board,1,a);
    return valid;
}
int computerhelper(vector<vector<char>>&board,int chance,pair<int,int>&random_answer,pair<int,int> &gotsolution)
{
    int flag=0;
    bool random_found = false;
    pair<int,int> random;
    pair<int,int> solution;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(chance==1)
            {
                if(board[i][j]=='_')
                {
                    flag=1;
                    board[i][j]='X';
                    if(check(board)==chance)
                    {
                        board[i][j] = '_';
                        gotsolution = {i,j};
                        return INT_MAX;
                    }
                    int ans=computerhelper(board,!chance,random,solution);
                    if(ans==0)
                    {
                        random_found = true;
                        random_answer= {i,j};
                        board[i][j]='_';
                    }
                    if(ans==INT_MAX)
                    {
                        board[i][j]='_';
                    }
                    if(ans==INT_MIN)
                    {
                        board[i][j] = '_';
                        gotsolution= {i,j};
                        return INT_MAX;
                    }
                }
            }
            else
            {
                if(board[i][j]=='_')
                {
                    flag=1;
                    board[i][j]='O';
                    if(check(board)==chance)
                    {
                        board[i][j] = '_';
                        gotsolution = {i,j};
                        return INT_MAX;
                    }
                    int ans=computerhelper(board,!chance,random,solution);
                    if(ans==0)
                    {
                        random_found = true;
                        random_answer= {i,j};
                        board[i][j]='_';
                    }
                    if(ans==INT_MAX)
                    {
                        board[i][j]='_';
                    }
                    if(ans==INT_MIN)
                    {
                        board[i][j] = '_';
                        gotsolution= {i,j};
                        return INT_MAX;
                    }
                }
            }

        }
    }
    if(flag==0)
    {
        int ans=check(board);
        if(ans==2)
        {
            random_found=true;
            return 0;
        }
    }
    if(random_found)
        return 0;
    else
        return INT_MIN;
}
void computer(vector<vector<char>>&board,int chance)
{
    pair<int,int> gotsolution;///we have some good move
    pair<int,int> random_answer= {5,5}; ///we get a draw move
    int ans = computerhelper(board,0,random_answer,gotsolution);
    if(ans == INT_MAX)
    {
        board[gotsolution.first][gotsolution.second]='O';
        return;
    }
    else if(ans == 0)
    {
        board[random_answer.first][random_answer.second]='O';
        return;
    }
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(board[i][j]=='_')
            {
                board[i][j]='O';
                return;
            }

        }
    }
}
void print(vector<vector<char>>&board)
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main ()
{
    vector<char>v;
    v.push_back('_');
    v.push_back('_');
    v.push_back('_');
    vector<vector<char>>board;
    board.push_back(v);
    board.push_back(v);
    board.push_back(v);
    for(int i=0; i<4; i++)
    {
        print(board);
        int valid =player(board);
        if(valid==0)
        {
            return 0;
        }
        if(check(board)==1)
        {
            cout<<"Player 1 wins";
            break;
        }
        print(board);
        computer(board,0);
        if(check(board)==0)
        {
            cout<<"Computer wins";
            break;
        }
    }
    print(board);
    int valid=player(board);
    if(valid==0)
    {
        return 0;
    }
    print(board);
    if(check(board)==1)
    {
        cout<<"Player 1 wins";
    }
    else
    {
        cout<<"Draw"<<endl;
    }

    return 0 ;
}
