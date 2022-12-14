#include "FasePalacio.h"


Fases::FasePalacio::FasePalacio(std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores) : Fase()
{
	this->Jogadores = pJogadores;

	this->num_sala = 0;
	this->num_Cobras = -1;
	this->num_Teias = -1;
	this->num_Portais = -1;


	/*for (auto const& Jogador : *Jogadores)
	{
		Jogador->setListaEntidade(&listaEntidades);
	}
	*/

	this->GerenciadorColisao = new Gerenciadores::GerenciadorColisoes(Jogadores, &listaInimigos, &listaPlataformas, &listaObstaculos);

	for (auto const& Jogador : *Jogadores)
	{
		listaEntidades.addEntidade(Jogador);
	}
	
	setPosicoesLivres();

	criaMapa();
	criaInimigos();
	criaObstaculos();

	for (unsigned int i = 0; i < listaEntidades.getTamanho(); i++) {
		/// 11 = teia
		/// 12 = espinhos
		/// 13 = portal
		if (listaEntidades[i]->getID() == 11 || listaEntidades[i]->getID() == 12 || listaEntidades[i]->getID() == 13) {
			listaObstaculos.addEntidade(listaEntidades[i]);
		}
		/// 21 = cobra
		/// 22 = morcego
		/// 23 = projetil
		/// 24 = rei
		else if (listaEntidades[i]->getID() == 21 || listaEntidades[i]->getID() == 22 || listaEntidades[i]->getID() == 23 || listaEntidades[i]->getID() == 24) {
			listaInimigos.addEntidade(listaEntidades[i]);
		}
		/// 31 = plataforma
		else if (listaEntidades[i]->getID() == 31) {
			listaPlataformas.addEntidade(listaEntidades[i]);
		}
	}
}

Fases::FasePalacio::~FasePalacio()
{
	for (unsigned int i = 0; i < listaEntidades.getTamanho(); i++) {
		if (listaEntidades[i]->getID() == 0) {
			listaEntidades.removeEntidade(listaEntidades[i]);
		}
	}
	listaEntidades.limpar();
}

void Fases::FasePalacio::setPosicoesLivres()
{
	//POSSIVEIS POSICOES OBSTACULOS

	listaPosObstaculos[0].cord = sf::Vector2f(300.0f, 450.0f);
	listaPosObstaculos[1].cord = sf::Vector2f(700.0f, 450.0f);
	listaPosObstaculos[2].cord = sf::Vector2f(500.0f, 200.0f);
	listaPosObstaculos[3].cord = sf::Vector2f(860.0f, 100.0f);
	listaPosObstaculos[4].cord = sf::Vector2f(-470.0f, -120.0f);
	listaPosObstaculos[5].cord = sf::Vector2f(-700.0f, 100.0f);
	listaPosObstaculos[6].cord = sf::Vector2f(-295.0f, 100.0f);
	listaPosObstaculos[7].cord = sf::Vector2f(-280.0f, 450.0f);
	listaPosObstaculos[8].cord = sf::Vector2f(-470.0f, -120.0f);
	listaPosObstaculos[9].cord = sf::Vector2f(-780.0f, 450.0f);
	listaPosObstaculos[10].cord = sf::Vector2f(-1188.0f, 450.0f);
	listaPosObstaculos[11].cord = sf::Vector2f(-780.0f, 450.0f);
	listaPosObstaculos[12].cord = sf::Vector2f(-780.0f, 450.0f);
	listaPosObstaculos[12].cord = sf::Vector2f(-1532.0f, 450.0f);
	listaPosObstaculos[13].cord = sf::Vector2f(-1922.0f, 450.0f);

	//POSSIVEIS POSICOES MORCEGOS

	listaPosMorcegos[0].cord = sf::Vector2f(700.0f, -40.0f);
	listaPosMorcegos[1].cord = sf::Vector2f(910.0f, - 285.4f);
	listaPosMorcegos[2].cord = sf::Vector2f(-451.0f, - 323.8f);
	listaPosMorcegos[3].cord = sf::Vector2f(-586.4f, - 60.1f);
	listaPosMorcegos[4].cord = sf::Vector2f(-350.4f, -60.1f);
	listaPosMorcegos[5].cord = sf::Vector2f(-518.8f, 277.0f);

	//POSSIVEIS POSICOES COBRAS

	listaPosCobras[0].cord = sf::Vector2f(860.0f, 450.0f);
	listaPosCobras[1].cord = sf::Vector2f(500.0f, 450.0f);
	listaPosCobras[2].cord = sf::Vector2f(795.0f, 100.0f);
	listaPosCobras[3].cord = sf::Vector2f(570.0f, -194.0f);
	listaPosCobras[4].cord = sf::Vector2f(-303.0f, -200.0f);
	listaPosCobras[5].cord = sf::Vector2f(-685.0f, 450.0f);
	listaPosCobras[6].cord = sf::Vector2f(-470, 100);
	listaPosCobras[7].cord = sf::Vector2f(-520, 450);
	listaPosCobras[8].cord = sf::Vector2f(-1300, 450);
	listaPosCobras[9].cord = sf::Vector2f(-1735, 450);
}

void Fases::FasePalacio::checkQuarto()
{
	sf::RectangleShape quarto1;
	quarto1.setSize(sf::Vector2f(10.0f, 200.0f));
	quarto1.setPosition(sf::Vector2f(100.0f, -183.0f));
	quarto1.setFillColor(sf::Color::Red);
	if (Jogadores->front()->getCorpo().getGlobalBounds().intersects(quarto1.getGlobalBounds())) {
		num_sala = 0;
	}
	sf::RectangleShape quarto2;
	quarto2.setSize(sf::Vector2f(10.0f, 200.0f));
	quarto2.setPosition(sf::Vector2f(0.0f, -183.0f));
	quarto2.setFillColor(sf::Color::Red);
	if (Jogadores->front()->getCorpo().getGlobalBounds().intersects(quarto2.getGlobalBounds())) {
		num_sala = 1;
	}
	sf::RectangleShape quarto3;
	quarto3.setSize(sf::Vector2f(10.0f, 200.0f));
	quarto3.setPosition(sf::Vector2f(-1000.0f, 450.0f));
	quarto3.setFillColor(sf::Color::Red);
	if (Jogadores->front()->getCorpo().getGlobalBounds().intersects(quarto3.getGlobalBounds())) {
		num_sala = 2;
	}
	sf::RectangleShape quarto4;
	quarto4.setSize(sf::Vector2f(10.0f, 200.0f));
	quarto4.setPosition(sf::Vector2f(-2036.0f, 450.0f));
	quarto4.setFillColor(sf::Color::Red);
	if (Jogadores->front()->getCorpo().getGlobalBounds().intersects(quarto4.getGlobalBounds())) {
		num_sala = 3;
	}

	sf::RectangleShape inicio;
	inicio.setSize(sf::Vector2f(200.0f, 200.0f));
	inicio.setPosition(sf::Vector2f(90.f, 90.0f));
	inicio.setFillColor(sf::Color::Red);
	if (Jogadores->front()->getCorpo().getGlobalBounds().intersects(inicio.getGlobalBounds())) {
		num_sala = 0;
	}
}

void Fases::FasePalacio::criaMapa()
{
	//CONSTRUCAO DA SALA 0
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(35.0f, 285.0f), sf::Vector2f(50.0f, 800.0f), 1));
	for (int i = 0; i < 2; i++) {
		listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(250.0f + (500 * i), 550.0f), sf::Vector2f(525.0f, 70.0f), 1));
		listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(250.0f + (500 * i), -400.0f), sf::Vector2f(525.0f, 70.0f), 1));
	}
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(985.0f, 15.0f), sf::Vector2f(50.0f, 1000.0f), 1));

	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(250.0f, 300.0f), sf::Vector2f(50.0f, 50.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(500.0f, 300.0f), sf::Vector2f(300.0f, 70.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(900.0f, 200.0f), sf::Vector2f(300.0f, 70.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(950.0f, 0.0f), sf::Vector2f(50.0f, 50.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(650.0f, -100.0f), sf::Vector2f(300.0f, 70.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(350.0f, 10.0f), sf::Vector2f(100.0f, 70.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(50.0f, -100.0f), sf::Vector2f(300.0f, 70.0f), 1));
	//CONSTRUCAO DA SALA 1
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-35.0f, 285.0f), sf::Vector2f(50.0f, 800.0f), 1));
	for (int i = 0; i < 2; i++) {
		listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-(250.0f + (500 * i)), 550.0f), sf::Vector2f(525.0f, 70.0f), 1));
		listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-(250.0f + (500 * i)), -400.0f), sf::Vector2f(525.0f, 70.0f), 1));
	}
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-985.0f, -135.0f), sf::Vector2f(50.0f, 650.0f), 1));

	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-450.028027f,- 100.834564f), sf::Vector2f(800.0f, 70.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-650.028027f, 200.834564f), sf::Vector2f(950.0f, 70.0f), 1));
	//CONSTRUCAO CORREDOR SALA1 -> SALA2
	for (int i = 0; i < 2; i++) {
		listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-(1250.0f + (500 * i)), 550.0f), sf::Vector2f(575.0f, 70.0f), 1));
		listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-(1300.0f + (500 * i)), 200.0f), sf::Vector2f(575.0f, 70.0f), 1));
	}
	//CONSTRUCAO SALA DO BOSS
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-3000.0f, 285.0f), sf::Vector2f(50.0f, 1500.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-2400.0f, 150.0f), sf::Vector2f(50.0f, 50.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-2675.0f, 50.0f), sf::Vector2f(50.0f, 50.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-2455.0f, 250.0f), sf::Vector2f(50.0f, 50.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-2821.0f, 350.0f), sf::Vector2f(50.0f, 50.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-2900.0f, 100.0f), sf::Vector2f(50.0f, 50.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-23210.0f, 100.0f), sf::Vector2f(50.0f, 50.0f), 1));
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-2200.0f, 350.0f), sf::Vector2f(50.0f, 50.0f), 1));
	for (int i = 0; i < 2; i++) {
		listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-(2300.0f + (500 * i)), 550.0f), sf::Vector2f(525.0f, 70.0f), 1));
		listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-(2300.0f + (500 * i)), -400.0f), sf::Vector2f(525.0f, 70.0f), 1));
	}
	listaEntidades.addEntidade(criaPlataforma(sf::Vector2f(-2060.0f, -135.0f), sf::Vector2f(50.0f, 650.0f), 1));
}

void Fases::FasePalacio::criaInimigos()
{
	this->num_Cobras = std::rand() % (6 + 1 - 3) + 3;
	this->num_Morcegos = (rand() % (6 + 1 - 3) + 3);

	for (int i = 0; i < num_Cobras; i++) {
		int aux = rand() % 10;
		while (!(listaPosCobras[aux].isLivre)) {
			aux = rand() % 10;
		}
		listaEntidades.addEntidade(criaCobra(Jogadores, sf::Vector2f(listaPosCobras[aux].cord), sf::Vector2f(100.0f, 100.0f)));
		listaPosCobras[aux].isLivre = false;
	}
	for (int i = 0; i < num_Morcegos; i++) {
		int aux = rand() % 6;
		while (!(listaPosMorcegos[aux].isLivre)) {
			aux = rand() % 6;
		}
		listaEntidades.addEntidade(criaMorcego(&listaEntidades, Jogadores, sf::Vector2f(listaPosMorcegos[aux].cord), sf::Vector2f(50.0f, 50.0f)));
		listaPosMorcegos[aux].isLivre = false;
	}

	listaEntidades.addEntidade(new Entidades::Personagens::Inimigos::Rei(Jogadores, sf::Vector2f(-2600.0f, 400.0f), sf::Vector2f(100.0f, 100.0f)));
}

void Fases::FasePalacio::criaObstaculos()
{
	this->num_Teias = std::rand() % (8 + 1 - 3) + 3;
	this->num_Portais = std::rand() % (3 + 1 - 3) + 3;

	for (int i = 0; i < num_Teias; i++) {
		int aux2 = rand() % 14;
		while (!(listaPosObstaculos[aux2].isLivre)) {
			aux2 = rand() % 14;
		}
		listaEntidades.addEntidade(criaTeia(Jogadores, sf::Vector2f(listaPosObstaculos[aux2].cord), sf::Vector2f(100.0f, 100.0f)));
		listaPosObstaculos[aux2].isLivre = false;
	}

	for (int i = 0; i < num_Portais; i++) {
		int aux3 = rand() % 14;
		while (!(listaPosObstaculos[aux3].isLivre)) {
			aux3 = rand() % 14;
		}
		listaEntidades.addEntidade(criaPortal(Jogadores, sf::Vector2f(100.f, 100.f), sf::Vector2f(listaPosObstaculos[aux3].cord), sf::Vector2f(70.0f, 70.0f)));
		listaPosObstaculos[aux3].isLivre = false;
	}
}

void Fases::FasePalacio::setListaEnt()
{
	for (auto const& Jogador : *Jogadores)
	{
		Jogador->setListaEntidade(&listaEntidades);
	}
}

void Fases::FasePalacio::multiplayer(bool status)
{
	if (status == true) {
		for (auto const& Jogador : *Jogadores)
		{
			if (Jogador == (Jogadores)->back()) {
				listaEntidades.addEntidade(Jogador);
			}
		}
	}
}

bool Fases::FasePalacio::checkTerminou()
{
	for (unsigned int i = 0; i < listaInimigos.getTamanho(); i++) {
		if (listaInimigos[i]->getID() == 24 && listaInimigos[i]->getIsVivo() == false) {
			return true;
		}
	}
	if (Jogadores->front()->getVida() <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void Fases::FasePalacio::update()
{
	this->GerenciadorColisao->updateColisao();
	render();
	checkQuarto();
}

void Fases::FasePalacio::render()
{
	if (num_sala == 0) {
		pGrafico->setView(sf::Vector2f(509.987488f, 66.165459f));
	}
	if (num_sala == 1) {
		pGrafico->setView(sf::Vector2f(-509.0f, 66.165459f));
	}
	if (num_sala == 2) {
		pGrafico->setView(sf::Vector2f(-1527.0f, 66.165459f));
	}
	if (num_sala == 3) {
		pGrafico->setView(sf::Vector2f(-2527.0f, 66.165459f));
	}
	for (unsigned int i = 0; i < listaEntidades.getTamanho(); i++) {
		if (listaEntidades[i] == Jogadores->back()) {
			pGrafico->desenhaSprites(Jogadores->back()->sprite);
		}
		else if (listaEntidades[i] == Jogadores->front()) {
			pGrafico->desenhaSprites(Jogadores->front()->sprite);
		}
		else {
			if (listaEntidades[i]->getIsVivo()) {
				listaEntidades[i]->seImprime(listaEntidades[i]->getCorpo());
			}
		}
	}
	for (unsigned int i = 0; i < listaEntidades.getTamanho(); i++) {
		if (listaEntidades[i]->getIsVivo()) {
			listaEntidades[i]->update();
		}
	}
}
