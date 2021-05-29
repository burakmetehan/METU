#include <stdio.h>
#define row_limit 5
#define col_limit 5

void print_visited(char visited[row_limit][col_limit]){
	int i, j;
	for (i = 0; i < row_limit; i++)
	{
		for (j = 0; j < col_limit; j++)
		{
			printf("%d ", visited[i][j]);
		}
		printf("\n");
	}
}

void rotate_180(int image[row_limit][col_limit], int c_row, int c_col, int p_row, int p_col, int N){
	/*
	N: copy_area_dimension (for loop limit) (N = copy_right_row - copy_left_row)
	c_row: copy_left_row
	c_col: copy_left_col
	p_row: paste_left_row
	p_col: paste_right_row
	*/
	int i, j;	
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			image[p_row+i][p_col+j] = image[c_row+N-i-1][c_col+N-j-1];
		}
	}
}

int main()
{
	/*
	char visited[row_limit][col_limit]={{0}};	
	
	print_visited(visited);
	*/

	int i,j;
	int copy_left_row, copy_left_col, copy_right_row, copy_right_col;
	int paste_left_row, paste_left_col, paste_right_row, paste_right_col;
	int image[row_limit][col_limit];


	
	for (i = 0; i < row_limit; i++)
	{
		for (j = 0; j < col_limit; j++)
		{
			scanf("%d", &image[i][j]);
		}
	}

	scanf("%d %d %d %d", &copy_left_row, &copy_left_col, &copy_right_row, &copy_right_col);
	scanf("%d %d %d %d", &paste_left_row, &paste_left_col, &paste_right_row, &paste_right_col);

	rotate_180(image, copy_left_row, copy_left_col, paste_left_row, paste_left_col,2);
	
	for (i=0; i < row_limit; i++)
	{
		for (j=0; j < col_limit; j++)
		{
			printf("%d ", image[i][j]);
		}
		printf("\n");
	}
		
	return 0;
}