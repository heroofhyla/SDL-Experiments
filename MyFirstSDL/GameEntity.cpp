/*
 * GameEntity.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: aezart
 */

#include "GameEntity.h"
#include "SDL2/SDL.h"

namespace cowboys {

GameEntity::GameEntity(std::string imageFile, SDL_Surface *screen) {
	SDL_Surface *surface_raw = SDL_LoadBMP(imageFile.c_str());
	surface = SDL_ConvertSurface(surface_raw,screen->format,0);
	SDL_FreeSurface(surface_raw);
	surface_raw = nullptr;
	rect.w = surface->w*2;
	rect.h = surface->h*2;
	rect.x = 0;
	rect.y = 0;
}

GameEntity::~GameEntity() {
	// TODO Auto-generated destructor stub
}

} /* namespace cowboys */
