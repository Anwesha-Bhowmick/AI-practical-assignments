#include<iostream>

using namespace std;

bool visited[11][11];

int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};

class Coordinates
{
  public: 
    int x, y;
    Coordinates(int x, int y)
    {
      this->x=x;
      this->y=y;
    }
};

bool is_valid(int a, int b)
{
  if(a<0 || b<0 || a>10 || b>10)
    return false;
  if(visited[a][b]==true)
    return false;
  return true;
}

bool dfs(Coordinates start, Coordinates goal)
{
  visited[start.x][start.y]=1;
  cout<<start.x<<" , "<<start.y<<endl;
  if((start.x==goal.x) && (start.y==goal.y))
  {
    cout<< "goal reached at "<<start.x<<" , "<<start.y<<endl;
    return true;
  }  
  for(int i=0;i<4;i++)
  {
    if(is_valid((start.x)+dx[i], (start.y)+dy[i]))
    {
      Coordinates temp(start.x+dx[i], start.y+dy[i]);
      if(dfs(temp,goal))
        return true;
    }
  }
  return false;
}

int main()
{
  Coordinates start(0,0);
  Coordinates goal(3,4);
  dfs(start, goal);
  return 0;
}
