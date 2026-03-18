#include "GameManager.h"

#include "Entity.h"
#include "Debug.h"
#include "Camera.h"
#include "InputManager.h"
#include "SceneManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "AssetManager.h"

#include <iostream>

GameManager::GameManager()
{
	mpWindow = nullptr;
	mDeltaTime = 0.0f;
	mpScene = nullptr;
	mWindowWidth = -1;
	mWindowHeight = -1;

	AssetManager::getInstance().InitMusicInDirectory();
	AssetManager::getInstance().InitTextureInDirectory();
	AssetManager::getInstance().InitSoundInDirectory();

}

GameManager* GameManager::Get()
{
	static GameManager mInstance;

	return &mInstance;
}

GameManager::~GameManager()
{
	delete mpWindow;

	for (Entity* entity : mEntities)
	{
		delete entity;
	}
}

void GameManager::CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit, sf::Color clearColor)
{
	_ASSERT(mpWindow == nullptr);

	mpWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);
	mpWindow->setFramerateLimit(fpsLimit);

	mWindowWidth = width;
	mWindowHeight = height;

	mClearColor = clearColor;
}

void GameManager::DrawSprite(sf::Sprite* _sprite)
{
	mpWindow->draw(*_sprite);
}

void GameManager::RefreshCamera(Camera* camera)
{
	if (camera->GetView() == nullptr)
	{
		std::cout << "Camera Not Initialized" << std::endl;
		exit(0);
	}
	mpWindow->setView(*camera->GetView());
	camera->GetUIView()->setViewport(sf::FloatRect(0, 0, 0.25f, 0.25f));
}
void GameManager::RefreshUI(Camera* camera)
{
	if (camera->GetView() == nullptr)
	{
		std::cout << "Camera Not Initialized" << std::endl;
		exit(0);
	}
	mpWindow->setView(*camera->GetUIView());

}



void GameManager::Run()
{
	if (mpWindow == nullptr) 
	{
		std::cout << "Window not created, creating default window" << std::endl;
		CreateWindow(1280, 720, "Default window");
	}

	//sf::View view2(sf::Vector2f(mWindowWidth / 2 , mWindowHeight / 2), sf::Vector2f(mWindowWidth  , mWindowHeight));
	//mCamera = &view2;

	//#TODO : Load somewhere else
	bool fontLoaded = mFont.loadFromFile("../../../res/Hack-Regular.ttf");
	_ASSERT(fontLoaded);

	_ASSERT(mpScene != nullptr);

	InputManager::Get().Init();

	AssetManager::getInstance().PlayMusic("Fight");
	AssetManager::getInstance().SetMusicVolume(0.f);


	sf::Clock clock;
	while (mpWindow->isOpen())
	{
		SetDeltaTime(clock.restart().asSeconds());

		HandleInput(); //OnEvent here

		Update();
		
		Draw();
	}
}

void GameManager::HandleInput()
{
	InputManager& IM = InputManager::Get();


	sf::Event event;
	while (mpWindow->pollEvent(event))
	{
		IM.Reset();

		if (event.type == sf::Event::Closed)
		{
			mpWindow->close();
		}

		IM.HandleInput(event);
		mpScene->OnEvent(event);
	}
}

void GameManager::Update()
{
	SceneManager& sm = SceneManager::getInstance();

	if (sm.Update())
	{
		_ASSERT(mpScene != nullptr);
		mpScene = sm.GetCurrentScene();
		mpScene->OnInitialize();
	}
	mpScene->OnUpdate();

    //Update
    for (auto it = mEntities.begin(); it != mEntities.end(); )
    {
		Entity* entity = *it;

        entity->Update();

        if (entity->ToDestroy() == false)
        {
            ++it;
            continue;
        }

        mEntitiesToDestroy.push_back(entity);
        it = mEntities.erase(it);
    }

    //Collision
    for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1)
    {
        auto it2 = it1;
        ++it2;
        for (; it2 != mEntities.end(); ++it2)
        {
            Entity* entity = *it1;
            Entity* otherEntity = *it2;

            if (entity->IsColliding(otherEntity))
            {
				if (entity->IsRigidBody() && otherEntity->IsRigidBody())
					entity->Repulse(otherEntity);

                entity->OnCollision(otherEntity);
                otherEntity->OnCollision(entity);
            }
        }
    }

	for (auto it = mEntitiesToDestroy.begin(); it != mEntitiesToDestroy.end(); ++it) 
	{
		delete *it;
	}

    mEntitiesToDestroy.clear();

	for (auto it = mEntitiesToAdd.begin(); it != mEntitiesToAdd.end(); ++it)
	{
		mEntities.push_back(*it);
	}

	mEntitiesToAdd.clear();
}

void GameManager::Draw()
{
	mpWindow->clear(mClearColor);
	
	for (Entity* entity : mEntities)
	{
		if (entity->hasSprite) DrawSprite(entity->GetSprite());
		else mpWindow->draw(*entity->GetShape());
	}

	sf::Sprite* sprite = AssetManager::getInstance().LoadSprite("sheet", 0, 0, 460, 600);
	//std::cout << sprite.getTextureRect().width << std::endl;
	sprite->setScale(0.1f, 0.1f);
	DrawSprite(sprite);
	Debug::Get()->Draw(mpWindow);

	mpWindow->display();
}

void GameManager::SetScene(Scene* scene)
{
	if (scene != nullptr)
	{
		mpScene = scene;
		mpScene->SetGameManager(this);
		mpScene->OnInitialize();
	}
	
}