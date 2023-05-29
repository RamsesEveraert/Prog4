#pragma once

#include "Component.h"
#include <vector>
#include <SDL.h>
#include <glm/glm.hpp>
#include <algorithm>
#include <functional>

namespace dae
{
	struct Event;
	class Grid final : public Component
	{
	public:

		struct Cell
		{
			int row, col;
			SDL_Rect dstRect;
			bool IsDug, IsRockStartPoint, IsPlayerStartPoint, IsOponentStartPoint, IsPookaStartPoint, IsFygarStartpoint;
		};

		// Rule of 6

		Grid(float width, float height, float sizeCells, const glm::vec2& position, const std::vector<std::string>& levelLayout);
		virtual ~Grid() = default;

		Grid(const Grid& other) = delete;
		Grid(Grid&& other) = delete;
		Grid& operator=(const Grid& other) = delete;
		Grid& operator=(Grid&& other) = delete;

		// Functions

		virtual void Render() override;

		glm::vec2 GetPlayerStartPoint() ;
		glm::vec2 GetOponentStartPoint() ;
		std::vector<glm::vec2> GetPookaStartPoints() ;
		std::vector<glm::vec2> GetFygarStartPoints() ;
		std::vector<glm::vec2> GetRockStartPoints() ;


		int GetNrColumns() const;
		int GetNrRows() const;

		int GetCellIdx(int row, int col) const;
		int GetCellIdxFromPosition(const glm::vec2& position) const;
		std::vector<Cell> GetCells() const;

		const glm::vec2 GetCellPosition(int row, int col) const;

		const glm::vec2& GetCellSize() const;
		const glm::vec2& GetGridPosition()const;
		const glm::vec2& GetGridSize()const;

	private:

		const glm::vec2 GetStartPoint(std::function<bool(const Cell&)> predicate) const; // helper function
		std::vector<glm::vec2> GetStartPoints(std::function<bool(const Cell&)> predicate) const; // helper function

		void SetDug(const dae::Event& event);	

		glm::vec2 m_GridOffset;
		glm::vec2 m_SizeCells;
		glm::vec2 m_GridSize;
		int m_AmountOfColumns, m_AmountOfRows;
		std::vector<Cell> m_Cells;

	};
}