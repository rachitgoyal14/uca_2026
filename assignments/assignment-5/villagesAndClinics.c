#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int validDistribution(int populationPerVillage[], int numberOfClinics, int numberOfVillages, double maxLoad);
double minimumMaximumLoadPerVillage(int populationPerVillage[], int numberOfVillages, int numberOfClinics);


int validDistribution(int populationPerVillage[], int numberOfClinics, int numberOfVillages, double maxLoad) {

    int allocatedClinics = 0;

    for (int i = 0; i < numberOfVillages; i++) {

        //number of clinics required for this specific village
        allocatedClinics += ceil((double) populationPerVillage[i] / maxLoad);

        // already need more clinics than we have
        if (allocatedClinics > numberOfClinics) {
            return 0;
        }
    }

    return 1;
}


double minimumMaximumLoadPerVillage(int populationPerVillage[], int numberOfVillages, int numberOfClinics) {

    int maximumPopulation = 0;

    for (int i = 0; i < numberOfVillages; i++) {
        if (populationPerVillage[i] > maximumPopulation) {
            maximumPopulation = populationPerVillage[i];
        }
    }

    double start = 0;
    double end = maximumPopulation;
    double answer = end;

    // binary search over continuous values
    for (int i = 0; i < 100; i++) {

        double mid = start + (end - start) / 2.0;

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
    scanf("%d", &numberOfTestCases);

    while (numberOfTestCases--) {

        int numberOfVillages;
        scanf("%d", &numberOfVillages);

        int numberOfClinics;
        scanf("%d", &numberOfClinics);

        int populationPerVillage[numberOfVillages];

        for (int i = 0; i < numberOfVillages; i++) {

            int population;
            scanf("%d", &population);

            populationPerVillage[i] = population;
        }

        double minimizedMaximumLoad = minimumMaximumLoadPerVillage(
            populationPerVillage,
            numberOfVillages,
            numberOfClinics
        );

        printf("%.2f\n", minimizedMaximumLoad);
    }

    return 0;
}