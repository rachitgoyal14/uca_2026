#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>

using namespace std;

double minimumMaximumLoadPerVillage(vector<int> populationPerVillage, int numberOfVillages, int numberOfClinics);
bool validDistribution(vector<int> populationPerVillage, int numberOfClinics, int numberOfVillages, double maxLoad);


bool validDistribution(vector<int> populationPerVillage, int numberOfClinics, int numberOfVillages, double maxLoad) {

     int allocatedClinics = 0;

    for (int i = 0; i < numberOfVillages; i++) {

        //number of clinics required for this specific village
        allocatedClinics += ceil((double) populationPerVillage[i] / maxLoad);

        // already need more clinics than we have
        if (allocatedClinics > numberOfClinics) {
            return false;
        }
    }

    return true;
}

double minimumMaximumLoadPerVillage(vector<int> populationPerVillage, int numberOfVillages, int numberOfClinics) {

    int maximumPopulation = 0;

    for (int population : populationPerVillage) {
        maximumPopulation = max(maximumPopulation, population);
    }

    double start = 0;
    double end = maximumPopulation;
    double answer = end;

    // binary search over continuous values
    for (int i = 0; i < 100; i++) {

        double mid = start + (end - start) / 2;

        if (validDistribution(populationPerVillage, numberOfClinics, numberOfVillages, mid)) {

            answer = mid;

            // load can be handled
            // lets try a smaller load
            end = mid;

        } else {

            // load cannot be handled since too little
            // try larger load
            start = mid;
        }
    }

    return answer;
}



int main() {

    int numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {

        int numberOfVillages;
        cin >> numberOfVillages;

        int numberOfClinics;
        cin >> numberOfClinics;

        vector<int> populationPerVillage;
        
        for (int i = 0; i < numberOfVillages; i++) {
            
            int population;
            cin >> population;

            populationPerVillage.push_back(population);
        }


        double minimizedMaximumLoad = minimumMaximumLoadPerVillage(populationPerVillage, numberOfVillages, numberOfClinics);

        cout << fixed << setprecision(2) << minimizedMaximumLoad << endl;
    }

    return 0;
}