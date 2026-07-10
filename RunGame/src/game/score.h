#pragma once

class CScore
{
public:
	void Init();
	void Load();
	void Tick();
	void Exit();
	void Draw();
	void Add(int score);
	void Set(int score);
	int Get();
};



