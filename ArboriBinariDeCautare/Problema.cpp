Header.h
 
#include<iostream>
using namespace std;
 
struct Nod{
    int data;
    Nod* stg;
    Nod* drt;
};
void InitTree(Nod*&root);
void Insert(Nod*&root, int val);
void BuildTree(Nod*&root);
Nod* MakeNod(int val);
 
void Preorder(Nod* root);
void Inorder(Nod*root);
void Postorder(Nod*root);
void IndentedListsing(Nod* root, int level);
 
void DeleteRoot(Nod*& root);
void Delete(Nod *&root, int val);
Nod* RemoveGreatest(Nod*& root);
 
Nod* Search(Nod* root, int val);
int SearchValue(Nod* root, int val);
 
void FreeMemory(Nod*& root);
 
bool MinimVal(Nod* rad, int &min);
bool MaximVal(Nod *rad, int &max);
 
/////////////
 
Functii.cpp
 
#include "Header.h"
 
 
void InitTree(Nod*& rad)
{
    rad = 0;
}
 
void BuildTree(Nod*& rad)
{
    int val;
    cout << "\n val=";
    cin >> val;
    while (val)
    {
        Insert(rad, val);
        cout << "\n val=";
        cin >> val;
    }
}
 
Nod* MakeNod(int val)
{
    Nod* p;
    p = new Nod;
    p->data = val;
    p->stg = 0;
    p->drt = 0;
    return p;
}
 
 
void Insert(Nod* &rad, int val)
{
    if (rad == NULL)
        rad = MakeNod(val);
    else if (val < rad->data)
        Insert(rad->stg, val);
    else if (val == rad->data)
        cout << "Duplicat";
    else
        Insert(rad->drt, val);
}
 
 
void Inorder(Nod* rad)
{
    if (rad)
    {
        Inorder(rad->stg);
        cout << rad->data <<" ";
        Inorder(rad->drt);
    }
}
 
 
void Preorder(Nod* rad)
{
    if (rad)
    {
        cout << rad->data << " ";
        Preorder(rad->stg);
        Preorder(rad->drt);
    }
}
 
 
void Postorder(Nod* rad)
{
    if (rad)
    {
        Postorder(rad->stg);
        Postorder(rad->drt);
        cout << rad->data << " ";
    }
}
 
 
Nod* Search(Nod *rad, int val)
{
    if (rad)
        if (rad->data == val)
            return rad;
        else if (rad->data > val)
            Search(rad->stg, val);
        else
            Search(rad->drt, val);
    else
        return 0;
 
}
 
 
int SearchValue(Nod *rad, int val)
{
    if (rad)
        if (rad->data == val)
            return 1;
        else if (rad->data > val)
            Search(rad->stg, val);
        else
            Search(rad->drt, val);
    else
        return 0;
 
}
 
void Delete(Nod* &rad, int val)
{
    if (rad)
        if (rad->data == val)
            DeleteRoot(rad);
        else if (rad->data < val)
            Delete(rad->drt, val);
        else if (rad->data > val)
            Delete(rad->stg, val);
        else
            cout << "Valoarea nu exista in arbore";
}
 
 
void DeleteRoot(Nod* &rad)
{
    int val = 0;
    Nod *p;
    p= MakeNod(val);
    if (rad)
        if (rad->stg == NULL)
        {
            p = rad->drt;
            delete rad;
            rad = p;
        }
        else if (rad->drt == NULL)
        {
            p = rad->stg;
            delete rad;
            rad = p;
        }
        else
        {
            p = RemoveGreatest(rad->stg);
            p->stg = rad->stg;
            p->drt = rad->drt;
            delete(rad);
            rad = p;
        }
}
 
 
Nod* RemoveGreatest(Nod* &rad)
{
    Nod *p;
    if (rad)
        if (rad->drt == NULL)
        {
            p = rad;
            rad = rad->stg;
            return p;
        }
        else
            return RemoveGreatest(rad->drt);
    else
        return 0;
}
 
 
void FreeMemTree(Nod* &rad)
{
    Nod *p;
    if (rad)
    {
        p = rad;
        FreeMemTree(rad->stg);
        FreeMemTree(rad->drt);
        delete p;
        p = 0;
    }
 
}
 
bool MinimVal(Nod* rad, int &min)
{
    if (rad)
    {
        min = rad->data;
        MinimVal(rad->stg, min);
        return 1;
    }
    else
        return 0;
}
 
 
bool MaximVal(Nod* rad, int &max)
{
    if (rad)
    {
        max = rad->data;
        MaximVal(rad->drt, max);
        return 1;
    }
    else
        return 0;
}
////////////////////
 
Main.cpp
 
#include "Header.h"
 
int main()
{
    Nod *rad;
    Nod* searched=NULL;
    int val1, val2, val3, val4;
 
    cout << "\n Initializare…";
    InitTree(rad);
 
    BuildTree(rad);
 
 
    cout << "\n Afisare in \n \t Inordine : ";
    Inorder(rad);
    cout << endl;
 
    cout << "\n Afisare in \n \t Preordine : ";
    Preorder(rad);
    cout << endl;
 
    cout << "\n Afisare in \n \t Postordine : ";
    Postorder(rad);
    cout << endl;
 
    if (MinimVal(rad, val1))
        cout << "\n Valoarea minima din arbore - " << val1;
    if (MaximVal(rad, val1))
        cout << "Valoarea maxima din arbore - " << val1;
 
    cout << "\n val cautata( o val care exista in arbore)- ";
    cin >> val2;
 
    searched = Search(rad, val2);
    if (searched)
        cout << "\nA fost gasit nodul ce contine valoarea " << searched->data << "\n";
    else
        cout << "\n Nu a fost gasit nici un nod care sa contina valoarea " << val2<< "\n";
 
    cout << "\n val cautata( o val care nu exista in arbore)-";
    cin >> val3;
 
    if(SearchValue(rad, val3))
        cout << "\nA fost gasit nodul ce contine valoarea" << searched->data << "\n";
    else
        cout << "\n Nu a fost gasit nici un nod care sa contina valoarea" << val3 << "\n";
 
 
    cout << "\n\n\n Afisare indentata\n";
 
    /*cout << endl << endl;
    cout << "\n Stergeri:";
    cout << "\n val de sters";
    cin >> val4;
    DeleteRoot(rad, val4);
 
    cout << "Stergere valoarea 1234:";
    DeleteNod(rad, 1234);
    cout << endl << endl << "Dupa stergere:\n";
    cout << endl;
 
    cout << "Eliberare memorie:";
    FreeMemTree(rad);
    rad = NULL;
    cout << endl << endl;
    */
 
    system("PAUSE");
    return 0;
}
 
///////////
