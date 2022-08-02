#include <stdio.h>
#include <stdlib.h>

void tilt(int** arr,char side,int ri,int rj,int bi,int bj,int cnt) {
    if(side=='l') {
        while(arr[bi-1][bj]!='#') {
            bi--;
            if(arr[bi][bj]=='O') {
                cnt=-1;
                break;
            }
        }
        while(arr[ri-1][rj]!='#') {
            arr[ri][rj]='#';
            ri--;
            if(arr[ri][rj]=='O') {
                cnt=1;
                break;
            }
        }
        
        cnt++;
        
    }
    else if(side=='r') {
        
    }
}

int main()
{
    int wid, len;
    int ri,rj;
    int bi,bj;
    int side=0;
    int cnt=0;
    scanf("%d %d",&wid,&len);
    char **arr;
    arr=(char**)malloc(sizeof(char*)*len);
    for(int i=0;i<len;i++) {
        arr[i]=(char*)malloc(sizeof(char)*(wid+1));
    }
    for(int i=0;i<len;i++) {
        for(int j=0;j<wid+1;j++) {
            scanf("%c",&arr[i][j]);
            if(arr[i][j]=='R') {
                ri=i;
                rj=j;
            }
            else if(arr[i][j]=='B') {
                bi=i;
                bj=j;
            }
        }
    }
    
    printf("%d %d\n%d %d\n",ri,rj,bi,bj);
    
    if(arr[ri-1][rj]=='O') {
        tilt(arr,'l',ri,rj,bi,bj,cnt);
    }
    else if(arr[ri+1][rj]=='O') {
        tilt(arr,'r',ri,rj,bi,bj,cnt);
    }
    else if(arr[ri][rj-1]=='O') {
        tilt(arr,'d',ri,rj,bi,bj,cnt);
    }
    else if(arr[ri][rj+1]=='O') {
        tilt(arr,'u',ri,rj,bi,bj,cnt);
    }
    
    else {
        while(1) {
            if(arr[ri-1][rj]=='.') {
                tilt(arr,'l',ri,rj,bi,bj);
            }
            else if(arr[ri+1][rj]=='.') {
                tilt(arr,'r',ri,rj,bi,bj);
            }
            else if(arr[ri][rj-1]=='.') {
                tilt(arr,'d',ri,rj,bi,bj);
            }
            else if(arr[ri][rj+1]=='.') {
                tilt(arr,'u',ri,rj,bi,bj);
            }
        }
    }
    
    while(cnt<10) {
        if(arr[])
    }
    
    
    free(arr);
    return 0;
}
