#include "arc.cpp"
#include "ShortestWay.cpp"

class Noeud {
private:
    Zone la_zone;
    int nombre_de_noeuds_suivants;
    arc les_noeuds_suivants[5];
    double score;
    vector<ShortestWay> shortest_way;
public:
    const Zone &getLaZone() const {
        return la_zone;
    }

    void setLaZone(const Zone &laZone) {
        la_zone = laZone;
    }

    double getScore() const {
        return score;
    }

    void setScore(double score1) {
        score = score1;
    }

    const vector<ShortestWay> &getShortestWay() const {
        return shortest_way;
    }

    void setShortestWay(const vector<ShortestWay> &shortestWay1) {
        shortest_way = cloneShortestWay(shortestWay1);
    }

    Zone getZone() const {
        return la_zone;
    }

    int getNombreDeNoeudsSuivants() const {
        return nombre_de_noeuds_suivants;
    }

    arc *getLesNoeudsSuivants() {
        return les_noeuds_suivants;
    }

    vector<ShortestWay> cloneShortestWay(vector<ShortestWay> shortestWay) {
        vector<ShortestWay> shortestWayC;
        for_each(shortestWay.begin(), shortestWay.end(), [&shortestWayC](ShortestWay sw) {
            ShortestWay swC;
            swC.setIdArrivee(sw.getIdArrivee());
            swC.setIdDepart(sw.getIdDepart());
            swC.setNodes(sw.getNodes());
            shortestWayC.push_back(swC);
        });
        return shortestWayC;
    }

    void setZone(Zone z) {
        la_zone = z;
    }

    void setNombreDeNoeudsSuivants(int nb) {
        nombre_de_noeuds_suivants = nb;
    }

    void setLesNoeudsSuivants(arc *arcs, int nb) {
        for (int i = 0; i < nb; i++) {
            les_noeuds_suivants[i] = arcs[i];
        }
        nombre_de_noeuds_suivants = nb;
    }

};
