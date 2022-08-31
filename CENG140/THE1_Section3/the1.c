#include <stdio.h>
#include <math.h>

int main(){
	/* General Variables */
	double present_x=0;
	double total_time=0;
	double delta_t, speed;	
	int n, i;
	
	/* Variables used in for loop */
	double x_i, current_i;
	double x_next, current_next;
	double alpha_i=0; /* It is zero because alpha_0 is zero */
	double alpha_next;
	double current;

	int flag;
	
	scanf("%lf %lf", &delta_t, &speed);
	scanf("%d", &n);
	scanf("%lf %lf", &x_i, &current_i);
	for (i = 0; i < n; i++)
	{
		scanf("%lf %lf", &x_next, &current_next);

		alpha_next = (-alpha_i) + 2*((current_next-current_i)/(x_next-x_i));

		flag=1;
		while(flag)
		{
			if (present_x >= x_next)
			{
				flag=0;
				break;
			}
			else
			{			
			/* current from spline formula */
			current = current_i + alpha_i*(present_x-x_i) + (((alpha_next-alpha_i)/(2*(x_next-x_i)))*((present_x-x_i)*(present_x-x_i)));
			
			/*printf("%f %f\n", present_x, current);*/
			present_x += (sqrt(pow(speed, 2)-pow(current, 2)))*delta_t;
			total_time += delta_t;
			}
		}
		alpha_i = alpha_next;
		x_i = x_next;
		current_i = current_next;
	}
	printf("%f\n", total_time);
	return 0;
}