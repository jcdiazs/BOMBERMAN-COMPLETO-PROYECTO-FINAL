#include <algorithm>

#include "../Scenes/Scene.h"

Scene::Scene(GameManager* _gameManager)
{
    this->gameManager = _gameManager;
    // set camera to up-left position
    camera = {0, 0, 0, 0};
}

Scene::~Scene() {}

void Scene::addObject(std::shared_ptr<GameObject> object)
{
    objects.push_back(std::move(object));
}

void Scene::insertObject(std::shared_ptr<GameObject> object, int position)
{
    objects.insert(objects.begin() + position, object);
}

void Scene::removeObject(std::shared_ptr<GameObject> object)
{
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

void Scene::setCamera(const int x, const int y)
{
    camera.x = x;
    camera.y = y;
}

void Scene::onEnter() {}

void Scene::onExit() {}

void Scene::onEvent(const SDL_Event& /*event*/) {}

void Scene::update(const unsigned int delta)
{
    for(auto& object : objects)
    {
        object->update(delta);
    }
}

void Scene::render() const
{
    for(const auto& object : objects)
    {
        object->render(camera);
    }
}
