#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include  <time.h>
#include <queue>
#include <limits>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Zone {
private:
    double latitude;
    double longitude;
    std::string nom;
    int nombre_habitants;
    int identifiant_unique;

public:
    // Getters
    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }

    std::string getNom() const {
        return nom;
    }

    int getNombreHabitants() const {
        return nombre_habitants;
    }

    int getIdentifiantUnique() const {
        return identifiant_unique;
    }

    // Setters
    void setLatitude(double lat) {
        latitude = lat;
    }

    void setLongitude(double lon) {
        longitude = lon;
    }

    void setNom(std::string n) {
        nom = n;
    }

    void setNombreHabitants(int nb) {
        nombre_habitants = nb;
    }

    void setIdentifiantUnique(int id) {
        identifiant_unique = id;
    }
};
