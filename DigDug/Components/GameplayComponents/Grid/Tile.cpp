#include "Tile.h"

#include "GameObject.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

#include "EventQueue.h"
#include "Event.h"

dae::Tile::Tile(const SDL_Rect& dstTile, Grid* pGrid, float gameScale)
	: m_DstTile {dstTile}
	, m_pGrid { pGrid }
	, m_TileCell { }
	, m_gameScale {gameScale}
{
	m_TileCell = m_pGrid->GetCells()[m_pGrid->GetCellIdxFromPosition(glm::vec2{ static_cast<float>(m_DstTile.x), static_cast<float>(m_DstTile.y) })];
	EventQueue::GetInstance().AddListener("DiggedCell", [this](const dae::Event& event) { OnCellDig(event); });
}


void dae::Tile::OnCellDig(const Event& event)
{
	if (GetOwner()->HasComponent<Sprite>()) return; 

	Grid::Cell eventCell{};

	for (const auto& data : event.data)
	{
		if (data.type() == typeid(dae::Grid::Cell))
		{
			eventCell = std::any_cast<dae::Grid::Cell>(data);

		}

	}

	if (m_TileCell.dstRect.x == eventCell.dstRect.x && m_TileCell.dstRect.y == eventCell.dstRect.y)
	{
		SDL_Rect tunnel{ 128, 0, 16,16 };
		GetOwner()->AddComponent<Sprite>("General Sprites.png", tunnel, m_gameScale);
		GetOwner()->AddComponent<SpriteRenderer>();
	}

	

	
}

