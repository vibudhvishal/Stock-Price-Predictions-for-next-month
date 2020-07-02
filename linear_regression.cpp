#include<stdio.h>
#include<math.h>
#include<stdlib.h>


float s_m=0, s_b=0, lr = 0.0001, s_cost=0;
int no_of_iteration=100000;

void predict(float X[][2], float y[], float y_pred[], int size, int col)
{
    int i=0;
    for(i=0;i<size;i++)
    {
        y_pred[i] = s_m*X[i][col] + s_b;
    }
}

float sum_d(float X[][2], float y[], float y_pred[], int size, int col)
{
    int i;
    float sum=0;
    for(i=0;i<size;i++)
    {
        sum = sum + (X[i][col]*(y[i] - y_pred[i]));
    }
    return sum;
}

float error_sum(float y[], float y_pred[], int size)
{
    float sum=0;
    int i;
    for(i=0;i<size;i++)
    {
        sum = sum + pow(y[i]-y_pred[i], 2);
    }
    return sum;
}
void grad_desc(float X_train[][2], float y[], float y_pred[], float n, int dim)
{
    float dm,db,sum=0;
    int size = n;
    FILE *fptr = fopen("sregression.csv","w");
    int i=1;
    while(i<=no_of_iteration)
    {
        predict(X_train, y, y_pred, size, 1);
        s_cost = (2/n)*error_sum(y, y_pred, size);
        dm = (-2/n)*sum_d(X_train, y, y_pred, size, 1);
        db = (-2/n)*sum_d(X_train, y, y_pred, size, 0);
        s_m = s_m - lr*dm;
        s_b = s_b - lr*db;
        
        fprintf(fptr,"%d", i);
        fprintf(fptr,"%c", '\t');
        fprintf(fptr,"%f", s_cost);
        fprintf(fptr,"%c", '\n');
        i++;
    }
    printf("m= %f, c = %f",s_m,s_b);

}

void spredict(float X_test[][2], float pred[], float n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        pred[i] = X_test[i][0]*s_b + X_test[i][1]*s_m;
    }
}

int main()
{
    float X[23][2]={{0,1},{0,2},{0,3},{0,4},{0,7},{0,8},{0,9},{0,10},{0,11},{0,14},{0,15},{0,16},{0,17},{0,18},{0,21},{0,22},{0,23},{0,24},{0,25},{0,28},{0,29},{0,30},{0,31}}; // For linear regression
    int i,j;

    int size,n=23;
    size=n;
     float pred[23],rmse=0,diff=0;
    for(i=0;i<size;i++)
    {
        X[i][0] = 1;
	pred[i]=0;
    }
     float y[] = {4997.55,4954.65,4901.50,4893.40,4925.55,4904.75,4918.75,4925.60,4935.95,4906.95,4912.10,4942.10,4919.90,4912.55,4884.85,4849.85,4856.85,4812.15,4815.40,4707.95,4653.30,4698.05,4675.05};
     grad_desc(X,y, pred, n,2);
     printf("\nTrue\t\tPredicted\tError\n");
      FILE *fptr1 = fopen("regressionline.csv","w");

     for(i=0;i<size;i++)
     {
     	printf("%f\t%f\t%f\n",y[i],pred[i],(y[i]-pred[i]));
	 diff = diff+pow(pred[i] - y[i],2);
	 rmse = sqrt(diff/n);
	 fprintf(fptr1,"%d", i);
        fprintf(fptr1,"%c", '\t');
        fprintf(fptr1,"%f", pred[i]);
        fprintf(fptr1,"%c", '\n');
     }
     	float y1 = s_m*32 + s_b;
	float y5 = s_m*34 + s_b;
	printf("Rmse is:%f\n",rmse);
	printf("the predicted opening value on 1st Feb is:%f\n",y1);
	printf("the predicted opening value on 5th Feb is:%f",y5);
    return 0;
}
