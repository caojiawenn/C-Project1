// 加减法练习
// 输出10道题，给出答错题目的个数 以及 正确答案，以及分数。10道题，一题10分，总分100分。

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <limits>
#include <time.h>

using namespace std;

// 用于将字符串转换为int
enum Status{kValid = 0,kInvalid};
int g_nStatus = kValid;//标志是否到达字符串结束符'\0' 

struct params{
    int a;
    int b;
    float ans;
    float right=-1; // -1表示用户回答正确，否则为正确答案。
    char op;
    
    void print(){
        cout << a << " "  << op << " "  << b  << " = " << ans << ";  ";
        if(right!=-1){
            cout<<"Wrong ! \nThe right anser is: "<< right << endl;
        }
        else{
            cout<<"correct !"<<endl;
        }
    }
};

params additive(int buttom,int top){
    params p;
    p.op='+';
    p.a = buttom + rand()%(top-buttom+1); // top -> buttom
    p.b = buttom + rand()%(top-buttom+1); // a+gap<=top,  b: 0-gap,  a + b <= top
    cout << p.a << " + " << p.b << " = ";
    cin >> p.ans;
    cout << "\n";
    
    int right = p.a+p.b;
    if( right != p.ans){
        p.right = right;
    }
//    p.print();
    return p;
}

params sub(int buttom,int top){
    params p;
    p.op='-';
    p.a = buttom + rand()%(top-buttom+1); // top -> buttom
    p.b = buttom + rand()%(p.a-buttom+1); // a<=top,  bottum <= b <= a
    cout << p.a << " - " << p.b << " = ";
    cin >> p.ans;
    cout << "\n";
    
    int right = p.a-p.b;
    if( right != p.ans){
        p.right = right;
    }
    
//    p.print();
    return p;
}

params divition(int buttom, int top){
    params p;
    p.op='/';
    p.a=buttom + rand()%(top-buttom+1);
    p.b=buttom + rand()%(p.a-buttom+1);
    if(p.b==0) p.b=1;
    cout << p.a << " / "<<p.b<<" = ";
    cin >> p.ans;
    cout <<"\n";

    float r=(float)p.a/(float)p.b*100.0;
    float right = round(r)/100.0;
    if(right != p.ans){
        p.right=right;
    }
    // p.print();
    return p;
}


params multi(int buttom, int top){
    params p;
    p.op='*';
    p.a=buttom + rand()%(top-buttom+1);
    p.b=buttom + rand()%(top-buttom+1);
    cout << p.a << " * "<<p.b<<" = ";
    cin >> p.ans;
    cout <<"\n";

    int right = p.a*p.b;
    if(right != p.ans){
        p.right=right;
    }
    // p.print();
    return p;
}

int check_flag(char ans){
    if(ans != 'y' && ans !='n'){
        cout << "Input y or n (y is yes and n is no): "<<endl;
        return 0;
    }
    else{
        return 1;
    }
}

int check_number(int num){
    if(num>=0) return 1;
    cout << "Input an integer num lager than 0: "<<endl;
    return 0;
}

// 处理用户输入的数字
int StrToInt(const char* str){
    g_nStatus = kInvalid;
    long long num = 0;
    if (str != NULL){
        const char* digit = str;
        bool minus = false;
        if (*digit == '+')
            digit++;
        else if (*digit == '-'){
            digit++;
            minus = true;
        }
        while(*digit != '\0'){
            if (*digit >= '0' && *digit <= '9'){//字符是表示数字的字符 
                num = num * 10 + (*digit - '0');
                if (num > std::numeric_limits<int>::max()){
                    num = 0;
                    break;
                }
                digit++;
            }
            else{//字符是其他不表示数字的字符 
                num = -1;
                break;
            }
        }
        if (*digit == '\0'){
            g_nStatus = kValid;
        if (minus)
            num = 0 - num;
        }
    }
    return num;
}


int main(int argc, char **argv)
{
    int n=0;
    char mul_div_flag = 'n';
    char ques_numberc[100];
    int ques_number;
    params anser[50]; // 最多50道
    int false_num = 0;
    char buttomc[100],topc[100];
    int buttom,top;

    
    std::cout << "Please enter the number of questions(up to 50):\n";
    while(1){
        std::cin >> ques_numberc;
        ques_number=StrToInt(ques_numberc);
        if(ques_number<=0 || ques_number>50){
            cout << "Please input a integer number which is lagger than 0 and less then 50.\n";
        }
        else {
            break;
        }
    }

    std::cout << "would you like to do  multiplication and division\n(The precision of the div result is two decimal places, eg 2.87)?(y or n)\n";
    while(1){
        std::cin >> mul_div_flag;
        if(check_flag(mul_div_flag)) break;
    }

    std::cout << "Please tell us the operation range(bottom to top):\nbuttom is ";
    while(1){
        std::cin >> buttomc;
        buttom=StrToInt(buttomc);
        if(check_number(buttom)) break;
    }
    std::cout << "\ntop is ";
    while(1){
        std::cin >> topc;
        top=StrToInt(topc);
        if(check_number(top)) break;
    }
    if(top <= buttom){
        cout<<"\n\n** Top cannot be greater than or equal to buttom."<<endl;
        system("Pause");
        exit(0);
    }


    std::cout <<"\n\nExercise begining.  Please answer carefully!\n";
    
    
    // rand ：a + rand() % (b-a+1) 
    // 设置随机数种子, 利用时间来设置，保证间隔一秒以上，得到的随机数都不一样
    srand(time(0));
    
    
    // 0 1 2 3随机数，决定 加减乘除
    int f_md;
    if(mul_div_flag == 'y') {
        f_md=4;
    }
    else{
        f_md=2;
    }
    int f1=rand()%f_md;
    clock_t start,end,min_time=NULL,tmp,sum_clock=0;
    cout.setf(ios::fixed);
    while( n < ques_number ){
        cout << "N0." << n+1 <<endl;
        start=clock();
        switch(f1){
            case 0:
                anser[n] = additive(buttom,top);
                break;
            case 1:
                anser[n] = sub(buttom,top);
                break;
            case 2:
                anser[n] = multi(buttom,top);
                break;
            case 3:
                anser[n] = divition(buttom,top);
                break;

        }
        end=clock();
        tmp=(end-start);
        if(!min_time){
            min_time=tmp;
        }
        else if(min_time>tmp){
            min_time=tmp;
        }
        sum_clock=tmp+sum_clock;
        cout<<"Use "<< setprecision(2)<<(float)tmp/(float)CLOCKS_PER_SEC<<"s.\n";
        f1=rand()%f_md;
        n++;
    }
    
    // 输出结果
    cout << "\n\n***************************************the results are as follows*************************************\n";
    for(auto &ans : anser){
        if(ans.right != -1){
            false_num++;
            ans.print();
        }
    }

    float si = 100.0/ques_number;
    cout << "\n\n--------------------------------------------------------\n";
    cout << "You got "<<(ques_number-false_num)<<" questions right, and " << false_num << " wrong." << endl;
    cout << "Total score is 100, you get " << setprecision(2) << (ques_number-false_num)*si << ".\n";
    cout << "The average time you spend on a question is "<< setprecision(2) <<(float)sum_clock/(float)ques_number/(float)CLOCKS_PER_SEC;
    cout <<"s, and the minimum time is "<< setprecision(2) <<(float)min_time/(float)CLOCKS_PER_SEC<<"s."<<endl;
    cout << "--------------------------------------------------------" << endl;
    system("Pause");
	return 0;
}