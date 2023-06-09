#include "Grid.h"

#include "GameObject.h"
#include "Transform.h"

#include "Renderer.h"
#include "EventHandler.h"
#include "Event.h"

using namespace dae;

dae::Grid::Grid(float width, float height, float sizeCells, const glm::vec2& position, const std::vector<std::string>& levelLayout)
	: m_AmountOfRows { static_cast<int>(height / sizeCells) }
	, m_AmountOfColumns { static_cast<int>(width / sizeCells) }
	, m_SizeCells {sizeCells, sizeCells}
	, m_GridOffset{position}
{

	EventHandler::GetInstance().AddListener("DiggedCell", [this](const dae::Event& event) { SetDug(event); });

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

			// p = player, r = red / pooka, g = green / fygar, & = rock, o = oponent

			char layoutChar = levelLayout[row][col];
			cell.IsDug = (layoutChar == '.' || layoutChar == 'p' || layoutChar == 'r' || layoutChar == 'g' || layoutChar == 'o');
			cell.IsRockStartPoint = (layoutChar == '&');
			cell.IsPlayerStartPoint = (layoutChar == 'p');
			cell.IsOponentStartPoint = (layoutChar == 'o');
			cell.IsPookaStartPoint = (layoutChar == 'r');
			cell.IsFygarStartpoint = (layoutChar == 'g');

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

const glm::vec2 dae::Grid::GetStartPoint(std::function<bool(const Cell&)> predicate) const
{
	auto it = std::find_if(m_Cells.begin(), m_Cells.end(), predicate);

	if (it != m_Cells.end()) {
		const Cell& startCell = *it;
		const glm::vec2 startPosition{ static_cast<float>(startCell.dstRect.x), static_cast<float>(startCell.dstRect.y) };
		return startPosition;
	}
	else {
		return glm::vec2{};
	}
}

std::vector<glm::vec2> dae::Grid::GetStartPoints(std::function<bool(const Cell&)> predicate) const
{
	std::vector<glm::vec2> startPoints;

	for (const Cell& cell : m_Cells) {
		if (predicate(cell)) {
			const glm::vec2 startPosition{ static_cast<float>(cell.dstRect.x), static_cast<float>(cell.dstRect.y) };
			startPoints.emplace_back(startPosition);
		}
	}
	return startPoints;
}


glm::vec2 dae::Grid::GetPlayerStartPoint()
{
	
	return GetStartPoint([](const Cell& cell) { return cell.IsPlayerStartPoint; }); // lamda functie als predicate;
}

glm::vec2 dae::Grid::GetOponentStartPoint()
{

	return GetStartPoint([](const Cell& cell) { return cell.IsOponentStartPoint; }); // lamda functie als predicate;
}


std::vector<glm::vec2> dae::Grid::GetPookaStartPoints() 
{
	return GetStartPoints([](const Cell& cell) { return cell.IsPookaStartPoint; });
}

std::vector<glm::vec2> dae::Grid::GetFygarStartPoints() 
{
	return GetStartPoints([](const Cell& cell) { return cell.IsFygarStartpoint; });
}

std::vector<glm::vec2> dae::Grid::GetRockStartPoints() 
{
	return GetStartPoints([](const Cell& cell) { return cell.IsRockStartPoint; });
}

int dae::Grid::GetNrColumns() const
{
	return m_AmountOfColumns;
}

int dae::Grid::GetNrRows() const
{
	return m_AmountOfRows;
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

const glm::vec2 dae::Grid::GetCellPosition(int row, int col) const
{
	Cell wantedCell{ m_Cells[GetCellIdx(row,col)] };
	return glm::vec2{ static_cast<float>(wantedCell.dstRect.x), static_cast<float>(wantedCell.dstRect.y) };
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

void dae::Grid::SetDug(const dae::Event& event)
{
	for (const auto& data : event.data)
	{
		if (data.type() == typeid(dae::Grid::Cell))
		{
			dae::Grid::Cell cell = std::any_cast<dae::Grid::Cell>(data);
			if (m_Cells[GetCellIdx(cell.row, cell.col)].IsDug == false)
			{
				m_Cells[GetCellIdx(cell.row, cell.col)].IsDug = true;
			}
		}
		
	}
}

