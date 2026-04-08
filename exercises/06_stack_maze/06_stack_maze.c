#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int visited[MAX_ROW][MAX_COL];

typedef struct _Position{
	int x;
	int y;
}Position;

int is_valid(Position position){
	if((position.x >= 0 && position.y >= 0) && (position.x < MAX_ROW && position.y < MAX_COL)){
		return 1;
	}else{
		return 0;
	}
}
int is_visited(Position position){
	if(is_valid(position) && (visited[position.x][position.y])){
		return 1;
	}else{
		return 0;
	}
}

int dfs(Position position){
	if(!is_valid(position)){
		return -1;
	}else if(is_visited(position)){
		return -1;
	}
	visited[position.x][position.y] = 1;
	if(maze[position.x][position.y]){
		return -1;
	}else if(position.x == MAX_ROW-1 && position.y == MAX_COL-1){
		return 1;
	}else{
		Position left  = {position.x, 	position.y-1};
		Position right = {position.x, 	position.y+1};
		Position up    = {position.x-1, 	position.y};
		Position down  = {position.x+1, 	position.y};

		if(dfs(up) == 1){
			printf("(%d, %d)\n", up.x, up.y);
			return 1;
		}
		if(dfs(down) == 1){
			printf("(%d, %d)\n", down.x, down.y);
			return 1;
		}
		if(dfs(right) == 1){
			printf("(%d, %d)\n", right.x, right.y);
			return 1;
		}		
		if(dfs(left) == 1){
			printf("(%d, %d)\n", left.x, left.y);
			return 1;
		}		

	}
	return -1;

}
int main(void)
{
	Position begin = {0, 0};
	if(dfs(begin) == 1){
		printf("(%d, %d)\n", begin.x, begin.y);
	};
	return 0;
}