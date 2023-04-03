#include "graphe.cpp"


int main(){
    Graphe g ;
    //Génération
    //g.genererGraphe(g,10);
    g.genererGrapheV6(g,1000,-75.05,-70.05,35.00,37.0);
    //Sauvegarde
   /// g.sauvegarderGrapheDansFichier(g,"carte.txt");
    //Dijkstra
   //z g.dijkstra(74,45,g);
    // Calcul et affichage du PageRank
    Graphe g1=g.cloneGraphe(g);
    Graphe g2=g.cloneGraphe(g1);
    Graphe g3=g.cloneGraphe(g2);
    /*
    g1.getShortestWayBetweenAllNodesOfTheGrapheV2(g);
    cout<<"graphe size v1 :" << g1.getCarte().size() << endl;*/
    //Affichage

   // vector<pair<int, double>> pageRanks = g.pageRankV1(g,10,0.5);
    vector<pair<int, double>> pageRanks = g1.pageRankV3(g1,10,0.5);
    cout<<"graphe size :" << g1.getCarte().size() << endl;


    //g1.getShortestWayBetweenAllNodesOfTheGrapheV2(g1);
    //g1.getShortestWayBetweenNodesOfTheGrapheV2(g1,1);
    cout<<"graphe size v2 :" << g1.getCarte().size() << endl;

   // g2.addPageRankToNodes(g2,pageRanks);
    vector<int> chemin=g3.dijkstraV4(0,999,g3);


    vector<int>ch;
    g1.addShoortestWay(g3.getShortWay());

    g1.sauvegarderGrapheDansFichierJSONV2(g1,"./../PageRankingWeb/carte.json");
    cout<<"graphe adress :" << &g2 << endl;

}
