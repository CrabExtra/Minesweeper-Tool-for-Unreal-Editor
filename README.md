# Minesweeper Tool for Unreal Editor

## Overview

The **Minesweeper Tool** is an Unreal Editor plugin that allows users to play a classic Minesweeper game directly within the editor. This tool demonstrates the use of Unreal Engine's Slate framework to create an interactive UI for gameplay and serves as an example of tooling development in C++.

### Features
- Toolbar button to open the Minesweeper tool window.
- Configurable grid settings:
  - **Grid Width**
  - **Grid Height**
  - **Number of Bombs**
- Gameplay interactions:
  - **Revealing a Tile**: Displays the number of adjacent bombs, or recursively reveals empty tiles if no adjacent bombs exist.
  - **Game Over**: A message is displayed when a bomb is clicked.
  - Start a new game at any time.
- Purely built using **C++** and **Slate** (no UMG or Editor Utility Widgets).

---

## Setup Instructions

### Prerequisites
- Unreal Engine version 5.5.
- A development environment set up for Unreal Engine C++ projects.

### Steps
1. Clone this repository into the `Plugins` folder of your Unreal project:
   ```bash
   git clone https://github.com/CrabExtra/Minesweeper-Tool-for-Unreal-Editor.git YourUnrealProject/Plugins/MinesweeperTool
   ```
2. Open your Unreal project in the Editor.
3. Build the project through the Unreal Editor or your IDE (e.g., Visual Studio or Rider).
4. After building, you will see a **Minesweeper** button in the toolbar. Click it to open the Minesweeper tool.

---

## How to Use

1. Open the Minesweeper tool by clicking the **Minesweeper** button in the Unreal Editor toolbar.
2. Configure the grid settings:
   - **Grid Width**: Set the horizontal size of the grid.
   - **Grid Height**: Set the vertical size of the grid.
   - **Number of Bombs**: Set the number of bombs to be placed on the grid.
3. Click **New Game** to start a new game with the specified settings.
4. Click on tiles to reveal them:
   - Bomb tiles will display a **Game Over** message.
   - Non-bomb tiles will show the number of adjacent bombs or recursively reveal empty tiles.
5. Click **New Game** at any time to reset the board.

---

## Implementation Details

### Architecture
The plugin is implemented as a self-contained Unreal Editor plugin:
- **Toolbar Button**: Added using Unreal's toolbar extension system.
- **Slate UI**: Built entirely with the Slate framework for maximum customization and editor integration.
- **Game Logic**: Encapsulated in a `FMinesweeperGameLogic` class for easy testing and separation of concerns.

### Code Highlights
- **Dynamic Bomb Placement**: Bombs are placed after the first click to ensure the first tile is always safe.
- **Recursive Reveal**: Empty tiles recursively reveal their neighbors, mimicking classic Minesweeper behavior.
- **Slate Widgets**: The grid, buttons, and text are implemented using Slate's `SNew` syntax for declarative UI construction.

---

## Use of AI/LLMs

### What was done with AI
- **Syntax Assistance**: AI tools like GitHub Copilot were used to assist with repetitive code generation, particularly for Slate UI.
- **Inline Code Generation**: AI was consulted for generating snippets for recursive reveal logic and bomb placement.
- **Debugging and Reference**: AI was used to validate Unreal-specific syntax and to confirm adherence to Minesweeper rules.

### Why AI Was Used
- To save time on repetitive or boilerplate-heavy tasks.
- To ensure best practices in Unreal Engine's Slate framework were followed.
- To assist in generating code for complex logic (e.g., recursive reveal).

### AI Integration Notes
AI was used sparingly, with the majority of the logic and architecture implemented manually. The focus remained on ensuring functionality and quality rather than over-reliance on automated tools.

---

## Known Limitations
- **No Bomb Flagging**: This feature was excluded per the task requirements.
- **Minimal Visual Design**: The focus was on functionality and code quality, not visual polish.

---

## Future Enhancements
- Add bomb flagging functionality.
- Improve visual feedback for revealed tiles (e.g., color coding or animations).
- Allow natural language input for grid configuration using AI and MCP integration.

---

## Author
- **CrabExtra**  
- GitHub: [https://github.com/CrabExtra](https://github.com/CrabExtra)

---

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.
