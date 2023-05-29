#pragma once
#include "Component.h"

namespace dae
{
	class Grid;
	class Enemy final : public Component
	{
	public:
		Enemy(Grid* pGrid, int indexEnemy);
		~Enemy() = default;

		Enemy(const Enemy& other) = delete;
		Enemy(Enemy&& other) noexcept = delete;
		Enemy& operator=(const Enemy& other) = delete;
		Enemy& operator=(Enemy&& other) noexcept = delete;

		void InitEnemy();
	private:
		void AddRequiredComponents();
		Grid* m_pGrid;
		const int m_IndexEnemy;
	};
}
