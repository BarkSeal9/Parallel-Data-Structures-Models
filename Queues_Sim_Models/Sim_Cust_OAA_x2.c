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
int m, x, y, r, i, j, l, n, ox, oy;
double a, p1, p2, p12, r1, q12, r2, ll, jll, tll;
printf("m\n"); //size of m
scanf("%i", &m);
printf("p1\n"); //ins I
scanf("%lf", &p1);
printf("p2\n"); //ins II
scanf("%lf", &p2);
p2=(p1+p2);
printf("p12\n"); //ins I & II
scanf("%lf", &p12);
p12=(p2+p12);
r1=1; //no op 1
printf("q12\n"); //del I & II
scanf("%lf", &q12);
r2=1; //no op 2
n=10000000; //num iter
r=10;//num go
srand(time(NULL)); //random, init
for (j=0; j<r; j++) {
	x=0; //size I
	y=0; //size II
	ox=0; //space I
	oy=0; //space II
	l=0; //lost go, sum
	ll=0; //lost go, avg
	for (i=1; i<=n; i++) {
		a=randoom(); //random, call
		if (x==0 && y==0) { //I & II empty
			ox=0;
			oy=0;
			//step 1
			if (i%2!=0) {
				if ((a>0) && (a<p1)) { //p1
					x++;
					ox=(m-1);
				}
				if ((a>p1) && (a<p2)) { //p2
					y++;
					oy=(m-1);
				}
				if ((a>p2) && (a<p12)) { //p12
					x++;
					ox=((m/2)-1);
					y++;
					oy=(m-x-y-ox);
				}
				if ((a>p12) && (a<r1)) { //r1
					x=x;
					ox=ox;
					y=y;
					oy=oy;
				}
			}
			//step 2
			if (i%2==0) {
				if ((a>0) && (a<q12)) { //q12
					x=0;
					ox=ox;
					y=0;
					oy=oy;
				}
				if ((a>q12) && (a<r2)) { //r2
					x=x;
					ox=ox;
					y=y;
					oy=oy;
				}
			}
		}
		else if (x==0 && y>0) { //I empty II some
			oy=(m-y);
			ox=0;
			//step 1
			if (i%2!=0) {
				if ((a>0) && (a<p1)) { //p1
					if ((x+y)==m) { //space not ava
						l++;
					}
					if ((x+y)<m) { //space ava
						x++;
						ox=((m-y)/2);
						if ((m-ox-y-x)>0) {oy=(m-ox-y-x);} else {oy=0;};
					}
				}
				if ((a>p1) && (a<p2)) { //p2
					if ((x+y)==m) { //space not ava
						l++;
					}
					if ((x+y)<m) { //space ava
						y++;
						oy--;
					}
				}
				if ((a>p2) && (a<p12)) { //p12
					if ((x+y)==m) { //space not ava
						l++;
					}
					if ((x+y)<m) { //space ava
						if ((x+y)<(m-1)) {
							x++;
							ox=((m-y)/2);
							y++;
							if ((m-ox-y-x)>0) {oy=(m-ox-y-x);} else {oy=0;};
						}
						else {
							x++;
							oy--;
							l++;
						}
					}
				}
				if ((a>p12) && (a<r1)) { //r1
					x=x;
					ox=ox;
					y=y;
					oy=oy;
				}
			}
			//step 2
			if (i%2==0) {
				if ((a>0) && (a<q12)) { //q12
					x=0;
					ox=ox;
					y--;
					oy=oy;
				}
				if ((a>q12) && (a<r2)) { //r2
					x=x;
					ox=ox;
					y=y;
					oy=oy;
				}
				//change
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
		}
		else if (x>0 && y==0) { //I some II empty
			ox=(m-x);
			oy=0;
			//step 1
			if (i%2!=0) {
				if ((a>0) && (a<p1)) { //p1
					if ((x+y)==m) { //space not ava
						l++;
					}
					if ((x+y)<m) { //space ava
						x++;
						ox--;
					}
				}
				if ((a>p1) && (a<p2)) { //p2
					if ((x+y)==m) { //space not ava
						l++;
					}
					if ((x+y)<m) { //space ava
						y++;
						oy=((m-x)/2);
						if ((m-oy-x-y)>0) {ox=(m-oy-x-y);} else {ox=0;};
					}
				}
				if ((a>p2) && (a<p12)) { //p12
					if ((x+y)==m) { //space not ava
						l++;
					}
					if ((x+y)<m) { //space ava
						if ((x+y)<(m-1)) {
							x++;
							ox=((m-x)/2);
							y++;
							if ((m-ox-y-x)>0) {oy=(m-ox-y-x);} else {oy=0;};
						}
						else {
							x++;
							ox--;
							l++;
						}
					}
				}
				if ((a>p12) && (a<r1)) { //r1
					x=x;
					ox=ox;
					y=y;
					oy=oy;
				}
			}
			//step 2
			if (i%2==0) {
				if ((a>0) && (a<q12)) { //q12
					x--;
					y=0;
					oy=oy;
					ox=ox;
				}
				if ((a>q12) && (a<r2)) { //r2
					x=x;
					ox=ox;
					y=y;
					oy=oy;
				}
				//change
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
		}
		else if (x>0 && y>0) { //I some II some
			//step 1
			if (i%2!=0) {
				if ((a>0) && (a<p1)) { //p1
					x++;
					ox--;
				}
				if ((a>p1) && (a<p2)) { //p2
					y++;
					oy--;
				}
				if ((a>p2) && (a<p12)) { //p12
					x++;
					ox--;
					y++;
					oy--;
				}
				if ((a>p12) && (a<r1)) { //r1
					x=x;
					ox=ox;
					y=y;
					oy=oy;
				}
				//change
				if ((ox<0) && (oy<0)) { //I & II overflow
					l++;
					x--;
					ox=0;
					y--;
					oy=0;
				}
				if ((ox<0) && (oy>=0)) { //I overflow
					l++;
					x--;
					ox=0;
				}
				if ((oy<0) && (ox>=0)) { //II overflow
					l++;
					y--;
					oy=0;
				}
			}
			//step 2
			if (i%2==0) {
				if ((a>0) && (a<q12)) { //q12
					x--;
					ox++;
					y--;
					oy++;
				}
				if ((a>q12) && (a<r2)) { //r2
					x=x;
					ox=ox;
					y=y;
					oy=oy;
				}
				//change
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
		}
	}
	ll=((double)l/n)*2; //lost avg this go
	jll=jll+ll; //lost sum all go
}
tll=(jll/r); //total lost, avg
//output
printf("Total lost: %lf\n", tll);
}
