#include "SDL2/SDL.h"
#include <iostream>
#include "GameEntity.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAX_BULLETS = 8;
const int MAX_ENEMY_BULLETS = 20;
const int MAX_BANDITS = 5;
SDL_Window *window = nullptr;
SDL_Surface *screenSurface = nullptr;
SDL_Surface *gameLogo = nullptr;
cowboys::GameEntity *sheriff = nullptr;
cowboys::GameEntity *bullet[MAX_BULLETS];
cowboys::GameEntity *bandit[MAX_BANDITS];
cowboys::GameEntity *enemyBullet[MAX_ENEMY_BULLETS];
bool upheld = false;
bool downheld = false;
bool leftheld = false;
bool rightheld = false;
bool spaceheld = false;
void gameInit();
void gameDraw();
void gameQuit();
void processKeyDowns(int);
void processKeyUps(int);
cowboys::GameEntity* getNextBullet();
cowboys::GameEntity* getNextEnemyBullet();
int main(int argc, char* args[]){
	srand(time(0));

	SDL_Init(SDL_INIT_VIDEO);
	gameInit();
	SDL_Event e;
	bool quit = false;
	int framestep = 0;
	while (!quit){
		++framestep;
		if (framestep > 1024){
			framestep = 0;
		}
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				quit = true;
			}else if (e.type == SDL_KEYDOWN){
				processKeyDowns(e.key.keysym.sym);
			}else if (e.type == SDL_KEYUP){
				processKeyUps(e.key.keysym.sym);
			}
		}
		if (leftheld){
			sheriff->rect.x -= 1;
		}
		if (rightheld){
			sheriff->rect.x += 1;
		}
		if (upheld){
			sheriff->rect.y -= 1;
		}
		if (downheld){
			sheriff->rect.y += 1;
		}
		for (int i = 0; i < MAX_BULLETS; ++i){
			if (bullet[i]->rect.x < SCREEN_WIDTH){
				bullet[i]->rect.x += 2;
			}
		}
		for (int i = 0; i < MAX_ENEMY_BULLETS; ++i){
			if (enemyBullet[i]->rect.x > 0){
				enemyBullet[i]->rect.x -= 2;
			}
		}
		for (int i = 0; i < MAX_BANDITS; ++i){
			if (framestep == (bandit[i]->rect.x)){
				cowboys::GameEntity *nextEnemyBullet = getNextEnemyBullet();
				nextEnemyBullet->rect.x = bandit[i]->rect.x;
				nextEnemyBullet->rect.y = bandit[i]->rect.y;
			}
		}
		gameDraw();
	}
	gameQuit();
	return 0;
}

void gameInit(){
	window = SDL_CreateWindow("Hello World",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	screenSurface = SDL_GetWindowSurface(window);
	SDL_Surface *gameLogo_raw = SDL_LoadBMP("cowboys.bmp");
	gameLogo = SDL_ConvertSurface(gameLogo_raw,screenSurface->format,0);
	SDL_FreeSurface(gameLogo_raw);
	gameLogo_raw = nullptr;
	sheriff = new cowboys::GameEntity("sheriff.bmp",screenSurface);
	for (int i = 0; i < MAX_BULLETS; i++){
		bullet[i] = new cowboys::GameEntity("bullet.bmp",screenSurface);
		bullet[i]->rect.x = SCREEN_WIDTH +1;
		bullet[i]->rect.y = SCREEN_HEIGHT +1;
	}
	for (int i = 0; i < MAX_BANDITS; i++){
		bandit[i] = new cowboys::GameEntity("bandit.bmp",screenSurface);
		bandit[i]->rect.x = rand()%SCREEN_WIDTH;
		bandit[i]->rect.y = rand()%(SCREEN_HEIGHT/2) + SCREEN_HEIGHT/2;
	}
	for (int i = 0; i < MAX_ENEMY_BULLETS; i++){
		enemyBullet[i] = new cowboys::GameEntity("bullet.bmp",screenSurface);
		enemyBullet[i]->rect.x = 2;
		enemyBullet[i]->rect.y = 2;
	}
	sheriff->rect.x = 256;
	sheriff->rect.y = 256;
}

void gameDraw(){
	SDL_BlitSurface(gameLogo,nullptr,screenSurface,nullptr);
	SDL_BlitSurface(sheriff->surface,nullptr,screenSurface,&sheriff->rect);
	for (int i = 0; i < MAX_BULLETS; i++){
		SDL_BlitScaled(bullet[i]->surface,nullptr,screenSurface,&bullet[i]->rect);
	}
	for (int i = 0; i < MAX_BANDITS; i++){
		SDL_BlitScaled(bandit[i]->surface,nullptr,screenSurface,&bandit[i]->rect);
	}
	for (int i = 0; i < MAX_ENEMY_BULLETS; i++){
		SDL_BlitScaled(enemyBullet[i]->surface,nullptr,screenSurface,&enemyBullet[i]->rect);
	}
	SDL_UpdateWindowSurface(window);
}

void gameQuit(){
	SDL_FreeSurface(gameLogo);
	gameLogo = nullptr;
	delete(sheriff);
	sheriff = nullptr;
	for (int i = 0; i < MAX_BULLETS; i++){
		delete(bullet[i]);
		bullet[i] = nullptr;
	}
	for (int i = 0; i < MAX_BANDITS; i++){
		delete(bandit[i]);
		bandit[i] = nullptr;
	}
	for (int i = 0; i < MAX_ENEMY_BULLETS; i++){
		delete(enemyBullet[i]);
		enemyBullet[i] = nullptr;
	}
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

int nextBulletIndex = 0;
cowboys::GameEntity *getNextBullet(){
	cowboys::GameEntity *nextBullet = bullet[nextBulletIndex++];
	if (nextBulletIndex > MAX_BULLETS - 1){
		nextBulletIndex = 0;
	}
	return nextBullet;
}

int nextEnemyBulletIndex = 0;
cowboys::GameEntity *getNextEnemyBullet(){
	cowboys::GameEntity *nextEnemyBullet = enemyBullet[nextEnemyBulletIndex++];
	if (nextEnemyBulletIndex > MAX_ENEMY_BULLETS - 1){
		nextEnemyBulletIndex = 0;
	}
	return nextEnemyBullet;
}

void processKeyDowns(int keycode){
	switch (keycode){
	case SDLK_UP:
		upheld = true;
		break;
	case SDLK_DOWN:
		downheld = true;
		break;
	case SDLK_LEFT:
		leftheld = true;
		break;
	case SDLK_RIGHT:
		rightheld = true;
		break;
	case SDLK_SPACE:
		if (!spaceheld){
		cowboys::GameEntity *nextBullet = getNextBullet();
		nextBullet->rect.x = sheriff->rect.x+35;
		nextBullet->rect.y = sheriff->rect.y+32;
		spaceheld = true;
		}
		break;
	case SDLK_LSHIFT:
		for (int i = 0; i < MAX_BANDITS; i++){
			bandit[i]->rect.x = rand()%(SCREEN_WIDTH - bandit[i]->rect.w);
			bandit[i]->rect.y = rand()%(SCREEN_HEIGHT/2 - bandit[i]->rect.h) + SCREEN_HEIGHT/2;
		}
		break;
	}
}

void processKeyUps(int keycode){
	switch (keycode){
	case SDLK_UP:
		upheld = false;
		break;
	case SDLK_DOWN:
		downheld = false;
		break;
	case SDLK_LEFT:
		leftheld = false;
		break;
	case SDLK_RIGHT:
		rightheld = false;
		break;
	case SDLK_SPACE:
		spaceheld = false;
		break;
	}
}
