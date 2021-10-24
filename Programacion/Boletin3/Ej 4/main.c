#define longitud 20
#include <stdio.h>
void burbuja(int arr[],int longit);
int main()
{
    int vec[]={1,2,6,9,8,7,5,8,9,6,5,4,88,5,6,9,8,5,14,0};
    burbuja(vec,longitud);
    for(int i=0; i<longitud;i++)
    {
        printf(" %i",vec[i]);
    }
    return 0;
}
void burbuja(int arr[],int longit)
{
    for(int i = 0;i<longit;i++)
    {
        for (int h= 0; h<longit-1;h++)
        {
            int camb=0;
            if(arr[h]>arr[h+1])
            {
                camb = arr[h];
                arr[h]=arr[h+1];
                arr[h+1]=camb;
            }

        }
    }
}