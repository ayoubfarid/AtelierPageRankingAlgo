#include "zone.cpp"

struct arc{
    int idNoeudDestination; //L'identifiant d'un noeud suivant
    int poids;//Le poids jusqu'a ce noeud
    int getPoids() const {
        return poids;
    }
};
