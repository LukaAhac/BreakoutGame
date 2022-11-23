#include "SceneManager.h"

#include "BasicScene.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::getInstance() {
    if (instance == nullptr) {
        instance = new SceneManager();
    }
    return instance;
}

SceneManager::~SceneManager() {
	delete currentScene;
}

void SceneManager::changeScene(BasicScene* scene) {
	delete currentScene;
	currentScene = scene;
    currentScene->loadScene();
}

void SceneManager::nextFrame() {
    currentScene->processEvents();
    currentScene->update();
    currentScene->render();
}