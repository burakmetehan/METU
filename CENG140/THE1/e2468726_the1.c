/*
	Burak Metehan Tunçel/2468726
	2020-2021
	METU CENG  
	CENG 140: Take Home Exam 1	
*/
/* main() function is at line 172 */
#include <stdio.h>
#define row_limit 25
#define col_limit 25


int pick_color(int r, int c){
	/* 
	To pick color there several conditions. 
	If point is inside of the image, there is no problem.
	However, if point i outside of image, I need to check 8 conditions.
	This function is checking these 8 conditions.

	r refers to row, c refers to column.
	*/

	/* 
	These are the border of image.
	In our code it will be 25-1=24.
	It generalize the code for conditions that main limit change.
	*/
	int r_limit = row_limit-1, c_limit = col_limit-1;

	if (r < 0 && c < 0) 
		return 0;
	else if (r < 0 && c >= 0 && c <= c_limit) 
		return 1;
	else if (r < 0 && c > c_limit) 
		return 2;
	else if (r >= 0 && r <= r_limit && c > c_limit) 
		return 3;
	else if (r > r_limit && c > c_limit) 
		return 4;
	else if (r > r_limit && c >= 0 && c <= c_limit) 
		return 5;
	else if (r > r_limit && c < 0) 
		return 6;
	else if (r >= 0 && r <= row_limit && c < 0) 
		return 7;
	else
		return -1;
}


void image_print(int image[row_limit][col_limit]){
	int i, j;
	for (i = 0; i < row_limit; i++)
	{
		for (j = 0; j < col_limit; j++)
		{
			printf("%d ", image[i][j]);
		}
		printf("\n");
	}
}


void fill(int init_color, int picked_color, int row, int col, int image[row_limit][col_limit], char visited[row_limit][col_limit]){
	/* Outside Check */
	if (row < 0 || row > row_limit-1 || col < 0 || col > col_limit-1)
		return;
	
	/* Check for being same with initial color */
	if (image[row][col] != init_color)
	{
		visited[row][col]=1;
		return;
	}

	/* Visited Check */
	if (visited[row][col] == 1)
		return;

	else
	{
		image[row][col]=picked_color;
		visited[row][col]=1;
		/* There are 8 conditions (to be checked) for function calling */
		fill(init_color, picked_color, row-1, col, image, visited);
		fill(init_color, picked_color, row-1, col-1, image, visited);
		fill(init_color, picked_color, row-1, col+1, image, visited);
		fill(init_color, picked_color, row, col-1, image, visited);
		fill(init_color, picked_color, row, col+1, image, visited);
		fill(init_color, picked_color, row+1, col, image, visited);
		fill(init_color, picked_color, row+1, col-1, image, visited);
		fill(init_color, picked_color, row+1, col+1, image, visited);
		return;
	}
}


									/* Rotate and Copy/Paste Functions */
/* Rotate 'R'ight '90' degrees and copy_paste */
int rotate_R_90(int image[row_limit][col_limit], int c_row, int c_col, int p_row, int p_col, int N, int count){
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
			if (image[p_row+i][p_col+j] != image[c_row +N-j-1][c_col+i])
			{
				count++;
				image[p_row+i][p_col+j] = image[c_row +N-j-1][c_col+i];
			}else;
		}
	}
	return count;
}

/* Rotate 'L'eft '90' degrees and copy_paste */
int rotate_L_90(int image[row_limit][col_limit], int c_row, int c_col, int p_row, int p_col, int N, int count){
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
			if (image[p_row+i][p_col+j] != image[c_row+j][c_col+N-i-1])
			{
				count++;
				image[p_row+i][p_col+j] = image[c_row+j][c_col+N-i-1];
			}else;
		}
	}
	return count;
}

/* Rotate '180' degrees and copy_paste */
int rotate_180(int image[row_limit][col_limit], int c_row, int c_col, int p_row, int p_col, int N, int count){
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
			if (image[p_row+i][p_col+j] != image[c_row+N-i-1][c_col+N-j-1])
			{
				count++;
				image[p_row+i][p_col+j] = image[c_row+N-i-1][c_col+N-j-1];
			}
		}
	}
	return count;
}


int main(){
	/* General Variables */
	int image[row_limit][col_limit];
	int i, j;
	char op_code;

	/* Image Input */
	for (i = 0; i < row_limit; i++)
	{
		for (j = 0; j < col_limit; j++)
		{
			scanf("%d", &image[i][j]);
		}
	}
	
	scanf(" %c", &op_code);
	/* 
	It will be needed to declare new variables. 
	These new variables will be condition specified.
	It means there is no need to declare if a certain condition is not satisfied.
	
	Therefore, it can be better to use if-else instead of switch-case
	*/
	if (op_code == 'F') /* Part 1 */
	{
		/* Color Coordinates and Picked Color Code / Initial pixel coordinates and Initial Color */
		int color_row, color_col, picked_color, init_row, init_col, init_color;
		
		/* 
		I will use an additional array to check the place I am on.
		Initially it holds zeros.
		When I check the point if it is visited or not, it will provide me 0 or 1.
		If it is 0, I need to compute.
		If it is 1, I do not need to compute anything because the place is already visited.
		*/
		char visited[row_limit][col_limit]={{0}};
		
		scanf("%d %d", &color_row, &color_col);
		scanf("%d %d", &init_row, &init_col);


		/* Picking Color */
		/* 
		I need to pick color. Point can be both inside and outside.
		So, I need to check if it is inside or not. 
		
		If it is inside I will directly continue and pick color inside of image.
		If it is outside I will call my pick_color() function.
		*/
		if (color_row >= 0 && color_row <= row_limit-1 && color_col >= 0 && color_col <= col_limit-1)
			picked_color=image[color_row][color_col];
		else
			picked_color = pick_color(color_row, color_col);	

		/* Initial Color */
		init_color = image[init_row][init_col];
		
		/* Now, it is needed to call fill() function. */
		fill(init_color, picked_color, init_row, init_col, image, visited);
		/* After fill() do its job, I need to print the image */
		image_print(image);		
	}
	else if (op_code == 'P') /* Part 2 */
	{
		int copy_row_1, copy_col_1, copy_row_2, copy_col_2;
		int paste_row_1, paste_col_1, paste_row_2, paste_col_2;
		int count; /* To count how many pixels are changed */
		/*int row, col, i, j;*/
		int i, j;
		/*int copy_row_lim, copy_col_lim;*/
		/*int row_ore, col_ore;*/ /* Oreantation between top-left points of copy and paste area */
		
		int c_row, c_col, p_row, p_col, N_row, N_col;

		scanf("%d %d %d %d", &copy_row_1, &copy_col_1, &copy_row_2, &copy_col_2);
		scanf("%d %d %d %d", &paste_row_1, &paste_col_1, &paste_row_2, &paste_col_2);

		/* 
		It is needed to find left top coordinates of both copy and paste areas.
		The reason is that I will iterate by beginning from these points.
		To iterate, I need to find the copy area dimensions (length of edges).

		After finding all necessary variables, I am able to iterate them.
		*/

		/* Determining Left Top Coordinates of Copy and Paste Areas */
		c_row = (copy_row_1 < copy_row_2) ? copy_row_1:copy_row_2;
		c_col = (copy_col_1 < copy_col_2) ? copy_col_1:copy_col_2;

		p_row = (paste_row_1 < paste_row_2) ? paste_row_1:paste_row_2;
		p_col = (paste_col_1 < paste_col_2) ? paste_col_1:paste_col_2;
		
		/* Determining Copy Areas Dimensions. N_row: length of row edge, N_col: length of col edge */
		N_row = (copy_row_1 < copy_row_2) ? (copy_row_2-copy_row_1+1):(copy_row_1-copy_row_2+1);
		N_col = (copy_col_1 < copy_col_2) ? (copy_col_2-copy_col_1+1):(copy_col_1-copy_col_2+1);
			
		/* Copying and Pasting */		
		count = 0;
		for (i=0; i < N_row; i++)
		{
			for (j=0; j < N_col; j++)
			{
				if (image[c_row+i][c_col+j] != image[p_row+i][p_col+j])
				{
					image[p_row+i][p_col+j] = image[c_row+i][c_col+j];
					count++;
				}else;
			}
		}

		/* Printing Image and Count */
		image_print(image);
		printf("%d\n", count);		
	}
	else if (op_code == 'R') /* Part 3 */
	{
		char turn_letter;
		int turn_degree, N, count=0; /* N: copy_area_dimension (for loop limit) */
		int copy_left_row, copy_left_col, copy_right_row, copy_right_col;
		int paste_left_row, paste_left_col, paste_right_row, paste_right_col;

		scanf(" %c %d", &turn_letter, &turn_degree);
		scanf("%d %d %d %d", &copy_left_row, &copy_left_col, &copy_right_row, &copy_right_col);
		scanf("%d %d %d %d", &paste_left_row, &paste_left_col, &paste_right_row, &paste_right_col);

		N = copy_right_row - copy_left_row + 1;

		if (turn_degree == 0)
		{
			/* Directly Copy and Paste */
			for (i = 0; i < N; i++)
			{
				for (j = 0; j < N; j++)
				{
					if (image[paste_left_row+i][paste_left_col+j] != image[copy_left_row+i][copy_left_col+j]) 
					{
						count++;
						image[paste_left_row+i][paste_left_col+j] = image[copy_left_row+i][copy_left_col+j];
					}
				}
			}
		}
		else if (turn_degree == 180)
		{
			count = rotate_180(image, copy_left_row, copy_left_col, paste_left_row, paste_left_col, N, count);
		}
		else if ((turn_letter == 'R' && turn_degree == 90) || (turn_letter == 'L' && turn_degree == 270))
		{
			count = rotate_R_90(image, copy_left_row, copy_left_col, paste_left_row, paste_left_col, N, count);
		}
		else
		{
			count = rotate_L_90(image, copy_left_row, copy_left_col, paste_left_row, paste_left_col, N, count);
		}

		/* Printing Image and Count */
		image_print(image);
		printf("%d\n", count);
	}
	else printf("Problem in Op_code\n");
	
	return 0;	
}
