/*
 * GameEntity.h
 *
 *  Created on: Sep 29, 2014
 *      Author: aezart
 */

#ifndef GAMEENTITY_H_
#define GAMEENTITY_H_
#include "SDL2/SDL.h"
#include <iostream>
namespace cowboys {

class GameEntity {
public:
	SDL_Surface *surface = nullptr;
	std::string bitmap;
	SDL_Rect rect;
	GameEntity(std::string, SDL_Surface*);
	virtual ~GameEntity();
};

} /* namespace cowboys */

#endif /* GAMEENTITY_H_ */
