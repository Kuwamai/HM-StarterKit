
#ifndef _PARAMETER

#include "static_parameters.h"

//物理的なパラメータ
#define TIRE_DIAMETER	(13.4-0.38)				//タイヤの直径	[mm]
#define TIRE_RADIUS	(TIRE_DIAMETER/2.0)		//タイヤの半径	[mm]
#define MMPP 		(TIRE_DIAMETER*PI)/(ENC_RES_MAX)	//エンコーダ1パルスあたりに進む距離[mm](TIRE_DIAMETER*PI)/(ENC_MAX)
#define ENC_RES_MAX	(1024)
#define ENC_RES_HALF	(512)

#define V_ref		3.8				//モータ制御の基準電圧

//ログ用のパラメータ
#define LOG_CNT		1000				//ログをとる個数。 1mmsで取得しているので、取得時間[s]はこの数の1000分の1

//センサ関連パラメータ
#define WAITLOOP_SLED	180				//LEDを光らせてからAD変換を開始するまでの時間稼ぎ用定数

//家のパラメータ
/*
#define REF_SEN_R	1160				//マウスを迷路中央に置いた時のセンサの値
#define REF_SEN_L	900				//マウスを迷路中央に置いた時のセンサの値
#define TH_SEN_R	200				//壁があるか否かの閾値	車体を区画の左へ寄せた時のセンサ値(壁あり)
#define TH_SEN_L	60				//壁があるか否かの閾値	車体を区画の右へ寄せた時のセンサ値(壁あり)
#define TH_SEN_FR	50				//壁があるか否かの閾値	
#define TH_SEN_FL	50				//壁があるか否かの閾値
*/
//全国大会会場のパラメータ
#define REF_SEN_R	1230				//マウスを迷路中央に置いた時のセンサの値
#define REF_SEN_L	1033				//マウスを迷路中央に置いた時のセンサの値
#define TH_SEN_R	230				//壁があるか否かの閾値	車体を区画の左へ寄せた時のセンサ値(壁あり)
#define TH_SEN_L	70				//壁があるか否かの閾値	車体を区画の右へ寄せた時のセンサ値(壁あり)
#define TH_SEN_FR	50				//壁があるか否かの閾値80って出てたけど少し少なめにしてみた
#define TH_SEN_FL	50				//壁があるか否かの閾値

#define CONTH_SEN_R	TH_SEN_R			//制御をかけるか否かの閾値
#define CONTH_SEN_L	TH_SEN_L			//制御をかけるか否かの閾値
/*
#define CON_WALL_KP	(0)				//壁センサによる姿勢制御の比例制御の比例定数
*/
#define CON_WALL_KP	(3.0)				//壁センサによる姿勢制御の比例制御の比例定数
#define IGNORE_WALL_LEN (7)

//フィードバックゲインパラメータ
//Pゲイン　最初に調整する	実速度が目標速度を中心として軽く振動する程度に調整
//Iゲイン　最後に調整する	積分値が合うようにする程度。
//Dゲイン　二番目に調整する。	P制御によって発生した振動を抑えられる程度に調整
//車体中心における並進方向速度に関するフィードバックゲイン
#define SPEED_KP	(20.0)				//Pゲイン
#define SPEED_KI	(0.4)				//Iゲイン
#define SPEED_KD	(0.01)				//Dゲイン　
//車体中心における回転方向速度に関するフィードバックゲイン
#define OMEGA_KP	(60.0)				//Pゲイン
#define OMEGA_KI	(0.7)				//Iゲイン
#define OMEGA_KD	(0.01)				//Dゲイン

//走行パラメータ
#define SEARCH_VEL	(0.3)				//探索走行の速度	[m/s]
#define SEARCH_ACC	(1.0)				//探索走行の加速度	[m/s^2]
#define TURN_ACCEL	(PI*2)				//超信地旋回の加速度	[rad/s^2]
#define	TURN_SPEED	(PI)			//超信地旋回の最高速度	[rad/s]
/*
#define SLALOM_ANG_ACC	(97.9310668)				//超信地旋回の加速度	[rad/s^2]
#define	SLALOM_ANG_VEL	(6.28318530)				//超信地旋回の最高速度	[rad/s]
#define SLALOM_OFFSET (6)
#define SLALOM_VEL    (0.2)
*/
#define SLALOM_OFFSET (5)
#define SLALOM_VEL (0.2)
#define SLALOM_ANG_VEL (8.79645943)
#define SLALOM_ANG_ACC (64.87646413)
#define HAYAME_DEG (2.9)  //予想減速開始姿勢より早めに角速度を減速させる

#define FAST_SPEED_0	(0.3)				//最短走行の速度	[m/s]
#define FAST_ACCEL_0	(1.0)				//最短走行の加速度	[m/s^2]

#define FAST_SPEED_1	(0.6)				//最短走行の速度	[m/s]
#define FAST_ACCEL_1	(1.5)				//最短走行の加速度	[m/s^2]

#define FAST_SPEED_2	(1.0)				//最短走行の速度	[m/s]
#define FAST_ACCEL_2	(2.0)				//最短走行の加速度	[m/s^2]

#define FAST_SPEED_3	(1.5)				//最短走行の速度	[m/s]
#define FAST_ACCEL_3	(2.0)				//最短走行の加速度	[m/s^2]

#define MIN_SPEED	(0.1)				//最低速度	[m/s]
#define TURN_MIN_SPEED	(PI/10.0)			//超信地旋回の最低速度	[rad/s]

//迷路関連パラメータ
#define GOAL_X	3		//ゴール座標(x)
#define GOAL_Y	3		//ゴール座標(y)
/*
#define GOAL_X	6		//ゴール座標(x)
#define GOAL_Y	9		//ゴール座標(y)
*/

//決定用センサパラメータ
#define	SEN_DECISION	3500	//メニュー決定用の光センサ閾値

#define _PARAMETER

#endif
