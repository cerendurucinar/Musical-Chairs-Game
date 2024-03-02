# Musical-Chairs-Game
A multithreaded C++ program that simulates the universal game called musical chairs using queue. The game starts after taking number of players as input. It simulates each round of the game via several threads (one for each player) and print relevant information. At each round, after the threads start, the threads will sleep until a certain time so that all players start the game at the same time. Capturing a chair is simulated by enqueueing the player ID to a queue shared by all threads. The main program displays the IDs of players who captured a chair on the screen in the capturing order (in a single line). After that, the next round starts by eliminating the player who could not capture a chair in the previous round. At each round, the number of chairs is decremented by one. The game finishes when there is a single player left who is declared as winner.
