//
//  Chromosome.cpp
//  Graph Coloring
//
//  Created by MacBook Pro on 12/18/15.
//  Copyright (c) 2015 AUC. All rights reserved.
//

#include "Chromosome.h"

Chromosome :: Chromosome (mutationFunctionPtr mutationFun, fitnessFunctionPtr fitnessFun )
{
    
    this->chromosomeSize = 0;
    this-> mutationFun = mutationFun;
    this->fitnessFun = fitnessFun;
}

mutationFunctionPtr Chromosome::getMutationFunctionPtr()
{
    return this->mutationFun;
    
}

fitnessFunctionPtr Chromosome::getFitnessFunctionPtr()
{
    return this->fitnessFun;
}

void Chromosome :: addGene (double gene)
{
    this->genes.push_back(gene);
    this->chromosomeSize++;
}

void Chromosome::popGene(){
    this->genes.pop_back();
    this->chromosomeSize--;
}

int Chromosome::size(){
    return this->chromosomeSize;
}

void Chromosome :: mutate()
{
    mutationFun(this);
    updateFitness();
}

void Chromosome::setGene(int idx, double val)
{
    genes[idx] = val;
}

vector<double> Chromosome::getGenes()
{
    return this->genes;
}

double Chromosome::getGeneAt(int idx)
{
    if (idx>=genes.size())
        throw "GENES ARRAY OUT OF RANGE";
    double ret = genes[idx];
    return ret;
}

void Chromosome::updateFitness()
{
    this->fitness = fitnessFun(this);
}

double Chromosome::getFitness()
{
    return this->fitness;
}

double Chromosome :: randDouble(double fMin, double fMax)
{
    
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}



bool Chromosome::operator<(const Chromosome& guest) const
{
    return this->fitness < guest.fitness;
}