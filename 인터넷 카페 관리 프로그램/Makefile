project : project.o NormalManagement.o MasterManagement.o function.o header.h
	gcc -o project project.o NormalManagement.o MasterManagement.o function.o

project.o : project.c
	gcc -c project.c

function.o : function.c
	gcc -c function.c

MasterManagement.o : MasterManagement.c
	gcc -c MasterManagement.c

NormalManagement.o : NormalManagement.c
	gcc -c NormalManagement.c

clean :
	rm *.o project
