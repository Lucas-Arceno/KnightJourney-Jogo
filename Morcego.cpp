#include "Morcego.h"


Entidades::Personagens::Inimigos::Morcego::Morcego(List::ListaEntidade* pListaEntidade, std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores, float posX, float posY, float tamX, float tamY) : Entidades::Personagens::Inimigos::Inimigo(22, pJogadores, sf::Vector2f(posX, posY), sf::Vector2f(tamX, tamY)), vidaMaxima(1), projetil()
{

}

Entidades::Personagens::Inimigos::Morcego::Morcego(List::ListaEntidade* pListaEntidade, std::list<Entidades::Personagens::Jogadores::Jogador*>* pJogadores, sf::Vector2f posicao, sf::Vector2f tamanho) : Entidades::Personagens::Inimigos::Inimigo(22, pJogadores, posicao, tamanho), vidaMaxima(1), projetil()
{
	this->pListaEntidade = pListaEntidade;
	this->corpo.setFillColor(sf::Color::White);
	this->texture.loadFromFile("assets/morcego.png");
	this->corpo.setTexture(&texture);
	projetil = new ProjetilInimigo(pJogadores);
	this->pListaEntidade->addEntidade(projetil);
	setVida(vidaMaxima);
}

Entidades::Personagens::Inimigos::Morcego::~Morcego()
{
}

void Entidades::Personagens::Inimigos::Morcego::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
{
	if (posJogador.x - posInimigo.x > 200.0f) {
		corpo.move(1.f, 0.0f);
	}
	else {
		corpo.move(-1.f, 0.0f);
	}
	if (posJogador.y - posInimigo.y > 100.0f) {
		corpo.move(0, 1.f);
	}
	else {
		corpo.move(0, -1.f);
	}
}

void Entidades::Personagens::Inimigos::Morcego::updateEmpuxo()
{
	//Gravity
	this->velocidade.y += 1 * this->gravity;
	if (std::abs(this->velocidade.x) > this->velocidadeMaxY) {
		this->velocidade.y = this->velocidadeMaxY * ((this->velocidade.y < 0.f) ? -1.f : 1.f);
	}

	//Deceleration
	this->velocidade *= this->drag;

	//Limit deceleration
	if (std::abs(this->velocidade.x) < this->velocidadeMin) {
		this->velocidade.x = 0.0f;
	}
	if (std::abs(this->velocidade.y) < this->velocidadeMin) {
		this->velocidade.y = 0.0f;
	}

	this->corpo.move(-(this->velocidade));
}

void Entidades::Personagens::Inimigos::Morcego::update()
{
	updateMovimento();
	updatePhysics();
	updateEmpuxo();

	// Variavel para passar a pos do inimigo
	sf::Vector2f posInimigo = corpo.getPosition();
	projetil->updateProjetil(posInimigo.x, posInimigo.y);
	if (this->vida <= 0) {
		projetil->setCorpoPosicao(sf::Vector2f( 5000.0f, 5000.0f));
	}
}

void Entidades::Personagens::Inimigos::Morcego::updateMovimento()
{
	sf::Vector2f posInimigo = corpo.getPosition();
	sf::Vector2f posJogador;

	for (auto const& pJogador : *pJogadores)
	{
		if (pJogador == pJogadores->front()) {
			posJogador = pJogador->getCorpo().getPosition();
		}
		else {
			if (pJogador->getCorpo().getPosition().x < posJogador.x) {
				posJogador = pJogador->getCorpo().getPosition();
			}
		}
	}

	if (fabs(posJogador.x - posInimigo.x) <= 300 && fabs(posJogador.y - posInimigo.y) <= 300) {
		persegueJogador(posJogador, posInimigo);
	}
	else randomMovimento();
}

void Entidades::Personagens::Inimigos::Morcego::reagir() {
	updateDano(1);
}