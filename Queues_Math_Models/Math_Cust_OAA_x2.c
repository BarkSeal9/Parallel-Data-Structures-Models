#include <stdio.h>
#include <stdlib.h>
//main
int main(void) {
int i, z, k, l, s, j, lp2q2, lsp6, m, n, nScreens, distance, tempSumm, lengthOfFirst, lengthOfSecond, old, distance12;
double p1, p2, r1, r2, p12, q12;
//input
printf ("Enter size (m)\n");
scanf ("%d", &m);
printf ("Enter probabilities:\n");
printf ("Ins in I (p1)\n");
scanf ("%lf", &p1);
printf ("Ins in II (p2)\n");
scanf ("%lf", &p2);
printf ("Ins in I & II (p12)\n");
scanf ("%lf", &p12);
printf ("Del from I & II (q12)\n");
scanf ("%lf", &q12);
r1 = 1-p1-p2-p12;
r2 = 1-q12;
//matrix
int countPositions[m+1];
int summPositions[m+6];
n=0;
for (i=0; i<m+1; i++) {
	countPositions[i] = (i+1)*(i+2)/2;
	n += countPositions[i];
}
int *busy = (int*)malloc(sizeof(int)*n);
for (i=0; i<n; i++)
	busy[i] = 0;
summPositions[0] = countPositions[m];
for (i=1; i<m+1; i++)
   summPositions[i] = summPositions[i-1]+countPositions[m-i];
summPositions[m+1] = summPositions[m]+summPositions[0]-m-1;
summPositions[m+2] = summPositions[m+1]+summPositions[0];
summPositions[m+3] = summPositions[m+2]+((m*(m-1))/2);
summPositions[m+4] = summPositions[m+3]+summPositions[0]-m-1;
summPositions[m+5] = summPositions[m+4]+summPositions[0];
summPositions[m+6] = summPositions[m+5]+summPositions[0]-(m+1)-m-(m-1)-(m-2);
nScreens = summPositions[m+6] - summPositions[m];
n += nScreens;
double **A = (double**)malloc(sizeof(double*)*n);
for (i=0; i<n; i++)
	A[i] = (double*)malloc(sizeof(double)*n);
for (i=0; i<n; i++)
   for (j=0; j<n; j++)
      A[i][j] = 0;
//work
for (z=0; z<=m; z++) {
if (z == 0) {
	for (i=0; i<summPositions[0]; i++) {
		//I & II empty
		if (i == 0) {
			if ((m-1)%2 == 1)
				distance = (m-1)/2+1;
			else
				distance = (m-1)/2;
			A[i][i] = r1*r2 + q12*r1 + p12*q12 + p1*q12 + p2*q12;
			A[i][i+1] = p2*r2;
			A[i][m+1] = p1*r2;
			if (distance == 1)
				A[i][m+2] = p12*r2;
			else
				A[i][summPositions[distance-2]+m+2-(distance-1)] = p12*r2;
			busy[i] = 1;
		}
		//I empty II some
		if ((i>0) && (i<m)) {
			if ((m-i)%2 == 1)
				distance = (m-i)/2+1;
			else
				distance = (m-i)/2;
			if ((m-i-1)%2 == 1)
				distance12 = (m-i-1)/2+1;
			else
				distance12 = (m-i-1)/2;
			if (distance == 1) {
				A[i][i+m+1] = p1*r2;
			}
			else
				A[i][summPositions[distance-2]+m+i+2-distance] = p1*r2;
			A[i][i-1] = q12*r1 + p1*q12;
			if (i == m-1)
				A[i][summPositions[m+1]] = p12*r2;
			else if (distance12 == 1)
				A[i][i+m+2] = p12*r2;
			else
				A[i][summPositions[distance12-2]+m+i+3-distance12] = p12*r2;
			if (i == m-1) {
				A[i][i] = r1*r2 + p2*q12;
				A[i][summPositions[m+3]+m-2] = p12*q12;
			}
			else
				A[i][i] = r1*r2 + p12*q12 + p2*q12;
			A[i][i+1] = p2*r2;
			busy[i] = 1;
		}
		//I full II empty
		if (i == summPositions[0]-1) {
			A[i][i] = r1*r2;
			A[i][summPositions[m+1]-1] = p1*r2 + p2*r2 + p12*r2;
			A[i][i-2] = q12*r1;
			A[i][summPositions[m+4]-1] = p12*q12 + p1*q12 + p2*q12;
			busy[i] = 1;
			k = i; 
			tempSumm = 0;
			//I full II full
			for (l=1; l<m; l++) {
				k -= l;
				A[k][k] = r1*r2;
				A[k][summPositions[m+1]-1-tempSumm-l] = p1*r2 + p12*r2;
				A[k][summPositions[m+1]+m-l] = p2*r2;
				if ((l == 1) || (l == m-1))
					A[k][k-l-3] = q12*r1;
				else
					A[k][summPositions[1]-1-tempSumm-(l+1)] = q12*r1;
				if ((k == summPositions[0]-2) || (k == m*2))
					A[k][summPositions[m+4]-2-tempSumm-l] = p12*q12 + p1*q12 + p2*q12;
				else
					A[k][summPositions[m+2]+m-1-l+(m-1)] = p12*q12 + p1*q12 + p2*q12;
				busy[k] = 1;
				tempSumm += l;
			}
			//I empty II full
			tempSumm = 0;
			k -= l;
			A[k][k] = r1*r2;
			A[k][summPositions[m+1]] = p2*r2 + p1*r2 + p12*r2;
			A[k][k-1] = q12*r1;
			A[k][summPositions[m+4]] = p12*q12 + p2*q12;
			A[k][summPositions[m+2]] = p1*q12;
			busy[k] = 1;
			k = i;
			//I some II empty
			for (l=2; l<m+1; l++) {
				k-=l;
				distance = (l-1)/2;
				distance12 = (l-2)/2;
				if (distance == 0)
					A[k][k+1] = p2*r2;
				else {
					tempSumm = ((4+(l/2-1))*(l/2))/2;
					A[k][summPositions[distance]-tempSumm] = p2*r2;
				}
				A[k][k-l-1] = q12*r1 + p2*q12;
				if (l == 2)
					A[k][summPositions[m+1]-1] = p12*r2;
				else if ((distance12 == 0) && (l != 2))
					A[k][k+l+1] = p12*r2;
				else {
					tempSumm = ((4+(l/2-1))*(l/2))/2;
					A[k][summPositions[distance]-tempSumm+l-distance] = p12*r2;
				}
				if (distance == 0) {
					A[k][k] = r1*r2 + p1*q12;
					A[k][summPositions[m+4]-3] = p12*q12;
				}
				else
					A[k][k] = r1*r2 + p12*q12 + p1*q12;
				A[k][k+l] = p1*r2;
				busy[k] = 1;
			}
		}
	}
	//I full II some
	l = 1;
	lp2q2 = 1;
	s = m+1;
	lsp6 = 1;
	for (i = 0; i<summPositions[0]; i++) {
		if (busy[i] == 0) {
			A[i][i] = r1*r2;
			A[i][summPositions[m]+l] = p1*r2;
			A[i][i+1] = p2*r2;
			A[i][summPositions[m+3]+l] = p12*q12;
			A[i][summPositions[m]+l+1] = p12*r2;
			if (busy[i-s-1] == 1)
				A[i][i-s-1] = q12*r1;
			else
				A[i][summPositions[0]+m+2*l+s-i-1-(s-1)] = q12*r1;
			A[i][summPositions[m+3]+l-1] = p1*q12;
			if (busy[i-s] == 1)
				A[i][i-s] = p2*q12;
			else {
				A[i][summPositions[0]+lp2q2+1] = p2*q12;
			}
			if (busy[i+1] == 1) {
				l = l+3;
				lp2q2 = lp2q2+2;
				s--;
			}
			else { 
				l++;
				lp2q2++;
				lsp6++;
			}
		}
	}
}
//I some II some
if ((z > 0) && (z < m)) {
	for (i = summPositions[z-1]; i<summPositions[z]; i++) {
		if (i == summPositions[z-1]) {
			if ((m-1)%2 == 1)
				distance = (m-1)/2+1;
			else
				distance = (m-1)/2;
			A[i][i] = r1*r2;
			A[i][i-summPositions[z-1]] = q12*r1 + p12*q12 + p1*q12 + p2*q12;
			A[i][i-summPositions[z-1]+1] = p2*r2;
			A[i][m+1] = p1*r2;
			if (distance == 1)
				A[i][m+2] = p12*r2;
			else
				A[i][summPositions[distance-2]+m+2-(distance-1)] = p12*r2;
			busy[i] = 1;
		}
		if ((i>summPositions[z-1]) && (i<summPositions[z-1]+m-z)) {
			distance = m-(i-summPositions[z-1]);
			if (distance%2 == 1)
				distance = distance/2+1;
			else
				distance = distance/2;
			distance12 = m-(i-summPositions[z-1]+1);
			if (distance12%2 == 1)
				distance12 = distance12/2+1;
			else
				distance12 = distance12/2;
			A[i][i] = r1*r2;
			if (distance == 1)
				A[i][(i-summPositions[z-1])+m+1] = p1*r2;
			else
				A[i][summPositions[distance-2]+m+(i-summPositions[z-1])+2-distance] = p1*r2;
			A[i][(i-summPositions[z-1])+1] = p2*r2;
			A[i][(i-summPositions[z-1])] = p12*q12 + p2*q12;
			A[i][(i-summPositions[z-1])-1] = q12*r1 + p1*q12;
			if (distance12 == 1)
				A[i][(i-summPositions[z-1])+m+2] = p12*r2;
			else
				A[i][summPositions[distance12-2]+m+(i-summPositions[z-1])+2-distance12+1] = p12*r2;
			busy[i] = 1;
		}
		if (i == summPositions[z]-1) {
			distance = (z-1)/2;
			distance12 = (z-2)/2;
			A[i][i] = r1*r2;
			if (distance == 0)
				A[i][(((2*(m+1)-m+z)*(m-z+1))/2)-z] = p2*r2;
			else
				A[i][summPositions[distance]-((((4+(z/2-1))*(z/2))/2)+(z/2+2))] = p2*r2;
			A[i][(((2*(m+1)-m+z+2)*(m-z-1))/2)] = q12*r1 + p2*q12;
			if (z == 1)
				A[i][summPositions[m+1]-1] = p12*r2;
			else if ((distance == 0) && (z != 1))
				A[i][(((2*(m+1)-m+z)*(m-z+1))/2)+1] = p12*r2;
			else
				A[i][summPositions[distance12]-((((4+((z-1)/2-1))*((z-1)/2))/2)+((z-1)/2+2))] = p12*r2;
			if (z == 1) {
				A[i][(((2*(m+1)-m+z+1)*(m-z))/2)] = p1*q12;
				A[i][summPositions[m]+(((2*(m+1)-m+z+2)*(m-z-1))/2)-m-1] = p12*q12;
			}
			else
				A[i][(((2*(m+1)-m+z+1)*(m-z))/2)] = p12*q12 + p1*q12;
			A[i][(((2*(m+1)-m+z)*(m-z+1))/2)] = p1*r2;
			busy[i] = 1;
			k = i;
			for (l = 1; l<m-z; l++) {
				k-=l;
				A[k][k] = r1*r2;
				tempSumm = ((l+1)*l)/2;
				A[k][summPositions[z-1]-tempSumm-1] = p1*r2;
				tempSumm = ((2*(m+1)-z)*(z+1))/2;
				A[k][summPositions[m+1]+tempSumm-l-1] = p2*r2;
				if (l == 1) {
					tempSumm = ((4+z)*(z+1))/2;
					A[k][summPositions[0]-tempSumm-1] = p1*q12;
				}
				else {
					A[k][k-1] = p1*q12;
				}
				tempSumm = ((l+1)*l)/2;
				A[k][summPositions[m+2]+(((2*m-z-2)*(z+1))/2)-l] = p12*q12;
				A[k][summPositions[m+1]+tempSumm-l-1-(m-(z-1))] = p12*r2;
				if ((l == m-z-1) && (l != 1))
					A[k][l-1] = q12*r1; 
				else if ((l == 1) && (l != m-z-1)) {
					tempSumm = ((4+z)*(z+1))/2;
					A[k][summPositions[0]-tempSumm-1-z-3] = q12*r1;
				}
				else if ((l == m-z-1) && (l == 1))
					A[k][l-1] = q12*r1;
				else {
					tempSumm = (l*(l-1))/2;
					A[k][summPositions[z+1]-tempSumm-1-l-1] = q12*r1;
				}
				if ((l == 1) && (l != m-z-1)) {
					tempSumm = ((4+z)*(z+1))/2;
					A[k][summPositions[m]+((summPositions[0]-tempSumm-1-(m-2+z-1))-(m+1))] = p2*q12;
				}
				else if ((l == m-z-1) && (l != 1))
					A[k][summPositions[m+3]+l-1] = p2*q12;
				else if ((l == 1) && (l == m-z-1))
					A[k][summPositions[m+3]+l-1] = p2*q12;
				else
					A[k][summPositions[m+2]+(((2*m-z-2)*(z+1))/2)-l+(m-1-z)] = p2*q12;
				busy[k] = 1;
			}
			k -= l;
			distance = m-(k-summPositions[z-1]);
			if (distance%2 == 1)
				distance = distance/2+1;
			else
				distance = distance/2;
			distance12 = m-(k-summPositions[z-1])+1;
			if (distance12%2 == 1)
				distance12 = distance12/2+1;
			else
				distance12 = distance12/2;
			A[k][k] = r1*r2;
			if (distance == 1)
				A[k][(k-summPositions[z-1])+m+1] = p1*r2;
			else
				A[k][summPositions[distance-2]+m+(k-summPositions[z-1])+2-distance] = p1*r2;
			A[k][k-summPositions[z-1]-1] = q12*r1 + p1*q12;
			if (distance12 == 1)
				A[k][summPositions[m+1]+1] = p12*r2;
			else if (distance12 == 2)
				A[k][(k-summPositions[z-1])+m+2] = p12*r2;
			else
				A[k][summPositions[distance12-3]+m+(k-summPositions[z-1])+2-distance12+2] = p12*r2;
			if (z == 1) {
				A[k][summPositions[m+3]+m-2] = p12*q12;
			}
			else
				A[k][k-summPositions[z-1]] = p12*q12 + p2*q12;
			A[k][k-summPositions[z-1]+1] = p2*r2;
			busy[k] = 1;
			k = i;
			for (l = 2; l<m-z+1; l++) {
				k-=l;
				A[k][summPositions[0]-(((1+l+z)*(l+z-2))/2)-1] = p1*r2;
				distance = (z+l-1)/2;
				distance12 = (z+l-3)/2;
				A[k][summPositions[distance]-(((4+((l+z)/2-1))*((l+z)/2))/2)] = p2*r2;
				A[k][summPositions[0]-(((3+l+z)*(l+z))/2)-1] = q12*r1 + p2*q12;
				A[k][summPositions[0]-(((2+l+z)*(l+z-1))/2)-1] = p12*q12 + p1*q12;
				A[k][summPositions[distance12]-(((4+((l+z)/2-1))*((l+z)/2))/2)] = p12*r2;
				busy[k] = 1;
			}
		}
	}
	lengthOfFirst = 1;
	lengthOfSecond = 1;
	for (i = summPositions[z-1]; i<summPositions[z]; i++) {
		if (busy[i] == 0) {
			A[i][i] = r1*r2 + p12*q12;
			tempSumm = ((2*(m+2-z)-lengthOfFirst)*(lengthOfFirst+1))/2;
			if (z == 1) {
				A[i][tempSumm+lengthOfSecond] = p1*r2;
			}
			else {
				A[i][summPositions[z-2]+tempSumm+lengthOfSecond] = p1*r2;
			}
			A[i][i+1] = p2*r2;
			if (lengthOfFirst == 1)
				A[i][(i-summPositions[z-1]-m-1+z)] = p2*q12;
			else {
				tempSumm = (((2*(m-z)-lengthOfFirst+1)*lengthOfFirst)/2)+lengthOfSecond-1;
				A[i][summPositions[z]+tempSumm+1-(m+2-(z+1)-lengthOfFirst)] = p2*q12;
			}
			tempSumm = (((2*(m-z)-lengthOfFirst+1)*lengthOfFirst)/2)+lengthOfSecond-1;
			A[i][i-1] = p1*q12;
			if (z == 1) {
				tempSumm = ((2*(m+2-z)-lengthOfFirst)*(lengthOfFirst+1))/2;
				A[i][tempSumm+lengthOfSecond+1] = p12*r2;
			}
			else {
				tempSumm = ((2*(m+2-z)-lengthOfFirst)*(lengthOfFirst+1))/2;
				A[i][summPositions[z-2]+tempSumm+lengthOfSecond+1] = p12*r2;
			}
			if (lengthOfSecond == 1)
				A[i][((2*m-lengthOfFirst+3)*lengthOfFirst)/2-(m+2-lengthOfFirst)] = q12*r1;
			else {
				tempSumm = (((2*(m-z)-lengthOfFirst+1)*lengthOfFirst)/2)+lengthOfSecond-1;
				A[i][summPositions[z]+tempSumm-(m-lengthOfFirst)+1] = q12*r1;
			}
			if (busy[i+1] == 1) {
				lengthOfFirst++;
				lengthOfSecond = 1;
			}
			else
				lengthOfSecond++;
			busy[i] = 1;
		}
	}
}
if (z == m) {
	i = summPositions[m]-1;
	if ((m-1)%2 == 1)
		distance = (m-1)/2+1;
	else
		distance = (m-1)/2;
	A[i][i] = r1*r2;
	A[i][m+1] = p1*r2;
	A[i][summPositions[m]-i] = p2*r2;
	A[i][summPositions[m]-i-1] = q12*r1 + p12*q12 + p1*q12 + p2*q12;
	if (distance == 1)
		A[i][m+2] = p12*r2;
	else
		A[i][summPositions[distance-2]+m+2-(distance-1)] = p12*r2;
}
}
//I reflective screen (I queue overflow)
old = summPositions[m];
lsp6 = 1;
for (z = m; z>0; z--) {
	for (i = old; i<old+z; i++) {
		if (i != old) {
			A[i][((m+z+2)*(m+1-z))/2+(i-old)] = r1*r2;
			if (i != old+z-1) {
				A[i][summPositions[m+3]+(i-summPositions[m])] = p12*q12;
				A[i][summPositions[m+3]+(i-summPositions[m])-1] = p1*q12;
				A[i][i] = p1*r2;
				A[i][i+1] = p12*r2;
				A[i][((m+z+2)*(m+1-z))/2+(i-old)+1] = p2*r2;
				if (i > summPositions[m]+m-1) {
					A[i][summPositions[0]+i-summPositions[m]+z-1+1-1-z] = p2*q12;
				}
				else
					A[i][((m+z+2)*(m+1-z))/2+(i-old)-z-1] = p2*q12;
				if (i+1 != old+z-1)
					lsp6++;
			}
			else {
				A[i][summPositions[m+3]+(i-summPositions[m])] = p12*q12;
				A[i][summPositions[m+1]+m+1-z] = p2*r2;
				A[i][i] = p1*r2 + p12*r2;
				A[i][summPositions[m+3]+(i-summPositions[m])-1] = p2*q12 + p1*q12;
			}
			if (i != old+1) {
				if (i > summPositions[m]+m-1)
					A[i][summPositions[0]+i-summPositions[m]+z-1-z] = q12*r1;
				else
					A[i][((m+z+2)*(m+1-z))/2+(i-old)-z-2] = q12*r1;
			}
			else {
				A[i][((m+z+2)*(m+1-z))/2+(i-old)-z-2] = q12*r1;
			}
			lsp6++;
		}
		else {
			if (i == old-z+1) {
				A[i][((m+z+2)*(m+1-z))/2+(i-old)] = r1*r2;
				A[i][summPositions[m+1]+m+1-z] = p2*r2;
				A[i][i] = p1*r2 + p12*r2;
				A[i][((m+z+2)*(m+1-z))/2+(i-old)-z-1] = q12*r1;
				A[i][summPositions[m+3]+(i-summPositions[m])] = p1*q12 + p2*q12 + p12*q12;
			}
			else {
				distance = (z-1)/2;
				distance12 = (z-2)/2;
				if (distance == 0)
					A[i][((m+z+2)*(m+1-z))/2+(i-old)+1] = p2*r2;
				else {
					tempSumm = ((4+(z/2-1))*(z/2))/2;
					A[i][summPositions[distance]-tempSumm] = p2*r2;
				}
				A[i][((m+z+2)*(m+1-z))/2+(i-old)+z] = p1*r2;
				if (distance == 0)
					A[i][summPositions[m+1]-1] = p12*r2;
				else if ((distance12 == 0) && (z != 2))
					A[i][((m+z+2)*(m+1-z))/2+(i-old)+z+1] = p12*r2;
				else {
					tempSumm = ((4+(z/2-1))*(z/2))/2;
					A[i][summPositions[distance]-tempSumm+z-distance] = p12*r2;
				}
				A[i][((m+z+2)*(m+1-z))/2+(i-old)-z-1] = q12*r1 + p2*q12;
				if (z == 2) {
					A[i][((m+z+2)*(m+1-z))/2+(i-old)] = r1*r2;
					A[i][summPositions[m+3]+(i-summPositions[m])] = p12*q12 + p1*q12;
				}
				else {
					A[i][((m+z+2)*(m+1-z))/2+(i-old)] = r1*r2 + p12*q12;
					A[i][summPositions[m+3]+(i-summPositions[m])] = p1*q12;
				}
			}
		}
	}
	old += z;
}
//I reflective screen (II queue overflow)
old = summPositions[m+1]+m;
for (z = 0; z<m+1; z++) {
	for (i = old; i>old-m+z-1; i--) {
		if (z == 0) {
			if ((i == old) && (i != old-m)) {
				A[i][i] = p2*r2 + p12*r2;
				A[i][((m+3)*m)/2] = r1*r2;
				A[i][((m+4)*(m-1))/2] = q12*r1;
				A[i][summPositions[m+4]-1] = p12*q12 + p1*q12 + p2*q12;
				A[i][summPositions[m+1]-1] = p1*r2;
			}
			else {
				if (i != old-m) {
					A[i][i] = p2*r2 + p12*r2;
					A[i][summPositions[m]+(((m+1+old-i)*(m-old+i))/2)-1] = p1*r2;
					A[i][summPositions[z]-(((1+old-i)*(old-i))/2)-1] = r1*r2;
					if ((i != old-1) && (i != old-m+z+1))
						A[i][summPositions[z]+(((m+old-i)*(m+1-old+i))/2)-1-(1+old-i)] = q12*r1;
					else if ((i == old-1) && (i != old-m+z+1))
						A[i][summPositions[z]-6] = q12*r1;
					else if ((i == old-m+z+1) && (i != old-1))
						A[i][m-2] = q12*r1;
					A[i][summPositions[m+2]+i-summPositions[m+1]-1+(m-1)] = p12*q12 + p1*q12 + p2*q12;
				}
				else {
					A[i][m] = r1*r2;
					A[i][summPositions[m+2]] = p1*q12;
					A[i][m-1] = q12*r1;
					A[i][i] = p2*r2 + p1*r2 + p12*r2;
					A[i][summPositions[m+5]-(summPositions[m+2]-i)] = p12*q12 + p2*q12;
				}
			}
		}
		else {
			if (i != old) {
				if (i != old-m+z) {
					A[i][summPositions[m+5]-(summPositions[m+2]-i)] = p12*q12;
					A[i][i] = p2*r2;
					if (z > 1) {
						A[i][summPositions[z-2]+(((m+3-z+old-i)*(m+2-z-old+i))/2)-1] = p1*r2;
						tempSumm = ((2*(m+1)-(z-1))*((z-1)+1))/2;
						A[k][summPositions[m+1]+tempSumm-((summPositions[z-1]-(summPositions[z-2]+(((m+3-z+old-i)*(m+2-z-old+i))/2)-1))-1)-1] = p12*r2;
					}
					else {
						A[i][(((m+3-z+old-i)*(m+2-z-old+i))/2)-1] = p1*r2;
						A[i][summPositions[m+1]+m-((summPositions[0]-((((m+3-z+old-i)*(m+2-z-old+i))/2)-1))-1)] = p12*r2;
					}
					A[i][summPositions[z]-(((1+old-i)*(old-i))/2)-1] = r1*r2;
					if ((i != old-m+z+1) && (i != old-1)) {
						A[i][summPositions[z]+(((m-z+old-i)*(m+1-z-old+i))/2)-1-(old-i+1)] = q12*r1;
						A[i][summPositions[m+2]+i-summPositions[m+1]-2*z-1+(m-(z+1))] = p2*q12;
					}
					else if ((i == old-m+z+1) && (i == old-1)) {
						A[i][old-i-1] = q12*r1;
						A[i][summPositions[m+3]] = p2*q12;
					}
					else if (z == (m-1)) {
						A[i][m-z-1] = q12*r1;
						A[i][summPositions[m+3]] = p2*q12;
					}
					else {
						if ((i == old-m+z+1) && (i != old-1)) {
							A[i][m-1-z-1] = q12*r1;
							A[i][summPositions[m+2]+i-summPositions[m+1]-2*z-1+(m-(z+1))] = p2*q12;
						}
						else if ((i == old-1) && (i != old-m+z+1)) {
							A[i][(((m+4+z)*(m-1-z))/2)-(z+3)] = q12*r1;
							A[i][(((m+4+z)*(m-1-z))/2)-(z+3)+summPositions[m]-m-1] = p2*q12;
						}
					}
					A[i][summPositions[z]-(((1+old-i)*(old-i))/2)-2] = p1*q12;
				}
			}
		}
	}
	old+=m-z;
}
//I reflective screen (ins in one + del from other)
for (z=0; z<m-1; z++) {
	old = summPositions[m+2]+((2*m-2-z)*(z+1)/2)-1;
	for (i=old; i>old-m+1+z; i--) {
		tempSumm = ((m+5-z+old-i)*(m-2-z-old+i))/2;
		if (i!=old-m+2+z) {
			if (z > 0) {
				k = summPositions[z-1]+tempSumm+old-i+1;
				for (l = 0; l<n; l++)
					A[i][l] = A[k][l];
			}
			else {
				k = tempSumm+old-i+1;
				for (l = 0; l<n; l++)
					A[i][l] = A[k][l];
			}
		}
		else {
			k = tempSumm+old-i+1;
			for (l = 0; l<n; l++)
				A[i][l] = A[k][l];
		}
	}
}
old = summPositions[m+5];
tempSumm = summPositions[0]+1;
for (l = m; l>0; l--) {
	for (i=old; i<old+l-3; i++) {
		k = tempSumm+l+i-old;
		for (j = 0; j<n; j++)
			A[i][j] = A[k][j];
	}
	old = old+l-3;
	tempSumm = tempSumm+l;
}
//II reflective screen (I queue overflow)
old = summPositions[m+3];
for (l = m; l>0; l--) {
	tempSumm = ((m+l+3)*(m-l))/2;
	for (i=old; i<old+l; i++) {
		k = tempSumm+i-old;
		for (j = 0; j<n; j++)
			A[i][j] = A[k][j];
	}
	old += l;
}
//II reflective screen (II queue overflow)
for (z = 0; z<m+1; z++) {
	old = summPositions[m+4]+((2*m+2-z)*(z+1)/2)-1;
	for (i = old; i>=old-m+z; i--) {
		if (i == old) {
			k = summPositions[0]-(((2+z)*(z+1))/2);
			for (l = 0; l<n; l++)
				A[i][l] = A[k][l];
		}
		if ((i == old-1) && (i != old-m+z)) {
			k = summPositions[0]-(((3+z)*(z+2))/2);
			for (l = 0; l<n; l++)
				A[i][l] = A[k][l];
		}
		if ((i>old-m+z) && (i<old-1)) {
			k = summPositions[z+1]-1-(((old-i)*(old-i-1))/2);
			for (l = 0; l<n; l++)
				A[i][l] = A[k][l];
		}
		if ((i == old-m+z) && (i != old)) {
			k = m-z-1;
			for (l = 0; l<n; l++)
			A[i][l] = A[k][l];
		}
	}
}
//output
FILE *result = fopen("result.txt","w");
for (i=0; i<n; i++) {
   for (j=0; j<n; j++)
      fprintf(result,"%.3f ",A[i][j]);
   fprintf(result,"\n");
}
fclose(result);
for (i=0; i<n; i++)
   free(A[i]);
free(A);
return 0;
}

