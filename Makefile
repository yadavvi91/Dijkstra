dijkstra: main.o dijkstra.o graph.o prioqueue.o
	gcc main.o dijkstra.o graph.o prioqueue.o -o dijkstra
main.o: main.c
	gcc -c main.c -o main.o
dijkstra.o: dijkstra.c
	gcc -c dijkstra.c -o dijkstra.o
graph.o: graph.c
	gcc -c graph.c -o graph.o
prioqueue.o: prioqueue.c
	gcc -c prioqueue.c -o prioqueue.o	
