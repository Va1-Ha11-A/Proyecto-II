#ifndef __j1EntityManager_H__
#define __j1EntityManager_H__
	
#include "PugiXml/src/pugixml.hpp"
#include "j1Module.h"
#include "p2Point.h"
#include "ResourceEntities.h"
#include "GoldMine.h"
#include "j1Entity.h"
#include "DynamicEnt.h"
#include "GoldMine.h"
#include "StaticEnt.h"
#include <list>

using namespace std;

struct SDL_Texture;
class ParticleSystem;
class Emiter;

class j1EntityManager : public j1Module
{
public:
	// Constructor
	j1EntityManager();

	// Destructor
	~j1EntityManager();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	// Create a new entity
	j1Entity* CreateEntity(DynamicEnt::DynamicEntityType type, int posx = 0, int posy = 0);

	j1Entity* CreateStaticEntity(StaticEnt::StaticEntType type, int posx = 0, int posy = 0, uint resource_type = 0, uint amount = 2000u);

	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&)const;
	ParticleSystem* CreateParticleSys(int posx = 0, int posy = 0 );

	// Delete an entity
	bool j1EntityManager::DeleteEntity(int id, j1Entity* entity);
	bool j1EntityManager::DeleteParticles(int id, j1Entity* entity);

	bool DeleteAllEntities();

	void LoadAnimations(const char* path, list<Animation*>& animations);

	//Check if any entity is selected
	bool IsSomethingSelected();

protected:
	TileSetEntity TileSetData;

public:
	vector<j1Entity*> entities;
	vector<j1Entity*> particles;
	vector<j1Entity*> player_dyn_ent;
	vector<j1Entity*> ai_dyn_ent;
	vector<j1Entity*> player_stat_ent;
	vector<j1Entity*> ai_stat_ent;
	vector<j1Entity*> resources_ent;
	vector<GoldMine*> mines;

	// Task times --------------------
	uint trees_time;
	uint mines_time;
	uint quarries_time;
	// ------------------------------

	SDL_Texture* foot_man_tex = nullptr;
	SDL_Texture* arch_man_tex = nullptr;
	SDL_Texture* foot_man_tex2 = nullptr;
	SDL_Texture* foot_man_tex3 = nullptr;
	SDL_Texture* arch_man_tex2 = nullptr;
	SDL_Texture* arch_man_tex3 = nullptr;
	SDL_Texture* gather_man_tex = nullptr;
	SDL_Texture* knight_tex = nullptr;
	SDL_Texture* knight_tex2 = nullptr;
	SDL_Texture* troll_tex = nullptr;
	SDL_Texture* ally_sel_tex = nullptr;
	SDL_Texture* enemy_sel_tex = nullptr;
	SDL_Texture* ogre_tex = nullptr;
	SDL_Texture* grunt_tex = nullptr;

	int			max_audio_attacks;
	int volume;
	j1PerfTimer	timer;

	// Animations ----------------------
	list<Animation*> archer_animations;
	list<Animation*> footman_animations;
	list<Animation*> gatherer_animations;
	list<Animation*> knight_animations;
	list<Animation*> troll_animations;
	list<Animation*> ogre_animations;
	list<Animation*> grunt_animations;
	// ---------------------------------

	SDL_Texture* building = nullptr;
	SDL_Texture* enemy_building = nullptr;
	SDL_Texture* miscs = nullptr;
	SDL_Texture* arrow = nullptr;
	SDL_Texture* life_bar = nullptr;

	bool pause;
	bool lights;

	// Load entities textures
};

#endif // __j1EntityManager_H__