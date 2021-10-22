#include <stdio.h>
#include <string.h>
void hacercosas(int vec1[],int elnum)
{
 //   int longitud = 0;
     int longitud = elnum;
    for (int t = 0; t<longitud;t++)
    {
        printf("\n %d",vec1[t]);
    }
}
int main() {
    int cosas[]={1,3,5,7,9,2,4,6,8,0};
    int numel = sizeof(cosas)/sizeof(cosas[0]);
    hacercosas(cosas,numel);
    return 0;
}
