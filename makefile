edit : main.o animation.o context.o event.o list.o missile.o mobile.o sprite.o utils.o
	gcc main.o animation.o context.o event.o list.o missile.o mobile.o sprite.o utils.o -o main -lSDL2 -lSDL2_image
main.o: main.c missile.h animation.h context.h event.h
	gcc -c main.c -lSDL2
animation.o: animation.c sprite.h list.h
	gcc -c animation.c -lSDL2
context.o: context.c utils.h sprite.h mobile.h missile.h animation.h
	gcc -c context.c -lSDL2
event.o: event.c
	gcc -c event.c -lSDL2
list.o: list.c
	gcc -c list.c -lSDL2
missile.o: missile.c utils.h mobile.h context.h
	gcc -c missile.c -lSDL2
mobile.o: mobile.c utils.h sprite.h
	gcc -c mobile.c -lSDL2
sprite.o: sprite.c utils.h
	gcc -c sprite.c -lSDL2
utils.o: utils.c
	gcc -c utils.c -lSDL2
