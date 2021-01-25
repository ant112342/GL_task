#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <math.h>


typedef struct {
	double x;
	double y;
} Point;

double delta = 1e-4;

Point *point_create(double x_cord, double y_cord)
{
	Point *p = malloc(sizeof(Point));
	if (p == NULL) {
		return NULL;
	}

	p->x = x_cord;
	p->y = y_cord;

	return p;
}

void point_free(Point *p)
{
	free(p);
}

double area_triangle(Point *p1, Point *p2, Point *p3)
{
	double a = 0;

	a = p1->x * (p2->y - p3->y) + p2->x * (p3->y - p1->y) +
	    p3->x * (p1->y - p2->y);

	return fabs(a / 2.0);
}

bool is_collinear(Point *a, Point *b, Point *c)
{
	if ((c->y - b->y) * (b->x - a->x) == (b->y - a->y) * (c->x - b->x))

		return true;

	else
		return false;
}

bool isInside(Point *p1, Point *p2, Point *p3, Point *p)
{
	double area = area_triangle(p1, p2, p3); //area of triangle ABC
	double area1 = area_triangle(p, p2, p3); //area of PBC
	double area2 = area_triangle(p1, p, p3); //area of APC
	double area3 = area_triangle(p1, p2, p); //area of ABP

	if (abs(area - (area1 + area2 + area3)) <= delta) {
	
		return true;
		
	} else
	
		return false;
}

void put_generated_num()
{
	double x[4], y[4];

	srand((unsigned int)time(NULL));

	FILE *fptr;
	fptr = fopen("data.txt", "w");

	if (fptr == NULL) {
		/* File not created hence exit */
		printf("Failed to open file\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < 4; i++) {
	
		x[i] = (((double)rand() / (double)(RAND_MAX)) * 100.00);
		printf("Generated x[%d] = %f\n", i, x[i]);
		y[i] = (((double)rand() / (double)(RAND_MAX)) * 100.00);
		printf("Generated y[%d] = %f\n", i, y[i]);
		fprintf(fptr, "%.5g\t%.5g\n", x[i], y[i]);
		
	}
	
	fclose(fptr);
	printf("Data successfully written in txt file\n");
	printf("The file is now closed.\n");
	
}

int main(void)
{
	struct Point *p1, *p2, *p3, *p;
	float in_x[4], in_y[4];
	char i = 0;

	FILE *file;
	put_generated_num();
	file = fopen("data.txt", "r");
	
	if (file == NULL) {
		printf("Failed to open file\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Reading values from file\n");

	while (fscanf(file, "%f%f", &(in_x[i]), &(in_y[i])) != EOF) {
	
		printf("x[%d]=%f, y[%d]=%f\n", i, in_x[i], in_y[i]);
		
		i++;
	}

	fclose(file);

	int del = remove("data.txt");

	if (!del)
		printf("The file is Deleted successfully\n");

	p = point_create(in_x[0], in_y[0]);
	p1 = point_create(in_x[1], in_y[1]);
	p2 = point_create(in_x[2], in_y[2]);
	p3 = point_create(in_x[3], in_y[3]);

	if (p == NULL || p1 == NULL || p2 == NULL || p3 == NULL) {
		return ENOMEM;
	} else {
		if (!is_collinear(p1, p2, p3)) {
			if (isInside(p1, p2, p3, p)) {
				printf("Good job 4th point is inside\n");
			} else
				printf("Shame 4th point is outside\n");
		} else
			printf("Three points are collinear\n");
	}

	point_free(p);
	point_free(p1);
	point_free(p2);
	point_free(p3);

	return 0;
}
