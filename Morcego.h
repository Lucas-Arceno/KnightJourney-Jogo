#pragma once
#include "Inimigo.h"

class Morcego : public Inimigo
{
private:

public:
	Morcego(Jogador* pJogador, sf::Vector2f posicao = sf::Vector2f(0.f, 0.f), sf::Vector2f tamanho = sf::Vector2f(50.f, 50.f));
	virtual ~Morcego();

	void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);

	void update();
	void updateEmpuxo();
	void updateMovimento();
};

