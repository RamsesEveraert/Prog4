#pragma once
#include "Component.h"
#include "grid.h"
#include <SDL.h>

namespace dae
{
	struct Cell;
	struct Event;
	class Grid;
	class Sprite;
	class Tile final : public Component
	{

	public:

		// Rule of 6
		Tile(const SDL_Rect& dstTile, Grid* pGrid, float gameScale);
		virtual ~Tile() = default;

		Tile(const Tile& other) = delete;
		Tile(Tile&& other) = delete;
		Tile& operator=(const Tile& other) = delete;
		Tile& operator=(Tile&& other) = delete;

		// functions

		void OnCellDig(const Event& event);

	private:
		SDL_Rect m_DstTile;
		Grid::Cell m_TileCell;
		Grid* m_pGrid;
		const float m_gameScale;
	};
}