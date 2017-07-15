#include <iostream>
#include<windows.h>
#include<fstream>
#include<time.h>
#include<ctime>
using namespace std;
void map_maker();
void display_refresher();
void player_move();
void bullet_logic();
void reload();
void enemy_logic();
void enemy_maker();
bool keyPressed();// check is user has pressed any key and refreshes the users position only
int rand_num();
int high_score();
char x[400]={' '},y[400]={' '};
int playerPos=349,bulletCounter=0,bullet=0,bulletNum=30,ammo=500,score=0,highscorea=0,speed=220;
unsigned last,elapse,start;
bool bulletOn=true,win=true,allow=true;
int main()
{
    unsigned run_time,run_time_last;

    last=clock();
    start=clock();
    srand(time(NULL));
    while(win){
        run_time=clock();

        //display_refresher();
        elapse=abs(last-clock());
        //elapse=clock()-last;
        /*if(elapse>speed){
            allow=true;
            last=clock();
        }else{
            allow=false;
        }*/
        if(score>75){
            speed=1;
        }else if(score>55){
            speed=50;
        }else if(score>30){
            speed=100;
        }else if(score>15){
            speed=200;
        }
        allow=true;

        if(abs(run_time-run_time_last)>40){
            display_refresher();
            player_move();
            allow=false;
            //keyPressed();
            run_time_last=clock();

        }



    }
    display_refresher();
    cout<<"       "<<"YOU LOSE"<<endl;
    system("pause");
    return 0;
}

bool keyPressed(){
    if(GetAsyncKeyState(VK_UP)||GetAsyncKeyState(VK_DOWN)||
       GetAsyncKeyState(VK_LEFT)||GetAsyncKeyState(VK_RIGHT)||
       GetAsyncKeyState(VK_CONTROL)){
        display_refresher();
        return true;
    }else{
        return false;
    }
}
int rand_num(){
    return rand()%20;
}
void enemy_maker(){
    int enemyPos=rand_num(),number;
    if(rand_num()==1){
        x[enemyPos]=-99;
    }
    if(rand_num()==2&&allow){
        for(int i=0;i<3;i++){
            x[enemyPos+i]=-99;
        }
        for(int i=0;i<3;i++){
            x[enemyPos+i+20]=-99;
        }
    }
    if(rand_num()==3&&allow){
        number=rand_num();
        if(number<enemyPos){
            int temp=number;
            number=enemyPos;
            enemyPos=temp;
        }
        for(int i=enemyPos;i<=number;i++){
            x[i]=-99;
        }
    }
}
void map_maker(){
    if(ammo<400){
        x[ammo]='o';
        ammo=500;
    }
    for(int i=399;i>=20;i--){
        x[i]=x[i-20];

    }
    for(int i=0;i<20;i++){
        x[i]=' ';
    }


}

void enemy_logic(){
    if(x[playerPos]==-99){
        win=false;
        x[playerPos]=176;
    }

}

void display_refresher(){
    reload();
    if(allow){
        map_maker();
        enemy_maker();
    }
    enemy_logic();
    bullet_logic();

    system("cls");
    for(int i=0;i<400;i++){
        if(playerPos==i&&win){
            cout<<"^";
        }else if(bulletOn){
            cout<<y[i];
        }
        else{
            cout<<x[i];
        }
        if((i+1)%20==0){
            cout<<endl;
        }
    }
    cout<<endl
            <<"SCORE: "<<score<<"       "
            <<"o: "<<bulletNum<<endl
            <<"HIGHSCORE: "<<high_score()<<endl
            <<speed;
}
void player_move(){

    if(GetAsyncKeyState(VK_LEFT)&&playerPos%20!=0 ){
        playerPos--;
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        if((playerPos-9)%10==0&&((playerPos-9)/10)&1){

        }else{
            playerPos++;
        }
    }
    if(GetAsyncKeyState(VK_UP)&&playerPos>19){
        playerPos-=20;
    }
    if(GetAsyncKeyState(VK_DOWN)&&playerPos<380){
        playerPos+=20;
    }
    if(GetAsyncKeyState(VK_CONTROL)){
        if(bulletNum>0){
            y[playerPos-20]='.';
            bullet++,bulletNum--;

        }else{
            if(bullet==bulletCounter){
                bulletOn=false;
            }

        }

    }
}
void bullet_logic(){
    for(int i=0;i<20;i++){
        if(y[i]=='.'){
            bulletCounter++;
        }

    }

    if(bulletOn){
        for(int i=380;i<400;i++){
            y[i]=x[i];
        }
        for(int i=20;i<400;i++){
            if(x[i]=='x'&&allow){
                x[i]=' ';
            }
            if(y[i]=='.'){
                //if(y[i-20]==-99||x[i-20]==-99||x[i]==-99){
                if(x[i]==-99){
                    //x[i-20]='x';
                    x[i]='x';
                    score++;
                }else if(x[i-20]==-99){
                    x[i-20]='x';
                    score++;
                }else{
                    y[i-20]=y[i];
                }
            }
            y[i]=x[i];
        }
    }
}
void reload(){
    if(rand_num()==1&&ammo>=500){
        ammo=rand_num();
    }
    if(x[playerPos]=='o'){
        bulletNum=30;
        bulletOn=true;
        x[playerPos]=' ';
        ammo=500;

    }

}
int high_score(){
    //new highscore
    if (score>highscorea){
        ofstream file("highscore.txt");
        file<<score;
        file.close();
    }
    //read highscore
    ifstream file("highscore.txt");
    file>>highscorea;
    file.close();

    return highscorea;
}

