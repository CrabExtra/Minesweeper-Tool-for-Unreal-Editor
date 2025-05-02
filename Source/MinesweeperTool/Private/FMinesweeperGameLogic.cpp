#include "FMinesweeperGameLogic.h"

FMinesweeperGameLogic::FMinesweeperGameLogic()
{
}

void FMinesweeperGameLogic::Reset(int32 InWidth, int32 InHeight, int32 InBombCount)
{
    Width = FMath::Clamp(InWidth, 2, 64);
    Height = FMath::Clamp(InHeight, 2, 64);
    BombCount = FMath::Clamp(InBombCount, 1, Width * Height - 1);

    Tiles.SetNum(Width * Height);
    for (auto& Tile : Tiles)
    {
        Tile.bIsBomb = false;
        Tile.bRevealed = false;
        Tile.AdjacentBombs = 0;
    }
    bGameOver = false;
    bFirstClick = true; // Reset the first-click flag
}

void FMinesweeperGameLogic::PlaceBombs(int32 SafeX, int32 SafeY)
{
    TArray<int32> Indices;
    for (int32 i = 0; i < Width * Height; ++i)
    {
        int32 X = i % Width;
        int32 Y = i / Width;
        // Exclude the safe tile and its neighbors
        if ((FMath::Abs(X - SafeX) <= 1) && (FMath::Abs(Y - SafeY) <= 1))
        {
            continue;
        }
        Indices.Add(i);
    }

    for (int32 i = 0; i < BombCount && Indices.Num() > 0; ++i)
    {
        int32 idx = FMath::RandRange(0, Indices.Num() - 1);
        Tiles[Indices[idx]].bIsBomb = true;
        Indices.RemoveAt(idx);
    }

    CalculateAdjacents();
}

void FMinesweeperGameLogic::CalculateAdjacents()
{
    for (int32 Y = 0; Y < Height; ++Y)
    {
        for (int32 X = 0; X < Width; ++X)
        {
            FTile& Tile = Tiles[Y * Width + X];
            if (Tile.bIsBomb)
            {
                Tile.AdjacentBombs = -1;
                continue;
            }

            int32 Count = 0;
            for (int32 dy = -1; dy <= 1; ++dy)
            {
                for (int32 dx = -1; dx <= 1; ++dx)
                {
                    if (dx == 0 && dy == 0)
                        continue;
                    int32 nx = X + dx;
                    int32 ny = Y + dy;
                    if (InBounds(nx, ny))
                    {
                        if (Tiles[ny * Width + nx].bIsBomb)
                            ++Count;
                    }
                }
            }
            Tile.AdjacentBombs = Count;
        }
    }
}

void FMinesweeperGameLogic::RevealTile(int32 X, int32 Y)
{
    if (!InBounds(X, Y))
        return;

    FTile& Tile = GetTile(X, Y);
    if (Tile.bRevealed)
        return;

    // Handle first-click logic
    if (bFirstClick)
    {
        bFirstClick = false;
        PlaceBombs(X, Y); // Place bombs after the first click
    }

    Tile.bRevealed = true;

    if (Tile.bIsBomb)
    {
        bGameOver = true;
        return;
    }

    if (Tile.AdjacentBombs == 0)
    {
        RevealRecursive(X, Y);
    }
}

void FMinesweeperGameLogic::RevealRecursive(int32 X, int32 Y)
{
    for (int32 dy = -1; dy <= 1; ++dy)
    {
        for (int32 dx = -1; dx <= 1; ++dx)
        {
            if (dx == 0 && dy == 0)
                continue;
            int32 nx = X + dx;
            int32 ny = Y + dy;
            if (InBounds(nx, ny))
            {
                FTile& Neighbor = GetTile(nx, ny);
                if (!Neighbor.bRevealed && !Neighbor.bIsBomb)
                {
                    Neighbor.bRevealed = true;
                    if (Neighbor.AdjacentBombs == 0)
                    {
                        RevealRecursive(nx, ny);
                    }
                }
            }
        }
    }
}

FTile& FMinesweeperGameLogic::GetTile(int32 X, int32 Y)
{
    return Tiles[Y * Width + X];
}

const FTile& FMinesweeperGameLogic::GetTile(int32 X, int32 Y) const
{
    return Tiles[Y * Width + X];
}

bool FMinesweeperGameLogic::InBounds(int32 X, int32 Y) const
{
    return X >= 0 && X < Width && Y >= 0 && Y < Height;
}

bool FMinesweeperGameLogic::IsWon() const
{
    for (const FTile& Tile : Tiles)
    {
        if (!Tile.bIsBomb && !Tile.bRevealed)
            return false;
    }
    return !bGameOver && Tiles.Num() > 0;
}