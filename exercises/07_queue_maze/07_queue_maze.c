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

typedef struct _Position{
	int x;
	int y;
}Position;

Position queue[MAX_ROW*MAX_COL*2];
int visited[MAX_ROW][MAX_COL];
Position parents[MAX_ROW][MAX_COL];
Position path[MAX_ROW*MAX_COL];

int queue_head = -1;
int queue_tail = 0;



void enqueue(Position position){
	queue[queue_tail++] = position;
}
Position dequeue(){
	return queue[++queue_head];
}

int queue_empty(){
	return (queue_head + 1) == queue_tail;
}

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
int is_wall(Position position){
	return maze[position.x][position.y];
}


int make_parent(Position child, Position parent){
	parents[child.x][child.y] = parent;
}

Position None = {-1, -1};

int is_none(Position position){
	return position.x == None.x && position.y == None.y;
}
int main(void)
{
	Position position = {0, 0};
	
	make_parent(position, None);

	enqueue(position);
	while(!queue_empty()){
		position = dequeue();
		visited[position.x][position.y] = 1;
		if(position.x == MAX_ROW-1 && position.y == MAX_COL-1){
			break;
		}
		Position left  = {position.x, 	position.y-1};
		Position right = {position.x, 	position.y+1};
		Position up    = {position.x-1, 	position.y};
		Position down  = {position.x+1, 	position.y};

		if(is_valid(left) && !is_visited(left) && !is_wall(left)){
			make_parent(left, position);
			enqueue(left);
		}
		if(is_valid(right) && !is_visited(right) && !is_wall(right)){
			make_parent(right, position);
			enqueue(right);
		}
		if(is_valid(up) && !is_visited(up) && !is_wall(up)) {
			make_parent(up, position);
			enqueue(up);
		}
		if(is_valid(down) && !is_visited(down) && !is_wall(down)){
			make_parent(down, position);
			enqueue(down);
		}
	}
	if(position.x == MAX_ROW-1 && position.y == MAX_COL-1){
		int path_len = 0;
		while(!is_none(position)){
			printf("(%d, %d)\n", position.x, position.y);
			path[path_len++] = position;
			position = parents[position.x][position.y];
		}

	}	
	
	return 0;
}