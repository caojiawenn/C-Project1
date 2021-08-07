// 加减法练习
// 输出10道题，给出答错题目的个数 以及 正确答案，以及分数。10道题，一题10分，总分100分。

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct params{
    int a;
    int b;
    int ans;
    int right=-1; // -1表示用户回答正确，否则为正确答案。
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

params additive(){
    params p;
    p.op='+';
    p.a = rand()%101; // 0-100
    int gap = 100 - p.a; // 0-100
    p.b = rand()%(gap+1); // a+gap<=100,  b: 0-gap,  a + b <= 100
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

params sub(){
    params p;
    p.op='-';
    p.a = rand()%101; // 0-100
    p.b = rand()%p.a; // a<=100,  b < a
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

int main(int argc, char **argv)
{
    int n=0;
    int ques_number=0;
    params anser[1000]; // 最多100道
    int false_num = 0;
    
    std::cout << "Please enter the number of questions(up to 1000):\n";
    std::cin >> ques_number;
    
	std::cout <<"Exercise begining.  Please answer carefully!\n";
    
    
    // rand ：a + rand() % (b-a+1) 
    // 设置随机数种子, 利用时间来设置，保证间隔一秒以上，得到的随机数都不一样
    srand(time(0));
    
    
    // 0 1随机数，决定是加法还是减法
    int f1=rand()%2;
    while( n < ques_number ){
        cout << "N0." << n+1 <<endl;
        // 加法
        if ( f1 ){
            anser[n] = additive();
        }
        // 减法
        else{
            anser[n] = sub();
        }
        
        f1=rand()%2;
        n++;
    }
    
    // 输出结果
    cout << "\n\n*********************************************\nthe results are as follows\n*********************************************\n";
    for(auto &ans : anser){
        if(ans.right != -1){
            false_num++;
            ans.print();
        }
    }

    float si = 100.0/ques_number;
    cout << "\n\n--------------------------------------------------------\n";
    cout << "You got "<<(ques_number-false_num)<<" questions right, and " << false_num << " wrong." << endl;
    cout.setf(ios::fixed);
    cout << "Total score is 100, you get " << setprecision(2) << (ques_number-false_num)*si << ".\n";
    cout << "--------------------------------------------------------" << endl;
    system("Pause");
	return 0;
}