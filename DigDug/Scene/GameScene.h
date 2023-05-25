#pragma once
namespace dae
{
    class Scene;
	class GameScene final
	{
    public:
        GameScene() = default;
        ~GameScene() = default;

        GameScene(const GameScene& other) = delete;
        GameScene(GameScene&& other) = delete;
        GameScene& operator=(const GameScene& other) = delete;
        GameScene& operator=(GameScene&& other) = delete;

        void LoadScene();

    private:
        void CreatePlayers(Scene& scene);
        void CreateEnemies(Scene& scene);
        void CreateGrid(Scene& scene);
        void CreateWorldTiles(Scene& scene);

        void SetupHUD(Scene& scene);

        // temporary
        void CreateBackground(Scene& scene);
        void SpriteTest(Scene& scene);
        void CreateFPSObject(Scene& scene);
	};

}

