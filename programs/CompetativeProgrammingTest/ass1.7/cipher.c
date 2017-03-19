#include<stdio.h>
#include<stdlib.h>

int digCount[] = {4,3,3,5,4,4,3,5,5,4};/*Count of letters in 0-9*/
int countToi[7][500];

int main (int argc, char *argv[]) {
	int i9, i10, i11, i12, i13, i14, i15;
	int t, len, curr, pos, flag;
	int i, j, k, iter;
	char cipher[20], *currDig;
	
	i9 = i10 = i11 = i12 = i13 = i14 = i15 = 0;
	for (i = 999; i >= 0; i -= 1) {/*Fill array countToi[i][] with 3 dig numbers 0f letter count 9+i in desc order*/
		t = i;
		len = 0;
		for (j = 0; j < 3; j += 1) {
			len += digCount[t%10];
			t /= 10;
		}
		switch(len){
				case 9: countToi[len-9][i9++] = i;
						countToi[len-9][i9] = -1;
						break;
				case 10: countToi[len-9][i10++] = i;
						countToi[len-9][i10] = -1;
						break;
				case 11: countToi[len-9][i11++] = i;
						countToi[len-9][i11] = -1;
						break;
				case 12: countToi[len-9][i12++] = i;
						countToi[len-9][i12] = -1;
						break;
				case 13: countToi[len-9][i13++] = i;
						countToi[len-9][i13] = -1;
						break;
				case 14: countToi[len-9][i14++] = i;
						countToi[len-9][i14] = -1;
						break;
				case 15: countToi[len-9][i15++] = i;
						countToi[len-9][i15] = -1;
						break;
			}
	}
	flag = 0;
	while (scanf("%s\n",cipher) == 1) {
		if(flag == 1) printf("\n");
		flag = 1;
		for (len = 0; cipher[len] != '\0'; len += 1);
		
		for (i = 0; countToi[len-9][i] != -1; i += 1) {
			char digits[20];
			curr = countToi[len-9][i];
			digits[0] = '\0';
			iter = 0;
			for(pos = 100; pos > 0; curr %= pos, pos /= 10) {
				switch(curr / pos){
					case 0: currDig = "zero";	break;
					case 1: currDig = "one";	break;
					case 2: currDig = "two";	break;
					case 3: currDig = "three";	break;
					case 4: currDig = "four";	break;
					case 5: currDig = "five";	break;
					case 6: currDig = "six";	break;
					case 7: currDig = "seven";	break;
					case 8: currDig = "eight";	break;
					case 9: currDig = "nine";	break;
				}
				
				for (j = 0; currDig[j] != '\0'; j += 1) {
					int val1,val2;
					val1 = cipher[iter++] - 'A';
					val2 = (currDig[j] - 'a' + 1) % 26;
					val2 = (26 + val1 - val2) % 26;
					val2 += 'A';
					printf("%c",val2);
					
				}
				for (j = 0; digits[j] != '\0'; j += 1);
				for (k = 0; currDig[k] != '\0'; k += 1, j += 1) {
					digits[j] = currDig[k];
				}
				digits[j] = '\0';
			}
			printf(" -> %s\n",digits);
		}
	}
	return 0;
}
