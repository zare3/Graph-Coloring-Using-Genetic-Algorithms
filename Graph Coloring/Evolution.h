//
//  Evolution.h
//  Neural Assignment 4
//
//  Created by MacBook Pro on 12/3/15.
//  Copyright (c) 2015 AUC. All rights reserved.
//

#ifndef Neural_Assignment_4_Evolution_h
#define Neural_Assignment_4_Evolution_h

#include "Chromosome.h"
#include "Visualisation Variables.h"
#include <vector>
#include <iomanip>
using namespace std;

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

Evolution :: Evolution (double targetMaximumFitness, int maxEpochCnt, int mutationRate, int maxPatienceCnt, int maxUselessShuffle)
{
    this -> targetMaximumFitness = targetMaximumFitness;
    this -> maxEpochCnt = maxEpochCnt;
    this->popSize = 0;
    this->averageMaxFitness = -1e9;
    this->currentMaximumFitness = -1e9;
    this->currEpochCnt = 0;
    this -> mutationRate = mutationRate;
    this-> patienceCnt = 0;
    this->maxFitness = -1e9;
    this->maxPatienceCnt = maxPatienceCnt;
    this->patienceAvgMaxFitness = -1e9;
    this->maxFitnessChromosomeVal = -1e9;
    this->maxUselessShuffle = maxUselessShuffle;
    
}

Chromosome Evolution::train(ostream* outS)
{
    ostream& o = *outS;
    int currentUselessShuffleCnt = 0;
    
    while (currentMaximumFitness < targetMaximumFitness && currEpochCnt < maxEpochCnt)
    {
        
        generateNewPopulation();
        o << "EPOCH: " << currEpochCnt << " MAX:  " << setprecision(9) << fixed << currentMaximumFitness << "    " << "AVG:  " << averageMaxFitness << endl;
        
        cout << "EPOCH: " << currEpochCnt << " MAX:  " << setprecision(9) << fixed << currentMaximumFitness << "    " << "AVG:  " << averageMaxFitness << endl;
        
        this->currEpochCnt++;
        
        if (maxFitnessChromosomeVal < population[0].getFitness()){
            maxFitnessChromosomeVal = population[0].getFitness();
            maxChromosomeSoFar = population[0];
            
            bestChromUniqueValues.clear();
            for (int i=0; i<maxChromosomeSoFar.size(); i++)
                bestChromUniqueValues.insert(maxChromosomeSoFar.getGeneAt(i));
        }
        resultsSimulation.push_back(population[0]);
        
        if (population[0].getFitness() == maxFitness && averageMaxFitness == patienceAvgMaxFitness){
            patienceCnt++;
        }
        else{
            maxFitness = population[0].getFitness();
            patienceAvgMaxFitness = averageMaxFitness;
        }
        
        
        if (patienceCnt >= maxPatienceCnt){
            
            
            o << "HELPER:  ...."<< endl;
            
            patienceCnt = 0;
            
            if (currentUselessShuffleCnt >= maxUselessShuffle)
                break;
            currentUselessShuffleCnt++;
            
            /*Chromosome testCh = population[0];
            for (int i=0; i<testCh.size(); i++)
            {
                
                for (auto j : bestChromUniqueValues)
                {
                    double oldFit = testCh.getFitness();
                    double oldGene = testCh.getGeneAt(i);
                    testCh.setGene(i, j);
                    testCh.updateFitness();
                    double newFit = testCh.getFitness();
                    
                    if (newFit < oldFit){
                        testCh.setGene(i, oldGene);
                        testCh.updateFitness();
                    }
                    
                }
            }
            
            population.push_back(testCh);
            
            for (int i=0; i< (int)(popSize * 0.4); i++){
                
                Chromosome newCh = testCh;
                int rnd = rand () % 2;
                if (rnd){
                    newCh.mutate();
                    population.push_back(newCh);
                }
                
            }*/
            
        }
        
        
        
        
    }
    
    
    
    o << "---------------------------" << endl;
    
    for (int i=0; i<maxChromosomeSoFar.size(); i++)
    {
        o << "CH: " << i << " " << maxChromosomeSoFar.getGeneAt(i) << endl;
    }
    o << endl << endl << endl;
    
    
    resultsSimulation.push_back(maxChromosomeSoFar);
    
    
    return maxChromosomeSoFar;
    
}

vector<Chromosome> Evolution::getResults()
{
    return this->resultsSimulation;
}

void Evolution::generateNewPopulation()
{
    vector<Chromosome> newGeneration;
    for (int i=0; i<popSize; i++){
        
        
        
        int p1,p2,p3,p4;
        int firstParent, secondParent;
        
        p1 = rand () % population.size();
        p2 = rand () % population.size();
        p3 = rand () % population.size();
        p4 = rand () % population.size();
        
        if (population[p1] < population[p2])
            firstParent = p2;
        else firstParent = p1;
        
        if (population[p3] < population[p4])
            secondParent = p4;
        else secondParent = p3;
        pair<Chromosome,Chromosome> children = marry(population[firstParent], population[secondParent]);
        
        
        double rnd = rand () % 101;
        
        if (mutationRate >= rnd){
            
            int intRnd = rand() % 2;
            if (intRnd){
                children.first.mutate();
            }
            else children.second.mutate();
            
        }
        
        
        population.push_back(children.first);
        population.push_back(children.second);
        
        
    }
    
    
    for (int i=0; i<newGeneration.size(); i++){
        population.push_back(newGeneration[i]);
    }
    
    sort (population.rbegin(), population.rend());
    population.erase(population.begin()+popSize, population.end());
    
    
    updateFitnessValues();
}

void Evolution::updateFitnessValues()
{
    currentMaximumFitness = population[0].getFitness();
    double sum = 0;
    for (int i=0; i<population.size(); i++)
    {
        sum += (population[i].getFitness());
    }
    sum /= population.size();
    this->averageMaxFitness = sum;
}

void Evolution::addChromosome(Chromosome ch)
{
    ch.updateFitness();
    this->popSize++;
    this->population.push_back(ch);
}

pair<Chromosome,Chromosome> Evolution::marry(Chromosome parent1, Chromosome parent2)
{
    
    Chromosome child1 (parent1.getMutationFunctionPtr(),parent1.getFitnessFunctionPtr());
    Chromosome child2 ( parent1.getMutationFunctionPtr(),parent1.getFitnessFunctionPtr());
    int pivot = rand() % parent1.size();
    
    for (int i=0; i<parent1.size(); i++){
        
        if (i < pivot)
            child1.addGene(parent1.getGeneAt(i));
        else child1.addGene(parent2.getGeneAt(i));
    }
    
    for (int i=0; i<parent1.size(); i++){
        
        if (i < pivot)
            child2.addGene(parent2.getGeneAt(i));
        else child2.addGene(parent1.getGeneAt(i));
    }
    
    child1.updateFitness();
    child2.updateFitness();
    
    return {child1,child2};
}


double Evolution::randDouble(double fMin, double fMax)
{
    
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}