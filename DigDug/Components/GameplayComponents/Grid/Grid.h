#pragma once

#include "Component.h"
#include <vector>
#include <SDL.h>
#include <glm/glm.hpp>

namespace dae
{
	class Grid final : public Component
	{
	public:

		struct Cell
		{
			int row, col;
			SDL_Rect dstRect;
		};

		// Rule of 6

		Grid(float width, float height, float sizeCells, const glm::vec2& position);
		virtual ~Grid() = default;

		Grid(const Grid& other) = delete;
		Grid(Grid&& other) = delete;
		Grid& operator=(const Grid& other) = delete;
		Grid& operator=(Grid&& other) = delete;

		// Functions

		virtual void Render() override;

		int GetNrColumns() const;
		int GetNrRows() const;

		int GetCellIdx(int row, int col) const;
		std::vector<Cell> GetCells() const;

		const glm::vec2& GetCellSize() const;
		const glm::vec2& GetGridPosition()const;
		const glm::vec2& GetGridSize()const;



	private:

		

		glm::vec2 m_PositionGrid;
		glm::vec2 m_SizeCells;
		glm::vec2 m_GridSize;
		int m_AmountOfColumns, m_AmountOfRows;
		std::vector<Cell> m_Cells;

	};
}