#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1EntityManager.h"
#include "Brofiler/Brofiler.h"
#include "j1Pathfinding.h"
#include "j1Gui.h"
#include "EntityRequest.h"


j1Scene::j1Scene() : j1Module()
{
	name.create("scene");

	Building_preview = false;
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	pugi::xml_node map;

	for (map = config.child("map"); map; map = map.next_sibling("map")) {
		p2SString lvlname;
		lvlname.create(map.attribute("name").as_string());
	}
	
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	LOG("Start scene");

	current_level = "test.tmx";
	debug = false;
	if (App->map->Load(current_level.GetString()) == true)
	{
		//App->audio->PlayMusic(App->map->data.music.GetString());

		LOG("%s", current_level.GetString());
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
		{
			LOG("Setting map %d", data[1]);
			App->pathfinding->SetMap(w, h, data);
		}
		else {
			LOG("Could not create walkability");
		}


		RELEASE_ARRAY(data);
	}
	
	//debug_tex = App->tex->Load("textures/maps/Tile_select.png");

	//App->entity->CreateEntity(DynamicEnt::DynamicEntityType::TEST_1, 100, 200);
	buttonNewGame = App->gui->CreateGuiElement(Types::button, 0, 0, { 444, 169, 244, 65 }, nullptr, this, NULL);
	buttonNewGame->setRects({ 444, 413, 244, 66 }, { 444, 661, 244, 65 });

	SDL_Rect rect = { 0, 0, 427, 218 };

	App->gui->CreateGuiElement(Types::text, 50, 14, rect, nullptr, this, "CONTINUE");
	App->gui->CreateGuiElement(Types::slider, 100, 100, { 28, 257, 12, 189 }, nullptr, this);
	App->gui->CreateGuiElement(Types::inputText, 400, 0, { 444, 661, 244, 65 }, nullptr, this);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate(float dt)
{
	BROFILER_CATEGORY("PreUpdate_Scene", Profiler::Color::Snow);


	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Update_Scene", Profiler::Color::Tomato);
		
//	App->render->Blit(Hello, 0, 0, NULL, 1.0f, 1.0f);

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		App->render->camera.y += 500*dt;
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		App->render->camera.x += 500*dt;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		App->render->camera.y -= 500*dt;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		App->render->camera.x -= 500*dt;
	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
		if (debug)debug = false;
		else {
			debug = true;
		}

	int x, y;
	App->input->GetMousePosition(x, y);
	
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->requests->AddRequest(Petition::SPAWN, 0.f, SpawnTypes::SWORDMAN, { x, y });
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		App->requests->AddRequest(Petition::SPAWN, 0.f, SpawnTypes::ARCHER, { x, y });
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN && !Building_preview) 
	{
		App->entity->CreateStaticEntity(StaticEnt::StaticEntType::TEST_3, p.x, p.y);
		Building_preview = true;
	}

	
	App->map->Draw();


	//This is to know the position of the mouse in tiles
	int xmouse, ymouse;
	App->input->GetMousePosition(xmouse, ymouse);
	map_coordinates = App->map->WorldToMap(xmouse - App->render->camera.x, ymouse - App->render->camera.y);

	//App->render->Blit(debug_tex, p.x, p.y);



	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate(float dt)
{
	bool ret = true;
	
	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	App->map->CleanUp();
	
	
	LOG("Freeing scene");

	return true;
}
bool j1Scene::Load(pugi::xml_node& data)
{
	LOG("Loading Scene state");
	return true;
}

// Save Game State
bool j1Scene::Save(pugi::xml_node& data) const
{
	LOG("Saving Scene state");
	

	pugi::xml_node scene = data.append_child("scenename");
	scene.append_attribute("name") = current_level.GetString();

	return true;
}


