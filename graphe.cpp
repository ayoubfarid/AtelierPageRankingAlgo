#include "noeud.cpp"


class Graphe {
private:
    queue<Noeud> la_carte;
    vector<pair<int,double>> pageRanks;
    vector<int> shortWay;
public:
    const vector<int> &getShortWay() const {
        return shortWay;
    }

    void setShortWay(const vector<int> &shortWay) {
        Graphe::shortWay = shortWay;
    }

public:
    void setLaCarte(const queue<Noeud> &laCarte1) {
        la_carte = laCarte1;
    }

public:
    // Getters
    queue<Noeud> getCarte()const  {
        return la_carte;
    }
    Noeud  getNoeudById(int id) {
        queue<Noeud> nodes = getCarte();
        while (!nodes.empty()) {
            Noeud& n = nodes.front();
            nodes.pop();
            if (n.getZone().getIdentifiantUnique() == id) {
                return n;
            }
        }

    }

    int getNombreDeNoeuds(){
        return la_carte.size();
    }

    // Setters
    void ajouterNoeud(Noeud n) {
        la_carte.push(n);
    }
    void genererGrapheV6(Graphe& g, int nombre_de_noeuds, double minLongitude, double maxLongitude, double minLatitude, double maxLatitude) {
        // Initialisation de la graine pour le générateur de nombres aléatoires
        srand(time(NULL));
        double R = 6371; // radius of the Earth in kilometers
        double maxDistance = 0.001; // maximum distance in kilometers between generated nodes

        // Ajout des noeuds au graphe
        queue<Noeud> nodeQueue;
        for (int i = 0; i < nombre_de_noeuds; i++) {
            Zone z;
            double latitude, longitude;
            bool validCoords = false;
            while (!validCoords) {
                latitude = (double)rand() / RAND_MAX * (maxLatitude - minLatitude) + minLatitude;
                longitude = (double)rand() / RAND_MAX * (maxLongitude - minLongitude) + minLongitude;
                z.setLatitude(latitude);
                z.setLongitude(longitude);
                z.setNom("Zone " + to_string(i));
                z.setNombreHabitants(rand() % 100000);
                z.setIdentifiantUnique(i);
                Noeud n;
                n.setZone(z);
                // Check if this node is more than maxDistance from any existing nodes
                validCoords = true;
                int nodeQueueSize = nodeQueue.size();
                for (int j = 0; j < nodeQueueSize; j++) {
                    double dLat = toRadians(latitude - nodeQueue.front().getZone().getLatitude());
                    double dLon = toRadians(longitude - nodeQueue.front().getZone().getLongitude());
                    double a = sin(dLat/2) * sin(dLat/2) +
                               cos(toRadians(latitude)) * cos(toRadians(nodeQueue.front().getZone().getLatitude())) *
                               sin(dLon/2) * sin(dLon/2);
                    double c = 2 * atan2(sqrt(a), sqrt(1-a));
                    double distance = R * c;
                    if (distance < maxDistance) {
                        validCoords = false;
                        break;
                    }
                    nodeQueue.push(nodeQueue.front());
                    nodeQueue.pop();
                }
            }
            // Ajout des arcs sortants pour ce noeud
            int nombre_de_noeuds_suivants = rand() % 5;
            arc* les_noeuds_suivants = new arc[nombre_de_noeuds_suivants];
            for (int j = 0; j < nombre_de_noeuds_suivants; j++) {
                int id_destination = rand() % nombre_de_noeuds;
                int poids = rand() % 1000;
                les_noeuds_suivants[j].idNoeudDestination = id_destination;
                les_noeuds_suivants[j].poids = poids;
            }
            Noeud n;
            n.setZone(z);
            n.setLesNoeudsSuivants(les_noeuds_suivants, nombre_de_noeuds_suivants);
            nodeQueue.push(n);
        }
        // Transfer nodes from the queue to the graph
        while (!nodeQueue.empty()) {
            g.ajouterNoeud(nodeQueue.front());
            nodeQueue.pop();
        }
    }

// Helper function to convert degrees to radians
    double toRadians(double degrees) {
        return degrees * M_PI / 180;
    }



    void genererGrapheV4(Graphe& g, int nombre_de_noeuds, double minLongitude, double maxLongitude, double minLatitude, double maxLatitude) {
        // Initialisation de la graine pour le générateur de nombres aléatoires
        srand(time(NULL));

        // Ajout des noeuds au graphe
        for (int i = 0; i < nombre_de_noeuds; i++) {
            Noeud n;
            Zone z;
            z.setLatitude((double)rand() / RAND_MAX * (maxLatitude - minLatitude) + minLatitude);
            z.setLongitude((double)rand() / RAND_MAX * (maxLongitude - minLongitude) + minLongitude);
            z.setNom("Zone " + to_string(i));
            z.setNombreHabitants(rand() % 100000);
            z.setIdentifiantUnique(i);
            n.setZone(z);

            // Ajout des arcs sortants pour ce noeud
            int nombre_de_noeuds_suivants = rand() % 5;
            arc* les_noeuds_suivants = new arc[nombre_de_noeuds_suivants];
            for (int j = 0; j < nombre_de_noeuds_suivants; j++) {
                int id_destination = rand() % nombre_de_noeuds;
                int poids = rand() % 1000;
                les_noeuds_suivants[j].idNoeudDestination = id_destination;
                les_noeuds_suivants[j].poids = poids;
            }
            n.setLesNoeudsSuivants(les_noeuds_suivants, nombre_de_noeuds_suivants);
            g.ajouterNoeud(n);
        }
    }

    void genererGrapheV3(Graphe& g, int nombre_de_noeuds) {
        // Initialisation de la graine pour le générateur de nombres aléatoires
        srand(time(NULL));

        vector<Zone> zones;
        // Ajout des noeuds au graphe
        for (int i = 0; i < nombre_de_noeuds; i++) {
            Noeud n;
            Zone z;
            double lat, lon;
            bool valid_location = false;
            while (!valid_location) {
                lat = (double)rand() / RAND_MAX * 180.0 - 90.0;
                lon = (double)rand() / RAND_MAX * 360.0 - 180.0;
                valid_location = true;
                for (const auto& prev_zone : zones) {
                    double dist = distance(lat, lon, prev_zone.getLatitude(), prev_zone.getLongitude());
                    if (dist < 0.5) { // 100m distance
                        valid_location = false;
                        break;
                    }
                }
            }
            z.setLatitude(lat);
            z.setLongitude(lon);
            z.setNom("Zone " + to_string(i));
            z.setNombreHabitants(rand() % 100000);
            z.setIdentifiantUnique(i);
            n.setZone(z);

            // Ajout des arcs sortants pour ce noeud
            int nombre_de_noeuds_suivants = rand() % 5;
            arc* les_noeuds_suivants = new arc[nombre_de_noeuds_suivants];
            for (int j = 0; j < nombre_de_noeuds_suivants; j++) {
                int id_destination = rand() % nombre_de_noeuds;
                int poids = rand() % 1000;
                les_noeuds_suivants[j].idNoeudDestination = id_destination;
                les_noeuds_suivants[j].poids = poids;
            }
            n.setLesNoeudsSuivants(les_noeuds_suivants, nombre_de_noeuds_suivants);
            g.ajouterNoeud(n);
            zones.push_back(z);
        }
    }

    double distance(double lat1, double lon1, double lat2, double lon2) {
        const double R = 6371.0; // Earth radius in km
        double dLat = toRadians(lat2 - lat1);
        double dLon = toRadians(lon2 - lon1);
        double a = sin(dLat / 2) * sin(dLat / 2) + cos(toRadians(lat1)) * cos(toRadians(lat2)) * sin(dLon / 2) * sin(dLon / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        return R * c;
    }



    void generateGrapheWithReasonableApproximation(int nombre_de_noeuds) {
        // Initialisation de la graine pour le générateur de nombres aléatoires
        srand(time(NULL));

        // Ajout des noeuds au graphe
        for (int i = 0; i < nombre_de_noeuds; i++) {
            Noeud n;
            Zone z;
            z.setLatitude((double)rand() / RAND_MAX * 180.0 - 90.0);
            z.setLongitude((double)rand() / RAND_MAX * 360.0 - 180.0);
            z.setNom("Zone " + to_string(i));
            z.setNombreHabitants(rand() % 100000);
            z.setIdentifiantUnique(i);
            n.setZone(z);

            // Ajout des arcs sortants pour ce noeud
            int nombre_de_noeuds_suivants = rand() % 5;
            arc* les_noeuds_suivants = new arc[nombre_de_noeuds_suivants];
            for (int j = 0; j < nombre_de_noeuds_suivants; j++) {
                int id_destination = rand() % nombre_de_noeuds;
                int poids = rand() % 1000;
                les_noeuds_suivants[j].idNoeudDestination = id_destination;
                les_noeuds_suivants[j].poids = poids;
            }
            n.setLesNoeudsSuivants(les_noeuds_suivants, nombre_de_noeuds_suivants);
            ajouterNoeud(n);
        }
    }

    void genererGraphe(Graphe& g, int nombre_de_noeuds) {
        // Initialisation de la graine pour le générateur de nombres aléatoires
        srand(time(NULL));

        // Ajout des noeuds au graphe
        for (int i = 0; i < nombre_de_noeuds; i++) {
            Noeud n;
            Zone z;
            z.setLatitude((double)rand() / RAND_MAX * 180.0 - 90.0);
            z.setLongitude((double)rand() / RAND_MAX * 360.0 - 180.0);
            z.setNom("Zone " + to_string(i));
            z.setNombreHabitants(rand() % 100000);
            z.setIdentifiantUnique(i);
            n.setZone(z);

            // Ajout des arcs sortants pour ce noeud
            int nombre_de_noeuds_suivants = rand() % 5;
            arc* les_noeuds_suivants = new arc[nombre_de_noeuds_suivants];
            for (int j = 0; j < nombre_de_noeuds_suivants; j++) {
                int id_destination = rand() % nombre_de_noeuds;
                int poids = rand() % 1000;
                les_noeuds_suivants[j].idNoeudDestination = id_destination;
                les_noeuds_suivants[j].poids = poids;
            }
            n.setLesNoeudsSuivants(les_noeuds_suivants, nombre_de_noeuds_suivants);
            g.ajouterNoeud(n);
        }
    }



    void sauvegarderGrapheDansFichier(Graphe g, std::string nom_fichier) {
        std::ofstream fichier(nom_fichier);

        if (fichier) {
            queue<Noeud> carte = g.getCarte();
            while (!carte.empty()) {
                Noeud n = carte.front();
                carte.pop();

                // Sauvegarde des informations de la zone
                Zone z = n.getZone();
                fichier << z.getLatitude() << " " << z.getLongitude() << " " << z.getNom() << " " << z.getNombreHabitants() << " " << z.getIdentifiantUnique() << "\n";

                // Sauvegarde des informations des arcs sortants
                int nb_arcs = n.getNombreDeNoeudsSuivants();
                fichier << nb_arcs << " ";
                arc* arcs = n.getLesNoeudsSuivants();
                for (int i = 0; i < nb_arcs; i++) {
                    fichier << "dest : "<< arcs[i].idNoeudDestination << " poids : " << arcs[i].poids << " , ";
                }
                fichier << "\n";
            }
            fichier.close();
        }
        else {
            std::cout << "Erreur : impossible d'ouvrir le fichier " << nom_fichier << std::endl;
        }
    }
    //void saveShortestWaysBetweenAllNodesForEveeryNodget
  //  void getShortestWaysUsingDijkstraBetweenAllNodes

    void sauvegarderGrapheDansFichierJSON(Graphe g, std::string nom_fichier) {
        std::ofstream fichier(nom_fichier);

        if (fichier) {
            queue<Noeud> carte = g.getCarte();
            fichier << "{\n";
            while (!carte.empty()) {
                Noeud n = carte.front();
                carte.pop();

                // Sauvegarde des informations de la zone
                Zone z = n.getZone();
                fichier << "\t\"" << z.getIdentifiantUnique() << "\": {\n";
                fichier << "\t\t\"latitude\": " << z.getLatitude() << ",\n";
                fichier << "\t\t\"longitude\": " << z.getLongitude() << ",\n";
                fichier << "\t\t\"nombre_habitant\": " << z.getNombreHabitants() << ",\n";
                fichier << "\t\t\"arcs\": [\n";

                // Sauvegarde des informations des arcs sortants
                int nb_arcs = n.getNombreDeNoeudsSuivants();
                arc* arcs = n.getLesNoeudsSuivants();
                for (int i = 0; i < nb_arcs; i++) {
                    fichier << "\t\t\t{\"idNoeudDestination\": " << arcs[i].idNoeudDestination << ", \"poids\": " << arcs[i].poids << "}";
                    if (i < nb_arcs - 1) {
                        fichier << ",";
                    }
                    fichier << "\n";
                }
                fichier << "\t\t]\n";
                fichier << "\t}";
                if (!carte.empty()) {
                    fichier << ",";
                }
                fichier << "\n";
            }
            fichier << "}";
            fichier.close();
        }
        else {
            std::cout << "Erreur : impossible d'ouvrir le fichier " << nom_fichier << std::endl;
        }
    }
    double getScoreByIDFromVectorPageRanking(vector<pair<int,double>> v, int id){
        for(int i = 0; i < v.size(); i++){
            if(v[i].first == id){
                return v[i].second;
            }
        }
        return 0;
    }
  void sauvegarderGrapheDansFichierJSONV2(Graphe g, std::string nom_fichier) {
        std::ofstream fichier(nom_fichier);

        if (fichier) {
            queue<Noeud> carte = g.getCarte();
            fichier << "{\n";
            while (!carte.empty()) {
                Noeud n = carte.front();
                carte.pop();

                // Sauvegarde des informations de la zone
                Zone z = n.getZone();
                fichier << "\t\"" << z.getIdentifiantUnique() << "\": {\n";
                fichier << "\t\t\"latitude\": " << z.getLatitude() << ",\n";
                fichier << "\t\t\"longitude\": " << z.getLongitude() << ",\n";
                fichier << "\t\t\"nombre_habitant\": " << z.getNombreHabitants() << ",\n";
                double score= getScoreByIDFromVectorPageRanking(pageRanks, z.getIdentifiantUnique());
                if (n.getZone().getIdentifiantUnique()==0){
                    fichier << "\t\t\"shortest\": [\n";
                    for (int i = 0; i < shortWay.size(); i++) {

                        if (i!=shortWay.size()-1)
                        {
                            fichier << shortWay[i] <<" ,";
                        }else
                            fichier << shortWay[i] ;

                    }
                    fichier << "\t\t],\n";

                }
                cout<< "score page ranking : " << score << endl;
                fichier << "\t\t\"score_page_ranking\": " << score << ",\n";


                fichier << "\t\t\"arcs\": [\n";

                // Sauvegarde des informations des arcs sortants
                int nb_arcs = n.getNombreDeNoeudsSuivants();
                arc* arcs = n.getLesNoeudsSuivants();
                for (int i = 0; i < nb_arcs; i++) {
                    fichier << "\t\t\t{\"idNoeudDestination\": " << arcs[i].idNoeudDestination << ", \"poids\": " << arcs[i].poids << "}";
                    if (i < nb_arcs - 1) {
                        fichier << ",";
                    }
                    fichier << "\n";
                }
                fichier << "\t\t],\n";




// Add the "shortest_way" array to the JSON object
                fichier << "\"shortest_way\":[";

// Iterate over the ShortestWay objects and add them to the "shortest_way" array
                bool first = true;
                for ( ShortestWay sh: n.getShortestWay()) {
                    // Add a comma separator between objects
                    if (!first) {
                        fichier << ",";
                    } else {
                        first = false;
                    }

                    // Add the ShortestWay object to the array as a JSON object
                    fichier << "{"
                         << "\"id_arrivee\":" << sh.getIdArrivee() << ","
                         << "\"nodes\":[";

                    // Add the nodes in the ShortestWay object to the "nodes" array
                    bool first_node = true;
                    for (int id : sh.getNodes()) {
                        // Add a comma separator between nodes
                        if (!first_node) {
                            fichier << ",";
                        } else {
                            first_node = false;
                        }
                        fichier << id;
                    }

                    // Close the "nodes" array and the ShortestWay object
                    fichier << "]"
                         << "}";
                }

// Close the "shortest_way" array and the JSON object
                fichier << "]";


                fichier << "\t}";
                if (!carte.empty()) {
                    fichier << ",";
                }
                fichier << "\n";
            }
            fichier << "}";
            fichier.close();
        }
        else {
            std::cout << "Erreur : impossible d'ouvrir le fichier " << nom_fichier << std::endl;
        }
    }/*
    void sauvegarderGrapheDansFichierV3(Graphe g, std::string nom_fichier) {
        std::ofstream fichier(nom_fichier);

        if (fichier) {
            queue<Noeud> carte = g.getCarte();
            while (!carte.empty()) {
                Noeud n = carte.front();
                carte.pop();

                // Sauvegarde des informations de la zone
                Zone z = n.getZone();
                fichier << z.getLatitude() << " " << z.getLongitude() << " " << z.getNom() << " " << z.getNombreHabitants() << " " << z.getIdentifiantUnique() << "\n";

                // Sauvegarde des informations des arcs sortants
                int nb_arcs = n.getNombreDeNoeudsSuivants();
                fichier << nb_arcs << " ";
                arc* arcs = n.getLesNoeudsSuivants();
                for (int i = 0; i < nb_arcs; i++) {
                    fichier << "dest : "<< arcs[i].idNoeudDestination << " poids : " << arcs[i].poids << " , ";
                }
                fichier << "\n";

                // Sauvegarde des informations du plus court chemin
                if (n.getShortestWay().size() > 0) {
                    fichier << "ShortestWay: { id_depart: " << n.getZone().getIdentifiantUnique() << ", id_arrivee: " << n.getPlusCourtChemin().back() << ", nodes: [";
                    for (int node : n.getShortestWay()) {
                        fichier << node << ",";
                    }
                    fichier << "], vector: [";
                    for (double value : n.getShortestWayVector()) {
                        fichier << value << ",";
                    }
                    fichier << "] }\n";
                }
            }
            fichier.close();
        }
        else {
            std::cout << "Erreur : impossible d'ouvrir le fichier " << nom_fichier << std::endl;
        }
    }

*/

    void afficherNomZoneParID(int idZone, const Graphe& graphe) {
        // Itération sur les nœuds du graphe
        queue<Noeud> carte = graphe.getCarte();
        while (!carte.empty()) {
            Noeud noeudCourant = carte.front();
            carte.pop();

            Zone zoneCourante = noeudCourant.getZone();
            if (zoneCourante.getIdentifiantUnique() == idZone) {
                cout << zoneCourante.getNom() ;
                return;
            }
        }
        cout << "Zone introuvable." << endl;
    }

    void dijkstra(int id_depart, int id_arrivee, Graphe& g) {
        // Initialisation des distances à l'infini et du prédécesseur à -1
        const int inf = numeric_limits<int>::max();
        vector<int> distances(g.getCarte().size(), inf);
        vector<int> predecesseurs(g.getCarte().size(), -1);

        // Initialisation de la file de priorité
        auto cmp = [](pair<int,int> left, pair<int,int> right) { return left.second > right.second; };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

        // Trouver le noeud de départ dans la carte
        queue<Noeud> carte = g.getCarte();
        Noeud depart;
        while (!carte.empty()) {
            Noeud n = carte.front();
            carte.pop();
            if (n.getZone().getIdentifiantUnique() == id_depart) {
                depart = n;
                break;
            }
        }

        // Ajouter le noeud de départ à la file de priorité avec une distance de 0
        distances[depart.getZone().getIdentifiantUnique()] = 0;
        pq.push(make_pair(depart.getZone().getIdentifiantUnique(), 0));

        // Boucle principale de l'algorithme de Dijkstra
        while (!pq.empty()) {
            int u = pq.top().first;
            pq.pop();

            // Trouver le noeud correspondant à l'identifiant u dans la carte
            queue<Noeud> carte = g.getCarte();
            Noeud n_u;
            while (!carte.empty()) {
                Noeud n = carte.front();
                carte.pop();
                if (n.getZone().getIdentifiantUnique() == u) {
                    n_u = n;
                    break;
                }
            }

            // Parcourir les arcs sortants du noeud u
            arc* les_noeuds_suivants = n_u.getLesNoeudsSuivants();
            int nb_arcs_sortants = n_u.getNombreDeNoeudsSuivants();
            for (int i = 0; i < nb_arcs_sortants; i++) {
                int v = les_noeuds_suivants[i].idNoeudDestination;
                int poids_uv = les_noeuds_suivants[i].poids;

                // Si une nouvelle plus courte distance vers le noeud v est trouvée, mettre à jour la distance et le prédécesseur
                if (distances[u] + poids_uv < distances[v]) {
                    distances[v] = distances[u] + poids_uv;
                    predecesseurs[v] = u;
                    pq.push(make_pair(v, distances[v]));
                }
            }
        }

        // Affichage du chemin le plus court
        vector<int> chemin;
        int arrivee = id_arrivee;
        while (arrivee != -1) {
            chemin.push_back(arrivee);
            arrivee = predecesseurs[arrivee];
        }
        reverse(chemin.begin(), chemin.end());
        for (int id : chemin) {
            cout<<"-->";
            afficherNomZoneParID(id,g) ;
        }
        cout << endl;
    }
    vector<int> dijkstraV4(int id_depart, int id_arrivee, Graphe& g) {
        // Initialisation des distances à l'infini et du prédécesseur à -1
        const int inf = numeric_limits<int>::max();
        vector<int> distances(g.getCarte().size(), inf);
        vector<int> predecesseurs(g.getCarte().size(), -1);

        // Initialisation de la file de priorité
        auto cmp = [](pair<int,int> left, pair<int,int> right) { return left.second > right.second; };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

        // Trouver le noeud de départ dans la carte
        queue<Noeud> carte = g.getCarte();
        Noeud depart;
        while (!carte.empty()) {
            Noeud n = carte.front();
            carte.pop();
            if (n.getZone().getIdentifiantUnique() == id_depart) {
                depart = n;
                break;
            }
        }

        // Ajouter le noeud de départ à la file de priorité avec une distance de 0
        distances[depart.getZone().getIdentifiantUnique()] = 0;
        pq.push(make_pair(depart.getZone().getIdentifiantUnique(), 0));

        // Boucle principale de l'algorithme de Dijkstra
        while (!pq.empty()) {
            int u = pq.top().first;
            pq.pop();

            // Trouver le noeud correspondant à l'identifiant u dans la carte
            queue<Noeud> carte = g.getCarte();
            Noeud n_u;
            while (!carte.empty()) {
                Noeud n = carte.front();
                carte.pop();
                if (n.getZone().getIdentifiantUnique() == u) {
                    n_u = n;
                    break;
                }
            }

            // Parcourir les arcs sortants du noeud u
            arc* les_noeuds_suivants = n_u.getLesNoeudsSuivants();
            int nb_arcs_sortants = n_u.getNombreDeNoeudsSuivants();
            for (int i = 0; i < nb_arcs_sortants; i++) {
                int v = les_noeuds_suivants[i].idNoeudDestination;
                int poids_uv = les_noeuds_suivants[i].poids;

                // Si une nouvelle plus courte distance vers le noeud v est trouvée, mettre à jour la distance et le prédécesseur
                if (distances[u] + poids_uv < distances[v]) {
                    distances[v] = distances[u] + poids_uv;
                    predecesseurs[v] = u;
                    pq.push(make_pair(v, distances[v]));
                }
            }
        }

        // Affichage du chemin le plus court
        vector<int> chemin;
        int arrivee = id_arrivee;
        while (arrivee != -1) {
            chemin.push_back(arrivee);
            arrivee = predecesseurs[arrivee];
        }
        reverse(chemin.begin(), chemin.end());

        shortWay.insert(shortWay.begin(), chemin.begin(),chemin.end());
        return chemin;
        /*
        for (int id : chemin) {
            cout<<"-->";
            afficherNomZoneParID(id,g) ;
        }
        cout << endl;*/
    }
    queue<Noeud> cloneCarte(queue<Noeud> carte){
        queue<Noeud> carteClone;
        while(!carte.empty()){
            Noeud n = carte.front();
            carte.pop();
            carteClone.push(n);
        }
        return carteClone;
    }
    vector<int> dijkstraV2(int id_depart, int id_arrivee, Graphe& g) {
        // Initialisation des distances à l'infini et du prédécesseur à -1
        const int inf = numeric_limits<int>::max();
        vector<int> distances(g.getCarte().size(), inf);
        vector<int> predecesseurs(g.getCarte().size(), -1);

        // Initialisation de la file de priorité
        auto cmp = [](pair<int,int> left, pair<int,int> right) { return left.second > right.second; };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

        // Trouver le noeud de départ dans la carte
        queue<Noeud> carte = g.getCarte();
        Noeud depart;
        while (!carte.empty()) {
            Noeud n = carte.front();
            carte.pop();
            if (n.getZone().getIdentifiantUnique() == id_depart) {
                depart = n;
                break;
            }
        }

        // Ajouter le noeud de départ à la file de priorité avec une distance de 0
        distances[depart.getZone().getIdentifiantUnique()] = 0;
        pq.push(make_pair(depart.getZone().getIdentifiantUnique(), 0));

        // Boucle principale de l'algorithme de Dijkstra
        while (!pq.empty()) {
            int u = pq.top().first;
            pq.pop();

            // Trouver le noeud correspondant à l'identifiant u dans la carte
            queue<Noeud> carte = g.getCarte();
            Noeud n_u;
            while (!carte.empty()) {
                Noeud n = carte.front();
                carte.pop();
                if (n.getZone().getIdentifiantUnique() == u) {
                    n_u = n;
                    break;
                }
            }

            // Parcourir les arcs sortants du noeud u
            arc* les_noeuds_suivants = n_u.getLesNoeudsSuivants();
            int nb_arcs_sortants = n_u.getNombreDeNoeudsSuivants();
            for (int i = 0; i < nb_arcs_sortants; i++) {
                int v = les_noeuds_suivants[i].idNoeudDestination;
                int poids_uv = les_noeuds_suivants[i].poids;

                // Si une nouvelle plus courte distance vers le noeud v est trouvée, mettre à jour la distance et le prédécesseur
                if (distances[u] + poids_uv < distances[v]) {
                    distances[v] = distances[u] + poids_uv;
                    predecesseurs[v] = u;
                    pq.push(make_pair(v, distances[v]));
                }
            }
        }

        // Affichage du chemin le plus court
        vector<int> chemin;
        int arrivee = id_arrivee;
        while (arrivee != -1) {
            chemin.push_back(arrivee);
            arrivee = predecesseurs[arrivee];
        }
        reverse(chemin.begin(), chemin.end());
        /*
        for (int id : chemin) {
            cout<<"-->";
            afficherNomZoneParID(id,g) ;
            cheminNode.push_back(id);
        }
        cout << endl;*/
        return chemin;
    }
    vector<Noeud> convertQueueToVector(queue<Noeud> carte){
        vector<Noeud> carteVector;
        while(!carte.empty()){
            Noeud n = carte.front();
            carte.pop();
            carteVector.push_back(n);
        }
        return carteVector;
    }
    queue<Noeud> convertVectorToQueue(vector<Noeud> carte){
        queue<Noeud> carteQueue;
        for (int i = 0; i < carte.size(); i++) {
            carteQueue.push(carte[i]);
        }
        return carteQueue;
    }
    void getShortestWayBetweenNodesOfTheGrapheV2(Graphe& g,int nombre) {
        vector<Noeud> nodes=convertQueueToVector( g.getCarte() );
        vector<vector<int>> cheminNodes;

        for (int i = 0; i < nombre; i++) {
            vector<ShortestWay> shortestWay ;
            for (int j = i+1; j < nodes.size(); j++) {
                Noeud nodeA = nodes[i];
                Noeud nodeB = nodes[j];
                //shortestWay
                int id_depart = nodeA.getZone().getIdentifiantUnique();
                int id_arrivee = nodeB.getZone().getIdentifiantUnique();
                ShortestWay subShortestWay;
                subShortestWay.setIdDepart(id_depart);
                subShortestWay.setIdArrivee(id_arrivee);
                if (id_depart != id_arrivee) {

                    vector<int> cheminNode = dijkstraV2(id_depart, id_arrivee, g);
                    subShortestWay.setNodes(cheminNode);
                    //  cheminNodes.push_back(cheminNode);
                    shortestWay.push_back(subShortestWay);

                    // Print out the shortest path
                    /* cout << "Shortest path between Node " << i << " and Node " << j << ": ";
                     for (int id : subShortestWay.getNodes()) {
                         cout << id << " ";
                      //   afficherNomZoneParID(id, g);
                     }*/

                }
            }
            nodes[i].setShortestWay( cloneShortestWay(shortestWay) );

        }
        g.setLaCarte(convertVectorToQueue(nodes));

    }
    void getShortestWayBetweenAllNodesOfTheGrapheV2(Graphe& g) {
        vector<Noeud> nodes=convertQueueToVector( g.getCarte() );
        vector<vector<int>> cheminNodes;

        for (int i = 0; i < nodes.size(); i++) {
            vector<ShortestWay> shortestWay ;
            for (int j = i+1; j < nodes.size(); j++) {
                Noeud nodeA = nodes[i];
                Noeud nodeB = nodes[j];
                //shortestWay
                int id_depart = nodeA.getZone().getIdentifiantUnique();
                int id_arrivee = nodeB.getZone().getIdentifiantUnique();
                ShortestWay subShortestWay;
                subShortestWay.setIdDepart(id_depart);
                subShortestWay.setIdArrivee(id_arrivee);
                if (id_depart != id_arrivee) {
                    vector<int> cheminNode = dijkstraV2(id_depart, id_arrivee, g);
                    subShortestWay.setNodes(cheminNode);
                  //  cheminNodes.push_back(cheminNode);
                    shortestWay.push_back(subShortestWay);

                    // Print out the shortest path
                   /* cout << "Shortest path between Node " << i << " and Node " << j << ": ";
                    for (int id : subShortestWay.getNodes()) {
                        cout << id << " ";
                     //   afficherNomZoneParID(id, g);
                    }*/

                }
            }
            nodes[i].setShortestWay( cloneShortestWay(shortestWay) );

            }
          g.setLaCarte(convertVectorToQueue(nodes));

        }

        vector<ShortestWay> cloneShortestWay(vector<ShortestWay> shortestWay){
            vector<ShortestWay> shortestWayClone;
            for (ShortestWay sh: shortestWay) {
                ShortestWay shClone;
                shClone.setIdDepart(sh.getIdDepart());
                shClone.setIdArrivee(sh.getIdArrivee());
                shClone.setNodes(sh.getNodes());
                shortestWayClone.push_back(shClone);
            }
            return shortestWayClone;
        }
    void getShortestWayBetweenAllNodesOfTheGraphe(Graphe& g){
        //queue<Noeud> carte = g.getCarte();
        queue<Noeud> carte=cloneCarte(g.getCarte());
        vector<vector<int>> cheminNodes;
        while(!carte.empty()){
            Noeud n = carte.front();
            carte.pop();
            int id_depart = n.getZone().getIdentifiantUnique();
            queue<Noeud> carte2 = g.getCarte();
            while(!carte2.empty()){
                Noeud n2 = carte2.front();
                carte2.pop();
                int id_arrivee = n2.getZone().getIdentifiantUnique();
                if(id_depart != id_arrivee){
                    vector<int> cheminNode = dijkstraV2(id_depart,id_arrivee,g);
                    for (int id : cheminNode) {
                        cout<<"-->"+id;
                        afficherNomZoneParID(id,g) ;
                    }
                    cout << endl;
                    cheminNodes.push_back(cheminNode);
                }
            }
        }
        cout<<" finished"<<endl;

    }
    /*
    vector<vector<int>> dijkstraV2BetweenNodes( Graphe& g) {
        // Initialisation des distances à l'infini et du prédécesseur à -1
        const int inf = numeric_limits<int>::max();
        vector<int> distances(g.getCarte().size(), inf);
        vector<int> predecesseurs(g.getCarte().size(), -1);

        // Initialisation de la file de priorité
        auto cmp = [](pair<int,int> left, pair<int,int> right) { return left.second > right.second; };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

        // Trouver le noeud de départ dans la carte
        queue<Noeud> carte = cloneCarte(g.getCarte());
        Noeud depart;
        vector<vector<int>> cheminNodes;
        while (!carte.empty()) {
            Noeud n = carte.front();

            vector<int> cheminNode= dijkstraV2(n.getZone().getIdentifiantUnique(), 0, cheminNode, g);
            for (int i = 0; i < n; ++i) {

            }
            carte.pop();
            if (n.getZone().getIdentifiantUnique() == id_depart) {
                depart = n;
                break;
            }
        }

        // Ajouter le noeud de départ à la file de priorité avec une distance de 0
        distances[depart.getZone().getIdentifiantUnique()] = 0;
        pq.push(make_pair(depart.getZone().getIdentifiantUnique(), 0));

        // Boucle principale de l'algorithme de Dijkstra
        while (!pq.empty()) {
            int u = pq.top().first;
            pq.pop();

            // Trouver le noeud correspondant à l'identifiant u dans la carte
            queue<Noeud> carte = g.getCarte();
            Noeud n_u;
            while (!carte.empty()) {
                Noeud n = carte.front();
                carte.pop();
                if (n.getZone().getIdentifiantUnique() == u) {
                    n_u = n;
                    break;
                }
            }

            // Parcourir les arcs sortants du noeud u
            arc* les_noeuds_suivants = n_u.getLesNoeudsSuivants();
            int nb_arcs_sortants = n_u.getNombreDeNoeudsSuivants();
            for (int i = 0; i < nb_arcs_sortants; i++) {
                int v = les_noeuds_suivants[i].idNoeudDestination;
                int poids_uv = les_noeuds_suivants[i].poids;

                // Si une nouvelle plus courte distance vers le noeud v est trouvée, mettre à jour la distance et le prédécesseur
                if (distances[u] + poids_uv < distances[v]) {
                    distances[v] = distances[u] + poids_uv;
                    predecesseurs[v] = u;
                    pq.push(make_pair(v, distances[v]));
                }
            }
        }

        // Affichage du chemin le plus court
        vector<int> chemin;
        int arrivee = id_arrivee;
        while (arrivee != -1) {
            chemin.push_back(arrivee);
            arrivee = predecesseurs[arrivee];
        }
        reverse(chemin.begin(), chemin.end());
        for (int id : chemin) {
            cout<<"-->";
            afficherNomZoneParID(id,g) ;
            cheminNode.push_back(id);
        }
        cout << endl;
        return cheminNode;
    }
*/
    /*
    void pageRank(Graphe g,int max_iterations,double damping_factor){

    }*/

    vector<pair<string, double>> pageRank(Graphe g, int max_iterations, double damping_factor) {
        queue<Noeud> nodes = g.getCarte();

        int num_nodes = nodes.size();

        // Initialiser les scores à 1/N pour chaque noeud
        vector<double> scores(num_nodes, 1.0 / num_nodes);

        // Calculer les scores itérativement
        for (int i = 0; i < max_iterations; i++) {
            vector<double> new_scores(num_nodes, 0.0);
            double teleportation = (1.0 - damping_factor) / num_nodes;

            while (!nodes.empty()) {
                Noeud n = nodes.front();
                nodes.pop();

                // Calculer la somme pondérée des scores des noeuds qui pointent vers ce noeud
                double weighted_sum = 0.0;
                arc* arcs = n.getLesNoeudsSuivants();
                int num_arcs = n.getNombreDeNoeudsSuivants();
                for (int j = 0; j < num_arcs; j++) {
                    int dest_node_id = arcs[j].idNoeudDestination;
                    double weight = arcs[j].getPoids() / g.getNoeudById(dest_node_id).getZone().getNombreHabitants();
                    weighted_sum += weight * scores[dest_node_id];
                }

                // Ajouter le facteur de téléportation et mettre à jour le nouveau score
                double new_score = teleportation + damping_factor * weighted_sum;
                new_scores[n.getZone().getIdentifiantUnique()] = new_score;
            }

            // Mettre à jour les scores pour la prochaine itération
            scores = new_scores;
            nodes = g.getCarte();
        }

        // Créer un vecteur de paires (zone, score)
        vector<pair<string, double>> zone_scores;
        int i = 0;
        while (!nodes.empty()) {
            Noeud n = nodes.front();
            nodes.pop();
            n.setScore(scores[i]);
            zone_scores.emplace_back(n.getZone().getNom(), scores[i]);
            i++;
        }

        // Trier les scores par ordre décroissant
        sort(zone_scores.begin(), zone_scores.end(), [](const auto& p1, const auto& p2) {
            return p1.second > p2.second;
        });
        // Afficher les scores avec le nom de la zone
        for (auto& zone_score : zone_scores) {
            cout << zone_score.first << " : " << zone_score.second << endl;
        }
        g.setLaCarte(cloneCarte(nodes));
        return zone_scores;
    }
    vector<pair<int, double>> pageRankV3(Graphe g, int max_iterations, double damping_factor) {
        queue<Noeud> nodes = g.getCarte();

        int num_nodes = nodes.size();

        // Initialiser les scores à 1/N pour chaque noeud
        vector<double> scores(num_nodes, 1.0 / num_nodes);

        // Calculer les scores itérativement
        for (int i = 0; i < max_iterations; i++) {
            vector<double> new_scores(num_nodes, 0.0);
            double teleportation = (1.0 - damping_factor) / num_nodes;

            while (!nodes.empty()) {
                Noeud n = nodes.front();
                nodes.pop();

                // Calculer la somme pondérée des scores des noeuds qui pointent vers ce noeud
                double weighted_sum = 0.0;
                arc* arcs = n.getLesNoeudsSuivants();
                int num_arcs = n.getNombreDeNoeudsSuivants();
                for (int j = 0; j < num_arcs; j++) {
                    int dest_node_id = arcs[j].idNoeudDestination;
                    double weight = arcs[j].getPoids() / g.getNoeudById(dest_node_id).getZone().getNombreHabitants();
                    weighted_sum += weight * scores[dest_node_id];
                }

                // Ajouter le facteur de téléportation et mettre à jour le nouveau score
                double new_score = teleportation + damping_factor * weighted_sum;
                new_scores[n.getZone().getIdentifiantUnique()] = new_score;
            }

            // Mettre à jour les scores pour la prochaine itération
            scores = new_scores;
            nodes = g.getCarte();
        }

        // Créer un vecteur de paires (zone, score)
        vector<pair<int, double>> zone_scores;
        int i = 0;
        while (!nodes.empty()) {
            Noeud n = nodes.front();
            nodes.pop();
            n.setScore(scores[i]);
            zone_scores.emplace_back(n.getZone().getIdentifiantUnique(), scores[i]);
            i++;
        }

        // Trier les scores par ordre décroissant
        sort(zone_scores.begin(), zone_scores.end(), [](const auto& p1, const auto& p2) {
            return p1.second > p2.second;
        });
        // Afficher les scores avec le nom de la zone
        for (auto& zone_score : zone_scores) {
            cout << zone_score.first << " : " << zone_score.second << endl;
        }
        g.setLaCarte(cloneCarte(nodes));
        pageRanks=zone_scores;
        return zone_scores;
    }
    Graphe cloneGraphe(Graphe g){
        Graphe g2;
        queue<Noeud> nodes = g.getCarte();
        while (!nodes.empty()) {
            Noeud n = nodes.front();
            nodes.pop();
            g2.ajouterNoeud(n);
        }
        return g2;
    }
    vector<pair<int, double>> pageRankV1(Graphe g, int max_iterations, double damping_factor) {
        queue<Noeud> nodes = g.getCarte();
        vector<Noeud> nodesClone= convertQueueToVector(nodes);

        int num_nodes = nodes.size();

        // Initialiser les scores à 1/N pour chaque noeud
        vector<double> scores(num_nodes, 1.0 / num_nodes);

        // Calculer les scores itérativement
        for (int i = 0; i < max_iterations; i++) {
            vector<double> new_scores(num_nodes, 0.0);
            double teleportation = (1.0 - damping_factor) / num_nodes;

            while (!nodes.empty()) {
                Noeud n = nodes.front();
                nodes.pop();

                // Calculer la somme pondérée des scores des noeuds qui pointent vers ce noeud
                double weighted_sum = 0.0;
                arc* arcs = n.getLesNoeudsSuivants();
                int num_arcs = n.getNombreDeNoeudsSuivants();
                for (int j = 0; j < num_arcs; j++) {
                    int dest_node_id = arcs[j].idNoeudDestination;
                    double weight = arcs[j].getPoids() / g.getNoeudById(dest_node_id).getZone().getNombreHabitants();
                    weighted_sum += weight * scores[dest_node_id];
                }

                // Ajouter le facteur de téléportation et mettre à jour le nouveau score
                double new_score = teleportation + damping_factor * weighted_sum;
                new_scores[n.getZone().getIdentifiantUnique()] = new_score;
            }

            // Mettre à jour les scores pour la prochaine itération
            scores = new_scores;
            nodes = g.getCarte();
        }

        // Créer un vecteur de paires (zone, score)
        vector<pair<int, double>> zone_scores;
        int i = 0;
        while (!nodes.empty()) {
            Noeud n = nodes.front();
            nodes.pop();
        //    n.setScore(scores[i]);
            zone_scores.emplace_back(n.getZone().getIdentifiantUnique(), scores[i]);
            i++;
        }

        // Trier les scores par ordre décroissant
        sort(zone_scores.begin(), zone_scores.end(), [](const auto& p1, const auto& p2) {
            return p1.second > p2.second;
        });
        // Afficher les scores avec le nom de la zone
        for (auto& zone_score : zone_scores) {
            cout << zone_score.first << " : " << zone_score.second << endl;
           // nodesClone[zone_score.first].setScore(zone_score.second);

        }
      //  g.setLaCarte(convertVectorToQueue(nodesClone));
        return zone_scores;
    }

    void addPageRankToNodes(Graphe g, vector<pair<int, double>> pageRank){
        queue<Noeud> nodes = g.getCarte();
        vector<Noeud> nodesClone= convertQueueToVector(nodes);
        for (auto& zone_score : pageRank) {
            nodesClone[zone_score.first].setScore(zone_score.second);
        }
        g.setLaCarte(convertVectorToQueue(nodesClone));
    }

    void addShoortestWay(const vector<int> &v) {

        for( auto it=v.begin();it!=v.end();*it++ )
            shortWay.push_back(*it);
    }
};

