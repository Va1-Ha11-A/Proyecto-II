#ifndef __j1APP_H__
#define __j1APP_H__

#include "j1Module.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "PugiXml\src\pugixml.hpp"
#include <list>

using namespace std;

#define MAXTEXT 100
// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Scene;
class j1Map;
class j1EntityManager;
class j1Entity;
class j1PathFinding;
class j1GroupMov;
class j1Gui;
class j1Fonts;
class j1Minimap;
class EntityRequest;
class j1FadeToBlack;
class j1WaveSystem;
class j1CutsceneManager;
class j1Tutorial;
class FoWManager;
class j1Video;
class ModuleParticles;
class MouseCursor;
class ModuleAssetsManager;


class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	void LoadGame();
	void SaveGame() const;
	void GetSaveGames(list<p2SString>& list_to_fill) const;


	bool Pause();
	bool GetPause();

	bool CheckSaveGame();

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow();
public:

	// Modules
	j1Window*			win = NULL;
	j1Input*			input = NULL;
	j1Render*			render = NULL;
	j1Textures*			tex = NULL;
	j1Audio*			audio = NULL;
	j1Scene*			scene = NULL;
	j1Map*				map = NULL;
	j1EntityManager*	entity = NULL;
	j1PathFinding*		pathfinding = NULL;
	j1GroupMov*			movement = NULL;
	j1Gui*				gui = NULL;
	j1Fonts*			font = NULL;
	j1Minimap*			minimap = NULL;
	EntityRequest*		requests = NULL;
	j1FadeToBlack*		fade = NULL;
	j1WaveSystem*		wave = NULL;
	j1CutsceneManager* cutscene;
	FoWManager*			fowManager = NULL;
	j1Tutorial*			tutorial = NULL;
	j1Video*			video = NULL;
	MouseCursor*		mouse_cursor = NULL;
	ModuleAssetsManager* assetManager = NULL;




	uint32				framerate = 0u;
	pugi::xml_document	config_file;

	p2SString vsync;
	p2SString framecap;
	bool cap = false;
	bool				want_to_load;
	p2SString temp[MAXTEXT];

private:

	list<j1Module*>		modules;
	uint				frames;
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;

	mutable bool		want_to_save;
	p2SString			load_game;
	mutable p2SString	save_game;
	bool				pause = true;

	j1PerfTimer			ptimer;
	j1PerfTimer			delaytimer;
	uint64				frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0u;
	uint32				prev_last_sec_frame_count = 0u;
	float	dt;

public:

	bool				quitGame = false;
};

extern j1App* App; 

#endif