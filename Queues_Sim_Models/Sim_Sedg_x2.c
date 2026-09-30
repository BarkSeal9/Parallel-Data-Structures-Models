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
int m, s, x, y, r, i, j, l, n;
double a, p1, p2, p12, r1, q1, q2, q12, r2, ll, jll, tll;
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
r1=1; //no op 1
printf("q1\n"); //del I
scanf("%lf", &q1);
printf("q2\n"); //del II
scanf("%lf", &q2);
q2=(q1+q2);
printf("q12\n"); //del I & II
scanf("%lf", &q12);
q12=(q2+q12);
r2=1; //no op 2
n=10000000; //num iter
r=10;//num go
srand(time(NULL)); //random, init
//work
for (j=0; j<r; j++) {
	x=0; //size I
	y=0; //size II
	l=0; //lost go, sum
	ll=0; //lost go, avg
	for (i=1; i<=n; i++) {
		a=randoom(); //random, call
		//step 1
		if (i%2!=0) {
			if ((a>0) && (a<p1)) { //p1
				y++;
			}
			if ((a>p1) && (a<p2)) { //p2
				x++;
			}
			if ((a>p2) && (a<p12)) { //p12
				x++;
				y++;
			}
			if ((a>p12) && (a<r1)) { //r1
				x=x;
				y=y;
			}
		}
		//change 1
		if ((y>s)&&(x>(m-s))) { //I & II overflow
			l++;
			y=s;
			x=(m-s);
		}
		if ((x>(m-s))&&(y<=s)) { //I overflow
			l++;
			x=(m-s);
		}
		if ((x<=(m-s)) && (y>s)) { //II overflow
			l++;
			y=s;
		}
		//step 2
		if (i%2==0) {
			if ((a>0) && (a<q1)) { //q1
				y--;
			}
			if ((a>q1) && (a<q2)) { //q2
				x--;
			}
			if ((a>q2) && (a<q12)) { //q12
				x--;
				y--;	
			}
			if ((a>q12) && (a<r2)) { //r2
				x=x;
				y=y;
			}
		}
		//change 2
		if ((x<0) && (y<0)) { //no minus I & II
			x=0;
			y=0;
		}
		if ((x<0) && (y>=0)) { //no minus I
			x=0;
			y=y;
		}
		if ((x>=0) && (y<0)) { //no minus II
			x=x;
			y=0;
		}
	}
	ll=((double)l/n)*2; //lost avg this go
	jll=jll+ll; //lost sum all go
}
tll=(jll/r); //total lost, avg
//output
printf("Total lost: %lf\n", tll);
}
