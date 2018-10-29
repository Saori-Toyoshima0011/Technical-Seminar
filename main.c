
/*BP16064  豊島早織*/

#define SENGEN
#include "stdio.h"
#include "stdlib.h"
//#include "string.h"
#include "livdec.h"
#include "livauxproto.h"
#include "livfioproto.h"          //ppm画像の読み書き
#include "livmemproto.h"          //callocの定義
#include "livcomproto.h"
#define FALSE 0
#define TRUE 1

typedef struct STACK{
	STACK a;
	int num;
}STACK;

void initialize_2D(UCHAR **, int, int, int);
void zenbu_Labeling(UCHAR **, int **, int, int);
void region_unification(UCHAR **, UCHAR **, int **, int, int, int);
int tougou(UCHAR **, UCHAR **, int**, int, int);

int main(argc, argv)
int argc;
char *argv[];
{
	int MaxGyou_A, MaxRetu_A;
	UCHAR ***org_data0;           //元データ
	int **label;
	UCHAR **region_data;         //領域分割処理をしたデータ
	//UCHAR **out_data0;           //出力データ
	UCHAR **gdata;
	UCHAR **temp;
	int tyumokuGaso;
	int num_label = 0;
	clock_t start, end;
	char out_fname[200];
	//int a;
	start = clock();

	org_data0 = (UCHAR ***)calloc_uchar3D(3, MaxGyou_org, MaxRetu_org);
	gdata = (UCHAR **)calloc_uchar2D(MaxGyou_org, MaxRetu_org);
	temp = (UCHAR **)calloc_uchar2D(MaxGyou_org, MaxRetu_org);
	region_data = (UCHAR **)calloc_uchar2D(MaxGyou_org, MaxRetu_org);

	/*画像の読み込み*/
	read_ppm(org_data0, "tubaki1.ppm", &MaxRetu_A, &MaxGyou_A);
	if ((MaxRetu_A != MaxRetu_org) || (MaxGyou_A != MaxGyou_org)){
		printf("(gyou,retu)=(%d,%d) should be (%d,%d)\n", MaxGyou_A, MaxRetu_A, MaxGyou_org, MaxRetu_org);
		error1("Dimension error");
	}

	convert_to_graylevel(org_data0, gdata, MaxGyou_org, MaxRetu_org);

	for (tyumokuGaso = 0; tyumokuGaso < 256; tyumokuGaso++){
		printf("Gaso = %d\n", tyumokuGaso);
		initialize_2D(temp, -1, MaxGyou_org, MaxRetu_org);
		binarize(temp, gdata, MaxGyou_org, MaxRetu_org, tyumokuGaso);
		sprintf_s(out_fname, 200, "./gasoti_search/Gaso%d.pgm", tyumokuGaso);
		write_pgm(temp, out_fname, MaxRetu_org, MaxGyou_org);
		printf("%s\n", out_fname);
	}

	/*ラべリング*/
	//zenbu_Labeling(gdata, label, MaxGyou_org, MaxRetu_org);

	region_unification(gdata, region_data, label, 10, MaxGyou_org, MaxRetu_org);

	end = clock();
	return 0;

}

void initialize_2D(UCHAR **data, int val, int MaxG, int MaxR){
	int g, r;
	for (g = 0; g < MaxG; g++){
		for (r = 0; r < MaxR; r++){
			data[g][r] = val;
		}
	}
}

/*一度に一つの画素をラべリングした方がいい*/
void zenbu_Labeling(UCHAR **org, int **label, int MaxG, int MaxR){


}

void region_unification(UCHAR **org, UCHAR **region, int **label, int renge, int MaxG, int MaxR){
	int tyumoku, num_label;
	int g, r;

	for (tyumoku = 0; tyumoku < 256; tyumoku++){
		num_label = labeling(label, tyumoku, org, MaxG, MaxR, RENKETU4);
		tougou(org, region, label, num_label, MaxG, MaxR);
	}
}

int tougou(UCHAR **org, UCHAR **region, int **label, int MaxG, int MaxR){
	int g, r;
	//int flag;

	for (g = 0; g < MaxG; g++){
		for (r = 0; r < MaxR; r++){
			if (label != -1)
		}
	}

	for (g = 0; g < MaxG; g++){
		for (r = 0; r < MaxR; r++){

		}
	}
	return FALSE;
}