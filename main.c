#include<stdio.h>
#include<stdbool.h>
#define Max_X 10
#define Max_Y 10
#define Max_Z 10


struct _MAZE{
    bool wall_F;
    bool wall_B;
    bool wall_R;
    bool wall_L;
    bool wall_U;
    bool wall_D;
    signed int score;
}maze[Max_X+1][Max_Y+1][Max_Z+1];
struct _ROBOT{
    int x;
    int y;
    int z;
}robot;
int i;
int j;
int k;
void scoreing()
{
 int tileScore=0;
    for(k=0; k < Max_Z;k++)
    {
        for(i=0; i< Max_X;i++)
        {
            for(j=0;j<Max_Y;j++)
            {
                maze[i][j][k].score=-1;
            }
        }
    }


  maze[robot.x][robot.y][robot.z].score=0;

   for(tileScore=0;tileScore<=(Max_X*Max_Y*Max_Z);tileScore++)
   {
      for (k=0;k < Max_Z;k++)
      {
        for(i=0;i<Max_Y;i++)
        {
            for(j=0;j<Max_X;j++)
            {
                if(maze[j][i][k].score == tileScore)
                {
                    if(j>0)
                        if(maze[j-1][i][k].score < 0 && maze[j][i][k].wall_L == 0)
                            maze[j-1][i][k].score = tileScore+1;

                    if(j<Max_X)
                        if(maze[j+1][i][k].score < 0 && maze[j][i][k].wall_R == 0)
                            maze[j+1][i][k].score = tileScore+1;

                    if(i>0)
                        if(maze[j][i-1][k].score < 0 && maze[j][i][k].wall_F == 0)
                            maze[j][i-1][k].score = tileScore+1;

                    if(i<Max_Y)
                        if(maze[j][i+1][k].score < 0 && maze[j][i][k].wall_B == 0)
                            maze[j][i+1][k].score = tileScore+1;
                    if(k > 0)
                        if(maze[j][i][k-1].score < 0 && maze[j][i][k].wall_D == 0)
                            maze[j][i][k-1].score = tileScore+1;
                    if(k < Max_Z)
                        if(maze[j][i][k+1].score < 0 && maze[j][i][k].wall_U == 0)
                            maze[j][i][k+1].score = tileScore+1;
                }
            }
        }
      }

   }

}
int nextX=0;
int nextY=0;
int nextZ=0;
signed int Xerr;
signed int Yerr;
signed int Zerr;
void gotoxyz(int goalX,int goalY,int goalZ)
{
    signed int nextScore;
    nextX=goalX;
    nextY=goalY;
    nextZ=goalZ;
    bool flag=0;
    scoreing();
    nextScore=maze[goalX][goalY][goalZ].score;
    while(nextScore>1)
    {
        if(nextX < Max_X-1)
            if(maze[nextX+1][nextY][nextZ].score == (nextScore-1) && !maze[nextX+1][nextY][nextZ].wall_L)
                 nextX++;flag=1;

        if(nextX > 0 && !flag)
            if(maze[nextX-1][nextY][nextZ].score == (nextScore-1) && !maze[nextX-1][nextY][nextZ].wall_R)
                nextX--;flag=1;

        if(nextY > 0 && !flag)
            if(maze[nextX][nextY-1][nextZ].score == (nextScore-1) && !maze[nextX][nextY][nextZ].wall_F)
                nextY--; flag=1;

        if(nextY < Max_Y-1 && !flag)
            if(maze[nextX][nextY+1][nextZ].score == (nextScore-1) && !maze[nextX][nextY][nextZ].wall_B)
                nextY++;flag=1;
        if(nextZ < Max_Z-1 && !flag)
            if(maze[nextX][nextY][nextZ+1].score == (nextScore-1) && !maze[nextX][nextY][nextZ].wall_U)
                nextZ++;flag=1;
        if(nextZ > 0 && !flag)
            if(maze[nextX][nextY][nextZ-1].score == (nextScore-1) && !maze[nextX][nextY][nextZ].wall_D)
                nextZ--;flag=1;

        nextScore--;
        flag=0;
   }

    Xerr=nextX-robot.x;
    Yerr=nextY-robot.y;
    Zerr=nextZ-robot.z;
    if(Xerr<0)
    {
        printf("GoLeft\n");
        robot.x--;
    }
    else if(Xerr>0)
    {
        printf("GoRight\n");
        robot.x++;
    }
    else if(Yerr<0)
    {
        printf("GoBack\n");
        robot.y--;
    }
    else if(Yerr>0)
    {
        printf("GoFront\n");
        robot.y++;
    }
    else if(Zerr > 0)
    {
         printf("GoUP\n");
         robot.z++;
    }
    else if(Zerr < 0)
    {
         printf("GoDown\n");
         robot.z--;
    }
}
int NextX;
int NextY;
int NextZ;
int main()
{
    while(true)
    {
        printf("Enter Starting X:");
        scanf("%u",&robot.x);
        if(robot.x>8)
            robot.x=8;

        printf("Enter Starting Y:");
        scanf("%u",&robot.y);
        if(robot.y>8)
            robot.y=8;

        printf("Enter Starting Z:");
        scanf("%u",&robot.z);
        if(robot.z>8)
            robot.z=8;

        printf("Enter Goal X:");
        scanf("%u",&NextX);
         if(NextX>8)
            NextX=8;

        printf("Enter Goal Y:");
        scanf("%u",&NextY);
         if(NextY>8)
            NextY=8;
        printf("Enter Goal Z:");
        scanf("%u",&NextZ);
         if(NextZ>8)
            NextZ=8;
        while(true)
        {
            gotoxyz(NextX,NextY,NextZ);
            if(Xerr==0 && Yerr==0 && Zerr==0)break;
        }
    }

}
