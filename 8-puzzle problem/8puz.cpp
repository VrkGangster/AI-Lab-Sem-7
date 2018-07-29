#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
int x,i,j,tile,tiles[9],sum=0, moves[100],
states[100][9], move_cost[100], last_swap =
-1, state_move = 0, last_state_move=0,
temp, zeroAt;
void a_star(int a[9]);
int md(int a[9], int PRINT)
{
sum=0;
for(x=0;x<9;x++)
{
if(a[x]==0)
continue;
int tmp =
abs((a[x]-1)%3-(x)%3)+abs((a[x]-1)/3-(x)/3);
sum+=tmp;
if(PRINT == 1)
printf("MD(%d) = %d\n", a[x], tmp);
}
return sum;
}
void print_state(int a[9])
{
printf("\n");
for(x=0;x<9;x++)
printf(" %d%s" , a[x] , ((x +1)%3)==0? "\n" : " " );
}
void possible_moves(int a[9])
{
int min=9999, min_i=-1,
multiple_min_state_flag=0,
min_states[4]={0};
for(i=0;i<9;i++)
if(a[i]==0) break;
zeroAt = i;
if(i%3==0)
{
moves[state_move++]=i+1;
}
else if(i%3==1)
{
moves[state_move++]=i+1;
moves[state_move++]=i-1;
}
else
{
moves[state_move++]=i-1;
}
if(i/3==0)
{
moves[state_move++]=i+3;
}
else if(i/3==1)
{
moves[state_move++]=i+3;
moves[state_move++]=i-3;
}
else
{
moves[state_move++]=i-3;
}
for(i=last_state_move;i<state_move;i++)
{
for(j=0;j<9;j++)
states[i][j]=a[j];
states[i][zeroAt]=states[i][moves[i]];
states[i][moves[i]]=0;
move_cost[i] = md(states[i],0);
if(min>move_cost[i] && last_swap!=
moves[i])
{
min = move_cost[i];
min_i = i;
}}
min_states[0]=min_i;
if(min==0)
{
print_state(states[min_i]);
printf("Solved\n");
exit(0);
}
for(i=last_state_move;i<state_move;i++)
{
if(i!=min_i && a[i]==min)
{
min_states[++multiple_min_state_flag]=i;
}
}
last_state_move = state_move;
printf("\nNext Iteration\n");
for(i=0;i<=multiple_min_state_flag;i++)
{
print_state(states[min_states[i]]);
a_star(states[min_states[i]]);
}
}
void a_star(int a[9])
{
possible_moves(a);
}
int main()
{
srand(time(0));
for (i=0; i<9; i++)
{
tile = rand() % 9 ;
if ( i==0)
tiles[i] = tile ;
else
{
for ( j=0; j <i ; j++)
{
if ( tile == tiles[j] )
{
tile = rand() % 9 ;
j=-1;
}
}
tiles[i] = tile ;
}
printf(" %d%s" , tiles[i] , ((i +1)%3)==0? "\n"
: " " ) ;
}
printf("Assuming ideal transformation...\n");
j=0;
for(i=0;i<8;i++)
if(tiles[i]!=(i+1)%9)
j++;
printf("No. of misplaced tiles = %d\n",j);
printf("Sum of Manhattan distances = %d",
md(tiles,0));
printf("\nEnter state to solve");
for(i=0;i<9;i++)
scanf("%d", &tiles[i]);
printf("\nGiven state:\n");
print_state(tiles);
a_star(tiles);
return 0;
}
