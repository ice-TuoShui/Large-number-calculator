#include "widget.h"
#include "ui_widget.h"
#include <string>
#include <QGraphicsOpacityEffect>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("大数运算器");
    this->setWindowIcon(QIcon(QStringLiteral(":/Resources/images/Resources/images/bg.png")));
    //ui->frame->lower();
}

Widget::~Widget()
{
    delete ui;
}

class BigNum{
    private:
        int a[2001];
        int bigPlus(int a[],int b[],int c[]){
            bigSetzero(c);
            int temp=0;
            int len=a[0]>b[0]?a[0]:b[0];
            for(int i=1;i<=len;i++){
                int ha=a[i],hb=b[i],hc=c[i];
                int hh=ha+hb+hc;
                c[i]=(a[i]+b[i]+temp)%10;
                temp=(a[i]+b[i])/10;
                ha=a[i],hb=b[i],hc=c[i];
            }
            if(temp)len++;
            if(len>2000)
                return -1;
            c[len]+=temp;
            c[0]=len;
            return 0;
        }
        int bigCmp (int a[],int b[]){
            if(a[0]>b[0])
                return 1;
            else if(b[0]>a[0])
                return -1;
            else{
                for(int i=a[0];i>0;i--)
                    if(a[i]>b[i])
                        return 1;
                    else if(b[i]>a[i])
                        return -1;
                return 0;
            }
        }
        int bigSub (int a[],int b[],int c[]){
            bigSetzero(c);
            if(!a[0] || !b[0])
                return 0;
            int k=bigCmp(a,b);
            if(k==1){
                int temp=0;
                for(int i=1;i<=a[0];i++){
                    c[i]=a[i]-b[i]-temp;
                    temp=0;
                    if(c[i]<0){
                        c[i]+=10;
                        temp++;
                    }
                    int hh=c[i];
                    hh=c[i];
                }
                c[0]=a[0];
                while(!c[c[0]] && c[0]>0){
                    c[0]--;
                }
            }
            else if(k==-1){
                return-1;
            }
            return 0;
        }
        int bigMult (int a[],int b[],int c[]){
            bigSetzero(c);
            if(a[0]+b[0]-1>2000)
                return -1;
            for(int i=1;i<=b[0];i++){
                int temp=0;
                for(int j=1;j<=a[0];j++){

                    c[i+j-1]+=a[j]*b[i]+temp;
                    temp=c[i+j-1]/10;
                    c[i+j-1]%=10;
                }
                int k=i+a[0];
                if(k>2000&&temp)
                    return -1;
                while(temp){
                    c[k]+=temp;
                    temp=c[k]/10;
                    c[k]%=10;
                    k++;
                    if(k>2000&&temp)
                        return -1;
                }
            }
            c[0]=a[0]+b[0];
            while(!c[c[0]]&&c[0]>0)
                c[0]--;
            return 0;
        }
        int bigDiv (int a[],int b[],int c[]){
            bigSetzero(c);
            if(!b[0])
                return -1;
            if(bigCmp(a,b)==-1)
                return 0;
            if(bigCmp(a,b)==0){
                c[0]=1;
                c[1]=1;
                return 0;
            }
            int d[2001];
            bigCopy(a,d);
            int e[2001],f[2001],g[2001];
            memset(f,0,sizeof f);
            f[0]=a[0]-b[0]+1;
            f[f[0]]=1;
            while(bigCmp(d,b)>=0){
                bigMult(f,b,e);
                while(bigCmp(d,e)>=0){
                    bigSub(d,e,g);
                    bigCopy(g,d);
                    c[f[0]]++;
                }
                f[f[0]--]=0;
                f[f[0]]=1;
                if(f[0]<=0)break;
            }
            c[0]=a[0]-b[0]+1;
            while(!c[c[0]])
                   c[0]--;
            return 0;
        }
        int bigMod(int a[],int b[],int d[]){
            bigSetzero(d);
            if(!b[0])
                return -1;
            if(bigCmp(a,b)==-1){
                bigCopy(a,d);
                return 0;
            }
            if(bigCmp(a,b)==0){
                return 0;
            }
            int c[2001];
            bigCopy(a,d);
            int e[2001],f[2001],g[2001];
            memset(f,0,sizeof f);
            f[0]=a[0]-b[0]+1;
            f[f[0]]=1;
            while(bigCmp(d,b)>=0){
                bigMult(f,b,e);
                while(bigCmp(d,e)>=0){
                    bigSub(d,e,g);
                    bigCopy(g,d);
                    c[f[0]]++;
                }
                f[f[0]--]=0;
                f[f[0]]=1;
                if(f[0]<=0)break;
            }
            return 0;
        }
        int bigSetzero(int a[]){
            for(int i=2000;i>=0;i--)
                a[i]=0;
        }
        int bigCopy(int a[],int b[]){
            for(int i=2000;i>=0;i--)
                b[i]=a[i];
        }

    public:
        BigNum kuaiSuMi(BigNum a,BigNum e){
            a=a%(*this);
            e=e%(*this);
            BigNum b,c;
            b.a[0]=1;
            b.a[1]=1;
            c.a[0]=1;
            c.a[1]=2;
            while(e.a[0]){
                BigNum f=e%c;
                if(f.a[0]){
                    b=b*a;
                    b=b%(*this);
                }
                a=a*a;
                a=a%(*this);
                e=e/c;
            }
            return b;
        }
        BigNum kuaiSuMi(){
            BigNum E(rand());
            BigNum A(rand());
            BigNum b,c;
            b.a[0]=1;
            b.a[1]=1;
            c.a[0]=1;
            c.a[1]=2;
            while(E.a[0]){
                BigNum f=E%c;
                if(f.a[0]){
                    b=b*A;
                    b=b%(*this);
                }
                A=A*A;
                A=A%(*this);
                E=E/c;
            }
            return b;
        }
        BigNum(){
            memset(a,0,sizeof a);
        }
        BigNum(int b){
            memset(a,0,sizeof a);
            if(b) {
                int i=1;
                for(i=1;b>0;i++){
                    a[i]=b%10;
                    b/=10;
                }
                a[0]=i-1;
            }
        }
        BigNum(QString s){
            memset(a,0,sizeof a);
            char*  ch;
            QByteArray ba = s.toLatin1();
            ch=ba.data();
            a[0]=strlen(ch);
            if(a[0]==1 && ch[0]=='0')
                a[0]=0;
            else
            for(int i=a[0];i>0;i--)
                a[i]=ch[a[0]-i]-'0';
        }
        BigNum operator +(BigNum B){
            BigNum C;
            bigPlus(this->a,B.a,C.a);
            return C;
        }
        BigNum operator -(BigNum B){
            BigNum C;
            bigSub(this->a,B.a,C.a);
            return C;
        }
        BigNum operator *(BigNum B){
            BigNum C;
            bigMult(this->a,B.a,C.a);
            return C;
        }
        BigNum operator =(BigNum B){
            bigCopy(B.a,this->a);
            return B;
        }
        BigNum operator /(BigNum B){
            BigNum C;
            bigDiv(this->a,B.a,C.a);
            return C;
        }
        BigNum operator %(BigNum B){
            BigNum C;
            bigMod(this->a,B.a,C.a);
            return C;
        }
        QString bigtoQString(){
            char ch[2000];
            for(int i=a[0];i>0;i--)
                ch[a[0]-i]=a[i]+'0';
            if(!a[0]){
                ch[0]='0';
                ch[1]='\0';
            }
            else
                ch[a[0]]='\0';
            QString str = QString(QLatin1String(ch));
            return str;
        }
};

void Widget::on_addButton_clicked()
{
    BigNum A(ui->A_lineEdit->text());
    BigNum B(ui->B_lineEdit->text());
    BigNum C=A+B;
    ui->C_lineEdit->setText(C.bigtoQString());
}

void Widget::on_subButton_clicked()
{
    BigNum A(ui->A_lineEdit->text());
    BigNum B(ui->B_lineEdit->text());
    BigNum C=A-B;
    ui->C_lineEdit->setText(C.bigtoQString());
}

void Widget::on_mulButton_clicked()
{
    BigNum A(ui->A_lineEdit->text());
    BigNum B(ui->B_lineEdit->text());
    BigNum C=A*B;
    ui->C_lineEdit->setText(C.bigtoQString());
}

void Widget::on_modButton_clicked()
{
    BigNum A(ui->A_lineEdit->text());
    BigNum B(ui->B_lineEdit->text());
    BigNum C=A%B;
    ui->C_lineEdit->setText(C.bigtoQString());
}

void Widget::on_divButton_clicked()
{
    BigNum A(ui->A_lineEdit->text());
    BigNum B(ui->B_lineEdit->text());
    BigNum C=A/B;
    ui->C_lineEdit->setText(C.bigtoQString());
}

void Widget::on_Button_clicked()
{
    BigNum M(ui->A_lineEdit->text());
    BigNum a(ui->a_lineEdit->text());
    BigNum e(ui->e_lineEdit->text());
    BigNum C=M.kuaiSuMi(a,e);
    ui->C_lineEdit->setText(C.bigtoQString());
}

void Widget::on_Button_2_clicked()
{
    BigNum M(ui->A_lineEdit->text());
    BigNum C=M.kuaiSuMi();
    ui->C_lineEdit->setText(C.bigtoQString());
}
