#pragma once
#include "Singleton.h"
#include "Scene.h"

#include <memory>

namespace dae
{
	struct Event;
	class GameObject;
	class NextLevelCommand;
	enum class GameMode
	{
		SINGLEPLAYER, CO_OP, VERSUS
	};
	class LevelManager final : public Singleton<LevelManager>
	{
	public:
		void LoadStartScreen();
		void LoadLevel(Scene& scene, GameMode mode, int nrLevel);
		void StartNextLevel(const Event& event);

		void LoadGameOver(const Event& event);
		
	private:
		friend class Singleton<LevelManager>;
		LevelManager() = default;

		void ResetLevel(Scene* scene);

		// game assets

		std::string GetLevelPath(int nrLevel);
		std::vector<std::string> GetLevelLayout(std::ifstream& levelFile);

		void CreateLevelBackground(Scene& scene, int nrLevel);
		void CreateGrid(Scene& scene, const std::vector<std::string>& levelLayout);
		void CreateWorldTiles(Scene& scene);
		void CreatePlayer(Scene& scene, const GameMode& gameMode);
		void CreateEnemies(Scene& scene, const GameMode& gameMode);
		void SetupHUD(Scene& scene, const GameMode& gameMode);
		void CreateFPSObject(Scene& scene);

		void CreateGameLogo(Scene& scene);
		void CreateGameOverLogo(Scene& scene);

		void CreateScoreDisplay(Scene& scene, GameObject*);

		// school assets

		void CreateSchoolBackground(Scene& scene);
		void CreateSchoolLogo(Scene& scene);

		//GameModes and buttons

		void CreateSinglePlayer(Scene& scene);
		void Create_Co_Op_Players(Scene& scene);
		void Create_Versus_Players(Scene& scene);

		void CreateSingplayerHUD(Scene& scene, GameObject* p1);
		void Create_CO_OP_HUD(Scene& scene, GameObject* p1, GameObject* p2);
		void CreateVersusHUD(Scene& scene, GameObject* p1, GameObject* p2);

		void CreateSinglePlayerButton(Scene& scene);
		void Create_Co_Op_Button(Scene& scene);
		void CreateVersusButton(Scene& scene);
		void CreateContinueButton(Scene& scene);

		// events

		

		// member variables

		Scene* m_CurrentScene{};
		GameMode m_GameMode{};
		const float m_GameScale{ 1.5f };
		int m_NrLevel{};
		bool m_IsAddedAsListener{};
		std::shared_ptr<NextLevelCommand> m_NextLevelCommand{nullptr};
	};

}

