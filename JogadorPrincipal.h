#pragma once
#include "Jogador.h"

enum JogadorPrincipal_Animation_States { IDLE = 0, MOVING_LEFT = 1, MOVING_RIGHT = 2, JUMPING = 3, HIT_LEFT = 4, HIT_RIGHT = 5};

class JogadorPrincipal : public Jogador
{
private:
	const int vidaMaxima;

	sf::Vector2i size;
	sf::Clock animationTimer;

	//Animation
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;
private:
	void initAnimations();

public:
	JogadorPrincipal(sf::Vector2f posicao = sf::Vector2f(0.f, 0.f), sf::Vector2f tamanho = sf::Vector2f(50.f, 50.f));
	~JogadorPrincipal();

	const bool& getAnimSwitch();
	void resetAnimationTimer();

	void initSprite();

	void update();
	void updateMovimento();
	void updateAnimations();
};

