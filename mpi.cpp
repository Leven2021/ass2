#include "asg2.h"
#include <stdio.h>
#include <mpi.h>

int rank;
int world_size;

void master()
{
	// TODO: procedure run in master process
	int count = 0;
	int column = 0;
	for (int k = 1; k < world_size; k++) {
		MPI_Send(&column, 1, MPI_INT, k, 7, MPI_COMM_WORLD);
		count++;
		column++;
	}
	float colors[Y_RESN];
	MPI_Status status;
	int target_column;
	Point* p;
	int terminator = -1;
	do {
		MPI_Recv(colors, Y_RESN, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		target_column = status.MPI_TAG;
		p = data + target_column * Y_RESN;
		for (int i = 0; i < Y_RESN; i++) {
			p->color = colors[i];
			p++;
		}
		count--;
		if (column < X_RESN) {
			MPI_Send(&column, 1, MPI_INT, status.MPI_SOURCE, 7, MPI_COMM_WORLD);
			count++;
			column++;
		} else {
			MPI_Send(&terminator, 1, MPI_INT, status.MPI_SOURCE, 7, MPI_COMM_WORLD);
		}
	} while (count > 0);
	// TODO END
}

void slave()
{
	// TODO: procedure run in slave process
	int column;
	Point* p = new Point;
	float colors[Y_RESN];
	while (true) {
		MPI_Recv(&column, 1, MPI_INT, 0, 7, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if (column == -1) break;
		p->x = column;
		p->y = 0;
		p->color = 0;
		for (int i = 0; i < Y_RESN; i++) {
			compute(p);
			colors[i] = p->color;
			p->y += 1;
		}
		MPI_Send(colors, Y_RESN, MPI_FLOAT, 0, column, MPI_COMM_WORLD);
	}
	// TODO END
}

int main(int argc, char *argv[])
{
	if (argc == 4)
	{
		X_RESN = atoi(argv[1]);
		Y_RESN = atoi(argv[2]);
		max_iteration = atoi(argv[3]);
	}
	else
	{
		X_RESN = 1000;
		Y_RESN = 1000;
		max_iteration = 100;
	}

	if (rank == 0)
	{
#ifdef GUI
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("MPI");
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(0, X_RESN, 0, Y_RESN);
		glutDisplayFunc(plot);
#endif
	}

	/* computation part begin */
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	if (rank == 0)
	{
		initData();
		t1 = std::chrono::high_resolution_clock::now();
	}

	if (rank == 0)
	{
		// you may change this part
		master();
	}
	else
	{
		// you may change this part
		slave();
	}

	if (rank == 0)
	{
		t2 = std::chrono::high_resolution_clock::now();
		time_span = t2 - t1;
	}

	if (rank == 0)
	{
		printf("Student ID: 119010211\n"); // replace it with your student id
		printf("Name: Ziang Liu\n");	   // replace it with your name
		printf("Assignment 2 MPI\n");
		printf("Run Time: %f seconds\n", time_span.count());
		printf("Problem Size: %d * %d, %d\n", X_RESN, Y_RESN, max_iteration);
		printf("Process Number: %d\n", world_size);
	}

	MPI_Finalize();
	/* computation part end */

	if (rank == 0)
	{
#ifdef GUI
		glutMainLoop();
#endif
	}

	return 0;
}
