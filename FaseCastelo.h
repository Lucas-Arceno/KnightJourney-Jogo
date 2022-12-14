#pragma once
#include "Fase.h"

namespace Fases {
	class FaseCastelo : public Fase
	{
	private:
		listaPos listaPosCobras[19];
		listaPos listaPosMorcegos[27];
		listaPos listaPosObstaculos[29];

		int num_Morcegos;
		int num_Cobras;
		int num_Espinhos;
		int num_Portais;
		int num_Teias;

		bool Multiplayer = false;

	public:
		FaseCastelo(std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores);
		~FaseCastelo();

		void setPosicoesLivres();

		void criaMapa();
		void criaInimigos();
		void criaObstaculos();

		void multiplayer(bool status);

		bool checkMorreu();
		bool checkTerminou();

		void update();
		void render();

	};
}


