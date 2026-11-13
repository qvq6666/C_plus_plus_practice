#include <iostream>
#include <windows.h>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;
std::mt19937 rng((unsigned int)time(nullptr));

string uers_input;

class Player
{
    private:

    public:
    int player_hp;
    int player_max_hp;
    int player_hit_damage;
    int player_Defensive_positions;
    int player_Storage_Defensive_positions;
    Player()
    {
        player_hp = 100;
        player_max_hp = 100;
        player_hit_damage = 20;
        player_Defensive_positions = 20;
        player_Storage_Defensive_positions = 0;
    }
    

    void typePrint(string text,int delay)
    {
    for (char ch : text)
        {
           cout<<ch;
           cout.flush();
           Sleep(delay);
        }
    }
    
    //简化选择遗物代码里的if判断语句
    void IF_Random_simplification(int opt)
    {
        if (opt == 0)
        {
            player_hit_damage += 10;
                    
        }
        else if (opt == 1)
        {
            player_max_hp += 10;
            player_hp = player_max_hp;   
        }
        else if (opt == 2)
        {
            player_hp += 40;
            if (player_hp > player_max_hp)
            {
                player_hp = player_max_hp;
            }
                    
        }
        else if (opt == 3)
        {
                player_Defensive_positions += 10;
        }

    }
    
    //简化选择遗物代码里的switch判断语句
    void SWITCH_Random_simplification(int opt)
    {
        switch (opt)
        {
        case 0:
            typePrint("   宝刀(攻击力提升+10)",50);
            break;
        case 1:
            typePrint("   钢铁肢体(最大生命值提升+10)",50);
            break;
        case 2:
            typePrint("   回复魔法(回复生命+40)",50);
            break;
        case 3:
            typePrint("   护盾(每一次的防御值+10)",50);
            break;
        }
        
  
    }
    void relicDraw()
    {
        cout<<"\033[92m";
        int pool[4] = {0,1,2,3};
        random_shuffle(pool,pool + 4);
        int opt_a = pool[0];
        int opt_b = pool[1];
        int opt_c = pool[2];
        typePrint("a.",50);
        SWITCH_Random_simplification(opt_a);
        typePrint("\nb.",50);
        SWITCH_Random_simplification(opt_b);
        typePrint("\nc.",50);
        SWITCH_Random_simplification(opt_c);

        cout<<"\033[93m\n";
        while (true)
        {
            cin>>uers_input;
            if (uers_input == "a")
            {
                IF_Random_simplification(opt_a);
                break;
            }
            else if (uers_input == "b")
            {
                IF_Random_simplification(opt_b);
                break;
            }
            else if (uers_input == "c")
            {
                IF_Random_simplification(opt_c);
                break;
            }
            else
            {
                cout<<"\033[91m";
                cout<<"没有这个选项!\n";
                cout<<"\033[0m";
            }
            
        }
        
    }





};

int Rand_Monster_Type()
    {
        int weight_slime = 6;//史莱姆
        int weight_goblin = 4;//哥布林
        int total = weight_slime + weight_goblin;

        std::uniform_int_distribution<int>dist(1,total);
        if (dist(rng) <= weight_slime)
        {
            return 0;//史莱姆70
        }
        else
        {
            return 1;//哥布林40
        }
    }

class monster
{
    private:
    
    public:
    int monster_Type;//0 = 史莱姆   1 = 哥布林
    int Enemy_hp;
    int Enemy_Max_hp;
    int monster_hit_damage;
    void Set_Monster_Type()
    {
        
        if(monster_Type == 0)
        {
            monster_hit_damage = 10;
            Enemy_hp = 50;
            Enemy_Max_hp = 50;
        }
        else if (monster_Type == 1)
        {
            monster_hit_damage = 30;
            Enemy_hp = 75;
            Enemy_Max_hp = 75;
        }
        

       
    }

    

};

void typePrint(string text,int delay)
{
    for (char ch : text)
    {
        cout<<ch;
        cout.flush();
        Sleep(delay);
    }
}

int main()
{
    Next_game:
    srand((unsigned)time(NULL));
    //变量
    
    string uers_Name; 
    
    //变量遗物
    

    Player p;
    monster m;
    
    p.player_Storage_Defensive_positions = 0;

    p.player_hp = 100;
    //开端
    cout<<"\033[90m";
    typePrint("你叫什么名字?\n",50);
    cout<<"\033[93m";
    cin >>uers_Name;
    cout<<"\033[90m";
    typePrint(uers_Name,50);
    typePrint("......\n",50);
    typePrint("真是一个好名字\n",50);
    typePrint("那么",50);
    typePrint(uers_Name,50);
    typePrint("......\n",50);
    typePrint("开始你的冒险吧！\n\n",50);

    //下一局的传送点
    RESTAPT_POINT:
    //游戏功能
    p.player_Storage_Defensive_positions = 0;

    
    m.monster_Type = Rand_Monster_Type(); 
    m.Set_Monster_Type();

    cout<<"\033[90m";
    if (m.monster_Type == 0)
    {
        typePrint("野生的史莱姆出现了！\n",50);
    }
    else if (m.monster_Type == 1)
    {
        typePrint("野生的哥布林出现了！\n",50);
    }
    
    
    
    
    //选项
    while (m.Enemy_hp > 0)
    {
        while (true)
        {
            cout<<"\033[92m";
            typePrint("a攻击",50);
            typePrint("   b防御\n",50);
            cout<<"\033[93m";
            cin>>uers_input;
            if (uers_input=="a"||uers_input=="b")
            {
                break;
            }
            else
            {
                cout<<"\033[31m";
                cout<<"没有这个选项!\n";
            }
    }
    //玩家结算
        if (uers_input=="a")
        {
           m.Enemy_hp -= p.player_hit_damage;
           cout<<"\033[90m";
           typePrint("你造成了",50);
           cout<<p.player_hit_damage;
           typePrint("点伤害\n",50);
           if (m.Enemy_hp <= 0)
            {
               cout<<"\033[33m";
               typePrint("你获胜了!",50);
               typePrint("选择战利品\n",50);
               p.relicDraw();
               cout<<"\n";
               cout<<"\033[0m";
               goto RESTAPT_POINT;
            }
            else
            {
               typePrint("怪物还剩",50);
               cout<<m.Enemy_hp<<"/"<<m.Enemy_Max_hp;
               typePrint("hp\n",50);
           }
        }

        else if(uers_input == "b")
        {
            cout<<"\033[90m";
            typePrint("你的防御点增加了",50);
            cout<<p.player_Defensive_positions<<"点\n";
            p.player_Storage_Defensive_positions += p.player_Defensive_positions;
            typePrint("防御点数:",50);
            cout<<p.player_Storage_Defensive_positions<<"\n";


        }
        //怪物结算
        
        int diff = p.player_Storage_Defensive_positions - m.monster_hit_damage;
        int realDmg;
        int blockDmg;

        if (diff >= 0)
        {
            p.player_Storage_Defensive_positions = diff;
            realDmg = 0;
        }
        else
        {
            p.player_Storage_Defensive_positions = 0;
            realDmg = -diff;
            p.player_hp -= (-diff);
        }
        blockDmg = m.monster_hit_damage - realDmg;

        cout<<"\033[90m";
        typePrint("怪物对你造成了",50);
        cout<<realDmg;
        typePrint("点伤害\n格挡了",50);
        cout<<blockDmg;
        typePrint("点\n",50);
        if (p.player_hp <= 0)
        {
            cout<<"\033[91m";
            typePrint("你死了...\n",50);
            typePrint("a退出游戏",50);
            typePrint("   b下一局\n",50);
            cout<<"\033[93m";
            cin>>uers_input;
            while (uers_input=="a"||uers_input=="b")
            {
                
                if (uers_input=="a")
                {
                    exit(0);
                }
                else if (uers_input=="b")
                {
                    goto Next_game;
                }
                else
                {
                    cout<<"\033[91m";
                    cout<<"没有这个选项!\n";
                }

            }
        }
        
        typePrint("你还有",50);
        cout<<p.player_hp<<"/"<<p.player_max_hp;
        typePrint("点血\n",50);
    }
    return 0;   
}