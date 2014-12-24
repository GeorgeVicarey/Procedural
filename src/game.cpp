/*
 * game.cpp
 *
 *  Created on: 10 Nov 2014
 *      Author: George Vicarey
 */

#include "game.h"
#include <iostream>
#include "stdio.h"

Game::Game() {
    window = NULL;
    screenSurface = NULL;
    mapSurface = NULL;
    map = new Map();
}

Game::~Game() {
    SDL_FreeSurface(screenSurface);
    SDL_FreeSurface(mapSurface);

    SDL_DestroyWindow(window);

    SDL_Quit();
}

/**
 * Initialise SDL so it's setup for OpenGL.
 */
bool Game::init() {
    SDL_Init(SDL_INIT_VIDEO);

    return true;
}

/**
 * initialise any game entities.
 */
bool Game::objectInit() {

    mapSurface = map->getSurface();
    if( mapSurface == NULL )
        {
            printf( "Unable to load image! SDL Error: %s\n", SDL_GetError() );

        }
    map->makeImage();
    std::cout << "image made" << std::endl;

    return true;
}

/**
 * Create an SDL window that's setup for OpenGL.
 */
bool Game::createWindow(const char* title, int width, int height) {
    // create SDL window
    window = SDL_CreateWindow(title, 100, 100, width, height, SDL_WINDOW_SHOWN);

    if (window == NULL) return false;
    else screenSurface = SDL_GetWindowSurface(window);

    return true;
}

/**
 * Empty method setup to easily handle events.
 */
bool Game::handleEvents(SDL_Event e) {

    return true;
}

/**
 * Games update method.
 */
bool Game::update() {

    return true;
}


/**
 * Games render method.
 */
bool Game::render() {

    SDL_BlitSurface(mapSurface, NULL, screenSurface, NULL);

    SDL_UpdateWindowSurface(window);

    return true;
}

/**
 * Swap out the openGL buffer to be called at every tick.
 */
void Game::swapBuffers() {
    SDL_GL_SwapWindow(window);
}
