//
//  main.cpp
//  DS_4.3
//
//  Created by Walter Mitty on 2018/5/19.
//  Copyright © 2018年 Walter Mitty. All rights reserved.
//

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
typedef char *STRING;      //定义新的字符串类型，即指向字符的指针
struct strheadlist{
    /*定义指向字符串的字针数组，并存放各字符串的串名（串名也用字符串来表示），及当前堆中串的数目*/
    STRING strhead[100];
    STRING strname[100];
    int curnum;
};
struct result{
    /*定义命令行编译以后形成的命令及参数等数据*/
    int num;
    int nametype[6];
    STRING str[6];
};
struct strheadlist head;
char cmd[40][80];
char ch[80];
int strtoint(STRING s){        //将字符串转换成整数常量
    int i=0;
    int total=0;
    while(s[i]!='\0'){
        total=total*10+s[i]-48;
        i++;
    }
    return(total);
}
int lookup(STRING s){
    /*查找串表中是否存在串名所对应的字符串，如存在则返回所对应的位置，否则返回-1*/
    int i;
    int look=-1;
    for(i=0;i<head.curnum;i++)
        if(strcmp(head.strname[i],s)==0){
            look=i;
            break;
        }
    if(look==head.curnum)
        look=-1;
    return(look);
}
struct result cmdsyna(int row){    //对输入的命令行进行编译
    int i;
    struct result res;
    char c;
    int word=0,start;
    res.num=-1;
    for(i=0;(c=cmd[row][i])!= '\0';i++){
        if(c==' '){
            word=0;
            cmd[row][i]= '\0';
        }
        else
            if(word==0){
                //出现了一个新的参数，将分离出的各参数以及命令动词放置于参数表中
                res.num++;
                start=i;
                word=1;
                res.str[res.num]=&cmd[row][start];
                if (res.num==0)
                    res.nametype[res.num]=1;
                    else
                        if(cmd[row][start]==39){
                            cmd[row][start]= '\0';
                            res.str[res.num]=&cmd[row][start+1];
                            res.nametype[res.num]=2;
                        }
                        else{
                            if(cmd[row][start]>= '0'&&cmd[row][start]<= '9')
                                res.nametype[res.num]=3;
                                else
                                    res.nametype[res.num]=4;
                                    }
            }
            else{
                if(res.nametype[res.num]==2&&c==39)
                    cmd[row][i]= '\0';        //处理参数中字符串常量
                    if(res.nametype[res.num]==3 &&(c<'0'||c>'9'))
                        cmd[row][i]= '\0';        //处理参数中整数常量
                        }
    }
    return(res);
}
int length(STRING s){
    return(strlen(s));
}
int index(STRING s,STRING t,int start){
    /*从串S起始置START开始查找串T，如找到，则返回第一次出现的位置，否则返回-1*/
    int i,j;
    if((start<0)||(start+length(t)>length(s))||(length(t)==0))
        return(-1);
    else{
        i=start;
        j=0;
        while(i<length(s)&&j<length(t)){
            if(s[i]==t[j]){
                i++;
                j++;
            }
            else{
                i=i-j+1;
                j=0;
            }
        }
    }
    if(j==length(t))
        return(i-length(t));
    else
        return(-1);
}
void substr(STRING s,int start,int len,STRING v){
    /*为新串开辟新的空间，并将从串S中START起始位置起取LEN长度的子串存放起来，把新串的串名和首地址存放于串表中*/
    int i;
    //char ch[80];
    if(start<0&&start>=length(s))
        printf("Cannot be substr!!!\n");
    else{
        if(len>=1&&len<=length(s)-start){
            head.strname[head.curnum]=v;
            head.strhead[head.curnum]=ch;
            for(i=0;i<len;i++)
                ch[i]=s[start+i];
            ch[i]= '\0';
            head.curnum++;
            printf("The string %s : %s\n",v,ch);
        }
        else
            printf("Cannot be substr!!!\n");
    }
}
void concat(STRING s,STRING t,STRING v){
    /*为新串开辟新的空间，并将两串连接起来存放起来，并输出连接后的字符串，将新串的串名和首地址存放到串表中*/
    int i,j;
    //char ch[80];
    head.strname[head.curnum]=v;
    head.strhead[head.curnum]=ch;
    for(i=0;s[i]!='\0';i++)
        ch[i]=s[i];
    for(j=i,i=0;t[i]!='\0';i++,j++)
        ch[j]=t[i];
    ch[j]='\0';
    head.curnum++;
    printf("The string %s : %s\n",v,ch);
}
int equal(STRING s,STRING t){
    /*比较两串是否相等，如相等则返加整数1，否则返回0*/
    if(strcmp(s,t)==0)
        return 1;
    else
        return 0;
}
void assign(STRING s,STRING t){
    /*将字符串s所指向的字符串的首地址和新串t的名称存入于串表相应的位置上，并输出赋值后的字符串*/
    int look1,look2;
    if((look1=lookup(t))==-1)
        printf("The string %s is not found!\n",t);
    else{
        if((look2=lookup(s))==-1){
            head.strhead[head.curnum]=head.strhead[look1];
            head.strname[head.curnum]=s;
            head.curnum++;
        }
        else{
            head.strhead[look1]=head.strhead[look2];
        }
        printf("The string %s : %s\n",s,head.strhead[look1]);
    }
}
void creat(STRING s,STRING ss){
    /*将字符串常量的首地址和串的名称存放于串表相应的位置上，并输出新建后的字符串*/
    head.strhead[head.curnum]=ss;
    head.strname[head.curnum]=s;
    head.curnum++;
    printf("The string %s : %s\n",s,ss);
}
int main(){
    struct result comm;
    int row=0,i;
    char c;
    head.curnum=0;
    while(1){        //重复输入并处理相应命令
        printf("CMD>");
        for(i=0;(c=getchar())!='\n';i++)
            cmd[row][i]=c;
        cmd[row][i]= '\0';
        comm=cmdsyna(row);        //对各命令动词进行判数并作参数分析
        if(strcmp(comm.str[0],"creat")==0){    //字符串创建
            if(comm.num!=2)
                printf("Parameters is wrong!\n");
            else
                if(lookup(comm.str[1])!=-1)
                    printf("String %s cannot be creat!\n");
                else{
                    if(comm.nametype[1]==4&&comm.nametype[2]==2)
                        creat(comm.str[1],comm.str[2]);
                }
        }
        else
            if(strcmp(comm.str[0],"assign")==0){    //字符串赋值
                if(comm.num!=2)
                    printf("Parameters is wrong!\n");
                else
                    assign(comm.str[1],comm.str[2]);
            }
            else
                if(strcmp(comm.str[0],"equal")==0){    //字符串判等
                    if(comm.num!=2)
                        printf("Parameters is wrong!\n");
                    else{
                        if(lookup(comm.str[1])==-1||lookup(comm.str[2])==-1)
                            printf("String %s or %s is not found!\n",comm.str[1],comm. str[2]);
                        else{
                            if(equal(head.strhead[lookup(comm.str[1])],head.strhead[lookup(comm.str[2])])==1)
                                printf("Equal!!!\n");
                            else
                                printf("Not equal!!!\n");
                        }
                    }
                }
                else
                    if(strcmp(comm.str[0],"length")==0){    //字符串求长
                        if(comm.num!=1)
                            printf("Parameters is wrong!\n");
                        else{
                            if(lookup(comm.str[1])==-1)
                                printf("The string %s connot be found!\n");
                            else
                                printf("String %s :%s length is %d\n",comm.str[1],
                                       head.strhead[lookup(comm.str[1])],
                                       length(head.strhead[lookup(comm.str[1])]));
                        }
                    }
                    else
                        if(strcmp(comm.str[0],"concat")==0){
                            //字符串连接并形成新的字符串
                            if(comm.num!=3)
                                printf("Parameters is wrong!\n");
                            else{
                                if(lookup(comm.str[1])==-1||lookup(comm.str[2])==-1)
                                    printf("The string %s or %s is not found!\n",
                                           comm.str[1],comm.str[2]);
                                else
                                    if(lookup(comm.str[3])!=-1)
                                        printf("String %s connot be creat!\n",comm.str[3]);
                                    else
                                        concat(head.strhead[lookup(comm.str[1])],
                                               head.strhead[lookup(comm.str[2])],comm.str[3]);
                            }
                        }
                        else
                            if(strcmp(comm.str[0],"substr")==0){
                                //取字符串子串，并形成新的字符串
                                if(comm.num!=4)
                                    printf("Parameters wrong!\n");
                                else{
                                    if(lookup(comm.str[1])==-1)
                                        printf("String %s is not found!\n",
                                               comm.str[1]);
                                    else{
                                        if(lookup(comm.str[4])!=-1)
                                            printf("String %s connot be creat!\n",
                                                   comm.str[4]);
                                        else{
                                            int start,len;
                                            start=strtoint(comm.str[2]);
                                            len=strtoint(comm.str[3]);
                                            substr(head.strhead[lookup(comm.str[1])],
                                                   start,len,comm.str[4]);
                                        }
                                    }
                                }
                            }
                            else
                                if(strcmp(comm.str[0],"index")==0){
                                    //字符串定位
                                    if(comm.num!=3)
                                        printf("Parameters wrong!\n");
                                    else{
                                        if(lookup(comm.str[1])==-1||lookup(comm.str[2])==-1)
                                            printf("String %s or %s is not found!\n",
                                                   comm.str[1],comm.str[2]);
                                        else{
                                            int start,flag=-1;
                                            start=strtoint(comm.str[3]);
                                            flag=index(head.strhead[lookup(comm.str[1])],
                                                       head.strhead[lookup(comm.str[2])],start);
                                            if(flag==-1)
                                                printf("String %s  start %d,String %s is not index!!!\n",
                                                       comm.str[1],start,comm.str[2]);
                                            else
                                                printf("String %s start %d,String %s is  index %d!!!\n",
                                                       comm.str[1],start,comm.str[2],flag);
                                        }
                                    }
                                }
                                else
                                    if(strcmp(comm.str[0],"quit")==0){
                                        //退出演示系统
                                        printf("Bye Bye!\n");
                                        break;
                                    }
                                    else
                                        printf("Bad filename or no command!\n");
        //错误命令动词提示
        row++;
    }
}

