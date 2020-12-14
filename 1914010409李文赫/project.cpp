#include<stdio.h>   
#include<stdlib.h>
#include<string.h> 
#include "goods.h"

bool   GetCharge(int   Sum, int   Money);
void   Getsmalcharge(int   Money, int* ChargeNum);
int KouLing();
char    ChooseJieMian();
char SaleCenter();
void loadGoodsFromFile(Goods* gs);
char ManageCenter();
void KunCun();
void Sale();
void ShangJia();
void TongJiFun();
Goods goods[3];
TongJi tj[3];

void init()
{
	for (int i = 0; i < 3; ++i) {
		tj[i].jrxl = 0;
		tj[i].jrzje = 0;
	}
}

void   main()
{
	//初始化
	init();

	int op = 0;
	//读取商品信息
	loadGoodsFromFile(goods);
	char c = ChooseJieMian();
	while (true)
	{
		system("cls");
		if (c == '1') {
			c = SaleCenter();
		}
		else if (c == '2') {
			op = KouLing();
			if (op == 1) {
				//进入管理界面
				c = ManageCenter();
				//system("pause");
			}
			else if (op == 0) {
				//进去销售界面
				c = SaleCenter();
			}
		}
	}
}

//----------------------------------------------------   

/**
* @return 1销售界面 2管理界面
*/
char SaleCenter()
{
	char   state = 'N';
	int   Sum = 0;
	char   Pro = 'd';
	//  商品选购界面  
	while (true)
	{
		state = 'N';
		Sum = 0;

		while (!(Pro == 'c' || Pro == 'a' || Pro == 'b' || Pro == 'q'))
		{
			system("cls");
			printf("\n\t┌──────────────────────────────────────────┐");
			printf("\n\t│ 请输入代表字母来选购商品 |q·进入管理界面│\n");
			printf("\n\t│  a·商品：%s     b·商品：%s    c·商品：%s │\n", goods[0].name, goods[1].name, goods[2].name);
			printf("\n\t│  库余  %d件         %d件         %d件    │", goods[0].totalCount, goods[1].totalCount, goods[2].totalCount);
			printf("\n\t│  价格： %d元          %d元          %d元    │", goods[0].price, goods[1].price, goods[2].price);
			printf("\n\t└──────────────────────────────────────────┘\n\t\t");
			Pro = getchar();
		}

		if (Pro == 'q')
			break;

		switch (Pro)
		{
		case   'a':
		{
			Sum = Sum + goods[0].price;
			printf("\n\t·商品%s价格为%d，请投币·", goods[0].name, goods[0].price);
		}

		break;
		case   'A':
		{
			Sum = Sum + goods[0].price;
			printf("\n\t·商品%s价格为%d，请投币·", goods[0].name, goods[0].price);
		}

		break;
		case   'b':
		{
			Sum = Sum + goods[1].price;
			printf("\n\t·商品%s价格为%d，请投币·", goods[1].name, goods[1].price);
		}

		break;
		case  'B':
		{
			Sum = Sum + goods[1].price;
			printf("\n\t·商品%s价格为%d，请投币·", goods[1].name, goods[1].price);
		}

		break;
		case   'c':
		{
			Sum = Sum + goods[2].price;
			printf("\n\t·商品%s价格为%d，请投币·", goods[2].name, goods[2].price);
		}

		break;
		case   'C':
		{
			Sum = Sum + goods[2].price;
			printf("\n\t·商品%s价格为%d，请投币·", goods[2].name, goods[2].price);
		}

		break;
		default:
		{
			printf("\n\t输入字母有误！！！！\n");
		}

		break;
		};


		int   Money;

		bool   st = false;

		while (!st)
		{
			//  printf("\n输入金额:");   
			scanf("%d", &Money);
			getchar();
			st = GetCharge(Sum, Money);
		};
		Pro = 'd';
		system("PAUSE");
	}

	return '2';
}
bool   GetCharge(int   Sum, int   Money)
{
	int   ChargeNum[4];
	for (int i = 0; i < 4; i++)
	{
		ChargeNum[i] = 0;
	}

	if (Sum > Money)
	{
		printf("\n\t 错误：所投金额不足支付所选商品，金额已退还，请重新选购投币\n");
		return   true;
	}

	else   if (Sum == Money)
	{
		//销售成功的操作
		if (Sum == goods[0].price)
		{
			if (goods[0].totalCount == 0)
			{
				printf("\n\t 错误：所选商品库存为 0 ，金额已退还，请重新选购商品投币\n");
				return true;
			}
			else
			{
				goods[0].totalCount--;
				Sale();
				tj[0].jrxl++;
				tj[0].jrzje += Sum;
			}
		}

		else if (Sum == goods[1].price)
		{
			if (goods[1].totalCount == 0)
			{
				printf("\n\t 错误：所选商品库存为 0 ，金额已退还，请重新选购商品投币\n");
				return true;
			}
			else
			{
				goods[1].totalCount--;
				Sale();
				tj[1].jrxl++;
				tj[1].jrzje += Sum;
			}
		}

		else if (Sum == goods[2].price)
		{
			if (goods[2].totalCount == 0)
			{
				printf("\n\t 错误：所选商品库存为 0 ，金额已退还，请重新选购商品投币\n");
				return true;
			}
			else
			{
				goods[2].totalCount--;
				Sale();
				tj[2].jrxl++;
				tj[2].jrzje += Sum;
			}
		}
		printf("\n\t·所投金额等于商品价格，请在商品出口处拿取商品·\n");

		return true;
	}

	else
	{
		int   Result = Money - Sum;
		Getsmalcharge(Result, ChargeNum);
		printf("\n\t┌──────────────────────────────────────────┐");
		printf("\n\t│   所投金额大于商品价格，总共为您找零%d元 │\n", Result);
		printf("\n\t│ 1 元面值    %d张    \t\t \t   │\n", ChargeNum[0]);
		printf("\n\t│ 2 元面值    %d张    \t\t \t   │\n", ChargeNum[1]);
		printf("\n\t│ 5 元面值    %d张    \t\t \t   │\n", ChargeNum[2]);
		printf("\n\t│10 元面值    %d张    \t\t \t   │\n", ChargeNum[3]);
		printf("\n\t│\t\t     请在取款处取走余额    │\n");
		printf("\n\t└──────────────────────────────────────────┘\n\t\t");
		//  printf("\n余额为%d元,应找零\n1   元%d张\n2   元%d张\n5   元%d张\n10元%d张\n",Result,ChargeNum[0],ChargeNum[1],ChargeNum[2],ChargeNum[3]);   

	}//end   if   

	//销售成功的操作
	if (Sum == goods[0].price)
	{
		goods[0].totalCount--;
		Sale();
		tj[0].jrxl++;
		tj[0].jrzje += Sum;
	}

	else if (Sum == goods[1].price)
	{
		goods[1].totalCount--;
		Sale();
		tj[1].jrxl++;
		tj[1].jrzje += Sum;
	}

	else if (Sum == goods[2].price)
	{
		goods[2].totalCount--;
		Sale();
		tj[2].jrxl++;
		tj[2].jrzje += Sum;
	}

	return   true;
}
/**
  成功卖出操作的后台操作
*/
void Sale() {
	FILE* fp;
	if ((fp = fopen("d:\\goods.out", "w")) == NULL)
	{
		printf("未找到文件d:\\goods.out...系统将退出\n ");
		exit(0);
	}
	fprintf(fp, "%s %d %d\n", goods[0].name, goods[0].totalCount, goods[0].price);
	fprintf(fp, "%s %d %d\n", goods[1].name, goods[1].totalCount, goods[1].price);
	fprintf(fp, "%s %d %d\n", goods[2].name, goods[2].totalCount, goods[2].price);
	//关闭文件
	fclose(fp);
	fp = NULL;
}
//------------------------------------   
void   Getsmalcharge(int   Money, int* ChargeNum)
{
	if (Money < 0)
		return;
	int   Sum = Money;
	int   charge[4] = { 1,2,5,10 };
	ChargeNum[3] = Sum / charge[3];
	Sum = Sum % charge[3];
	ChargeNum[2] = Sum / charge[2];
	Sum = Sum % charge[2];
	ChargeNum[1] = Sum / charge[1];
	Sum = Sum % charge[1];
	ChargeNum[0] = Sum / charge[0];
	Sum = Sum % charge[0];
}


/**
*@return  1 口令正确  0 口令错误,并返回销售界面
*/
int KouLing()
{
	char kl[50];
	int count = 0, ret = 0;
	char rkl[50] = "admin";
	while (strcmp(rkl, kl) != 0)
	{
		if (count == 0)
		{
			printf("\n\t┌──────────────────────────────────────────┐");
			printf("\n\t│           管理员后台密码验证             │\n");
			printf("\n\t│     请输入后台管理密码以进入后台管理     │\n");
			printf("\n\t│ 若忘记密码,请输入“cancel”以进入销售界面│\n");
			printf("\n\t└──────────────────────────────────────────┘\n\t\t");
		}

		else
		{
			printf("\n\t┌──────────────────────────────────────────┐");
			printf("\n\t│           管理员后台密码验证             │\n");
			printf("\n\t│         管理员后台密码输入错误           │\n");
			printf("\n\t│ 若忘记密码,请输入“cancel”以进入销售界面│\n");
			printf("\n\t│\t\t     密码输入错误次数：%d次 │\n", count);
			printf("\n\t└──────────────────────────────────────────┘\n\t\t");
		}

		count++;
		scanf("%s", kl);
		system("CLS");
		if (count == 3)
		{
			printf("\n你是憨批吗，输入这么多次错误密码，再输错一次就给爷爬\n");
			printf("\n你是憨批吗，输入这么多次错误密码，再输错一次就给爷爬\n");
			printf("\n你是憨批吗，输入这么多次错误密码，再输错一次就给爷爬\n");
			printf("\n你是憨批吗，输入这么多次错误密码，再输错一次就给爷爬\n");
		}

		if (count == 4)
		{
			return ret;
		}

		if (strcmp(kl, "cancel") == 0)
			break;
	}

	if (strcmp(kl, "cancel") == 0)
		ret = 0;

	else
		ret = 1;

	return ret;
}

/**
* @ return  '1' , '2'
*/
char ChooseJieMian()
{
	char c = '3';
	while (true)
	{
		system("cls");
		printf("\n\t┌──────────────────────────────────────────┐");
		printf("\n\t│          欢迎使用本无人售货机            │\n");
		printf("\n\t│           选择您要进行的操作             │\n");
		printf("\n\t│         输入前缀数字来进行相应选择       │\n");
		printf("\n\t│    1·进入销售界面  |  2·进入管理后台   │\n");
		printf("\n\t└──────────────────────────────────────────┘\n\t\t");
		c = getchar();

		if (c == '1' || c == '2')
			break;
	}
	system("cls");
	return c;

}

char ManageCenter()
{
	while (true)
	{
		int op = 7;
		while (!(op == 1 || op == 2 || op == 3 || op == 4 || op == 5 || op == 6))
		{
			system("cls");
			printf("\n\t┌──────────────────────────────────────────┐");
			printf("\n\t│              欢迎您，管理员              │\n");
			printf("\n\t│           选择您要进行的操作             │\n");
			printf("\n\t│     1·库存查询   |   2·商品上架        │\n");
			printf("\n\t│     3·销售查询   |   6·销售界面        │\n");
			printf("\n\t└──────────────────────────────────────────┘\n\t\t");

			scanf("%d", &op);
		}

		bool flag = false;
		switch (op)
		{
		case 1:
		{
			KunCun();
		}
		break;
		case 2:
		{
			ShangJia();
		}
		break;
		case 3:
		{
			TongJiFun();
		}
		break;
		case 4: {}break;
		case 5: {}break;
		case 6:
		{
			flag = true;
		}
		break;
		default:break;
		}

		if (flag)
			break;
		else
			system("PAUSE");
	}
	return '1';
}

/***
*从文件里读取商品信息
@return 商品列表
*/
void loadGoodsFromFile(Goods* gs)
{
	//获得FILE 指针
	FILE* fp;
	if ((fp = fopen("d:\\goods.out", "r")) == NULL)
	{
		printf("未找到商品信息文件d:\\goods.out...系统将退出\n ");
		exit(0);
	}
	//Goods gs[3];
	int i = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%s %d %d", gs[i].name, &gs[i].totalCount, &gs[i].price);
		i++;
	}
	//关闭文件
	fclose(fp);
	fp = NULL;

}

void KunCun()
{
	int i = 0;
	printf("\n\t┌──────────────────────────────────────────┐");
	printf("\n\t│  商品名称   商品价格(元)   商品余量（件）│\n");
	for (i = 0; i < 3; ++i) {
		printf("\n        │   -%s-\t\t-%d-\t\t-%d-       │", goods[i].name, goods[i].price, goods[i].totalCount);
	}
	printf("\n\t└──────────────────────────────────────────┘\n\t\t");
}
void ShangJia()
{
	printf("\n\t┌──────────────────────────────────────────┐");
	printf("\n\t│         整数增加，复数减少商品           │\n");
	int gs1 = 0, gs2 = 0, gs3 = 0;
	printf("\n\t│ 商品：%s(余%d件):  ", goods[0].name, goods[0].totalCount);
	scanf("%d", &gs1);
	printf("\n\t│ 商品：%s(余%d件):  ", goods[1].name, goods[1].totalCount);
	scanf("%d", &gs2);
	printf("\n\t│ 商品：%s(余%d件):  ", goods[2].name, goods[2].totalCount);
	scanf("%d", &gs3);

	goods[0].totalCount = gs1 + goods[0].totalCount < 0 ? 0 : gs1 + goods[0].totalCount;
	goods[1].totalCount = gs2 + goods[1].totalCount < 0 ? 0 : gs2 + goods[1].totalCount;
	goods[2].totalCount = gs3 + goods[2].totalCount < 0 ? 0 : gs3 + goods[2].totalCount;

	//写文件
	//获得FILE 指针
	FILE* fp;
	if ((fp = fopen("d:\\goods.out", "w")) == NULL)
	{
		printf("未找到商品信息文件d:\\goods.out...系统将退出\n ");
		exit(0);
	}

	fprintf(fp, "%s %d %d\n", goods[0].name, goods[0].totalCount, goods[0].price);
	fprintf(fp, "%s %d %d\n", goods[1].name, goods[1].totalCount, goods[1].price);
	fprintf(fp, "%s %d %d\n", goods[2].name, goods[2].totalCount, goods[2].price);
	//关闭文件
	fclose(fp);
	fp = NULL;
}

void TongJiFun()
{
	printf("\n\t┌──────────────────────────────────────────┐");
	printf("\n\t│          今日商品销售情况一览            │\n");
	printf("\n\t│        商品：%s     %d件     共%d元         │\n", goods[0].name, tj[0].jrxl, tj[0].jrzje);
	printf("\n\t│        商品：%s     %d件     共%d元         │\n", goods[1].name, tj[1].jrxl, tj[1].jrzje);
	printf("\n\t│        商品：%s     %d件     共%d元         │\n", goods[2].name, tj[2].jrxl, tj[2].jrzje);
	printf("\n\t│             共计%d件，%d元                 │\n", tj[0].jrxl + tj[1].jrxl + tj[2].jrxl, tj[0].jrzje + tj[1].jrzje + tj[2].jrzje);
	printf("\n\t└──────────────────────────────────────────┘\n\t\t");
}