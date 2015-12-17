//
//  GraphColoring.h
//  Graph Coloring
//
//  Created by MacBook Pro on 12/13/15.
//  Copyright (c) 2015 AUC. All rights reserved.
//

#ifndef Graph_Coloring_GraphColoring_h
#define Graph_Coloring_GraphColoring_h


#endif

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <fstream>
#include "Evolution.h"
using namespace std;

#define DIMACS 1


int N;
int mat [10000][10000];
int allowedColors;

int popSize ;
double maxFitness;
int maxIterations;
double mutationRate;

Chromosome target;
int numOfColoredUsed ;
set<int> finalColors;

Texture img;
Sprite imgSprite;
sf::Clock clk;
sf::Text epochCnt;
sf::Text colorsUsedSoFar;
sf::Text colorsUsed;
sf :: Text bestSoFar;
sf::Font font;
int clrIdx;
bool canVisualise;
int simIdx;


int maxNodesToBeRand;
int maxEdgeCnt;
int patienceTime;




vector<Chromosome> simulationResults;

double fitnessFunction (Chromosome* ch);
void loadUIVariables ();
double checkError ();
void mutationFunction (Chromosome* ch);

int colorCnt;
int minClrCnt;
set<int> legend;

map<int,int> colorMap;
set<int> usedColorsSoFar;

CircleShape legendCircle;

int maxUselessShuffle;

string relativePath = "/Users/Home/AUC/Fall 15/Neural/Project/Graph Coloring/";

string inputFileNames [12] = {"anna.col","david.col","fpsol2.i.1.col","games120.col","homer.col","huck.col","jean.col","miles250.col",
    "miles1000.col", "myciel3.col", "myciel4.col", "myciel5.col"};
string outputPath;


void init ()
{
    usedColorsSoFar.clear();
    colorMap.clear();
    legend.clear();
    simulationResults.clear();
    simIdx = 0;	
    canVisualise = 1;
    clrIdx = 0;
    numOfColoredUsed = 0;
    finalColors.clear();
}


void buildGraphFromDIMACS(int idx)
{
    string filePath = "";
    filePath+=relativePath;
    filePath+="input data/";
    filePath+=inputFileNames[idx];
    filePath+=".txt";
    
    outputPath = "";
    outputPath+=relativePath;
    outputPath+="resultsWithoutHelper/";
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


void buildGraph(int idx = -1)
{
    colorCnt = 0;
    minClrCnt = 1e9;
    
    init ();
    
    if (DIMACS) buildGraphFromDIMACS(idx);
    else{
        int currEdgeCnt = 0;
        for (int i=0; i<N; i++)
        {
            for (int j=0; j<N; j++)
            {
                if (currEdgeCnt >= maxEdgeCnt && N >=maxNodesToBeRand ) mat[i][j] = 0;
                else if (i==j) mat[i][j] = 0;
                else if (mat[j][i] == 1) mat[i][j] = 0;
                else mat[i][j] = rand() % 2;
                
                if (mat[i][j] == 1)
                    currEdgeCnt++;
            }
        }
    }
    
    ofstream OUT (outputPath);
    if (OUT.fail()) throw "FAILED TO OPEN " + outputPath;
    
    int x = 25;
    int y = 30;
    for (int i=0; i<N; i++)
    {
        circles[i].setRadius(20);
        circles[i].setFillColor(sf::Color::Red);
        circles[i].setPosition(x, y);
        x+=50;
    }
    
    
    
    
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
    allowedColors = N*5;
    
    
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
    cout << "OUT " << endl;
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
    
    return -(  50 * (colorsUsed.size()-1) +  100 * ret) / N;
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
                ch->setGene(u,rand()%allowedColors);
                
            }
        }
    }
    
}






string convertFromRgbToHext (int r, int g, int b)
{
    unsigned long rgb = (r<<16)|(g<<8)|b;
    std::stringstream stream;
    stream << std::hex << rgb;
    std::string result = "";
    result+="#";
    result+=stream.str();
    
    while (result.size()<7)
        result.insert(1, "0");
    
    return result;
    
    
}

string drawGraph ()
{
    
    ofstream OUT ("/Users/Home/AUC/graphRep/hw.dot");
    string query = "";
    query+="graph {";
    query+="\n";
    
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            if (mat[i][j]){
                query+= to_string(i);
                query+= " -- ";
                query+= to_string(j);
                query+=";";
                query+= '\n';
            }
        }
    }
    
    for (int i=0; i<N; i++)
    {
        query+="\"";
        query+=to_string(i);
        query+="\" ";
        query+="[shape=circle, style=filled, fillcolor=\"";
        query+=convertFromRgbToHext(circles[i].getFillColor().r, circles[i].getFillColor().g, circles[i].getFillColor().b);
        query+="\"]\n";
    }
    query+="}";
    
    OUT << query;
    OUT.close();
    
    return "/Users/Home/AUC/graphRep/hw.png";
    
    
}



void loadUIVariables ()
{
    
    
    srand(time(NULL));
    
    
    font.loadFromFile(resourcePath() + "sansation.ttf");
    
    epochCnt.setPosition(1100, 550);
    epochCnt.setFont(font);
    epochCnt.setCharacterSize(40);
    epochCnt.setColor(sf::Color::Black);
    
    
    
    colorsUsed.setPosition(600, 550);
    colorsUsed.setFont(font);
    colorsUsed.setCharacterSize(40);
    colorsUsed.setColor(sf::Color::Black);
    colorsUsed.setString("colors usage solution " + to_string(numOfColoredUsed));
    
    
    colorsUsedSoFar.setPosition(600, 550);
    colorsUsedSoFar.setFont(font);
    colorsUsedSoFar.setCharacterSize(40);
    colorsUsedSoFar.setColor(sf::Color::Black);
    colorsUsedSoFar.setString("color usage so far " + to_string(1));
    
    
    bestSoFar.setPosition(120, 550);
    bestSoFar.setFont(font);
    bestSoFar.setCharacterSize(40);
    bestSoFar.setColor(sf::Color::Black);
    bestSoFar.setString("best: " + to_string(1));
    
    
    epochCnt.setString("CAN'T VISUALIZE MORE THAN 24 COLORS");
    
    if (numOfColoredUsed > 24){
        canVisualise = 0;
        epochCnt.setPosition(220, 250);
    }
    
    
    if (canVisualise){
        string pngPath = drawGraph();
        system("/usr/local/bin/dot -Tpng /Users/Home/AUC/graphRep/hw.dot  -o /Users/Home/AUC/graphRep/hw.png");
        img.loadFromFile("/Users/Home/AUC/graphRep/hw.png");
        imgSprite.setTexture(img);
        epochCnt.setString(to_string(simIdx));
    }
    
    
    
    
}


void refreshUI(RenderWindow* window)
{
    
    if (clk.getElapsedTime() >= milliseconds(1)){
        
        if (canVisualise){
            string pngPath = drawGraph();
            system("/usr/local/bin/dot -Tpng /Users/Home/AUC/graphRep/hw.dot  -o /Users/Home/AUC/graphRep/hw.png");
            img.loadFromFile("/Users/Home/AUC/graphRep/hw.png");
            imgSprite.setTexture(img);
            epochCnt.setString(to_string(simIdx));
        }
        
        
        
        usedColorsSoFar.clear();
        colorMap.clear();
        
        clrIdx = 0;
        if (simIdx < simulationResults.size()){
            legend.clear();
            for (int i=0; i<simulationResults[simIdx].size(); i++)
            {
                int nodeColor = (int) simulationResults[simIdx].getGeneAt(i);
                usedColorsSoFar.insert(nodeColor);
                if (colorMap.find(nodeColor)==colorMap.end()){
                    circles[i].setFillColor(colorsArray[clrIdx]);
                    legend.insert(clrIdx);
                    
                    colorMap[nodeColor] = clrIdx++;
                }
                else{
                    circles[i].setFillColor(colorsArray[colorMap[nodeColor]]);
                    legend.insert(colorMap[nodeColor]);
                }
                
                
            }
            
            simIdx++;
            colorCnt = usedColorsSoFar.size();
        }
        clk.restart();
        
        
        
        
        minClrCnt = min (minClrCnt, colorCnt);
        colorsUsedSoFar.setString("color usage so far " + to_string(colorCnt));
        bestSoFar.setString("best: " + to_string(minClrCnt));
        
        
        // Clear screen
        window->clear(Color::White);
        
        
        
        
        
        if (canVisualise)
            window->draw(imgSprite);
        
        
        legendCircle.setRadius(15);
        int posX = 1150;
        int posY = 30;
        
        for (auto c : legend)
        {
            legendCircle.setFillColor(colorsArray[c]);
            legendCircle.setPosition(posX, posY);
            window->draw(legendCircle);
            posY+=50;
        }
        
        
        
        window->draw(epochCnt);
        //window->draw(colorsUsed);
        window->draw(colorsUsedSoFar);
        window->draw(bestSoFar);
        // Update the window
        window->display();
        
    }
}


