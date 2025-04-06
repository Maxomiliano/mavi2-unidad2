#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>

// Constructor de la clase Game
Game::Game(int ancho, int alto, std::string titulo)
{
	// Inicializaci�n de la ventana y configuraci�n de propiedades
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	SetZoom(); // Configuraci�n de la vista del juego
	InitPhysics(); // Inicializaci�n del motor de f�sica
	//controlBody->ApplyLinearImpulse(b2Vec2(10000, 10), b2Vec2(50, 50), true);
}

// Bucle principal del juego
void Game::Loop()
{
	while (wnd->isOpen())
	{
		wnd->clear(clearColor); // Limpiar la ventana
		DoEvents(); // Procesar eventos de entrada
		CheckCollitions(); // Comprobar colisiones
		UpdatePhysics(); // Actualizar la simulaci�n f�sica
		DrawGame(); // Dibujar el juego
		wnd->display(); // Mostrar la ventana
	}
}

// Actualizaci�n de la simulaci�n f�sica
void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8); // Simular el mundo f�sico
	phyWorld->ClearForces(); // Limpiar las fuerzas aplicadas a los cuerpos
	phyWorld->DebugDraw(); // Dibujar el mundo f�sico para depuraci�n
}

// Dibujo de los elementos del juego
void Game::DrawGame() {}

// Procesamiento de eventos de entrada
void Game::DoEvents()
{
	Event evt;
	while (wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			wnd->close(); // Cerrar la ventana si se presiona el bot�n de cerrar
			break;
		}
	}

	controlBody->SetAwake(true);
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		controlBody->ApplyForce(b2Vec2(-200, 0), controlBody->GetWorldCenter(), true);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		controlBody->ApplyForce(b2Vec2(200, 0), controlBody->GetWorldCenter(), true);
	}
}

// Comprobaci�n de colisiones (a implementar m�s adelante)
void Game::CheckCollitions()
{
	// Implementaci�n de la comprobaci�n de colisiones
}

// Configuraci�n de la vista del juego
void Game::SetZoom()
{
	View camara;
	// Posicionamiento y tama�o de la vista
	camara.setSize(100, 100);
	camara.setCenter(50, 50);
	wnd->setView(camara); // Asignar la vista a la ventana
}

// Inicializaci�n del motor de f�sica y los cuerpos del mundo f�sico
void Game::InitPhysics()
{
	// Inicializar el mundo f�sico con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	// Crear un renderer de debug para visualizar el mundo f�sico
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	phyWorld->SetDebugDraw(debugRender);

	// Crear el suelo y las paredes est�ticas del mundo f�sico
	//b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	//groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);
	b2Body* groundBody = Box2DHelper::CreateStaticBody(phyWorld);
	b2FixtureDef box = Box2DHelper::CreateRectangularFixtureDef(100, 10, 0.0f, 0.03f, 0.0f);
	groundBody->CreateFixture(&box);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	b2Body* ceilingBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	ceilingBody->SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);

	b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

	b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

	// Crear un c�rculo que se controlar� con el teclado
	controlBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 10, 10, 1, 0.03f, 0.1f);
	controlBody->SetTransform(b2Vec2(50.0f, 90.0f), 0.0f);
}

// Destructor de la clase

Game::~Game(void)
{
}