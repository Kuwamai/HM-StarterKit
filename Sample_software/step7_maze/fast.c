
#include "portdef.h"
#include "iodefine.h"
#include "parameters.h"
#include "mytypedef.h"
#include "glob_var.h"
#include "run.h"
#include "interface.h"
#include "sci.h"

extern int get_nextdir(int x, int y, int mask, t_direction *dir);

void fast_run(int x, int y, float fast_speed, float fast_accel, float turn_vel)
{
//引数の座標x,yに向かって最短走行する

	t_direction glob_nextdir;
	int straight_count=0;
	float straight_offset=0;
	float straight_length=0;

	//現在の向きから、次に行くべき方向へ向く
	switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//次に行く方向を戻り値とする関数を呼ぶ
	{
		case front:
			straight_count++;			//前向きだった場合は直線を走る距離を伸ばす
			break;
		
		case right:					//右に向く
			turn(90,TURN_ACCEL,TURN_SPEED,0,RIGHT,SPIN_MODE);				//右に曲がって
			straight_count = 1;
			break;
		
		case left:					//左に向く
			turn(90,TURN_ACCEL,TURN_SPEED,0,LEFT,SPIN_MODE);				//左に曲がって
			straight_count = 1;
			break;
		
		case rear:					//後ろに向く
			turn(180,TURN_ACCEL,TURN_SPEED,0,LEFT,SPIN_MODE);				//左に曲がって
			straight_count = 1;
			break;
	}

	mypos.dir = glob_nextdir;	//自分の向きを更新


	//向いた方向によって自分の座標を更新する
	switch(mypos.dir)
	{
		case north:
			mypos.y++;	//北を向いた時はY座標を増やす
			break;
			
		case east:
			mypos.x++;	//東を向いた時はX座標を増やす
			break;
			
		case south:
			mypos.y--;	//南を向いた時はY座標を減らす
			break;
		
		case west:
			mypos.x--;	//西を向いたときはX座標を減らす
			break;

	}


	
	while((mypos.x != x) || (mypos.y != y)){			//ゴールするまで繰り返す


		switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//次に行く方向を戻り値とする関数を呼ぶ
		{
			case front:					//直線をまとめて走るようにする
				straight_count++;
				break;
			
			case right:
				if(turn_vel == 0)
				{
					straight(SECTION*straight_count,fast_accel,fast_speed,0.0);
					turn(90,TURN_ACCEL,TURN_SPEED,turn_vel,RIGHT,SPIN_MODE);				//右に曲がって
					straight_count = 1;			//走る直線の距離をリセット
				}else{
					straight_length = straight_count * SECTION - HALF_SECTION + SLALOM_OFFSET + straight_offset;
					straight(straight_length,fast_accel,fast_speed,turn_vel);
					turn(90,SLALOM_ANG_ACC,SLALOM_ANG_VEL,turn_vel,RIGHT,SPIN_MODE);				//右に曲がって
					straight_offset = -HALF_SECTION + SLALOM_OFFSET;
					straight_count = 1;			//走る直線の距離をリセット
				}
				break;
			
			case left:
				if(turn_vel == 0)
				{
					straight(SECTION*straight_count,fast_accel,fast_speed,0.0);
					turn(90,TURN_ACCEL,TURN_SPEED,turn_vel,LEFT,SPIN_MODE);				//左に曲がって
					straight_count = 1;			//走る直線の距離をリセット
				}else{
					straight_length = straight_count * SECTION - HALF_SECTION + SLALOM_OFFSET + straight_offset;
					straight(straight_length,fast_accel,fast_speed,turn_vel);
					turn(90,SLALOM_ANG_ACC,SLALOM_ANG_VEL,turn_vel,LEFT,SPIN_MODE);				//右に曲がって
					straight_offset = -HALF_SECTION + SLALOM_OFFSET;
					straight_count = 1;			//走る直線の距離をリセット
				}
				break;
			
			case rear:
				if(turn_vel == 0)
				{
					straight(SECTION*straight_count,fast_accel,fast_speed,0.0);
					turn(180,TURN_ACCEL,TURN_SPEED,turn_vel,LEFT,SPIN_MODE);				//左に曲がって
					straight_count = 1;			//走る直線の距離をリセット
				}else{
					straight_length = straight_count * SECTION + straight_offset;
					straight(straight_length,fast_accel,fast_speed,0.0);
					turn(180,TURN_ACCEL,TURN_SPEED,0,LEFT,SPIN_MODE);				//左に曲がって
					straight_offset = 0;
					straight_count = 1;			//走る直線の距離をリセット
				}
				break;
		}
	
		mypos.dir = glob_nextdir;	//自分の向きを修正
		
		//向いた方向によって自分の座標を更新する
		switch(mypos.dir)
		{
			case north:
				mypos.y++;	//北を向いた時はY座標を増やす
				break;
				
			case east:
				mypos.x++;	//東を向いた時はX座標を増やす
				break;
				
			case south:
				mypos.y--;	//南を向いた時はY座標を減らす
				break;
			
			case west:
				mypos.x--;	//西を向いたときはX座標を減らす
				break;

		}
	}
	if(turn_vel == 0)
	{
		straight(SECTION*straight_count,fast_accel,fast_speed,0.0);
	}else{
		straight_length = straight_count * SECTION + straight_offset;
		straight(straight_length,fast_accel,fast_speed,0.0);
	}
}
