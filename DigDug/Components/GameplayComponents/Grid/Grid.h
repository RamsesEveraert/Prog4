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
			bool IsDug;
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

		const glm::ivec2& GetStepsPerCell() const;

		int GetCellIdx(int row, int col) const;
		int GetCellIdxFromPosition(const glm::vec2& position) const;
		std::vector<Cell> GetCells() const;

		const glm::vec2& GetCellSize() const;
		const glm::vec2& GetGridPosition()const;
		const glm::vec2& GetGridSize()const;



	private:

		

		glm::vec2 m_GridOffset;
		glm::vec2 m_SizeCells;
		glm::vec2 m_GridSize;
		int m_AmountOfColumns, m_AmountOfRows;
		glm::ivec2 m_MoveStepsPerCell;
		std::vector<Cell> m_Cells;

	};
}