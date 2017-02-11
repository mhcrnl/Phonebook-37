#ifndef LIBRARY_HPP_INCLUDED
#define LIBRARY_HPP_INCLUDED
#include <iostream>
#include <string>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;
typedef struct
{
    char st[100];
    char flat[100];
    char city[100];
} adressform;
typedef struct
{
    char fname[100];
    char lname[100];
    adressform address;
    char phone[100];
    char email[100];
} contact;
char* scan()
{
    char *str=(char*)malloc(100);
    int i=0;
    str[0]='a';
    do
    {
        scanf ("%c",&str[i]);
        i++;
    }
    while (str[i-1]!='\n');
    str[i-1]='\0';
    return str;
}
void to_lwr(char *str)
{
    int n=strlen(str); for (int i=0;i<n;i++) if ((str[i]<='Z')&&(str[i]>='A')) str[i]+=32;
}
void to_capital(char *m)
{
    to_lwr(m);
    if((*m>='a')&&(*m<='z'))
        m[0]-=32;
}
int LOAD(contact*c, char *filename)
{
    int i=0;
    FILE*fp=fopen(filename,"r");
    if(fp==NULL)
    {
        fp=fopen(filename,"w");
        printf("The file was not found. New blank file is created.\n");
        fclose(fp);
        fp=fopen(filename,"r");
    }
    while(!feof(fp))
    {
        char z;
        fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s%c",(c+i)->fname,(c+i)->lname,(c+i)->address.st,(c+i)->address.flat,(c+i)->address.city,(c+i)->phone,(c+i)->email,&z);
        to_capital((c+i)->fname);
        to_capital((c+i)->lname);
        i++;
    }
    fclose(fp);
    return i;
}
int validName(char*name)
{
    int i;
    for(i=0; i<strlen(name); i++)
    {
        if(!(name[i]>='a'&&name[i]<='z')&&!(name[i]>='A'&&name[i]<='Z'))
        {
            printf("Invalid.\n");
            return 0;
        }
    }
    return 1;
}
int validNumber(char*number)
{
    int i;
    for(i=0; i<strlen(number); i++)
    {
        if(!isdigit(number[i]))
        {
            printf("Invalid.\n");
            return 0;
        }
    }
    return 1;
}
int validEmail(char*email)
{
    int i;
    int c1=0,c2=0;
    for(i=0; i<strlen(email); i++)
    {
        if(email[i]=='@')
        {
            c1++;
        }
        if(email[i]=='.')c2=1;
        if(email[i]==' ')
        {
            printf("Invalid.\n");
            return 0;
        }
    }
    if(c1==1&&c2==1)return 1;
  printf("Invalid.\n"); return 0;
}
int ADD(contact *c,int n)
{
    int i=n;
    char z;
    do
    {
        puts("Enter first name.");
        scanf("%s",(c+i)->fname);
        to_capital((c+i)->fname);
    }
    while(!validName((c+i)->fname));
    do
    {
        puts("Enter last name.");
        scanf("%s",(c+i)->lname);
        to_capital((c+i)->lname);
        scanf("%c",&z);
    }
    while(!validName((c+i)->lname));
    puts("Enter street.");
    char *T=scan();
    //T[strlen(T)-1]='\0';
    strcpy(c[i].address.st,T);
    do
    {
        puts("Enter flat number.");
        scanf("%s",(c+i)->address.flat);
        scanf("%c",&z);
    }
    while(!validNumber((c+i)->address.flat));
    do
    {
        puts("Enter city.");
        scanf("%s",(c+i)->address.city);
    }
    while(!validName((c+i)->address.city));
    do
    {
        puts("Enter phone number.");
        scanf("%s",(c+i)->phone);
    }
    while(!validNumber((c+i)->phone));
    do
    {
        printf("Enter email.\n");
        scanf("%s",(c+i)->email);
    }
    while(!validEmail((c+i)->email));
    n++;
    return n;
}
void printU(contact c)
{
    cout<<"Name: "<<c.fname<<" "<<c.lname<<endl;
    cout<<"Address: "<<"flat "<<c.address.flat<<", "<<c.address.st<<", "<<c.address.city<<endl;
    cout<<"Phone: "<<c.phone<<endl;
    cout<<"E-mail: "<<c.email<<endl<<endl;
    return;
}
int query(contact *c, int n)
{
    cout<<"Enter first name: ";
    char f[100];
    cin>>f;
    to_capital(f);
    vector <int> found;
    for (int i=0; i<n; i++) if (strcmp(f,c[i].fname)==0) found.push_back(i);
    if (found.size()==0)
    {
        cout<<"No one found"<<endl;
        return -1;
    }
    if (found.size()==1) return found[0];
    cout<<"The following was found, choose his number to modify/delete/show: "<<endl;
    for (int i=0; i<found.size(); i++)
        cout<<i+1<<"-"<<c[found[i]].fname<<" "<<c[found[i]].lname<<endl;
    int C;
    cout<<endl<<"The chosen contact is # ";
    cin>>C;
    char j;
    scanf("%c",&j);
    return found[C-1];
}
void show(contact *c, int n)
{
    int i=query(c,n);
    if (i==-1) return;
    printU(c[i]);
    return;
}
int del(contact *c, int n,bool *flag)
{
    int x=query(c,n);
    cout<<"Contact to delete is:"<<endl<<endl;
    printU(c[x]);
    cout<<"Are you sure you want to delete? (y/n)"<<endl;
    char C;
    cin>>C;
    if ((C=='y')||(C=='Y'))
    {
        c[x]=c[n-1];
        *flag=true;
        n--;
    }
    return n;
}
bool cmp(contact a, contact b)
{
    if (strcmp(a.fname,b.fname)<0) return true;
    if (strcmp(a.fname,b.fname)>0) return false;
    if (strcmp(a.lname,b.lname)<0) return true;
    if (strcmp(a.lname,b.lname)>0) return false;
}
void printAll(contact *c, int n)
{
    sort (c,c+n,cmp);
    for (int i=0; i<n; i++)
        printU(c[i]);
    return;
}
void save(contact* m,int n, char* filename)
{
    int i;
    FILE* f;
    f=fopen(filename,"w");
    sort (m,m+n,cmp);
    for(i=0; i<n; i++)
    {
        fprintf(f,"%s,%s,%s,%s,%s,%s,%s\n",m[i].fname,m[i].lname,m[i].address.st,m[i].address.flat,m[i].address.city,m[i].phone,m[i].email);
    }
    fclose(f);
    printf("The changes had been saved.\n\n");
}
void modify(contact* m,int n,bool *flag)
{
    int x=query(m,n);
    if (x==-1) return;
    char *f;
    scanf("%c",&f);
    printU(m[x]);
    cout<<"Press the enter button to leave data unmodified"<<endl;
    do
    {
        cout<<"Enter new first name: ";
        f=scan();
        if((f[0]!='\n')&&(f[0]!='\0'))
        {
            to_capital(f);
            strcpy(m[x].fname,f);
            *flag=true;
        }
        else break;
    }
    while(!validName(m[x].fname));
    do
    {
        cout<<"Enter new last name: ";
        f=scan();
        if((f[0]!='\n')&&(f[0]!='\0'))
        {
            to_capital(f);
            strcpy(m[x].lname,f);
            *flag=true;
        }
        else break;
    }
    while(!validName(m[x].lname));
    do
    {
        cout<<"Enter new flat number: ";
        f=scan();
        if((f[0]!='\n')&&(f[0]!='\0'))
        {
            strcpy(m[x].address.flat,f);
            *flag=true;
        }
        else break;
    }
    while(!validNumber(m[x].address.flat));
    cout<<"Enter new street: ";
    char v[100];
    char b[100];
    scanf("%c",&b[0]);
    b[1]='\0';
    if(b[0]!='\n')
    {
        gets(v);
        strcat(b,v);
        strcpy(m[x].address.st,b);
        *flag=true;
    }
    do
    {
        cout<<"Enter new city: ";
        f=scan();
        if((f[0]!='\n')&&(f[0]!='\0'))
        {
            strcpy(m[x].address.city,f);
            *flag=true;
        }
        else break;
    }
    while(!validName(m[x].address.city));
    do
    {
        cout<<"Enter new phone number: ";
        f=scan();
        if((f[0]!='\n')&&(f[0]!='\0'))
        {
            strcpy(m[x].phone,f);
            *flag=true;
        }
        else break;
    }
    while(!validNumber(m[x].phone));
    do
    {
        cout<<"Enter new E-mail: ";
        f=scan();
        if((f[0]!='\n')&&(f[0]!='\0'))
        {
            strcpy(m[x].email,f);
            *flag=true;
        }
        else break;
    }
    while(!validEmail(m[x].email));
    return;
}
#endif // LIBRARY_HPP_INCLUDED
