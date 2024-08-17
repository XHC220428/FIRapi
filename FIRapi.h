#include<cmath>
struct FIRapi{
	int _Map[17][17];
	struct _score{
		bool Flag;
		unsigned int Value;
		void Clear(){Flag=false,Value=0;}
		operator +=(short v){
			if(v>=0) Value+=v;
			else Flag=true;
		}
	}_Score[17][17];
	int _FinalX,_FinalY,_FinalNum;
	bool _FinalFlag;
	void Clear(){
		for(int i=0;i<17;i++) for(int j=0;j<17;j++) _Map[i][j]=0;
	}
	bool Input(int Coordinate1=-1,int Coordinate2=-1,int Flag=0){
		if(Coordinate1<0||Coordinate1>16) return false;
		if(Coordinate1<0||Coordinate1>16) return false;
		if(Flag<-1||Flag>1) return false;
		_Map[Coordinate1][Coordinate2]=Flag;
	}
	int Output(int Flag=0){
		if(_FinalX==-1||_FinalY==-1) return -1;
		switch(Flag){
			case 0:
				if(_Score[_FinalX][_FinalY].Flag) return 0x7fffff;
				else return _Score[_FinalX][_FinalY].Value;
			case 1:
				return _FinalX;
			case 2:
				return _FinalY;
		}
		return -1;
	}
	void _AnalyzeLayer1(){
		for(int i=2;i<=14;i++){
			for(int j=2;j<=14;j++){
				if(_Map[i][j]>=0) continue;
				if(_Map[i-1][j]==-1&&_Map[i+1][j]==-1&&_Map[i-2][j]!=1&&_Map[i+2][j]!=1) _Score[i-2][j]+=-1,_Score[i+2][j]+=-1;
				if(_Map[i][j-1]==-1&&_Map[i][j+1]==-1&&_Map[i][j-2]!=1&&_Map[i][j+2]!=1) _Score[i][j-2]+=-1,_Score[i][j+2]+=-1;
				if(_Map[i-1][j-1]==-1&&_Map[i+1][j+1]==-1&&_Map[i-2][j-2]!=1&&_Map[i+2][j+2]!=1) _Score[i-2][j-2]+=-1,_Score[i+2][j+2]+=-1;
				if(_Map[i-1][j+1]==-1&&_Map[i+1][j-1]==-1&&_Map[i-2][j+2]!=1&&_Map[i+2][j-2]!=1) _Score[i-2][j+2]+=-1,_Score[i+2][j-2]+=-1;
			}
		}
		for(int i=1;i<=15;i++){
			for(int j=1;j<=15;j++){
				if(_Map[i][j]!=0) continue;
				if(_Map[i-1][j]==-1&&_Map[i+1][j]==-1){
					if(i>=3&&_Map[i-2][j]==-1&&_Map[i-3][j]!=1&&_Map[i+2][j]!=1) _Score[i][j]+=-1;
					if(i<=13&&_Map[i+2][j]==-1&&_Map[i+3][j]!=1&&_Map[i-2][j]!=1) _Score[i][j]+=-1;
				}
				if(_Map[i][j-1]==-1&&_Map[i][j+1]==-1){
					if(j>=3&&_Map[i][j-2]==-1&&_Map[i][j-3]!=1&&_Map[i][j+2]!=1) _Score[i][j]+=-1;
					if(j<=13&&_Map[i][j+2]==-1&&_Map[i][j+3]!=1&&_Map[i][j-2]!=1) _Score[i][j]+=-1;
				}
				if(_Map[i-1][j-1]==-1&&_Map[i+1][j+1]==-1){
					if(i>=3&&j>=3) if(_Map[i-2][j-2]==-1&&_Map[i-3][j-3]!=1&&_Map[i+2][j+2]!=1) _Score[i][j]+=-1;
					if(i<=13&&j<=13) if(_Map[i+2][j+2]==-1&&_Map[i+3][j+3]!=1&&_Map[i-2][j-2]!=1) _Score[i][j]+=-1;
				}
				if(_Map[i-1][j+1]==-1&&_Map[i+1][j-1]==-1){
					if(i>=3&&j<=13) if(_Map[i-2][j+2]==-1&&_Map[i-3][j+3]!=1&&_Map[i+2][j-2]!=1) _Score[i][j]+=-1;
					if(i<=13&&j>=3) if(_Map[i+2][j-2]==-1&&_Map[i+3][j-3]!=1&&_Map[i-2][j+2]!=1) _Score[i][j]+=-1;
				}
			}
		}
	}
	void _AnalyzeLayer3(){
		for(int i=2;i<=14;i++){
			for(int j=2;j<=14;j++){
				if(_Map[i][j]!=1) continue;
				if(_Map[i-1][j]==1&&_Map[i+1][j]==1&&_Map[i-2][j]!=-1&&_Map[i+2][j]!=-1) _Score[i-2][j]+=50,_Score[i+2][j]+=50;
				if(_Map[i][j-1]==1&&_Map[i][j+1]==1&&_Map[i][j-2]!=-1&&_Map[i][j+2]!=-1) _Score[i][j-2]+=50,_Score[i][j+2]+=50;
				if(_Map[i-1][j-1]==1&&_Map[i+1][j+1]==1&&_Map[i-2][j-2]!=1&&_Map[i+2][j+2]!=1) _Score[i-2][j-2]+=50,_Score[i+2][j+2]+=50;
				if(_Map[i+1][j-1]==1&&_Map[i-1][j+1]==1){
					if(i<=14&&j>=2) _Score[i+2][j-2]+=50;
					if(i>=2&&j<=14) _Score[i-2][j+2]+=50;
				}
			}
		} 
	}
	void _AnalyzeLayer4(){
		for(int i=0;i<=16;i++){
			for(int j=0;j<=16;j++){
				short Cnt=0;
				if(i>=1&&_Map[i-1][j]!=0) Cnt+=5;
				if(i<=15&&_Map[i+1][j]!=0) Cnt+=5;
				if(j>=1&&_Map[i][j-1]!=0) Cnt+=5;
				if(j<=15&&_Map[i][j+1]!=0) Cnt+=5;
				if(i>=1&&j>=1&&_Map[i-1][j-1]!=0) Cnt+=4;
				if(i>=1&&j<=15&&_Map[i-1][j+1]!=0) Cnt+=4;
				if(i<=15&&j>=1&&_Map[i+1][j-1]!=0) Cnt+=4;
				if(i<=15&&j<=15&&_Map[i+1][j+1]!=0) Cnt+=4;
				if(i>=2&&_Map[i-2][j]!=0) Cnt+=2;
				if(i<=14&&_Map[i+2][j]!=0) Cnt+=2;
				if(j>=2&&_Map[i][j-2]!=0) Cnt+=2;
				if(j<=14&&_Map[i][j+2]!=0) Cnt+=2;
				_Score[i][j]+=Cnt;
			}
		}
		for(int i=0;i<=16;i++){
			for(int j=0;j<=16;j++){
				if(i>=2&&_Map[i-2][j]==1&&_Map[i-1][j]==1) _Score[i][j]+=3;
				if(i<=14&&_Map[i+2][j]==1&&_Map[i+1][j]==1) _Score[i][j]+=3;
				if(j>=2&&_Map[i][j-2]==1&&_Map[i][j-1]==1) _Score[i][j]+=3;
				if(j<=14&&_Map[i][j+2]==1&&_Map[i][j+1]==1) _Score[i][j]+=3;
				if(i>=2&&j>=2&&_Map[i-2][j-2]==1&&_Map[i-1][j-1]==1) _Score[i][j]+=3;
				if(i>=2&&j<=14&&_Map[i-2][j+2]==1&&_Map[i-1][j+1]==1) _Score[i][j]+=3;
				if(i<=14&&j>=2&&_Map[i+2][j-2]==1&&_Map[i+1][j-1]==1) _Score[i][j]+=3;
				if(i<=14&&j<=14&&_Map[i+2][j+2]==1&&_Map[i+1][j+1]==1) _Score[i][j]+=3;
			}
		}
		for(int i=1;i<=15;i++){
			for(int j=1;j<=15;j++){
				if(_Map[i-1][j]==1&&_Map[i+1][j]==1) _Score[i][j]+=4;
				if(_Map[i][j-1]==1&&_Map[i][j+1]==1) _Score[i][j]+=4;
				if(_Map[i-1][j-1]==1&&_Map[i+1][j+1]==1) _Score[i][j]+=4;
				if(_Map[i-1][j+1]==1&&_Map[i+1][j-1]==1) _Score[i][j]+=4;
			}
		}
		for(int i=0;i<=16;i++){
			for(int j=0;j<=16;j++){
				if(i>=2&&_Map[i-2][j]==-1&&_Map[i-1][j]==-1) _Score[i][j]+=3;
				if(i<=14&&_Map[i+2][j]==-1&&_Map[i+1][j]==-1) _Score[i][j]+=3;
				if(j>=2&&_Map[i][j-2]==-1&&_Map[i][j-1]==-1) _Score[i][j]+=3;
				if(j<=14&&_Map[i][j+2]==-1&&_Map[i][j+1]==-1) _Score[i][j]+=3;
				if(i>=2&&j>=2&&_Map[i-2][j-2]==-1&&_Map[i-1][j-1]==-1) _Score[i][j]+=3;
				if(i>=2&&j<=14&&_Map[i-2][j+2]==-1&&_Map[i-1][j+1]==-1) _Score[i][j]+=3;
				if(i<=14&&j>=2&&_Map[i+2][j-2]==-1&&_Map[i+1][j-1]==-1) _Score[i][j]+=3;
				if(i<=14&&j<=14&&_Map[i+2][j+2]==-1&&_Map[i+1][j+1]==-1) _Score[i][j]+=3;
			}
		}
		for(int i=1;i<=15;i++){
			for(int j=1;j<=15;j++){
				if(_Map[i-1][j]==-1&&_Map[i+1][j]==-1) _Score[i][j]+=4;
				if(_Map[i][j-1]==-1&&_Map[i][j+1]==-1) _Score[i][j]+=4;
				if(_Map[i-1][j-1]==-1&&_Map[i+1][j+1]==-1) _Score[i][j]+=4;
				if(_Map[i-1][j+1]==-1&&_Map[i+1][j-1]==-1) _Score[i][j]+=4;
			}
		}
	}
	void _Stat(){
		_FinalX=-1,_FinalY=-1,_FinalNum=0,_FinalFlag=false;
		for(int i=0;i<=16;i++){
			for(int j=0;j<=16;j++){
				if(_Map[i][j]!=0) continue;
				if(_FinalFlag==false){
					if(_Score[i][j].Flag) _FinalFlag=true,_FinalX=i,_FinalY=j;
					if(_Score[i][j].Value>_FinalNum) _FinalNum=_Score[i][j].Value,_FinalX=i,_FinalY=j;
				}else if(_Score[i][j].Value>_FinalNum&&_Score[i][j].Flag) _FinalNum=_Score[i][j].Value,_FinalX=i,_FinalY=j;
			}
		}
	}
	void APIrun(){
		for(int i=0;i<17;i++) for(int j=0;j<17;j++) _Score[i][j].Clear();
		_AnalyzeLayer1();
		_AnalyzeLayer3();
		_AnalyzeLayer4();
		_Stat();
	}
};
