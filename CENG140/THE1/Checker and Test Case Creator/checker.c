#include <stdio.h>
#define row_limit 25
#define col_limit 25


int main(){
	int i, j, flag=0;
	int output[row_limit][col_limit];
	int expected_output[row_limit][col_limit];
	
	for (i = 0; i < row_limit; i++)
	{
		for (j = 0; j < col_limit; j++)
		{
			scanf("%d", &output[i][j]);
		}
	}


	for (i = 0; i < row_limit; i++)
	{
		for (j = 0; j < col_limit; j++)
		{
			scanf("%d", &expected_output[i][j]);
		}
	}

	for (i = 0; i < row_limit; i++)
	{
		if (flag) break;
		for (j = 0; j < col_limit; j++)
		{
			if (output[i][j] != expected_output[i][j])
			{
				flag = 1;
				printf("Erro Points: %d %d\n", i, j);
				break;
			}
		}
	}

	if (flag) printf("Error Occured\n");
	else printf("Done!\n");

	return 0;
}
