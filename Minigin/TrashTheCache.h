#pragma once

struct Transform
{
	float matrix[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
};

class GameObject3D
{
public:
	Transform transform{};
	int ID{};
};

class GameObject3DAlternative
{
public:
	Transform* transform{};
	int ID{};
};

class TrashTheCache final
{
public:

	void PlotExercice1();
	void Exercice2();

	TrashTheCache() = default;
	~TrashTheCache() = default;

	TrashTheCache(const TrashTheCache& other) = delete;
	TrashTheCache(TrashTheCache&& other) = delete;
	TrashTheCache& operator=(const TrashTheCache& other) = delete;
	TrashTheCache& operator=(TrashTheCache&& other) = delete;

private:


};

