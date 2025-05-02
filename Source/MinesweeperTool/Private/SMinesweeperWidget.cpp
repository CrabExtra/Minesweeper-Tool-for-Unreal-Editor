#include "SMinesweeperWidget.h"
#include "FMinesweeperGameLogic.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"

void SMinesweeperWidget::Construct(const FArguments& InArgs)
{
    Game = MakeUnique<FMinesweeperGameLogic>();
    // Do not start/reset game or build grid yet!

    ChildSlot
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot().AutoHeight().Padding(4)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot().AutoWidth().Padding(2)
            [
                SNew(STextBlock).Text(FText::FromString("Grid Width:"))
            ]
            + SHorizontalBox::Slot().AutoWidth().Padding(2)
            [
                SNew(SNumericEntryBox<int32>)
                .Value_Lambda([this]() { return GridWidth; })
                .MinValue(2).MaxValue(32)
                .OnValueChanged(this, &SMinesweeperWidget::OnGridWidthChanged)
            ]
            + SHorizontalBox::Slot().AutoWidth().Padding(8)
            [
                SNew(STextBlock).Text(FText::FromString("Grid Height:"))
            ]
            + SHorizontalBox::Slot().AutoWidth().Padding(2)
            [
                SNew(SNumericEntryBox<int32>)
                .Value_Lambda([this]() { return GridHeight; })
                .MinValue(2).MaxValue(32)
                .OnValueChanged(this, &SMinesweeperWidget::OnGridHeightChanged)
            ]
            + SHorizontalBox::Slot().AutoWidth().Padding(8)
            [
                SNew(STextBlock).Text(FText::FromString("Bombs:"))
            ]
            + SHorizontalBox::Slot().AutoWidth().Padding(2)
            [
                SNew(SNumericEntryBox<int32>)
                .Value_Lambda([this]() { return BombCount; })
                .MinValue(1).MaxValue(1024)
                .OnValueChanged(this, &SMinesweeperWidget::OnBombCountChanged)
            ]
            + SHorizontalBox::Slot().AutoWidth().Padding(8)
            [
                SNew(SButton)
                .Text(FText::FromString("New Game"))
                .OnClicked(this, &SMinesweeperWidget::OnNewGameClicked)
            ]
        ]
        + SVerticalBox::Slot().FillHeight(1.0f).Padding(4)
        [
            SAssignNew(GridBox, SVerticalBox)
        ]
    ];

    RebuildGrid();
}

void SMinesweeperWidget::OnGridWidthChanged(int32 NewValue)
{
    GridWidth = NewValue;
}

void SMinesweeperWidget::OnGridHeightChanged(int32 NewValue)
{
    GridHeight = NewValue;
}

void SMinesweeperWidget::OnBombCountChanged(int32 NewValue)
{
    BombCount = NewValue;
}

FReply SMinesweeperWidget::OnNewGameClicked()
{
    bGameStarted = true;
    Game->Reset(GridWidth, GridHeight, BombCount);
    RebuildGrid();
    return FReply::Handled();
}

void SMinesweeperWidget::RebuildGrid()
{
    if (!GridBox.IsValid())
        return;

    GridBox->ClearChildren();

    if (!bGameStarted)
    {
        GridBox->AddSlot()
        [
            SNew(STextBlock).Text(FText::FromString("Press 'New Game' to start!"))
        ];
        return;
    }

    if (Game->IsGameOver())
    {
        GridBox->AddSlot()
        [
            SNew(STextBlock).Text(FText::FromString("Game Over!"))
        ];
        return;
    }
    else if (Game->IsWon())
    {
        GridBox->AddSlot()
        [
            SNew(STextBlock).Text(FText::FromString("You win!"))
        ];
        return;
    }

    for (int32 Y = 0; Y < Game->GetHeight(); ++Y)
    {
        TSharedPtr<SHorizontalBox> Row;
        GridBox->AddSlot()
        [
            SAssignNew(Row, SHorizontalBox)
        ];
        for (int32 X = 0; X < Game->GetWidth(); ++X)
        {
            const FTile& Tile = Game->GetTile(X, Y);

            FString Label = TEXT("");
            FSlateColor TextColor = FSlateColor(FLinearColor::White);

            if (Tile.bRevealed)
            {
                if (Tile.bIsBomb)
                {
                    Label = TEXT("B");
                    TextColor = FSlateColor(FLinearColor::Red);
                }
                else
                {
                    // Always show number (for debugging, including 0)
                    Label = FString::FromInt(Tile.AdjacentBombs);

                    // Optional: color code numbers
                    switch (Tile.AdjacentBombs)
                    {
                        case 1: TextColor = FSlateColor(FLinearColor::Blue); break;
                        case 2: TextColor = FSlateColor(FLinearColor::Green); break;
                        case 3: TextColor = FSlateColor(FLinearColor::Red); break;
                        case 4: TextColor = FSlateColor(FLinearColor::Gray); break;
                        case 5: TextColor = FSlateColor(FLinearColor::Yellow); break;
                        default: TextColor = FSlateColor(FLinearColor::White); break;
                    }
                }
            }

            // Use an if/else to avoid Ternary Widget Construction Error
            TSharedRef<SWidget> TileWidget =
                Tile.bRevealed
                ? StaticCastSharedRef<SWidget>(SNew(STextBlock)
                    .Text(FText::FromString(Label))
                    .ColorAndOpacity(TextColor)
                    .Justification(ETextJustify::Center))
                : StaticCastSharedRef<SWidget>(SNew(SButton)
                    .Text(FText::FromString(TEXT("")))
                    .OnClicked(this, &SMinesweeperWidget::OnTileClicked, X, Y)
                    .IsEnabled(!Game->IsGameOver() && !Game->IsWon()));

            Row->AddSlot().AutoWidth().Padding(1)
            [
                SNew(SBox)
                .WidthOverride(32)
                .HeightOverride(32)
                [
                    TileWidget
                ]
            ];
        }
    }
}

FReply SMinesweeperWidget::OnTileClicked(int32 X, int32 Y)
{
    if (!bGameStarted)
        return FReply::Handled();

    Game->RevealTile(X, Y);
    RebuildGrid();
    return FReply::Handled();
}