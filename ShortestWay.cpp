//
// Created by pc on 26/03/2023.
//
#include <vector>

using namespace std;
struct ShortestWay {
public:
    int id_depart;
    int id_arrivee;
   vector<int> nodes;

    int getIdDepart() const {
        return id_depart;
    }

    void setIdDepart(int idDepart) {
        id_depart = idDepart;
    }

    int getIdArrivee() const {
        return id_arrivee;
    }

    void setIdArrivee(int idArrivee) {
        id_arrivee = idArrivee;
    }

    const vector<int> &getNodes() const {
        return nodes;
    }
    vector<int> cloneNodesId(const vector<int> &nodesC) {
        vector<int> nodes;
        for_each(nodesC.begin(),nodesC.end(),[&nodes](int id){
            nodes.push_back(id);
        });
        return nodes;
    }
    void setNodes(const vector<int> &nodesC) {
        nodes = cloneNodesId(nodesC) ;
    }
};