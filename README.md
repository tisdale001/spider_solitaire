# spider_solitaire
C++ project: spider_solitaire
## Description
This is one-suit spider solitaire for C++. This is a program I wrote, just for fun, to practice certain C++ good coding practice skills. The program uses design patterns: Model/View/Controller and the Command pattern. The command pattern was used to acheive the undo/redo feature. I also created a design pattern of my own (similar to the Decorator pattern or Adapter pattern). I call it an "AnimationWrapper". It "wraps" a card class and handles the animation instructions of a linear animation you want to accomplish, given starting point, destination point, and number of frames as input. Thousands of these animation wrappers can be advanced, frame-by-frame, to produce simultaneous card animations.

During game play you can click and drag to make moves or simply click a card and the program will execute the first possible legal move. Of course you can always undo as many moves as you want. The goal of the game is to get all cards into the 'Ace' piles at the top right of the screen by creating complete 'stacks', from Ace to King.

For complete rules, try this link: [https://www.bvssolitaire.com/rules/spider-solitaire-one-suit.htm](link)

## Features
* Image animation (card animation)
* Memory management: no memory leaks through use of smart pointers
* Model/View/Controller pattern used for framework
* Command pattern: used to implement undo/redo feature
* AnimationWrapper: design pattern of my creation to handle card animation
* Object-oriented design: different classes for elements of game such as cards, deck of cards, card piles, etc.
* Drag-and-drop gameplay or one-click play
* Creation of algorithms to handle rules of game

## How to Build
cd into bin directory

You may have to change line 48 in cmake_install.cmake to your actual path. Something like this:

file(WRITE "/home/user/GithubRepos/spider_solitaire/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
```
cmake ..
make
```
## How to Run
```
./spider
```
## "Hotkeys":
'D' = re-Deal<br>
'Z' = undo<br>
'Y' = redo<br>
'M' = play winning "cardburst" animation (hit any key to stop)<br>
***
![spider_solitaire_1](https://user-images.githubusercontent.com/53150782/193928067-8a2cc551-0ba7-409c-8d1f-43f8c16fe98b.PNG)
![spider_solitaire_2](https://user-images.githubusercontent.com/53150782/193928085-1b964497-13f5-45b3-bbf8-049a358e0a2e.PNG)
