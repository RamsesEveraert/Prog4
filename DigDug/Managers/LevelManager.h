#pragma once
#include "Singleton.h"
#include "Scene.h"

namespace dae
{
	struct Event;
	enum class GameMode
	{
		SINGLEPLAYER, CO_OP, VERSUS
	};
	class LevelManager final : public Singleton<LevelManager>
	{
	public:
		void LoadLevel(Scene& scene, GameMode mode, int nrLevel);
		void StartNextLevel(const Event& event);
	private:
		friend class Singleton<LevelManager>;
		LevelManager() = default;

		void ResetLevel(Scene& scene);
		void CreateBackground(Scene& scene, int nrLevel);
		void CreateGrid(Scene& scene, const std::vector<std::string>& levelLayout);
		void CreateWorldTiles(Scene& scene);
		void CreatePlayer(Scene& scene, const GameMode& gameMode);
		void CreateSinglePlayer(Scene& scene);
		void SetupHUD(Scene& scene);
		void CreateFPSObject(Scene& scene);

		Scene* m_CurrentScene{};
		GameMode m_GameMode{};
		const float m_GameScale{ 1.5f };
		int m_NrLevel{};
		bool m_IsAddedAsListener{};
	};

}

