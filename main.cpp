#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include "Library.hpp"
using namespace std;
int main()
{
    contact c[10000];
    char s[100];
    printf("Enter file name: ");
    scanf("%s",s);
    int x,n=LOAD(c,s);
    n--;
    //cout<<endl<<n<<endl;
    char z;
    bool flag=false;
    while (1)
    {
        printf("\n\nMain Menu\n\n\t");
        printf("Please choose one of the following option by entering its number:\n\n");
        printf("1.Load contact from file\n2.Search for a contact\n3.Add a new contact\n4.Modify a contact\n5.Delete a contact\n6.Print all data\n7.Save data\n0.Quit program\n\n your Choice is: ");
        scanf("%d",&x);
        printf("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n");
        switch (x)
        {
        case 1:
            printf("Enter file name: ");
            scanf("%s",s);
            n=LOAD(c,s);
            n--;
            break;
        case 2:
            show(c,n);
            break;
        case 3:
            n=ADD(c,n);
            flag=true;
            break;
        case 4:
            modify(c,n,&flag);
            break;
        case 5:
            n=del(c,n,&flag);
            break;
        case 6:
            printAll(c,n);
            break;
        case 7:
            save(c,n,s);
            flag=false;
            break;
        case 0:
            if(flag)
            {
                scanf("%c",&z);
                printf(" The data has not been saved. Do you want to save? (y/n)\n");
                scanf("%c",&z);
                if(z=='y'||z=='Y')  save(c,n,s);
            }
            return 0;
            break;
        default:
            printf("NOt valid Number\n");
        }
         printf("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n");
    }
    return 0;
}
