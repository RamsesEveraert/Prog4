#include "Grid.h"

#include "GameObject.h"
#include "Transform.h"

#include "Renderer.h"

using namespace dae;

dae::Grid::Grid(float width, float height, float sizeCells, const glm::vec2& position)
	: m_AmountOfRows { static_cast<int>(height / sizeCells) }
	, m_AmountOfColumns { static_cast<int>(width / sizeCells) }
	, m_SizeCells {sizeCells, sizeCells}
	, m_MoveStepsPerCell{static_cast<glm::ivec2>(m_SizeCells)}
	, m_GridOffset{position}
{
	m_GridSize = glm::vec2{ m_AmountOfColumns ,  m_AmountOfRows } * m_SizeCells;

	for (int row{}; row < m_AmountOfRows; ++row)
	{
		for (int col{}; col < m_AmountOfColumns; ++col)
		{
			Cell cell;
			cell.row = row;
			cell.col = col;
			cell.dstRect.x = static_cast<int>(m_GridOffset.x + col * m_SizeCells.x);
			cell.dstRect.y = static_cast<int>(m_GridOffset.y + row * m_SizeCells.y);
			cell.dstRect.w = cell.dstRect.h = static_cast<int>(m_SizeCells.x);
			cell.IsDug = false;

			m_Cells.emplace_back(cell);
		}
	}
}

void dae::Grid::Render()
{
#ifdef _DEBUG

	SDL_Renderer* renderer = Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255); // red color

	for (const auto& cell : m_Cells)
	{
		SDL_RenderDrawRect(renderer, &cell.dstRect);
	}
#endif

	
}

int dae::Grid::GetNrColumns() const
{
	return m_AmountOfColumns;
}

int dae::Grid::GetNrRows() const
{
	return m_AmountOfRows;
}

const glm::ivec2& dae::Grid::GetStepsPerCell() const
{
	return m_MoveStepsPerCell;
}

int dae::Grid::GetCellIdx(int row, int col) const
{
	return row * m_AmountOfColumns + col ;
}

int dae::Grid::GetCellIdxFromPosition(const glm::vec2& position) const
{
	// Calculate the normalized position relative to the grid
	glm::vec2 normalizedPosition = position - m_GridOffset;

	// Calculate the row and column indices based on the normalized position
	int row = static_cast<int>(normalizedPosition.y / m_SizeCells.y);
	int col = static_cast<int>(normalizedPosition.x / m_SizeCells.x);

	// Check if the calculated indices are within the grid boundaries
	if (row < 0 || row >= m_AmountOfRows || col < 0 || col >= m_AmountOfColumns)
	{
		return -1;
	}
	else
	{
		return GetCellIdx(row, col);
	}
}



std::vector<Grid::Cell> dae::Grid::GetCells() const
{
	return m_Cells;
}

const glm::vec2& dae::Grid::GetCellSize() const
{
	return m_SizeCells;
}

const glm::vec2& dae::Grid::GetGridPosition() const
{
	return m_GridOffset;
}

const glm::vec2& dae::Grid::GetGridSize() const
{
	return m_GridSize;
}
