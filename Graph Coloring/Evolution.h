
#ifndef Neural_Assignment_4_Evolution_h
#define Neural_Assignment_4_Evolution_h


#include "Chromosome.h"

class Evolution
{
    
    
public:
    
    Evolution (double targetMaximumFitness, int maxEpochCnt, int mutationRate, int maxPatienceCnt, int maxUselessShuffle);
    void addChromosome (Chromosome);
    Chromosome train(ostream*);
    vector<Chromosome> getResults ();
    
    
private:
    
    vector<Chromosome> population;
    vector<Chromosome> resultsSimulation;
    int popSize;
    double currentMaximumFitness;
    double targetMaximumFitness;
    double averageMaxFitness;
    int maxEpochCnt;
    int currEpochCnt;
    int patienceCnt;
    double maxFitness;
    double patienceAvgMaxFitness;
    double mutationRate;
    int maxPatienceCnt;
    pair<Chromosome,Chromosome> marry (Chromosome , Chromosome );
    set<double> bestChromUniqueValues;
    void generateNewPopulation();
    void updateFitnessValues();
    
    double randDouble(double fMin, double fMax);
    
    double maxFitnessChromosomeVal;
    Chromosome maxChromosomeSoFar;
    
    void callHelper ();
    
    int maxUselessShuffle;
};


#endif