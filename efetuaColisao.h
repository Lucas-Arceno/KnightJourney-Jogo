#pragma once
#include <SFML/Graphics.hpp>

class calculoColisao
{
private:
	sf::RectangleShape& corpo;
public:
	calculoColisao(sf::RectangleShape& corpo);
	~calculoColisao();

	void Move(float dx, float dy) { corpo.move(dx, dy); }
	

	// Fun??o simples para ver se houve colis?o
	bool verificaColisao(sf::RectangleShape outroCorpo);

	// Al?m de conferir se houve colis?o, a fun??o verificaEColide tamb?m empurra em sentido contrario qualquer corpo colidindo.
    // Feito com base em : www.youtube.com/watch?v=l2iCYCLi6MU&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=13
	bool verificaEColide(calculoColisao outro, float push);
	sf::Vector2f GetPosition() { return corpo.getPosition(); }
	sf::Vector2f GetHalfSize() { return corpo.getSize() / 2.0f; }
};

