
## Pacman reunion 

This repository is a project summarizing the knowledge gained during computer architecture classes at the Bialystok University of Technology. The goal was to create a game modeled on the iconic production Pacman.
The program was created for msp430-easyweb2 boards.

<br/>

**Rules**: 

Player, depending on the difficulty of the level, has assigned a health number, power Ups and game speed.
During the game, player travels the map, which consists of paths, coins and enemies.
The aim of the game is to score as many points as possible. This can be done by collecting coins or by eating your opponents when you use Power Ups.
The game ends when a player loses all hearts, reaches the limit of possible coins to collect or reaches the end of the map.

![pacman-reunion](https://user-images.githubusercontent.com/71569327/213878953-f2c68eb7-f264-41f0-bb8c-c4f936c44615.png)

<br/>

**Thoughts**: 

During the implementation of this project, we encountered a problem that did not allow for full optimization of the code.
The outdated environment "IAR Embedded Workbench" in which we programmed does not allow us to load the entire project due to the limit of lines of code.
This forced us to change our approach from optimizing the code to writing as few lines as possible so that the project could be uploaded to the msp430 board.

<br/>

**License**: 

Pacman reunion project is licensed under [MIT License](https://github.com/TR0U8L3-gif/pacman-reunion/blob/main/LICENSE.md).
