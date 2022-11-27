#pragma once
#include "Obstaculo.h"

namespace Entidades {
	namespace Obstaculos {
		class Teia : public Obstaculo
		{
		private:
			int estagio; //quanto menor mais complicado de passar
			std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores;
		public:
			Teia(std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores, sf::Vector2f posicao = sf::Vector2f(0.f, 0.f), sf::Vector2f tamanho = sf::Vector2f(30.f, 50.f));
			virtual ~Teia();

			const int getEstagio();

			void update();
			void updateMovimento();
			void reagir();
		};
	}
}


