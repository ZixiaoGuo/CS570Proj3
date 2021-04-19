pagetable:
	g++ -std=c++11 -g -pthread -lrt main.h io.h io.cpp production.h main.cpp frogProducer.cpp consumer.cpp -o mizzo

clean:
	rm *.o
# Name: Zixiao Guo, Kian Fahimi
# Account: cssc3425, cssc3422
# CS570 Spring2021
# Assignment #2 wordcount
# Filename: makefile
# RedID: 822029189, 822758164
