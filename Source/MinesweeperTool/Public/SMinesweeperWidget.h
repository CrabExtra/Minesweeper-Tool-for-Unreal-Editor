#pragma once

#include "Widgets/SCompoundWidget.h"
#include "FMinesweeperGameLogic.h"

class SMinesweeperWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMinesweeperWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	int32 GridWidth = 8;
	int32 GridHeight = 8;
	int32 BombCount = 10;

	bool bGameStarted = false;

	TUniquePtr<FMinesweeperGameLogic> Game;
	TSharedPtr<SVerticalBox> GridBox;

	void OnGridWidthChanged(int32 NewValue);
	void OnGridHeightChanged(int32 NewValue);
	void OnBombCountChanged(int32 NewValue);
	FReply OnNewGameClicked();
	void RebuildGrid();
	FReply OnTileClicked(int32 X, int32 Y);
};