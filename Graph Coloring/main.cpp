
/* Graph Coloring Using Genetic Algorithms*/
/* Copyrights @zare3 2015*/
/*For more info, don't hesitate to contact me at zare3@aucegypt.edu*/



#include "GraphColoring.h"





int main(int, char const**)
{
    
    srand(time(NULL));
    
    /* IF YOU WANT US TO GENERATE A RANDOM GRAPH FOR YOU*/
    
    N = 10; // number of nodes in the graph
    
    /* you can do this by not sending an argument to colorGraph() -- see below in the code */
    
    
    
    
    /*------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------------------------------------*/
    
    
    /* if you send an argument to colorGraph(idx), it will use idx to generate a graph according to this dictionary of graphs
     
     "anna.col"             0
     "david.col"            1
     "fpsol2.i.1.col"       2
     "games120.col"         3
     "homer.col"            4
     "huck.col"             5
     "jean.col"             6
     "miles250.col"         7
     "miles1000.col"        8
     "myciel3.col"          9
     "myciel4.col"          10
     "myciel5.col"          11
     
     The graphs could be found in /input data OR you can find them here: http://mat.gsia.cmu.edu/COLOR/instances.html
     
     ---- if you want to add more graphs to the dictionary, you can do so by this statement:
     ---- inputFileNames[i] = "newGraph"; -- i should start from 12 -- and maximumly: 2999
     ---- such that newGraph.txt should be in the /input data folder, and should abide by the same descripting syntax in the anna.col, david.col, .... ---
     
     */
    
    

    
    /*------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------------------------------------*/
    
    
    
    /*relative path to search for the /input data and to search for /results*/
    /* if you're using an OS that supports relative paths, leave this empty*/
    
    
    //relativePath = ""; // windows or linux
    
    
    relativePath = "/Users/Home/AUC/Fall 15/Neural/Project/Graph Coloring/"; // osx
    
    
    
    /*------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------------------------------------*/
    
    
    
    /* Genetic Algorithm Variables */
    popSize = 200; // population size
    maxFitness = -0.1; // stop when fitness reaches maxFitness
    mutationRate = 100; //for each 2 new children, i select one randomly to mutate, but this process happens with a mutationRate possibility (0 - 100)
    maxIterations = 5000; // when you reach maxIterations, end training
    patienceTime = 70; // when generations saturate for patienceTime generations, the helper function gets called
    maxUselessShuffle = 2 ; // maximum number of times to call the helper function
    // the helper function is a function designed to kill saturation and increase maximum fitness
    
    
    
    
    
    /*------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------------------------------------*/
    
    
    
    for (int i=0; i<12; i++){
        
        try{
            colorGraph(i);
            
        }
        catch (string err)
        {
            cout << err << endl;
        }
    }
    
    cout << " END " << endl;
    return 0;
}
