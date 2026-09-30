#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//random
double randoom() {
	double z=rand();
	double w=z/RAND_MAX;
	return w; 
}
//main
int main() {
//input
int m, s, x, y, t, l, i, j, n;
double a, p1, p2, p12, q1, q2, q12, pq12, pq21, r, tt, ttt;
printf("m\n"); //size of m
scanf("%i", &m);
printf("s\n"); //size of s
scanf("%i", &s);
printf("p1\n"); //ins I
scanf("%lf", &p1);
printf("p2\n"); //ins II
scanf("%lf", &p2);
p2=(p1+p2);
printf("p12\n"); //ins I & II
scanf("%lf", &p12);
p12=(p2+p12);
printf("q1\n"); //del I
scanf("%lf", &q1);
q1=(p12+q1);
printf("q2\n"); //del II
scanf("%lf", &q2);
q2=(q1+q2);
printf("q12\n"); //del I & II
scanf("%lf", &q12);
q12=(q2+q12);
printf("pq12\n"); //ins I & del II
scanf("%lf", &pq12);
pq12=(q12+pq12);
printf("pq21\n"); //ins II & del I
scanf("%lf", &pq21);
pq21=(pq12+pq21);
r=1; //no op
ttt=0; //time
n=10000; //num iter
r=1000; //num go
//work
for (j=0; j<r; j++) {
	srand(time(NULL)); //random, init
	tt=0;
	for (i=0; i<n; i++) {
		x=0; //size I
		y=0; //size II
		t=0; //time iter
		l=0; //lost
		while (l!=1) {
			//prob
			a=randoom(); //random, call
			if ((a>0) && (a<p1)) { //p1
				x++;
			}
			if ((a>p1) && (a<p2)) { //p2
				y++;
			}
			if ((a>p2) && (a<p12)) { //p12
				x++;
				y++;
			}
			if ((a>p12) && (a<q1)) { //q1
				x--;
			}
			if ((a>q1) && (a<q2)) { //q2
				y--;
			}
			if ((a>q2) && (a<q12)) { //q12
				x--;
				y--;	
			}
			if ((a>q12) && (a<pq12)) { //pq12
				x++;
				y--;	
			}
			if ((a>pq12) && (a<pq21)) { //pq21
				x--;
				y++;	
			}
			if ((a>pq21) && (a<r)) { //r
				x=x;
				y=y;
			}
			//check
			if ((x>s) && (y>(m-s))) { //lost I & II
				l=1;
			}
			if ((x>s) && (y<=(m-s))) { //lost I
				l=1;
			}
			if ((x<=s) && (y>(m-s))) { //lost II
				l=1;
			}
			//change
			if ((x<0) && (y<0)) { //no minus I & II
				x=0;
				y=0;
			}
			if ((x<0) && (y<=1)) { //no minus I
				x=0;
				y=y;
			}
			if ((x<=1) && (y<0)) { //no minus II
				x=x;
				y=0;
			}
			//work-stealing
			if ((x<0) && (y>=2)) { //I steal half
				if (s>=(y/2)) { //I can steal 1/2
					x=y/2;
					y=y-x;
				}
				else { //I can't steal 1/2 (steal one)
					x=1;
					y=y-1;
				}
			}
			else if ((x>=2) && (y<0)) { //II steal half
				if ((m-s)>=(x/2)) { //II can steal 1/2
					y=x/2;
					x=x-y;
				}
				else { //II can't steal 1/2 (steal one)
					y=1;
					x=x-1;
				}
			}
			//result
			if (l==0) { //next
				t++;
			}
		}
		tt=tt+t; //time, sum iter
	}
	tt=tt/n;
	ttt=ttt+tt; //time, sum go
}
ttt=ttt/r;
//output
printf("Total time: %lf\n", ttt);
}
