#pragma once
#include "Component.h"

namespace dae
{
	class Grid;
	class Enemy : public Component
	{
	public:
		Enemy(Grid* pGrid, int indexEnemy);
		~Enemy() = default;

		void InitEnemy();
	private:
		void AddRequiredComponents();
		Grid* m_pGrid;
		const int m_IndexEnemy;
	};
}
