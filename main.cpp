#include "Tool.h"

//打印
void Show(double* x,int num,double x_right){
    cout<<"迭代结束\n根的迭代过程为:"<<endl;
    for (int i = 0; i < num; ++i) {
        cout<<"第"<<i<<"次迭代:x="<<x[i]<<endl;
    }
    cout<<"准确值约为:"<<x_right<<endl;
}

//y=e^-x
double fun_e_x(double x) {
    return exp(-x);
}
//y':y=e^-x
double fun_e_x_derivative(double x) {
    return -exp(-x);
}

//y=x^3-x-1
double fun_x3x1(double x){
    return pow(x,3)-x-1;
}
//y':y=x^3-x-1
double fun_x3x1_derivative(double x){
    return 3* pow(x,2)-1;
}

//y=e^x-2
double fun_ex_2(double x) {
    return exp(x)-2;
}
//y':y=e^x-2
double fun_ex_2_derivative(double x) {
    return exp(x);
}

//普通迭代算法
void NormalIteration() {
    cout << "\n-------普通迭代算法------" << endl;
    cout << "本环节将对(x=e^-x)的根进行普通迭代求解" << endl;
    double x[50];
    cout << "请输入初值x0:";
    x[0] = inputDouble();
    cout << "请输入精度ε:";
    double ep = inputDouble();
    cout << "开始迭代..."<<endl;

//  double x_right = 0.5671432904178;//真正的准确值
    double x_right = 0.567143;//计算的准确值

    int i = 1;
    do {
        x[i] = fun_e_x(x[i-1]);;
        i++;
    } while (i < 100 && fabs(x[i-1]-x[i-2])>ep);
    if (i>=50){
        cout<<"数据迭代次数过多，请尝试先缩小初值的范围。"<<endl;
    } else{
        Show(x,i, x_right);
    }
}

//埃特金算法
void Aitken(){
    cout<<"\n---------埃特金算法--------"<<endl;
    cout<<"本环节将对(x=e^-x)的根进行埃特金算法迭代求解"<<endl;
    double x[50];
    cout << "请输入初值x0:";
    x[0] = inputDouble();
    cout << "请输入精度ε:";
    double ep = inputDouble();
    cout << "开始迭代..."<<endl;

    //  double x_right = 0.5671432904178;//真正的准确值
    double x_right = 0.567143;//计算的准确值
    double tmpX1 = x[0];
    double tmpX2 = x[0];

    int i = 1;
    do {
        cout<<"\n第"<<i<<"次迭代:"<<endl;
        tmpX1 = fun_e_x(x[i-1]);
        cout<<"x~:"<<tmpX1<<endl;
        tmpX2 = fun_e_x(tmpX1);
        cout<<"x-:"<<tmpX2<<endl;
        x[i] = tmpX2 - (pow((tmpX2-tmpX1),2))/(tmpX2-2*tmpX1+x[i-1]);
        cout<<"x:"<<x[i]<<endl;
        i++;
    } while (i < 100 && fabs(x[i-1]-x[i-2])>ep);
    if (i>=50){
        cout<<"数据迭代次数过多，请尝试先缩小初值的范围。"<<endl;
    } else{
        Show(x,i, x_right);
    }
}

//牛顿法
double fun_Newton(double x,double (*fun)(double),double (*derivative)(double)){
    return x-fun(x)/derivative(x);
}
//牛顿法
void Newton(){
    cout<<"\n----------牛顿法---------"<<endl;
    cout<<"本环节将对(e^x-2=0和x^3-x-1=0)的根进行牛顿法迭代求解"<<endl;
    cout<<"先对(e^x-2=0)的根进行牛顿法迭代求解:"<<endl;
    double x[50];
    cout << "请输入初值x0:";
    x[0] = inputDouble();
    cout << "请输入精度ε:";
    double ep = inputDouble();
    cout << "开始迭代..."<<endl;

    //  double x_right = 0.6931476715177;//真正的准确值
    double x_right = 0.693148;//计算的准确值

    int i = 1;
    do {
        x[i] = fun_Newton(x[i - 1], fun_ex_2, fun_ex_2_derivative);
        i++;
    } while (i < 100 && fabs(x[i-1]-x[i-2])>ep);
    Show(x,i, x_right);
    cout<<"\n再对(x^3-x-1=0)的根进行牛顿法迭代求解"<<endl;
    cout << "请输入初值x0:";
    x[0] = inputDouble();
    cout << "开始迭代..."<<endl;
    //  x_right = 1.3247179572447;//真正的准确值
    x_right = 1.324717;//计算的准确值

    i = 1;
    do {
        x[i] = fun_Newton(x[i-1],fun_x3x1,fun_x3x1_derivative);
        i++;
    } while (i < 100 && fabs(x[i-1]-x[i-2])>ep);
    if (i>=50){
        cout<<"数据迭代次数过多，请尝试先缩小初值的范围。"<<endl;
    } else{
        Show(x,i, x_right);
    }
}

//开方公式
double fun_sqrt(double x,double c){
    return 0.5*(x+c/x);
}
//开方公式
void Square(){
    cout<<"\n----------开方公式---------"<<endl;
    cout<<"本环节将对(x^2-c=0(x>0))的根进行开方公式迭代求解"<<endl;
    double x[50],ep;
    int c;
    cout << "请输入初整数c:";
    c = inputInt();
    cout << "请输入初值x0:";
    x[0] = inputDouble();
    cout << "请输入精度ε:";
    ep = inputDouble();
    cout << "开始迭代..."<<endl;

    double x_right = sqrt(c);//计算的准确值

    int i = 1;
    do {
        x[i] = fun_sqrt(x[i-1],c);
        i++;
    } while (i < 100 && fabs(x[i-1]-x[i-2])>ep);
    if (i>=50){
        cout<<"数据迭代次数过多，请尝试先缩小初值的范围。"<<endl;
    } else{
        Show(x,i, x_right);
    }
}

//牛顿下山法
void NewtonDownHill(){
    cout<<"\n----------牛顿下山法---------"<<endl;
    cout<<"本环节将对(x^3-x-1=0)的根进行牛顿下山法迭代求解"<<endl;
    double x[50];
    cout << "请输入初值x0:";
    x[0] = inputDouble();
    cout << "请输入精度ε:";
    double ep = inputDouble();
    cout << "开始迭代..."<<endl;

    // double x_right = 1.3247179572447;//真正的准确值
    double x_right = 1.324717;//计算的准确值

    int i = 1;
    do {
        double x2 = fun_Newton(x[i-1],fun_x3x1,fun_x3x1_derivative);
        double lamda = 1.0;
        double x3 = x2;
        while (fabs(fun_x3x1(x3))>= fabs(fun_x3x1(x[i-1]))){
            lamda/=2.0;
            x3 = lamda*x2+(1 - lamda)*x[i-1];
        }
        x[i]=x3;
        i++;
    } while (i < 100 && fabs(x[i-1]-x[i-2])>ep);
    if (i>=50){
        cout<<"数据迭代次数过多，请尝试先缩小初值的范围。"<<endl;
    } else{
        Show(x,i, x_right);
    }
}

//弦截法
double fun_secant(double x0,double x,double (*fun)(double)){
    return x-(fun(x)/(fun(x)-fun(x0)))*(x-x0);
}
//弦截法
void Secant(){
    cout<<"\n----------弦截法---------"<<endl;
    cout<<"本环节将对(e^x-2=0)的根进行弦截法迭代求解"<<endl;
    double x[50];
    cout << "请输入初值x0:";
    x[0] = inputDouble();
    cout << "请输入第二个初值x1:";
    x[1] = inputDouble();
    cout << "请输入精度ε:";
    double ep = inputDouble();
    cout << "开始迭代..."<<endl;

    //  double x_right = 0.6931476715177;//真正的准确值
    double x_right = 0.693148;//计算的准确值

    int i = 2;
    do {
        x[i] = fun_secant(x[0], x[i - 1], fun_ex_2);
        i++;
    } while (i < 100 && fabs(x[i-1]-x[i-2])>ep);
    if (i>=50){
        cout<<"数据迭代次数过多，请尝试先缩小初值的范围。"<<endl;
    } else{
        Show(x,i, x_right);
    }
}

//快速弦截法
void FastSecant(){
    cout<<"\n----------快速弦截法---------"<<endl;
    cout<<"本环节将对(e^x-2=0)的根进行弦截法迭代求解"<<endl;
    double x[50];
    cout << "请输入初值x0:";
    x[0] = inputDouble();
    cout << "请输入第二个初值x1:";
    x[1] = inputDouble();
    cout << "请输入精度ε:";
    double ep = inputDouble();
    cout << "开始迭代..."<<endl;

    //  double x_right = 0.6931476715177;//真正的准确值
    double x_right = 0.693148;//计算的准确值

    int i = 2;
    do {
        x[i] = fun_secant(x[i-2], x[i - 1], fun_ex_2);
        i++;
    } while (i < 100 && fabs(x[i-1]-x[i-2])>ep);
    if (i>=50){
        cout<<"数据迭代次数过多，请尝试先缩小初值的范围。"<<endl;
    } else{
        Show(x,i, x_right);
    }
}

int main() {
    try {
        cout << "这里是非线性方程求根问题的求解" << endl;
        cout << "您可以随时输入'q'来结束当前任务" << endl;
        cout << "----------请选择模式--------" << endl;
        cout << "1.普通迭代算法" << endl;//e^-x=x
        cout << "2.埃特金算法" << endl;//e^-x=x
        cout << "3.牛顿法" << endl;//e^x-2=0;x^3-x-1=0
        cout << "4.开方公式" << endl;//sqr(x)
        cout << "5.牛顿下山法" << endl;//x^3-x-1=0
        cout << "6.弦截法" << endl;//e^x-2=0
        cout << "7.快速弦截法" << endl;//e^x-2=0
        cout << "--------------------------" << endl;
        cout << "请选择:";
        int choice = inputInt();
        switch (choice) {
            case 1:
                NormalIteration();
                break;
            case 2:
                Aitken();
                break;
            case 3:
                Newton();
                break;
            case 4:
                Square();
                break;
            case 5:
                NewtonDownHill();
                break;
            case 6:
                Secant();
                break;
            case 7:
                FastSecant();
                break;
            default:
                throw myExpection("选择错误");
                break;
        }
    }catch(myExpection e){
        cout<<e.what()<<endl;
    }
    return 0;
}
