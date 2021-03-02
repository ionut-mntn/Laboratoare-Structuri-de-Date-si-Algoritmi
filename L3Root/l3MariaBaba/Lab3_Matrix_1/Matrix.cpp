#include "Matrix.h"
#include <exception>
#include <iostream>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    //TODO - Implementation
    // best case = worst case = avg case -> Θ(1)
    NrColoane = nrCols;
    NrLinii = nrLines;
    cap = (NrLinii + NrColoane) * 2;
    matrix = new SLLANode[cap];
    lungime_curenta = NrColoane + NrLinii + 1;
    first_empty = lungime_curenta;

    SLLANode current_linie;
    current_linie.val = NULL_TELEM;
    current_linie.pozitie_coloana = current_linie.next_col = -1;

    SLLANode current_col;
    current_col.val = NULL_TELEM;
    current_col.next_linie = current_col.pozitie_linie = -1;

    for(int i=0; i<NrLinii; i++) // initializez head-urile pt linii
    {
        if(i == NrLinii-1)
        {
            current_linie.pozitie_linie = i;
            current_linie.next_linie = -1;
            matrix[i] = current_linie;
        }
        else{
            current_linie.pozitie_linie = i;
            current_linie.next_linie = i+1;
            matrix[i] = current_linie;
        }

    }

    for (int j = 0; j < NrColoane; j++)  // initializez head-urile pentru coloane
    {
        if(j == NrColoane -1)
        {
            current_col.pozitie_coloana = j;
            current_col.next_col = -1;
            matrix[NrLinii+j] = current_col;

        }
        else{
            current_col.pozitie_coloana = j;
            current_col.next_col = j+1;
            matrix[NrLinii+j] = current_col;
        }

    }

    SLLANode head;
    head.val = NULL_TELEM;
    head.pozitie_linie = -1;
    head.next_linie = matrix[0].pozitie_linie; // head-ul principa "pointeaza" spre prima linie
    head.next_col = matrix[NrLinii].pozitie_coloana; // head-ul principa "pointeaza" spre prima coloana
    head.pozitie_coloana = -1;
    matrix[NrLinii + NrColoane] = head;
   // cout<<matrix[NrLinii+NrColoane].next_col;

}


int Matrix::nrLines() const {
    //TODO - Implementation
    //  best case = worst case = avg case -> Θ(1)
    if(NrLinii> 0)
        return NrLinii;
    return 0;
}


int Matrix::nrColumns() const {
    //TODO - Implementation
    //  best case = worst case = avg case -> Θ(1)
    if(NrColoane > 0)
        return NrColoane;
    return 0;
}


TElem Matrix::element(int i, int j) const {
    //TODO - Implementation
    if (i> NrLinii || j>NrColoane  || i<0 || j<0) // verific daca (i,j) este o pozitie valida in matrice
    {
        exception ex;
        throw ex;
    }

    if(lungime_curenta == NrColoane + NrLinii + 1) // verific daca in matrice mai am elemente pe langa head-uri
       return NULL_TELEM;

    for (int k = NrLinii + NrColoane; k <= lungime_curenta; k++)
    {
        if(matrix[k].pozitie_coloana == j && matrix[k].pozitie_linie == i)
            return matrix[k].val;
    }
    return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
 //TODO - Implementation
    cout << "intra " << i << " " << j << '\n';
    cin.get();

    SLLANode new_elem;
    new_elem.val = e;
    new_elem.pozitie_linie = i;
    new_elem.pozitie_coloana = j;

   if (i> NrLinii || j>NrColoane || i<0 || j<0) // verific daca (i,j) este o pozitie valida in matrice
    {
        exception ex;
        throw ex;
    }

   //resize
    if (lungime_curenta == cap)
    {
        cout << "S-A FACUT SI RESIZE!!!\n";
        SLLANode* aux;
        cap = cap *2;
        aux = new SLLANode[cap];
        for (int it = 0; it < lungime_curenta; it++)
        {
            aux[it] = matrix[it];

        }
        cout << "iese\n";
        delete matrix;
        matrix = aux;
    }

    if (lungime_curenta == NrColoane + NrLinii + 1) // daca matricea este "goala"
    {
        cout << "matricea a fost goala\n";
        if (e == NULL_TELEM) // val noua =0 => nu fac nimic
            return NULL_TELEM;
        else // noul element trebuie adaugat
        {
            matrix[i].next_col = new_elem.pozitie_coloana;
            new_elem.next_col = matrix[i].pozitie_coloana;
            matrix[NrLinii + j].next_linie = new_elem.pozitie_linie;
            new_elem.next_linie = matrix[NrLinii + j].pozitie_coloana;
            matrix[lungime_curenta] = new_elem;
            lungime_curenta++;

            first_empty++;
            return NULL_TELEM;
        }
    }
    else if (element(i,j) != NULL_TELEM && e != NULL_TELEM) // exista deja un element pe poz(i,j) si val lui trebuie modificata cu e != Null_TElem
    {
        cout << "matricea nu a fost goala2\n";
        int old_val;
        for (int k = NrColoane + NrLinii; k <= lungime_curenta; k++)
            if(matrix[k].pozitie_coloana == j && matrix[k].pozitie_linie == i)
            {
                old_val = matrix[k].val;
                matrix[k].val = e;
                return  old_val;
            }
    }
    else if(element(i,j) != NULL_TELEM && e == NULL_TELEM) //pe pozitia (i,j) exista o val, dar e = Null_TElem => elem de pe poz (i,j) trebuie sters
    {
        cout << "matricea nu a fost goala3\n";
        SLLANode current1, current2;
        current1  = matrix[i]; // initializez current1 cu head-ul liniei i
        current2 = matrix[NrLinii+j]; // current2 cu head-ul coloanei j
        int old_val;
        while(current1.pozitie_coloana <= j-1)
        {
            current1.pozitie_coloana = current1.next_col;

        }
        // ies din while cand current1 se afla cu o coloana inainte de coloana j

        while(current2.pozitie_linie <= i-1)
        {
            current2.pozitie_linie = current2.next_linie;
        }
        // ies din while cand current2 se afla cu o linie inainte de linia i

        for (int k =NrLinii+NrColoane; k <= lungime_curenta; k++) // caut elementul de pe pozitia (i,j)
            if(matrix[k].pozitie_coloana == j && matrix[k].pozitie_linie == i) // elementul cautat = matrix[k]
            {
                first_empty = k;
                old_val = matrix[k].val;
                current1.next_col = matrix[k].next_col;
                current2.next_linie= matrix[k].next_linie;
                lungime_curenta --;
                return old_val;
            }
    }
    else if(element(i,j) == NULL_TELEM && e!= NULL_TELEM)//nu am un element pe pozitia(i,j), e este nenul => trebuie sa adaug un nou elemet in matrice
    {
        cout << "matricea nu a fost goala4\n";
        SLLANode current1, current2, current1_next, current2_next;
        current1 = matrix[i]; // initializez current1 cu head-ul liniei i
        current1_next = matrix[i];
        current2 = matrix[NrLinii + j]; // current2 cu head-ul coloanei j
        current2_next = matrix[NrLinii +j];
        cout << "trece1\n";

        if (matrix[i].next_col == -1) // nu mai am elemente pe linia resectiva
        {
            matrix[i].next_col = new_elem.pozitie_coloana;
            new_elem.next_col = matrix[i].pozitie_coloana;
            cout << "trece2\n";
        } 
        else 
        { // mai am elemente pe linia i
            cout << "trece3\n";
            cout << current1.pozitie_coloana << '\n';
            cout << "ok\n";
            cin.get();
            while (current1.pozitie_coloana <= j - 1)
            {
                current1.pozitie_coloana = current1.next_col;
                
                // AFISARE DE PROBA
                cout << current1.pozitie_coloana << " " << current1.next_col << '\n';
                cin.get();
                // FAC cin.get() doar ca sa nu dispara imediat de pe ecran ce se afiseaza si sa 
                // se tot afiseze cand apas eu enter
            }
            cout << "DE ASTA NU MAI TRECE\n";
            // ies din while cand current1 se afla cu o coloana inainte de coloana j
            current1_next.pozitie_coloana = current1.next_col;
            // current1_next se afla cu o coloana dupa coloana j
            current1.next_col = new_elem.pozitie_coloana;
            new_elem.next_col = current1_next.pozitie_coloana;
            cout << "trece4\n";
        }
        if(matrix[NrLinii+j].next_linie == -1) //nu mai am elemente pe coloana respectiva
        {
            matrix[NrLinii+j].next_linie = new_elem.pozitie_linie;
            new_elem.next_linie = matrix[NrLinii+j].pozitie_linie;
            cout << "trece5\n";
        }else{ // mai am elemente pe coloana j
            while(current2.pozitie_linie <=i-1)
                current2.pozitie_linie = current2.next_linie;
            // ies din while cand current2 se afla cu o linie inainte de linia i
            current2_next.pozitie_linie = current2.next_linie;
            // current2_next se afla cu o linie dupa linia i
            current2_next.next_linie = new_elem.pozitie_linie;
            new_elem.next_linie = current2_next.pozitie_linie;
            cout << "trece6\n";
        }
        matrix[lungime_curenta] = new_elem;
        lungime_curenta++;
        return NULL_TELEM;
    }

    return NULL_TELEM;
}


