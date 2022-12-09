//#include "header.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <CL/cl.hpp>

void DrawParticles(float* particles);



#define randf() static_cast <float> (rand()) / static_cast <float> (RAND_MAX)

const unsigned int WINDOW_WIDTH = 500;
const unsigned int WINDOW_HEIGHT = 500;
const double G = 0.0000000001;
const int PARTICLEAMOUNT = 3;
float particles[PARTICLEAMOUNT * 5];

static byte windowBuffer[WINDOW_WIDTH * WINDOW_HEIGHT * 4];


int main() {
	std::cout << "start\n";
	//cl::Platform platfrom;
	//cl_float8 aa = { 2, 3, 4, 5, 6, 7, 8, 9 };

    srand(0);
    for (int i = 0; i < PARTICLEAMOUNT; i += 5) {
        particles[i] = randf() * 0.2f + 0.4f;
        particles[i + 1] = randf() * 0.2f + 0.4f;
        particles[i + 2] = 0;
        particles[i + 3] = 0;
        particles[i + 4] = randf();
    }

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "N-Body simulation");
    //window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "N-Body simulation");

    sf::Texture windowTexture;
    windowTexture.update(windowBuffer);
    sf::Sprite windowSprite;
    windowSprite.setTexture(windowTexture);
    
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        memset(windowBuffer, 0, sizeof(windowBuffer));
        DrawParticles(particles);
        windowTexture.update(windowBuffer);
        windowSprite.setTexture(windowTexture);
        window.draw(windowSprite);
        window.display();
        //std::cout << "aa\n";
    }

	std::cout << "end\n";
	return 0;
}

void DrawParticles(float * particles) {
    for (int i = 0; i < PARTICLEAMOUNT; i += 5) {
        if (particles[i] < 0 || particles[i] >= 1.0 || particles[i + 1] < 0 || particles[i + 1] >= 1.0)
            return;

        int x = (int)(particles[i] * WINDOW_WIDTH);
        int y = (int)(particles[i + 1] * WINDOW_HEIGHT);

        int index = (y * WINDOW_WIDTH + x) * 4;

        windowBuffer[index] = (byte)255;
        windowBuffer[index + 1] = (byte)255;
        windowBuffer[index + 2] = (byte)255;
        windowBuffer[index + 3] = (byte)255;

        if (i == 0) {
            std::cout << index << "\n";
        }
    }
}