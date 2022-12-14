#pragma once
#include <SFML/Graphics.hpp>
#include "Ente.h"
#include "efetuaColisao.h"

namespace Entidades {
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

		// Fisica dos objetos
		float acceleration;
		float drag;
		float gravity;
		const int velocidadeMaxY;

		bool isVivo = true;

	public:
		Entidade(int id = 0, sf::Vector2f posicao = sf::Vector2f(0.f, 0.f), sf::Vector2f tamanho = sf::Vector2f(0.f, 0.f));
		virtual ~Entidade();

		void setCorpoPosicao(sf::Vector2f pos);

		calculoColisao GetColisao() { return calculoColisao(corpo); }

		const int getID() { return ID; }
		bool getIsVivo() { return isVivo; }
		
		const sf::RectangleShape getCorpo();

		// Inicializa e atualiza a fisica
		void initPhysics();
		void updatePhysics();

		virtual void update() = 0;
		virtual void updateMovimento() = 0;

		virtual void reagir() = 0;
		virtual void reagirDano() = 0;
	};
}

