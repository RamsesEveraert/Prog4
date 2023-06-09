#pragma once
#include "Singleton.h"
#include "Scene.h"

namespace dae
{
	struct Event;
	class GameObject;
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

		void ResetLevel(Scene& scene);

		// game assets

		void CreateLevelBackground(Scene& scene, int nrLevel);
		void CreateGrid(Scene& scene, const std::vector<std::string>& levelLayout);
		void CreateWorldTiles(Scene& scene);
		void CreatePlayer(Scene& scene, const GameMode& gameMode);
		void CreateEnemies(Scene& scene, const GameMode& gameMode);
		void SetupHUD(Scene& scene);
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
	};

}

