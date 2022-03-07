# Battleship 
##### V1.2

This README file is dedicated to the repository of Team 4's adaptation of another team's _Battleship_ project. In it you will find the following folders:

| File | Purpose|
|------|--------|
| Back-End/class_example | Previous team's back-end python files. |
| Documentation | Previous and current team's documentation (denoted by version).  |
| Front-End | Previous team's back-end python files. |
| Terminal-Based Implementation | Our addaption of the Battleship Project. |

Both the **Back-End** and **Front-End** folders contain Python files pertaining to the original group's vision for the project. Unfortunately this codebase was started in Python and switched to C++ halfway though development which led to the repository being a bit unorganized when we first received it. 

This would be the group's **Terminal-Based Implementation** folder. However upon closer inspection we found that this implementation also didn't function. After speaking to the instructor, we decided to pursue the route of using this C++ implementation rather than using the Python codebase. Within this folder you will find the following:

| Folder/File | Purpose|
|------|--------|
| Sounds | This folder contains the sounds used during the game. |
| Board.cpp | Source file for defining all function in the Board **class**. |
| Board.h | Header file used to list all functions within the Board **class** |
| Executive.cpp | Source file for defining all non-Board related functions. |
| Executive.h | Header file used to list all functions used in the main game's "loop" |
| main.cpp | Source file used to start the game's main loop. |
| makefile | Used to compile and create the object(s)/executable for the _**Battleship**_ |

**Documentation** folder is pretty standard. It contains files from both the current development team as well as the previous development team. More information to be found below.

## Gameplay
The following are screenshots of gameplay. While each game has the potential for a different outcome, this is the general look and feel of our implementation:

<img width="1208" alt="startGame" src="https://user-images.githubusercontent.com/98842234/156965248-d0cbc83a-4077-4f1b-9a3a-080f0644622d.png">

<img width="1198" alt="finishedGame" src="https://user-images.githubusercontent.com/98842234/156965256-58dd0de4-9f8c-4a57-aa26-5700c161d07d.png">

<img width="1200" alt="AIstart" src="https://user-images.githubusercontent.com/98842234/156965263-28c599d1-f955-4427-bed9-a85a684f6ce6.png">




## Installation
Our Battleship game functions by using a C++ _**terminal-based implementation**_.
- _**Clone**_ or _**download**_ the repository to your local machine,
- Locate and navigate to the source files (**Terminal-based Implementation/Battleship**) in your terminal.
-Use the _make_ command to compile and build
the executable.
-Use the command ./battleship to run the program.

> Any terminal implementation should work, just make sure you have a large enough resolution in order to be able to view the game-board correctly.

## Documentation
Within the _Battleship_ repository, there is a folder labeled **documentation**. This folder was used to both _estimate_ and _record_ the total time spent developing this project (for both our team and the previous development team). Here, it also serves to familiarize any team with how our software works, as to avoid confusion. 

> While this isn't much use to anyone who contributes this the project later, feel free to add columns/tabs for your team to measure how long improvements or changes you've made took.

Additionally, there exists files labled _**Software Architecture**_ and _**Collection of Features**_.

_**Software Architecture**_ is our team's analysis of the previous team's methods, specifically what Software Architecture style/design the previous team went with and why we think they pursued it (also if we think it was the right approach for the given project).

_**Collection of Features**_ is an evaluation of how we sought out to improve upon the previous team's implementation and what we could do to improve upon it. It should be noted though that while we improved upon the generic _battleship_ game, we also needed to get the project to _function as intended_ prior to making improvements. While not difficult, it did add additional work to our project.

> For those who contribute to this project at a later date, please make sure to adequately comment the code. If major changes are made please be sure to _specify_ **why** these changes were made, and how they improve upon the original design.


## Development

##### Why C++?
- We felt that between the options of C++ and Python, the codebase was more usable in a C++ format 
- While certain compromises were made to meet the required deadline, specifically the lack of a visually appealing _terminal output_, we feel like this project was an improvement upon the already existing codebase, and stands as a better version of the product.


## License
This software is not currently liscensed in any capacity or copyrighted in any way. However, while permission to use this software for personal development is allowed, commercial use is **not**.



