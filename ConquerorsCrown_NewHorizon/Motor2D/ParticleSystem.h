#pragma once
#include "j1Entity.h"
#include "vector"

class Emiter;

class ParticleSystem : public j1Entity
{
public:
	ParticleSystem();
	ParticleSystem(float x, float y);

	~ParticleSystem();

	void PushEmiter(Emiter& emiter);

	bool Update(float dt);
	bool PostUpdate(float dt);

	void Desactivate();
	void Activate();

	bool IsActive();

	void Move(int x, int y);

private:
	std::vector<Emiter> emiterVector;
	std::vector<float>	position;

	bool active;
};
