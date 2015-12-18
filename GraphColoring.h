

#ifndef Graph_Coloring_GraphColoring_h
#define Graph_Coloring_GraphColoring_h


#include "Evolution.h"


int N;
int mat [10000][10000];
int popSize ;
double maxFitness;
int maxIterations;
double mutationRate;
int maxUselessShuffle;
int patienceTime;
int numOfColoredUsed ;
set<int> finalColors;
Chromosome target;
vector<Chromosome> simulationResults;
string relativePath; 
string defaultInputFileNames [12] = {"anna.col","david.col","fpsol2.i.1.col","games120.col","homer.col","huck.col","jean.col","miles250.col",
    "miles1000.col", "myciel3.col", "myciel4.col", "myciel5.col"};
string outputPath;
vector<string> inputFileNames;


double fitnessFunction (Chromosome* ch);
double checkError ();
void mutationFunction (Chromosome* ch);
void buildGraphFromDIMACS (int);
void colorGraph (int = -1);



#endif



void init ()
{
    simulationResults.clear();
    numOfColoredUsed = 0;
    finalColors.clear();
    
    outputPath = "";
    outputPath+=relativePath;
    outputPath+="results/";
    
    inputFileNames.resize(3000);
    for (int i=0; i<12; i++)
        inputFileNames[i] = defaultInputFileNames[i];
    
    
}


void buildGraphFromDIMACS(int idx)
{
    string filePath = "";
    filePath+=relativePath;
    filePath+="input data/";
    filePath+=inputFileNames[idx];
    filePath+=".txt";
    
    outputPath+=inputFileNames[idx];
    outputPath+=".txt";
    
    ifstream IN (filePath);
    
    if (IN.fail()) throw ("CAN'T OPEN " + filePath);
    
    string inp;
    IN >> inp;
    while (!IN.eof() && inp!="edge"){
        IN >> inp;
    }
    
    IN >> N;
    IN >> inp;
    
    char e;
    int u,v;
    memset(mat, 0, sizeof mat);
    IN >> e;
    
    while (!IN.eof())
    {
        IN >> u >> v;
        mat[u][v] = 1;
        IN >> e;
    }
    IN.close();
}


void colorGraph(int idx)
{
    
    init ();
    
    if (idx != -1) buildGraphFromDIMACS(idx);
    else{
        
        
        
        
        int currEdgeCnt = 0;
        for (int i=0; i<N; i++)
        {
            for (int j=0; j<N; j++)
            {
                if (i==j) mat[i][j] = 0;
                else if (mat[j][i] == 1) mat[i][j] = 0;
                else mat[i][j] = rand() % 2;
                
                if (mat[i][j] == 1)
                    currEdgeCnt++;
            }
        }
        
        outputPath+="GRAPH: ";
        outputPath+= to_string(N);
        outputPath+= " " ;
        outputPath+= to_string(currEdgeCnt);
        outputPath+=".txt";
    }

    ofstream OUT (outputPath);
    if (OUT.fail()) throw "FAILED TO OPEN " + outputPath;
    
    OUT << "GRAPH IS : " << endl;
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            OUT << mat[i][j] << ' ';
        }
        OUT << endl;
    }
    OUT << endl << endl;
    OUT << endl << endl << "----------------------------" << endl << endl;
    
    
    Evolution evolution (maxFitness, maxIterations,mutationRate,patienceTime,maxUselessShuffle);
    
    
    for (int i=0; i<popSize; i++)
    {
        Chromosome ch (mutationFunction, fitnessFunction);
        for (int j=0; j<N; j++)
        {
            ch.addGene(1);
        }
        evolution.addChromosome(ch);
    }
    
    
    target = evolution.train(&OUT);
    simulationResults = evolution.getResults();
    
    
    OUT << endl << endl << "END " << "------------------------" << endl;
    OUT <<"ERROR: " << checkError() << endl;
    OUT << "NUM OF COLORS USED = " << numOfColoredUsed << endl;
    OUT.close();
}





double fitnessFunction (Chromosome* ch)
{
    
    double ret = 0;
    set<int> colorsUsed ;
    for (int u=0; u<N; u++)
    {
        int uClr = ch->getGeneAt(u);
        colorsUsed.insert(uClr);
        for (int v=0; v<N; v++)
        {
            if (mat[u][v])
                if (ch->getGeneAt(v) == uClr)
                    ret++;
        }
    }
    
    return -(  50 * (colorsUsed.size()-1) +  1000 * ret) / N;
}


double checkError ()
{
    double err = 0;
    int edges = 0;
    for (int i=0; i<N; i++)
    {
        finalColors.insert((int)target.getGeneAt(i));
        for (int j=0; j<N; j++)
        {
            if (mat[i][j])
            {
                edges++;
                if ((int)target.getGeneAt(i) == (int)target.getGeneAt(j)){
                    
                    err++;
                }
            }
        }
    }
    numOfColoredUsed = finalColors.size();
    
    
    if (edges == 0 ) return err;
    else return (err / edges);
}


void mutationFunction (Chromosome* ch){
    
    for (int u=0; u<N; u++){
        int uClr = ch->getGeneAt(u);
        for (int v=0; v<N; v++)
        {
            if (ch->getGeneAt(v) == uClr){
                ch->setGene(u,rand());
                
            }
        }
    }
    
}



















