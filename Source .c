/*
ビルドする前に
scanf_s() → scanf()
strcpy_s() → strcpy()
入力2,10,16進数未対応
*/

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define PI 3.141592653589793
#define ARITHMETIC 0
#define FUNCTION 1

#define BIN 2
#define DEC 10
#define HEX 16

//プロトタイプ宣言
int InCheck(const char *, int *);
void OutChange(double *, int *);
void printhelp();
void printfunc();
double factorial(double);

int main(void) {
	double n = 0.0, m, a;
	double memory = 0.0;
	int calmode = ARITHMETIC;
	int inmode, outmode, i, count;
	inmode = outmode = DEC;//初期は10進数
	char sw[100];

	printf("Function Mode\n");
	printf(">>");
	scanf_s("%lf", &n);
	printf("\\help\n");

	while (1) {
		strcpy_s(sw, "\0");
		m = 0.0;
		scanf_s("%s", sw, 100);
		if (!strcmp(sw, "\\q"))break;
		else if (!strcmp(sw, "\\f")) { calmode = FUNCTION;		printf("Function Mode\n");		continue; } else if (!strcmp(sw, "\\a")) { calmode = ARITHMETIC;	printf("Arithemetic Mode\n");	continue; }
		//else if (!strcmp(sw, "\\in-2"))	{ inmode = BIN;		printf("In-Bin\n");		continue; }
		//else if (!strcmp(sw, "\\in-10"))	{ inmode = DEC;		printf("In-Dec\n");		continue; }
		//else if (!strcmp(sw, "\\in-16"))	{ inmode = HEX;		printf("In-Hex\n");		continue; }
		else if (!strcmp(sw, "\\out-2")) { outmode = BIN;	printf("Out-Bin\n");	continue; } else if (!strcmp(sw, "\\out-10")) { outmode = DEC;	printf("Out-Dec\n");	continue; } else if (!strcmp(sw, "\\out-16")) { outmode = HEX;	printf("Out-Hex\n");	continue; }

		else if (!strcmp(sw, "\\inmemo")) { memory = n; printf("memory=%lf\n", memory); 	continue; } else if (!strcmp(sw, "\\+memo")) { memory += n; printf("memory=%lf\n", memory); 	continue; } else if (!strcmp(sw, "\\-memo")) { memory -= n; printf("memory=%lf\n", memory); 	continue; } else if (!strcmp(sw, "\\outmemo")) { printf("memory=%lf\n", memory); memory = 0;	continue; } else if (!strcmp(sw, "\\reset")) {
			n = 0.0;
			printf(">>");
			scanf_s("%lf", &n);
			printf("\\help\n"); continue;
		}

		else if (!strcmp(sw, "\\func")) { printfunc();	continue; }	//見やすさ的に関数化
		else if (!strcmp(sw, "\\help")) { printhelp();	continue; }	//見やすさ的に関数化
		else if (sw[0] == '\\') { printf("Command Error\n"); continue; }


		//if (InCheck(sw, &inmode) == -1) { printf("Re\n"); continue; }

		switch (calmode) {
		case ARITHMETIC:
			m = strtod(&sw[1], NULL);
			break;
		case FUNCTION:
			//関数の文字数カウント
			count = 1;
			for (i = 1; sw[i] != '\0'; i++) {
				if (!isdigit(sw[i]))count++;
			}
			//printf("%d\n",count);
			m = strtod(&sw[count], NULL);
			if (sw[1] == 's')		m = sin(m * PI / 180.0);
			else if (sw[1] == 't')	m = tan(m * PI / 180.0);
			else if (sw[1] == 'p')	m = pow(n, m);
			else if (sw[1] == 'c')	m = cos(m * PI / 180.0);
			else if (sw[1] == 'l')	m = log(m);
			else if (sw[1] == 'r')	m = sqrt(m);
			else if (sw[1] == '!')	m = factorial(m);
			else if (sw[1] == 'm')	m = fmod(n, m);
			else if (sw[1] == 'e' && sw[2] == 'x')	m = exp(m);
			else if (sw[1] == 'a' && sw[2] == 's')	m = asin(m * PI / 180.0);
			else if (sw[1] == 'a' && sw[2] == 'c')	m = acos(m * PI / 180.0);
			else if (sw[1] == 'a' && sw[2] == 't')	m = atan(m * PI / 180.0);
			else if (sw[1] == 'a' && sw[2] == 'b')	m = fabs(m);
			else if (count > 1) { printf("Function Error\n"); continue; }

		default:
			break;
		}


		switch (sw[0]) {
		case '+':
			a = n + m;
			OutChange(&a, &outmode);
			n = a;
			break;
		case '-':
			a = n - m;
			OutChange(&a, &outmode);
			n = a;
			break;
		case '*':
			a = n * m;
			OutChange(&a, &outmode);
			n = a;
			break;
		case '/':
			a = n / m;
			OutChange(&a, &outmode);
			n = a;
			break;
		default:
			printf("Error Re\n");
		}

	}

	return 0;
}

//今はつかわない（めんどくなった）
//入力を2,10、16進数と変更したときに入力チェックを行う
int InCheck(const char *n, int *mode) {
	int i;
	int ret;
	switch (*mode) {
	case BIN:
		break;
	case DEC:
		break;
	case HEX:
		break;
	}
	return 0;
}

//出力関数
void OutChange(double *a, int *mode) {
	unsigned int bit = (1 << (sizeof(int) * 8 - 1));
	char s[100];
	switch (*mode) {
	case BIN:
		sprintf_s(s, "%lf", *a);
		printf("=");
		for (; bit != 0; bit >>= 1) {
			if ((int)*a & bit) {
				printf("1");
			} else {
				printf("0");
			}
		}
		printf("\n");
		break;
	case DEC:
		printf("=%lf\n", *a);
		break;
	case HEX:
		sprintf_s(s, "%x", (int)*a);
		printf("=%x\n", (int)strtol(s, NULL, *mode));
		break;
	}
}

//コマンドリスト表示
void printhelp() {
	printf("--Comand List--\n");
	printf("OutMode\n");
	printf("\\out-2\n");	//出力2進数
	printf("    -10\n");	//出力10進数（ディフォルト）
	printf("    -16\n\n");	//出力16進数

	printf("CalMode\n");
	printf("\\f Function Mode\n");			//関数モード
	printf("\\a Arithemetic Mode\n\n");		//通常モード（変える意味あるんかな？）

	printf("\\reset Reset\n");	//リセット
	printf("\\inmemo\n");		//メモリーに格納
	printf("\\+memo\n");		//メモリーに＋
	printf("\\-memo\n");		//メモリーに-
	printf("\\outmemo\n");		//メモリーの値表示

	printf("\\func function list\n");	//関数リスト表示
	printf("\\help \n");				//コマンドリスト表示
	printf("--------------\n");
}

//関数リスト表示
void printfunc() {
	printf("--Function List--\n");
	printf("s sin\n");
	printf("c cos\n");
	printf("p power\n");
	printf("l log\n");
	printf("r sqrt\n");
	printf("! factorial\n");
	printf("ex ネイピア数eのべき乗\n");
	printf("m モジュロ\n");
	printf("as arcsin\n");
	printf("ac arccons\n");
	printf("at arctan\n");
	printf("ab absolute\n");
	printf("--------------\n");

}

//階乗を求める関数
double factorial(double n) {
	if (n > 0) {
		return n * factorial(n - 1);
	} else {
		return 1;
	}
}
