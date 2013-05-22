#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void sortVstavkaInt(int size, int *array);
void sortVstavkaChar(int size, char *array);
void print_arrInt(int N,int *array);
void print_arrChar(int N,char *array);
void initArr(int N,int *array);
int i_pow(int v, int p);

int i_pow(int v, int p)//Возведение в числа v в степень p перемножением.
{
    if(p<0) return 0;

    int i, rez=1;
    for(i=0; i<p; ++i) rez*=v;
    return rez;
}

void sortVstavkaInt(int size, int *array)
{
    int i, j, temp;
    for (i = 1; i < size; i++)
    {
        temp = array[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (array[j] < temp)
                break;
            array[j+1] = array[j];
            array[j]= temp;
        }
    }

}

void sortVstavkaChar(int size, char *array)
{
    int i, j, temp;
    for (i = 1; i < size; i++)
    {
        temp = array[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (array[j] < temp)
                break;
            array[j+1] = array[j];
            array[j]= temp;
        }
    }

}

void print_arrInt(int N,int *array)
{
    int i;
    for(i=0; i<N; i++) printf(" %i ",array[i]);
    printf("\n");
}

void print_arrChar(int N,char *array)
{
    int i;
    for(i=0; i<N; i++)
        printf(" %c ",array[i]);
    printf("\n");
}

void initArrInt(int N,int *array)
{
    int i;
    for(i=0; i<N; ++i) array[i]=rand()%360;
}

void initArrChar(int N,char *array)
{
    int i;
    for(i=0; i<N; ++i)
        array[i]=rand()%39+61;
}

void merge( int *a, int *b, int *c, int m, int n )
{
    int i = 0, j = 0, k = 0;
    while (i < m && j < n)
    {
        if( a[i] < b[j] )
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    }
    while ( i < m )
        c[k++] = a[i++];
    while ( j < n )
        c[k++] = b[j++];
}

void mergeSort(int size, int *array)
{
    int i,j;

    int *w =calloc(size,sizeof(int));//Указатель на промежуточный массив.
    int *b1=array;//Промежуточный массив из которого берутся данные.
    int *b2=w;//Промежуточный массив в который вставляются данные.

    i=1;
    int num=0;//количество шагов сортировки
    
    while(i<size) i=i*2, ++num;
    
    printf("num=%d\n",num);

    for(i=0; i<num; ++i)
    {
        int numElem=i_pow(2,i);//количество элементов в группах сравнений
        int numDel=size/i_pow(2,i+1);
        printf("numDel=%d\n",numDel);
	
        for(j=0; j<numDel; ++j)
        {
            int startArr1=2*j*numElem;		//Смещение от первой части массива b1
            int startArr2=2*j*numElem+numElem;	//Смещение от второй части массива b1
            int startArr3=2*j*numElem;		//Смещение от начала результирующего массива b2
            printf("i=%d ,j=%d startArr1=%d startArr2=%d\n",i,j,startArr1,startArr2);
	    
            merge(b1+startArr1,b1+startArr2,b2+startArr3,numElem,numElem);

            print_arrInt(size,b1); print_arrInt(size,b2);
        }
        int *b3=b2;
        b2=b1;
        b1=b3;//Перестановка буферов местами
    }
    if(array==b2)
        for(i=0; i<size; ++i)
            array[i]=b1[i];
    free(w);
}

int main ()
{
    int N=25;
    int arr[N];
    char brr[N];
    int i=0;
    clock_t start,end;
    double t;
    int n=1000000;
    int stime;
    long ltime;

    ltime=time(NULL);
    stime=(unsigned)ltime/2;
    srand(stime);

    initArrInt(N,arr);
    initArrChar(N,brr);

    /*
    	printf("Method of sorting(int)\n");
    	print_arrInt(N,arr);

    	start=clock();
    	for(i=0;i<n;++i)
    		{
    			sortVstavkaInt(N,arr);
    		}
    	end=clock();
    	t=(end-start)*1.0/CLOCKS_PER_SEC;
    	print_arrInt(N,arr);
    	printf("Time for sum int=%f\n",t);

    	printf("\n");
    	printf("Method of sorting(char)\n");
    	print_arrChar(N,brr);


    	start=clock();
    	for(i=0;i<n;++i)
    	{
    		sortVstavkaChar(N,brr);
    	}
    	end=clock();
    	t=(end-start)*1.0/CLOCKS_PER_SEC;
    	print_arrChar(N,brr);
    	printf("Time for sum int=%f\n",t);*/

    print_arrInt(N,arr);
    mergeSort(N,arr);
    print_arrInt(N,arr);
    return 0;
}