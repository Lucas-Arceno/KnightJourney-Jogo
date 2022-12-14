#pragma once
#include "ListaEntidade.h"
#include "Inimigo.h"
#include "ProjetilInimigo.h"
#include "GerenciadorGrafico.h"

namespace Entidades {
	namespace Personagens {
		namespace Inimigos {
			class Morcego : public Inimigo
			{
			private:
				const int vidaMaxima;
				List::ListaEntidade* pListaEntidade;
				ProjetilInimigo* projetil;

			public:
				Morcego(List::ListaEntidade* pListaEntidade, std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores, float posX, float posY, float tamX, float tamY);
				Morcego(List::ListaEntidade* pListaEntidade, std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores, sf::Vector2f posicao = sf::Vector2f(0.f, 0.f), sf::Vector2f tamanho = sf::Vector2f(50.f, 50.f));
				virtual ~Morcego();

				void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);

				void update();
				void updateEmpuxo();
				void updateMovimento();
				void reagir();
			};
		}
	}
}

