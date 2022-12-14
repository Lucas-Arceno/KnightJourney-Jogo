#pragma once

#include<cstdlib>
#include<ctime>

#include "Save.h"

#include "GerenciadorEvento.h"
#include "GerenciadorGrafico.h"
#include "GerenciadorColisoes.h"

#include "ListaEntidade.h"

#include "Plataforma.h"

#include "Teia.h"
#include "Espinhos.h"
#include "Portal.h"

#include "Inimigo.h"
#include "Cobra.h"
#include "Morcego.h"
#include "Rei.h"

namespace Fases {

	// Struct usada para determinar o possivel local de surgimento para obstaculos e inimigos
	struct listaPos {
		sf::Vector2f cord;
		bool isLivre = true;
	};

	class Fase : public Ente
	{
	protected:
		//Corpo, textura e afins
		sf::RectangleShape background;
		sf::Texture backgroundTexture;

		//Listas
		List::ListaEntidade listaEntidades;

		List::ListaEntidade listaObstaculos;
		List::ListaEntidade listaInimigos;
		List::ListaEntidade listaPlataformas;

		//Jogadores
		std::list<Entidades::Personagens::Jogadores::Jogador*>* Jogadores;
	
		//Gerenciadores
		Gerenciadores::GerenciadorEvento* pEvento;
		Gerenciadores::GerenciadorColisoes* GerenciadorColisao;
	public:
		Fase();
		virtual ~Fase();

		// Fun??es para criar os objetos
		Entidades::Obstaculos::Teia* criaTeia(std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores, sf::Vector2f(posicao), sf::Vector2f(tamanho));
		Entidades::Obstaculos::Portal* criaPortal(std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores, sf::Vector2f(destino), sf::Vector2f(posicao), sf::Vector2f(tamanho));
		Entidades::Plataforma* criaPlataforma(sf::Vector2f(posicao), sf::Vector2f(tamanho), const int tipo);
		Entidades::Personagens::Inimigos::Cobra* criaCobra(std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores, sf::Vector2f(posicao), sf::Vector2f(tamanho));
		Entidades::Personagens::Inimigos::Morcego* criaMorcego(List::ListaEntidade* pListaEntidade, std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores, sf::Vector2f(posicao), sf::Vector2f(tamanho));

		virtual void update() = 0;
		virtual void render() = 0;
	};
}

