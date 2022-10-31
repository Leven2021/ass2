CXX = g++ -std=c++11
CXXFLAG = -g -wall -std=c++11

a2: asg2.h mpi.cpp pthread.cpp sequential.cpp
	g++ sequential.cpp -o seq -O2 -std=c++11
	mpic++ mpi.cpp -o mpi -std=c++11
	g++ pthread.cpp -o pthread -lpthread -O2 -std=c++11
a2_gui: asg2.h mpi.cpp pthread.cpp sequential.cpp
	g++ sequential.cpp -o seqg -I/usr/include -L/usr/local/lib -L/usr/lib -lglut -lGLU -lGL -lm -DGUI -O2 -std=c++11
	mpic++ mpi.cpp -o mpig -I/usr/include -L/usr/local/lib -L/usr/lib -lglut -lGLU -lGL -lm -DGUI -std=c++11
	g++ pthread.cpp  -o pthreadg -I/usr/include -L/usr/local/lib -L/usr/lib -lglut -lGLU -lGL -lm -lpthread -DGUI -O2 -std=c++11
clean:
	rm -f seq
	rm -f seqg
	rm -f mpi
	rm -f mpig
	rm -f pthread
	rm -f pthreadg
