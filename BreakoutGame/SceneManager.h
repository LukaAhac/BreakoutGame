#pragma once

class BasicScene;

//Singleton class for managing and rendering scenes in the game
//Provides public method for changing scene and method for rendering next frame
class SceneManager {

private:

	static SceneManager* instance;
	BasicScene* currentScene;

	SceneManager() : currentScene(nullptr) {};

public:
	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

	static SceneManager* getInstance();
	~SceneManager();

	void changeScene(BasicScene* scene);
	void nextFrame();
};