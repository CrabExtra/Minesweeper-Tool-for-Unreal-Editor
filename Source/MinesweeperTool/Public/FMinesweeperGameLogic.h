#pragma once

#include "CoreMinimal.h"

struct FTile
{
	bool bIsBomb = false;
	bool bRevealed = false;
	int32 AdjacentBombs = 0;
};

class FMinesweeperGameLogic
{
public:
	FMinesweeperGameLogic();
	~FMinesweeperGameLogic() = default;

	void Reset(int32 InWidth, int32 InHeight, int32 InBombCount);
	void RevealTile(int32 X, int32 Y);
	bool IsGameOver() const { return bGameOver; }
	bool IsWon() const;
	int32 GetWidth() const { return Width; }
	int32 GetHeight() const { return Height; }
	FTile& GetTile(int32 X, int32 Y);
	const FTile& GetTile(int32 X, int32 Y) const;

private:
	int32 Width = 0;
	int32 Height = 0;
	int32 BombCount = 0;
	TArray<FTile> Tiles;
	bool bGameOver = false;
	bool bFirstClick = true;
	
	void PlaceBombs(int32 SafeX, int32 SafeY);
	void CalculateAdjacents();
	void RevealRecursive(int32 X, int32 Y);
	bool InBounds(int32 X, int32 Y) const;
};