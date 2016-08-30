#ifndef CONSTANTS_H
#define CONSTANTS_H

const int Size = 40;

const int SceneLength = 640;

const int SceneWidth = 800;

const int WindowWidth = 810;

const int WindowLength = 680;

enum GameOBJType{
  G_O_Type
};

enum MyType
{
    Block_Type = 1,Jumping_Type,Enemy_Type,Boss_Type,Npc_Type,Punch_Type,Hero_Type,Trap_Type,
    Hurt_Type,Stuff_Type,Fire_Type,OMG_Type
};

enum _Direction {
    Left,Right,Up,Down,LeftUp,RightUp,LeftDown,RightDown
};


enum Dimao
{
    //************ 障碍物 ***********************//
    Tree = 0,Water_Center,Water_Left,Water_Right,Water_Up,Water_Down,Jump,Rock,Player,
    //******************* 陷阱 *******************//
    _Trap_1_Left,_Trap_1_Left_UP,_Trap_1_Left_RIGHT,//朝左的trap-1
    _Trap_1_Right,_Trap_1_Right_UP,_Trap_1_Right_LEFT,//朝右的
    _Trap_1_Up,_Trap_1_Up_RIGHT,_Trap_1_Up_DOWN,//朝上
    _Trap_1_Down,_Trap_1_Down_UP,_Trap_1_Down_LEFT,//朝下
    _Trap_2,_Trap_3,
    // ******************** 敌人 ***************//
    Kong,_Enemy1,_Enemy2,_Enemy3,_Boss,_Stuff
};


#endif // CONSTANTS_H
