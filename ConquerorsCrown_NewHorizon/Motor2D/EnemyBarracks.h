#ifndef __ENEMYBARRACKS_H__
#define __ENEMYBARRACKS_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "j1Entity.h"
#include "StaticEnt.h"
#include "EntityRequest.h"

class EnemyBarracks : public StaticEnt
{
public:
	// Constructor
	EnemyBarracks(int posx, int posy);

	// Destructor
	~EnemyBarracks();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate(float dt);

	bool CleanUp();

	// Animation
	void checkAnimation(float dt);

	// UI

	//Queue

	//FreeTile
	iPoint Searchtile(iPoint respawn);

public:
	// Animations
	Animation inconstruction;
	Animation finishedconst2;
	SDL_Rect Construction;
	SDL_Rect Created;

	// Stats
	int attackrange;
	int collrange;

	// Queue


	// Queue_v2

	
	// UI
	

	//UI BARRACK


	//UI Progress Bar


	// Queue positions
	//iPoint pos0;
	//iPoint pos1;
	//iPoint pos2;
	//iPoint pos3;
	//iPoint pos4;
	//iPoint pos5;

private:
	iPoint respawn;

};
#endif // __TEST_1_H__
