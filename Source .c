/*
	�r���h����O��
	scanf_s() �� scanf()
	strcpy_s() �� strcpy()
	����2,10,16�i�����Ή�
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

//�v���g�^�C�v�錾
int InCheck(const char *, int *);
void OutChange(double *, int *);
void printhelp();
void printfunc();
double factorial(double);

int main(void) {
	double n = 0.0, m, a;
	double memory = 0.0;
	int calmode = ARITHMETIC;
	int inmode, outmode, i,count;
	inmode = outmode = DEC;//������10�i��
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
		else if (!strcmp(sw, "\\f")) { calmode = FUNCTION;		printf("Function Mode\n");		continue; } 
		else if (!strcmp(sw, "\\a")) { calmode = ARITHMETIC;	printf("Arithemetic Mode\n");	continue; }
		//else if (!strcmp(sw, "\\in-2"))	{ inmode = BIN;		printf("In-Bin\n");		continue; }
		//else if (!strcmp(sw, "\\in-10"))	{ inmode = DEC;		printf("In-Dec\n");		continue; }
		//else if (!strcmp(sw, "\\in-16"))	{ inmode = HEX;		printf("In-Hex\n");		continue; }
		else if (!strcmp(sw, "\\out-2"))	{ outmode = BIN;	printf("Out-Bin\n");	continue; } 
		else if (!strcmp(sw, "\\out-10"))	{ outmode = DEC;	printf("Out-Dec\n");	continue; } 
		else if (!strcmp(sw, "\\out-16"))	{ outmode = HEX;	printf("Out-Hex\n");	continue; } 

		else if (!strcmp(sw, "\\inmemo"))	{ memory = n; printf("memory=%lf\n", memory); 	continue; }
		else if (!strcmp(sw, "\\+memo")) { memory += n; printf("memory=%lf\n", memory); 	continue; }
		else if (!strcmp(sw, "\\-memo")) { memory -= n; printf("memory=%lf\n", memory); 	continue; }
		else if (!strcmp(sw, "\\outmemo"))	{ printf("memory=%lf\n", memory); memory = 0;	continue; }
		else if (!strcmp(sw, "\\reset")) {
			n = 0.0;
			printf(">>");
			scanf_s("%lf", &n);
			printf("\\help\n"); continue; 
		}

		else if (!strcmp(sw, "\\func")) { printfunc();	continue; }	//���₷���I�Ɋ֐���
		else if (!strcmp(sw, "\\help")) { printhelp();	continue; }	//���₷���I�Ɋ֐���
		else if (sw[0] == '\\') { printf("Command Error\n"); continue; }


		//if (InCheck(sw, &inmode) == -1) { printf("Re\n"); continue; }

		switch (calmode) {
		case ARITHMETIC:
			m = strtod(&sw[1], NULL);
			break;
		case FUNCTION:
			//�֐��̕������J�E���g
			count = 1;
			for (i = 1;sw[i] != '\0'; i++) {
				if (!isdigit(sw[i]))count++;
			}
			//printf("%d\n",count);
			m = strtod(&sw[count], NULL);
			if (sw[count] == 's')		m = sin(m * PI / 180.0);
			else if(sw[count] == 'c')	m = cos(m * PI / 180.0);
			else if (sw[count] == 't')	m = tan(m * PI / 180.0);
			else if (sw[count] == 'p')	m = pow(n, m); 
			else if (sw[count] == 'l')	m = log(m);
			else if (sw[count] == 'r')	m = sqrt(m);
			else if (sw[count] == '!')	m = factorial(m);
			else if (sw[count] == 'm')	m = fmod(n,m);
			else if (sw[count] == 'e' && sw[count + 1] == 'x')	m = exp(m);
			else if (sw[count] == 'a' && sw[count + 1] == 's')	m = asin(m * PI / 180.0);
			else if (sw[count] == 'a' && sw[count + 1] == 'c')	m = acos(m * PI / 180.0);
			else if (sw[count] == 'a' && sw[count + 1] == 't')	m = atan(m * PI / 180.0);
			else if (sw[count] == 'a' && sw[count + 1] == 'b')	m = fabs(m);

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

//���͂���Ȃ��i�߂�ǂ��Ȃ����j
//���͂�2,10�A16�i���ƕύX�����Ƃ��ɓ��̓`�F�b�N���s��
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

//�o�͊֐�
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

//�R�}���h���X�g�\��
void printhelp() {
	printf("--Comand List--\n");
	printf("OutMode\n");
	printf("\\out-2\n");	//�o��2�i��
	printf("    -10\n");	//�o��10�i���i�f�B�t�H���g�j
	printf("    -16\n\n");	//�o��16�i��

	printf("CalMode\n");
	printf("\\f Function Mode\n");			//�֐����[�h
	printf("\\a Arithemetic Mode\n\n");		//�ʏ탂�[�h�i�ς���Ӗ�����񂩂ȁH�j

	printf("\\reset Reset\n");	//���Z�b�g
	printf("\\inmemo\n");		//�������[�Ɋi�[
	printf("\\+memo\n");		//�������[�Ɂ{
	printf("\\-memo\n");		//�������[��-
	printf("\\outmemo\n");		//�������[�̒l�\��

	printf("\\func function list\n");	//�֐����X�g�\��
	printf("\\help \n");				//�R�}���h���X�g�\��
	printf("--------------\n");
}

//�֐����X�g�\��
void printfunc() {
	printf("--Function List--\n");
	printf("s sin\n");
	printf("c cos\n");
	printf("p power\n");
	printf("l log\n");
	printf("r sqrt\n");
	printf("! factorial\n");
	printf("ex �l�C�s�A��e�ׂ̂���\n");
	printf("m ���W����\n");
	printf("as arcsin\n");
	printf("ac arccons\n");
	printf("at arctan\n");
	printf("ab absolute\n");
	printf("--------------\n");

}

//�K������߂�֐�
double factorial(double n) {
	if (n > 0) {
		return n * factorial(n - 1);
	} else {
		return 1;
	}
}