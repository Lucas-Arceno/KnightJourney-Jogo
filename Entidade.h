#pragma once
#include <SFML/Graphics.hpp>
#include "Ente.h"
#include "Colisao.h"

class Entidade : public Ente
{
protected:
	sf::Vector2f velocidade;
	const int velocidadeMax;
	const int velocidadeMin;

	sf::RectangleShape corpo;
	sf::Vector2f posicao;
	sf::Vector2f tamanho;

	sf::Texture texture;

	//Physics
	float acceleration;
	float drag;
	float gravity;
	const int velocidadeMaxY;

	bool isVivo = true;

public:
	Entidade(int id = 0, sf::Vector2f posicao = sf::Vector2f(0.f,0.f),sf::Vector2f tamanho = sf::Vector2f(0.f, 0.f));
	~Entidade();

	void setCorpoPosicao(sf::Vector2f pos);

	Colisao GetColisao() { return Colisao(corpo); }

	const int getID() { return ID; }

	void initPhysics();
	void updatePhysics();
	virtual void update() = 0;
	virtual void updateMovimento() = 0;

	void setPosicao(sf::Vector2f pos);
	const sf::RectangleShape getCorpo();
	sf::Vector2f getPosicao() const;
	sf::Vector2f getTamanho() const;
};

