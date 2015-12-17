
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//



// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "GraphColoring.h"
#include <thread>
#include <map>
using namespace std;

/*

 string inputFileNames [16] = {"anna.col","david.col","fpsol2.i.1.col","games120.col","homer.col","huck.col","jean.col","miles250.col",
 "miles1000.col", "myciel3.col", "myciel4.col", "myciel5.col", "queen5_5.col", "queen6_6.col", "queen7_7.col",
 "queen8_8.col"};
 */
 


int main(int, char const**)
{
    
    srand(time(NULL));
    
    
    N = 10;
    maxNodesToBeRand = 16;
    popSize = 200;
    maxFitness = -0.1;
    mutationRate = 100;
    maxIterations = 5000;
    maxEdgeCnt = 5*N;
    patienceTime = 70;
    maxUselessShuffle = 2 ;
    
    for (int i=0; i<12; i++){
    
        buildGraph(i);
    }
    //loadUIVariables ();
    
    cout << " END " << endl;
    return 0;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Colored Graph");
    double scale = min ( window.getSize().x/(float)img.getSize().x, window.getSize().y/(float)img.getSize().y );
    scale/=1.1;
    imgSprite.setScale( scale, scale);
    
    // Start the game loop
    while (window.isOpen() && !DIMACS)
    {
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        // update the UI
        refreshUI(&window);
        //---------------------
            
    }
        
        
    
    
    return EXIT_SUCCESS;
}
