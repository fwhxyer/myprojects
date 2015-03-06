#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<string>
#include<map>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<ctime>

using namespace std;
//powered by fwhxyer

typedef pair<int,int> Point;
typedef int Mp[12][12];
typedef queue<Point> Next;
const int MAXINF=2100000000;
const int NextLevelNeedAchieve[1000]={0,1000,3000,5000,7000
                                ,10000,13000,16000,19000,23000
                                ,27000,31000,35000,39000,43000
                                ,47000,51000,55000,59000,63000
                                ,67000,71000,75000,79000,83000
                                ,87000,91000,95000,99000,103000
                                ,107000,111000,115000,119000,123000
                              };
int NextLevelNeed(int n){if (n<10) return NextLevelNeedAchieve[n]; return NextLevelNeedAchieve[10]+4000*(n-10);}

char EorC='E';
bool randomData=0;
bool BMPData=0;
bool BMPDetail=0;
bool TestAI=0;
bool detail=1;//1 or -1
string BMPPath="1.bmp";
string BMPPath1="C:\\Users\\hp\\Desktop\\1.bmp";

void MpCopy(Mp lhs,Mp rhs)
{
    for (int i=0;i<=11;i++){
        for (int j=0;j<=11;j++){
            lhs[i][j]=rhs[i][j];
        }
    }
}
int rand0(int n=32768){
	return rand()%n;
}
int rand1(int n=32768,int p=1){
	if (n<p) return 0;
	return rand()%(n-p)+p;
}

char name[6]={' ','Y','G','B','R','P'};
string nameC[6]={"  ","黄","绿","蓝","红","紫"};
Mp mp={0};//1 黄 2 绿 3 蓝 4 红 5 紫
pair<int,int> cnt[11][6];
Next nextMp;

int getBMP();
int getScore(int n){
	return 5*n*n;
}
int getLeftScore(int n){
	if (n<=10)
		return 2000-20*n*n;
	return 0;
}
int paintx,painty,paintn;
int way[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
void paintMid(Mp &mp,int x,int y){
	if (mp[x][y]!=0) {
		if (x>paintx || (x==paintx && y>painty) ){
			paintx=x;painty=y;
		}
		int color=mp[x][y];
		mp[x][y]=0;
		paintn++;
		for (int i=0;i<4;i++){
			int xt=x+way[i][0];
			int yt=y+way[i][1];
			if (mp[xt][yt]==color)
				paintMid(mp,xt,yt);
		}
	}
}
void paintMid(Mp &mp,Point p){
	paintMid(mp,p.first,p.second);
}
Point paint(Mp &mp,int x,int y){
	paintx=painty=-1;
	paintn=0;
	paintMid(mp,x,y);
	if (paintn>1)
		return make_pair(paintx,painty);
	else
		return make_pair(-1,-1);
}
Point countPaint(Mp &mp,Point p){
	paintn=0;
	paintMid(mp,p.first,p.second);
	return make_pair(getScore(paintn),paintn);
}

Next getNext(Mp mp){
	Mp mpNext;
	Point p;
	Next next;
	while(!nextMp.empty()) nextMp.pop();
	/*
	for (int i=0;i<=11;i++){
		for (int j=0;j<=11;j++){
			mpNext[i][j]=mp[i][j];
		}
	}*/
	MpCopy(mpNext,mp);
	for (int i=1;i<=10;i++){
		for (int j=1;j<=10;j++){
			Point t=paint(mpNext,i,j);
			if (t!=make_pair(-1,-1))
				next.push(t);
		}
	}
	return next;
}
int getAllScore(Mp mp){
	Mp mpScore;
	/*for (int i=0;i<=11;i++){
		for (int j=0;j<=11;j++){
			mpScore[i][j]=mp[i][j];
		}
	}*/
	MpCopy(mpScore,mp);
	Next next=getNext(mpScore);
	int ans=0;
	while (!next.empty()){
		ans+=countPaint(mpScore,next.front()).first;
		next.pop();
	}
	return ans;
}

int value(char t){
//1 黄 2 绿 3 蓝 4 红 5 紫
	switch (t)
	{
	case'y':case'Y':case'1':
		return 1;
	case'g':case'G':case'2':
		return 2;
	case'b':case'B':case'3':
		return 3;
	case'r':case'R':case'4':
		return 4;
	case'p':case'P':case'5':
		return 5;
	case'd':
		detail=!detail;
		cout<<endl<<"detail change to "<<detail<<endl<<endl;
		return -1;
	case't':
	    TestAI=!TestAI;
		cout<<endl<<"TestAI change to "<<TestAI<<endl<<endl;
		return -1;
	case'-':
		cout<<endl<<"Random Data!"<<endl<<endl;
		return -2;
	case'*':
		cout<<endl<<"BMP Data!"<<endl<<endl;
		return -3;
	case'_':
		cout<<endl<<"Random All Data!"<<endl<<endl;
		return -4;
	case'&':
		cout<<endl<<"BMP All Data!"<<endl<<endl;
		return -5;
	default:
		return 0;
		break;
	}
}
void makedata()
{
	if (randomData){
		memset(mp,0,sizeof(mp));
		for (int i=1;i<=10;i++)
			for (int j=1;j<=10;j++)
			{
				mp[i][j]=rand1(6);
			}
	}else if (BMPData){
		if (getBMP()) {
			BMPData=0;
			makedata();
			return;
		}
	}else{
		cout<<"========|请输入给定矩阵：\n";
		cout<<"========|          格式：\tyY1 gG2 bB3 rR4 pP5=color\n"
              "========|                \td=detail t=testAI\n"
              "========|                \t-=random _=randomAll *=BMP &=BMPAll\n"
		      "   1234567890\n";
		memset(mp,0,sizeof(mp));
		for (int i=1;i<=10;i++){
			if (i!=10)
				cout<<" "<<i<<" ";
			else
				cout<<i<<" ";
			for (int j=1;j<=10;j++)
			{
				char t;
				cin>>t;
				mp[i][j]=value(t);
				if (mp[i][j]==-1) {
					randomData=0;
					makedata();
					return;
				}
				if (mp[i][j]==-2) {
					randomData=1;
					makedata();
					randomData=0;
					return;
				}
				if (mp[i][j]==-3) {
					BMPData=1;
					makedata();
					BMPData=0;
					return;
				}
				if (mp[i][j]==-4) {
					randomData=1;
					makedata();
					return;
				}
				if (mp[i][j]==-5) {
					BMPData=1;
					makedata();
					return;
				}
			}
		}
	}
}

void showdata(Mp mpShow=mp)
{
	for (int i=1;i<=11;i++)
		cout<<"==";
	cout<<"="<<endl;
	for (int i=1;i<=10;i++){
		cout<<"┋";
		for (int j=1;j<=10;j++)
		{
			if (EorC=='E')
			{cout<<name[mpShow[i][j]];if (j!=10) cout<<" ";}
			else
				cout<<nameC[mpShow[i][j]];
		}
		cout<<"┋"<<endl;
	}
	for (int i=1;i<=11;i++)
		cout<<"==";
	cout<<"="<<endl;
}

void init()
{
	for (int j=0;j<=10;j++)
		for (int i=0;i<6;i++)
			cnt[j][i]=make_pair(0,i);
	for (int i=1;i<=10;i++)
		for (int j=1;j<=10;j++)
		{
			cnt[0][mp[i][j]].first++;
		}
	sort(cnt[0]+1,cnt[0]+6);
	for (int i=1;i<6/2;i++)
	{	cnt[0][0]=cnt[0][i];cnt[0][i]=cnt[0][6-i];cnt[0][6-i]=cnt[0][0];	}
	//for (int i=1;i<6;i++) cout<<name[cnt[0][i].second]<<" "<<cnt[0][i].first<<" "<<getScore(cnt[0][i].first)<<endl;
	//输出各种颜色的总个数及分数
	for (int i=1;i<=10;i++)
		for (int j=1;j<=10;j++)
		{
			cnt[i][mp[j][i]].first++;
		}
	/*
	int allScore=getAllScore(mp);
	//if (allScore>1500)
		cout<<allScore<<endl;*/
}

Point goNextStep(Mp &mp,Point p){
	Point tt=countPaint(mp,p);
	int score=tt.first;
	int paintn=tt.second;
	for (int j=1;j<=10;j++){
		for (int i=2;i<=10;i++){
			if (mp[i][j]==0){
				for (int k=i;k>1;k--)
					mp[k][j]=mp[k-1][j];
				mp[1][j]=0;
			}
		}
	}
	for(int i=9;i>=1;i--)
		if (mp[10][i]==0){
			for (int j=i;j<=9;j++)
				for (int k=1;k<=10;k++)
					mp[k][j]=mp[k][j+1];
			for (int k=1;k<=10;k++)
				mp[k][10]=0;
		}
	return make_pair(score,paintn);}

Point tryGreedy(Mp mp,Point p){
	Mp mpGreedy;
	/*for (int i=0;i<=11;i++){
		for (int j=0;j<=11;j++){
			mpGreedy[i][j]=mp[i][j];
		}
	}*/
	MpCopy(mpGreedy,mp);
	Point tt=goNextStep(mpGreedy,p);
	int t=tt.first;
	int pp=tt.second;
	return make_pair(getAllScore(mpGreedy)+t,pp);
}
int greedy(int &score,int level,bool NoTest=1){
    bool det=1;Mp mpt;
    if (!NoTest) {det=detail;detail=0;MpCopy(mpt,mp);}
	int ans=score,anstmp=score;
	Next next=getNext(mp);
	while (!next.empty()){
		int maxt=0;
		int minpaintnum=MAXINF;
		Point nextStep;
		while(!next.empty()){
			Point tt=tryGreedy(mp,next.front());
			int t=tt.first;
			int p=tt.second;
			if (maxt<t || (maxt==t && p<=minpaintnum)){
				maxt=t;
				minpaintnum=p;
				nextStep=next.front();
			}
			next.pop();
		}
		if (detail) {
			if (!TestAI) system("pause");
			if (NoTest)
			cout<<"下一步： x "<<nextStep.second
				<<"\ty "<<nextStep.first<<"\tcolor "
				<<nameC[mp[nextStep.first][nextStep.second]]
				<<"\tpoint "<<ans<<endl;showdata();
		}
		ans+=goNextStep(mp,nextStep).first;
		next=getNext(mp);
	}
	int anst=0;
	for (int i=1;i<=10;i++)
		for (int j=1;j<=10;j++)
		{
			if (mp[i][j]) anst++;
		}
    if (NoTest)
	cout<<"奖励分： "<<getLeftScore(anst)<<endl;
	ans+=getLeftScore(anst);
    if (NoTest)
	cout<<"总共得分： "<<ans<<"\t\t过关需求："<<NextLevelNeed(level)<<endl<<endl;
    if (NoTest)
	cout<<"本局得分： "<<ans-anstmp<<endl;
    if (NoTest)
	score=ans;
    if (!NoTest) {detail=det;MpCopy(mp,mpt);}
	return ans-anstmp;
}

Next nextStep;
stack<Point> nextDFSStep;
int MaxDFSScore=0,minDFSPaintNum=MAXINF;

void tryDFS(Mp mp,Next next,int n,int MaxScore,int minPaintNum){//n=StepNum
    if (n<=0) {
        MaxScore+=getAllScore(mp);
        if (MaxDFSScore<MaxScore || (MaxDFSScore==MaxScore&&minPaintNum<minDFSPaintNum) ){
            MaxDFSScore=MaxScore;
            minDFSPaintNum=minPaintNum;
            stack<Point> nextDFSStept,nextDFSSteptt;
            while(!nextDFSStep.empty()){
                nextDFSStept.push(nextDFSStep.top());
                nextDFSSteptt.push(nextDFSStep.top());
                nextDFSStep.pop();
            }
            while(!nextStep.empty()) nextStep.pop();
            while(!nextDFSStept.empty()){
                nextStep.push(nextDFSStept.top());
                nextDFSStept.pop();
            }
            while(!nextDFSSteptt.empty()){
                nextDFSStep.push(nextDFSSteptt.top());
                nextDFSSteptt.pop();
            }
        }
        return;
    }
    if (next.empty()){
        int anst=0;
        if(n>-1)
        for (int i=1;i<=10;i++)
            for (int j=1;j<=10;j++)
            {
                if (mp[i][j]) anst++;
            }
        tryDFS(mp,next,0,MaxScore+getLeftScore(anst),minPaintNum);
    }else
    while(!next.empty()){
        Mp mpT;
        Next nextT;
        int MaxScoret=MaxScore;
        int minPaintNumt=minPaintNum;
        /*for (int i=0;i<=11;i++){
            for (int j=0;j<=11;j++){
                mpT[i][j]=mp[i][j];
            }
        }*/
        MpCopy(mpT,mp);
        Point pp=goNextStep(mpT,next.front());
        MaxScoret+=pp.first;
        minPaintNumt+=pp.second;
        nextT=getNext(mpT);
        nextDFSStep.push(next.front());
        tryDFS(mpT,nextT,n-1,MaxScoret,minPaintNumt);
        nextDFSStep.pop();
        next.pop();
    }
}
int DFS(int &score,int level,int n=1,bool NoTest=1,int cross=0){
    if (!n){return greedy(score,level,NoTest);}
    bool det=1;Mp mpt;
    if (!NoTest) {det=detail;detail=0;MpCopy(mpt,mp);}
	int ans=score,anstmp=score;
	Next next=getNext(mp);
	while (!next.empty()){
		MaxDFSScore=0;
		minDFSPaintNum=MAXINF;
		while(!nextStep.empty()) nextStep.pop();
		while(!nextDFSStep.empty()) nextDFSStep.pop();
        tryDFS(mp,next,n-cross,0,0);
        if (cross) cross=0;
        while(!nextStep.empty()){
            if (detail) {
                if (!TestAI) system("pause");
                if (NoTest)
                cout<<"下一步： x "<<nextStep.front().second
                    <<"\ty "<<nextStep.front().first<<"\tcolor "
                    <<nameC[mp[nextStep.front().first][nextStep.front().second]]
                    <<"\tpoint "<<ans<<endl;showdata();
            }
            ans+=goNextStep(mp,nextStep.front()).first;
            nextStep.pop();
        }
        next=getNext(mp);
	}
	int anst=0;
	for (int i=1;i<=10;i++)
		for (int j=1;j<=10;j++)
		{
			if (mp[i][j]) anst++;
		}
    if (NoTest)
	cout<<"奖励分： "<<getLeftScore(anst)<<endl;
	ans+=getLeftScore(anst);
    if (NoTest)
	cout<<"总共得分： "<<ans<<"\t\t过关需求："<<NextLevelNeed(level)<<endl<<endl;
    if (NoTest)
	cout<<"本局得分： "<<ans-anstmp<<endl;
    if (NoTest)
	score=ans;
    if (!NoTest) {detail=det;MpCopy(mp,mpt);}
	return ans-anstmp;
}

int main(){
	srand(time(0));
	int score=0,scoretmp=0;
	int level=1;
	while (level){
        scoretmp=score;
		makedata();
		showdata();
		init();
		int maxt=0,method=0,cross=0;
		cout<<"=====|预测分析开始进行："<<endl;
		for (int i=0;i<5;i++){
                int t=DFS(score,level,i,0);if (t>maxt){maxt=t;method=i;}
        }
        if (maxt<3000){
            cout<<"          "<<maxt<<"分未达到预期，开始错位分析\n"<<endl;
            for (int i=1;i<5;i++){
                    int t=DFS(score,level,4,0,i);if (t>maxt){maxt=t;method=4;cross=i;}
            }
		}
        if (maxt<3000){
            cout<<"          "<<maxt<<"分未达到预期，开始高级分析\n"<<endl;
            int t=DFS(score,level,5,0);
            if (t>maxt){maxt=t;method=5;}
		}
		cout<<"      本局游戏最高得分："<<maxt<<"\t方案："<<method<<endl;
		DFS(score,level,method,1,cross);//0=greedy(score,level);
		if (!TestAI) system("pause");
		if (score>=NextLevelNeed(level))
            level++;
        else {
            score=scoretmp;
            cout<<"你已经死了，本局游戏重新开始。\n";
            system("pause");
        }
	}
	cout<<"你已经死了，游戏结束。\n";
	system("pause");
}












//This part is BMP=============================================================================================================

			#define BITMAPFILEHEADERLENGTH 14   // The bmp FileHeader length is 14
			#define BM 19778                    // The ASCII code for BM
			/* Test the file is bmp file or not */
			void bmpFileTest(FILE* fpbmp);
			/* To get the OffSet of header to data part */
			void bmpHeaderPartLength(FILE* fpbmp);
			/* To get the width and height of the bmp file */
			void BmpWidthHeight(FILE* fpbmp);
			//get r,g,b data
			void bmpDataPart(FILE* fpbmp);
			// output data to corresponding txt file
			//void bmpoutput(FILE *fpout);
			void bmpoutput();

			unsigned int OffSet = 0;    // OffSet from Header part to Data Part
			long width ;          // The Width of the Data Part
			long height ;         // The Height of the Data Part
			unsigned char r[2000][2000],output_r[2000][2000];
			unsigned char g[2000][2000],output_g[2000][2000];
			unsigned char b[2000][2000],output_b[2000][2000];


			int getBMP()
			{
				 /* Open bmp file */
			//unsigned char *fp_temp;


				 FILE *fpbmp;
				 //FILE *fpout;


				 fpbmp= fopen(BMPPath.c_str(), "rb");


				 if (fpbmp == NULL)
				 {
				 fpbmp= fopen(BMPPath1.c_str(), "rb");

				 if (fpbmp == NULL)
				 {
			 printf("Open bmp failed!!!\n");
			 return 1;
				 }
				 }


				 /*fpout= fopen("out.bmp", "wb+");
				 if (fpout == NULL)
				 {
			 printf("Open out.bmp failed!!!\n");
			 return 1;
				 }*/

				 bmpFileTest(fpbmp);                //Test the file is bmp file or not
				 bmpHeaderPartLength(fpbmp);        //Get the length of Header Part
				 BmpWidthHeight(fpbmp);             //Get the width and width of the Data Part


			//
			fseek(fpbmp, 0L, SEEK_SET);
			//fseek(fpout, 0L, SEEK_SET);

			/*fp_temp=malloc(OffSet);
			fp_temp=(unsigned char*)malloc(sizeof(OffSet)*OffSet);
					 fread(fp_temp, 1, OffSet, fpbmp);
			fwrite(fp_temp,1,OffSet,fpout);*/

			bmpDataPart(fpbmp);                //Reserve the data to file


			/*


			 如果您想对图片进行处理，请您再这里插入处理函数!!!!!!!!!!!!!!!!!!


			*/






			bmpoutput();
			fclose(fpbmp);
			//fclose(fpout);
					 return 0;
			}


			//void bmpoutput(FILE *fpout)
			void bmpoutput()
			{
					 int i, j=0;
					 int stride;
			unsigned char* pixout=NULL;

			stride=(24*width+31)/8;
			stride=stride/4*4;
			pixout=(unsigned char*)malloc((stride)*stride);

			//fseek(fpout, OffSet, SEEK_SET);


			for(j=0;j<height;j++)
			{



			   for(i=0;i<width;i++)
					{
						pixout[i*3+2]=output_r[height-1-j][i];
						pixout[i*3+1]=output_g[height-1-j][i];
						pixout[i*3]  =output_b[height-1-j][i];
					}
			//fwrite(pixout, 1, stride, fpout);

			}
			}


			void bmpDataPart(FILE* fpbmp)
			{
					 int i, j=0;
			int stride;
			unsigned char* pix=NULL;

			/*
			FILE* fpr;
			FILE* fpg;
			FILE* fpb;

				 if((fpr=fopen("bmpr.txt","w+")) == NULL)
				 {
				printf("Failed to construct file bmpr.txt.!!!");
			exit(1);
				 }


				 if((fpg=fopen("bmpg.txt","w+")) == NULL)
				 {
			 printf("Failed to construct file bmpg.txt.!!!");
			 exit(1);
				 }


			if((fpb=fopen("bmpb.txt","w+")) == NULL)
				 {
			printf("Failed to construct file bmpb.txt.!!!");
			exit(1);
				 }*/

				 fseek(fpbmp, OffSet, SEEK_SET);
			stride=(24*width+31)/8;
			stride=stride/4*4;
			pix=(unsigned char*)malloc(sizeof(stride)*stride);
			for(j=321;j<height;j++)
			{
			fread(pix, 1, stride, fpbmp);

			   for(i=0;i<width;i++)
					{
						r[height-1-j][i]   =pix[i*3+2];
						g[height-1-j][i]   =pix[i*3+1];
						b[height-1-j][i]   =pix[i*3];


			output_r[height-1-j][i]   =pix[i*3+2];
						output_g[height-1-j][i]   =pix[i*3+1];
						output_b[height-1-j][i]   =pix[i*3];
					}

			}

			 for(i =0; i < 640; i++)
				 {
			for(j = 0; j < width-1; j++)
			{
				if (i%64-32==0 && j%64-32==0){
					if (BMPDetail) printf("%4d\t%4d\t%4d\t\t%d\t%d\t",b[i][j],g[i][j],r[i][j],i,j);
					if (b[i][j]==214 && g[i][j]==52 && r[i][j]==165){mp[i/64+1][j/64+1]=5; if (BMPDetail) cout<<"紫"<<endl;}
					if (b[i][j]==74 && g[i][j]==215 && r[i][j]==57 ){mp[i/64+1][j/64+1]=2; if (BMPDetail) cout<<"绿"<<endl;}
					if (b[i][j]==214 && g[i][j]==150 && r[i][j]==57){mp[i/64+1][j/64+1]=3; if (BMPDetail) cout<<"蓝"<<endl;}
					if (b[i][j]==57 && g[i][j]==195 && r[i][j]==214){mp[i/64+1][j/64+1]=1; if (BMPDetail) cout<<"黄"<<endl;}
					if (b[i][j]==74 && g[i][j]==52  && r[i][j]==214){mp[i/64+1][j/64+1]=4; if (BMPDetail) cout<<"红"<<endl;}
					//system("pause");
				}
			/*fprintf(fpb,"%4d",b[i][j]);
			fprintf(fpg,"%4d",g[i][j]);
			fprintf(fpr,"%4d",r[i][j]);*/
			}
			/*fprintf(fpb,"%4d\n",b[i][j]);
			fprintf(fpg,"%4d\n",g[i][j]);
			fprintf(fpr,"%4d\n",r[i][j]);*/
			 }

			/*fclose(fpr);
			fclose(fpg);
			fclose(fpb);*/
			}


			void bmpFileTest(FILE* fpbmp)
			{
				 unsigned short bfType = 0;

				 fseek(fpbmp, 0L, SEEK_SET);//seek_set 起始位置
				 fread(&bfType, sizeof(char), 2, fpbmp);
				 if (BM != bfType)
				 {
			 printf("This file is not bmp file.!!!\n");
			 exit(1);
				 }
			}


			/* To get the OffSet of header to data part */
			void bmpHeaderPartLength(FILE* fpbmp)
			{
				 fseek(fpbmp, 10L, SEEK_SET);
				 fread(&OffSet, sizeof(char), 4, fpbmp);
				 //printf("The Header Part is of length %d.\n", OffSet);
			}


			/* To get the width and height of the bmp file */
			void BmpWidthHeight(FILE* fpbmp)
			{
				 fseek(fpbmp, 18L, SEEK_SET);
				 fread(&width, sizeof(char), 4, fpbmp);
				 fseek(fpbmp, 22L, SEEK_SET);
				 fread(&height, sizeof(char), 4, fpbmp);
				 //printf("The Width of the bmp file is %ld.\n", width);
				// printf("The Height of the bmp file is %ld.\n", height);
			}

//This part is BMP=============================================================================================================
