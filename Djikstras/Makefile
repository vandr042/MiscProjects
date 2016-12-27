all: Main.class Graph.class Djikstra.class

Djikstra.class: src/Djikstra.java
	javac -cp src/ src/Djikstra.java -d out
Graph.class: src/Graph.java
	javac src/Graph.java -d out	
Main.class: src/Main.java
	javac -cp src src/Main.java -d out

Main: out/Main.class
	java -cp out Main /home/vandr042/Classes/csci4211/Djikstras/Graphs/graph2.txt
