#include "Level_Two.h"

Level_Two::Level_Two(Game* instance) :Level(instance)
{
	createGameobject(new Background("../assets/urban-landscape-background.png", instance));
	createGameobject(new Laserbarrier({ 500,100,20,2000 }, instance));
	createGameobject(new Laserbarrier({ 0,100,500,20 }, instance));
	createGameobject(new Laserbarrier({ 0,instance->window_h + 20,500,20 }, instance));
	createGameobject(new Laserbarrier({ -20,100,20,2000 }, instance));
	player = new Player(instance);
	createGameobject(player);
	createGameobject(new Enemy({ 600,700,100,100 }, instance));
	createGameobject(new Wall({ 600,800,100,1000 }, instance));
	createGameobject(new Enemy({ 850,300,100,100 }, instance));
	createGameobject(new Wall({ 850,400,100,1000 }, instance));
	createGameobject(new Enemy({ 1050,500,100,100 }, instance));
	createGameobject(new Wall({ 1050,600,100,1000 }, instance));
	createGameobject(new Enemy({ 1250,750,100,100 }, instance));
	createGameobject(new Wall({ 1250,850,100,1000 }, instance));
	createGameobject(new TextRender({ 750,100,0,0 }, "Listen to my heartbeat", 40, { 0,0,0,0 }, instance));

	one_star = new Sprite("../assets/OneStarRating.png", 1, { instance->window_w / 2 - 960 / 2,instance->window_h / 2 - 540 / 2,32,18 }, 200, instance);
	one_star->setSize(960, 540);
	one_star->setVisible(false);
	createGameobject(one_star);

	two_star = new Sprite("../assets/TwoStarRating.png", 1, { instance->window_w / 2 - 960 / 2,instance->window_h / 2 - 540 / 2,32,18 }, 200, instance);
	two_star->setSize(960, 540);
	two_star->setVisible(false);
	createGameobject(two_star);

	three_star = new Sprite("../assets/ThreeStarRating.png", 1, { instance->window_w / 2 - 960 / 2,instance->window_h / 2 - 540 / 2,32,18 }, 200, instance);
	three_star->setSize(960, 540);
	three_star->setVisible(false);
	createGameobject(three_star);

	popup_text_r = new TextRender({ instance->window_w / 2 - 960 / 2 + 50,instance->window_h / 2 + 540 / 8,0,0 }, "Restart(R)", 72, { 0,0,0,0 }, instance);
	popup_text_r->setVisible(false);
	createGameobject(popup_text_r);
	popup_text_c = new TextRender({ instance->window_w / 2 - 960 / 2 + 50,instance->window_h / 2 + 540 / 4,0,0 }, "Continue(Enter)", 72, { 0,0,0,0 }, instance);
	popup_text_c->setVisible(false);
	createGameobject(popup_text_c);
	m_background = Mix_LoadMUS("../assets/BackgroundMusic.wav");
	Mix_PlayMusic(m_background, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}

Level_Two::~Level_Two()
{
	Mix_FreeMusic(m_background);
}

void Level_Two::update(int delta)
{

	SDL_PollEvent(&instance->event);
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_R]) {
		Level_Two* lt = new Level_Two(instance);
		instance->unregisterGameobject(this);
		instance->registerGameobject(lt);
		SDL_Delay(200);
		delete this;
		return;
	}
	if (state[SDL_SCANCODE_RETURN] && allEnemiesDead())
	{
		Level_One* lo = new Level_One(instance);
		instance->unregisterGameobject(this);
		instance->registerGameobject(lo);
		SDL_Delay(200);
		delete this;
	}
	else if (allEnemiesDead())
	{
		if (player->shots == 1)
		{
			three_star->setVisible(true);
		}
		else if (player->shots <= 3)
		{
			two_star->setVisible(true);
		}
		else
		{
			one_star->setVisible(true);
		}
		popup_text_c->setVisible(true);
		popup_text_r->setVisible(true);
	}

}



void Level_Two::render()
{
}

bool Level_Two::allEnemiesDead()
{
	bool dead = true;
	for (int i = 0; i < lvlObjects.size(); i++)
	{
		std::string filter = "Enemy";
		if (lvlObjects[i]->type == filter)
		{
			Enemy* e = (Enemy*)lvlObjects[i];
			if (!e->dead)
			{
				dead = false;
			}
		}
	}
	return dead;
}