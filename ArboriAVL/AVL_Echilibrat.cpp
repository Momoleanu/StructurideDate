Header.h
 
#pragma once
#include<iostream>
#include<vector>
using namespace std;
 
 
struct AVL {
    AVL* stg;
    int bf; //balance factor = h(stg)-h(drt)
    int data;
    AVL* drt;
};
 
void InitTree(AVL*& rad);
void Insert(AVL*& rad, int val);
void preordine(AVL* p);
void inordine(AVL* r);
void postordine(AVL* r);
void AfisNodInd(AVL* r, int nivel);
 
 
int testAVL(AVL* r);
int depth(AVL* r);
 
AVL* MakeNodAVL(int a);
void InserAVL(AVL*& r, int val);
void Echilibrare(AVL*& r, int val, bool stg);
void RSS(AVL*& r);
void RSD(AVL*& r);
void RDD(AVL*& r);
void RDS(AVL*& r);
 
void AfisareIndentata(AVL* r, int nivel);
void InordineRec(AVL* r);
void EliberareMemorie(AVL*& r);
 
///////////////
 
Functii.cpp
 
#include"Header.h"
 
bool EqRequired;
 
void InitTree(AVL*& rad)
{
    rad = 0;
}
 
AVL* MakeNod(int val)
{
    AVL* p;
    p = new AVL;
    p->data = val;
    p->stg = 0;
    p->drt = 0;
    return p;
}
 
void Insert(AVL*& rad, int val) {
    if (rad == 0) {
        rad = MakeNod(val);
    }
    else {
        if (val < rad->data) {
            Insert(rad->stg, val);
        }
        else if (rad->data == val) {
            cout << "Duplicat\n";
        }
        else {
            Insert(rad->drt, val);
        }
    }
}
 
void preordine(AVL* p)
{
    if (p)
    {
        cout << p->data << ' ';
        preordine(p->stg);
        preordine(p->drt);
    }
}
void inordine(AVL* r) {
    if (r) {
        inordine(r->stg);
        cout << r->data << " ";
        inordine(r->drt);
    }
}
void postordine(AVL* r) {
    if (r) {
        postordine(r->stg);
        postordine(r->drt);
        cout << r->data << " ";
 
    }
}
 
void AfisNodInd(AVL* r, int nivel)
{
    int i;
    for (i = 0; i < nivel; i++) cout << "\t";
    if (r == 0)     cout << "-\n";  //pun "-" pentru nod vid
    else
    {
        cout << r->data << endl;
        AfisNodInd(r->stg, nivel + 1);
        AfisNodInd(r->drt, nivel + 1);
    }
}
 
 
 
int depth(AVL* r)
{
    int as = 1, ad = 1;
 
    if (!r)
    {
        return 0;
    }
    else
    {
        as = as + depth(r->stg);
        ad = ad + depth(r->drt);
        return as < ad ? ad : as;
    }
}
 
int testAVL(AVL* r) //intoarce 0 daca este AVL
{
    int bf, n = 0;
 
    if (!r)
    {
        return 0;
    }
    else
    {
        bf = depth(r->stg) - depth(r->drt);
        if (bf == 1 || bf == -1 || bf == 0)
        {
            testAVL(r->stg);
            testAVL(r->drt);
            return n;
        }
        else
        {
            cout << "\n\t->Arborele r nu este AVL! ";
            cout << "\tTestul s-a oprit la nodul:\t" << r->data;
            return n + 1;
        }
    }
}
 
AVL* MakeNodAVL(int a)
{
    AVL* p = new AVL;
    p->data = a;
    p->stg = NULL;
    p->drt = NULL;
    p->bf = 0;
    return p;
}
 
void RSS(AVL*& r)
{
    AVL* b;
    b = r->drt;
    r->drt = b->stg;
    b->stg = r;
    r->bf = b->bf = 0;
    r = b; //b devine noua rad
}
 
void RSD(AVL*& r)
{
    AVL* b;
    b = r->stg;
    r->stg = b->drt;
    b->drt = r;
    r->bf = b->bf = 0;
    r = b;
}
 
void RDD(AVL*& r)
{
    AVL* b, * c;
    b = r->stg;
    c = b->drt;
    //se actualizeaza bf pentru starea finala
    switch (c->bf)
    {
    case 0:
        //h(t2s)=h(t2d) inainte de refacerea legaturilor
        r->bf = b->bf = 0; // inserarea echilibreaza
        break;
    case -1:
        //h(t2s)<h(t2d), initial, inainte de refacerea leg.
        r->bf = 0; //// deoarece h(T3)=h(t2d)
        b->bf = 1; // deorace h(T1)> h(t2s)
        break;
    case 1:
        //h(t2s)>h(t2d), initial, inainte de refacerea leg.
        r->bf = -1; // deoarece h(t2d)< h(T3)
        b->bf = 0; // // deoarece h(T1)=h(t2s)
        break;
    }
    r->stg = c->drt;
    b->drt = c->stg;
    c->bf = 0;
    c->drt = r;
    c->stg = b;
    r = c;
}
 
void RDS(AVL*& r)
{
    AVL* b, * c;
    b = r->drt;
    c = b->stg;
    switch (c->bf)
    {
    case 0:
        r->bf = b->bf = 0;
    case -1:
        r->bf = 0;
        b->bf = 1;
    case 1:
        r->bf = -1;
        b->bf = 0;
    }
    r->drt = c->stg;
    b->stg = c->drt;
    c->bf = 0;
    c->stg = r;
    c->drt = b;
    r = c;
}
 
void InserAVL(AVL*& r, int val)
{
    if (r == NULL)
    {
        r = MakeNodAVL(val);
        EqRequired = true;
    }
    else
    {
        if (val < r->data)
        {
            InserAVL(r->stg, val);
            Echilibrare(r, val, true);
        }
        else
        {
            if (val > r->data)
            {
                InserAVL(r->drt, val);
                Echilibrare(r, val, false);
            }
        }
    }
}
 
void Echilibrare(AVL*& r, int val, bool stg)
{
 
    if (EqRequired)
    {
        if (stg == true)
        {
            switch (r->bf)
            {
            case 1:
                EqRequired = false;
                (val < r->stg->data) ? RSD(r) : RDD(r);
                break;
            case 0:
                r->bf = 1;
                break;
            case -1: //inserarea in acest caz produce echilibru
                r->bf = 0;
                EqRequired = false;
                break;
            }
        }
        else
        {
            switch (r->bf)
            {
            case 1:
                r->bf = 0;
                EqRequired = false;
                break;
 
            case 0:
                r->bf = -1;
                break;
            case  -1:
                EqRequired = false;
                (val > r->drt->data) ? RSS(r) : RDS(r);
                break;
            }
        }
    }
}
 
 
void InordineRec(AVL* r)
{
    if (r != NULL)
    {
        InordineRec(r->stg);
        cout << r->data << " ";
        InordineRec(r->drt);
    }
}
 
