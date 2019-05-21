#include "page.hpp"

#include <algorithm>
#include <assert.h>
#include <stdlib.h>

#include <iostream>

unsigned int partitionRand (std::vector<Resultat>& resultats_non_tries, unsigned int l, unsigned int r){
    unsigned int t =  rand()%(r-1-l + 1) + l;
    iter_swap(resultats_non_tries.begin() + l , resultats_non_tries.begin() + t);
    unsigned int j = l;
    for (unsigned int i = l + 1; i < r; i++){
        if (resultats_non_tries.at(i) < resultats_non_tries.at(l)){
            j++;
            iter_swap(resultats_non_tries.begin() + i, resultats_non_tries.begin() + j);
        }
    }
    iter_swap(resultats_non_tries.begin() + j, resultats_non_tries.begin() + l);
    return j;
}

Resultat selctionRec (std::vector<Resultat>& resultats_non_tries, unsigned int l, unsigned int r, unsigned int k){
    unsigned int s = partitionRand(resultats_non_tries, l, r);
    if (s-l == k) {  return resultats_non_tries.at(s); }
    if (s-l > k) {  return selctionRec(resultats_non_tries, l, s, k); }
    if (s-l < k) {  return selctionRec(resultats_non_tries, s+1, r, k-s+l-1); }
}

void quickSortRec (std::vector<Resultat>& resultats_non_tries, unsigned int l, unsigned int r){
    if( l < r){
        unsigned int s = partitionRand(resultats_non_tries, l, r);
        quickSortRec(resultats_non_tries, l, s);
        quickSortRec(resultats_non_tries, s+1, r);
    }
}


// Retourne les resultats d'une page
// Entrees:
//   resultats_non_tries: tous les resultats de recherche non tries
//   nombre_resultats_par_page: le nombre de resultats par page (sauf possiblement sur la derniere page)
//   numero_page: le numero de la page. La premiere page est la page numero 0.
// Sortie:
//   page: les resultats de recherche se trouvant sur la page demandee
void retournePage(const std::vector<Resultat>& resultats_non_tries, unsigned int nombre_resultats_par_page, unsigned int numero_page, std::vector<Resultat>& page) {
  assert(!resultats_non_tries.empty());
  assert(page.empty());
  assert(nombre_resultats_par_page > 0);
  assert(numero_page < (resultats_non_tries.size() + nombre_resultats_par_page - 1) / nombre_resultats_par_page);

  // Inserez votre code ici.
  //  - Vous ne pouvez pas modifier le vecteur resultats_non_tries, mais rien ne vous empeche de modifier une copie.
  //  - N'hesitez pas a definir d'autres fonctions (mais ne les declarez pas le .hpp)

    std::vector<Resultat> resultats_non_tries_copie(resultats_non_tries);
    unsigned int k = nombre_resultats_par_page * (numero_page+1) - nombre_resultats_par_page;
    unsigned int nombre_resultats = 0;
    if (resultats_non_tries_copie.size() - k > nombre_resultats_par_page){ nombre_resultats = nombre_resultats_par_page; }
    else { nombre_resultats = resultats_non_tries_copie.size() - k; }
    unsigned int l = 0;
    unsigned int r = resultats_non_tries_copie.size();

    k = nombre_resultats_par_page * (numero_page+1) - nombre_resultats_par_page;
    l = 0;
    r = resultats_non_tries_copie.size();

    Resultat debut = selctionRec(resultats_non_tries_copie, l, r, k);

    l = k;

    Resultat fin = selctionRec(resultats_non_tries_copie, l, r, nombre_resultats-1);

    r = k+nombre_resultats-1;

    quickSortRec(resultats_non_tries_copie, l, r);

    for (unsigned int i = 0; i < nombre_resultats; ++i){
        page.push_back(resultats_non_tries_copie.at(k));
        k++;
    }
}



