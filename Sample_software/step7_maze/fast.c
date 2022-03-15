
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
//�����̍��Wx,y�Ɍ������čŒZ���s����

	t_direction glob_nextdir;
	int straight_count=0;
	float straight_offset=0;
	float straight_length=0;

	//���݂̌�������A���ɍs���ׂ������֌���
	switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//���ɍs��������߂�l�Ƃ���֐����Ă�
	{
		case front:
			straight_count++;			//�O�����������ꍇ�͒����𑖂鋗����L�΂�
			break;
		
		case right:					//�E�Ɍ���
			turn(90,TURN_ACCEL,TURN_SPEED,0,RIGHT,SPIN_MODE);				//�E�ɋȂ�����
			straight_count = 1;
			break;
		
		case left:					//���Ɍ���
			turn(90,TURN_ACCEL,TURN_SPEED,0,LEFT,SPIN_MODE);				//���ɋȂ�����
			straight_count = 1;
			break;
		
		case rear:					//���Ɍ���
			turn(180,TURN_ACCEL,TURN_SPEED,0,LEFT,SPIN_MODE);				//���ɋȂ�����
			straight_count = 1;
			break;
	}

	mypos.dir = glob_nextdir;	//�����̌������X�V


	//�����������ɂ���Ď����̍��W���X�V����
	switch(mypos.dir)
	{
		case north:
			mypos.y++;	//�k������������Y���W�𑝂₷
			break;
			
		case east:
			mypos.x++;	//��������������X���W�𑝂₷
			break;
			
		case south:
			mypos.y--;	//�������������Y���W�����炷
			break;
		
		case west:
			mypos.x--;	//�����������Ƃ���X���W�����炷
			break;

	}


	
	while((mypos.x != x) || (mypos.y != y)){			//�S�[������܂ŌJ��Ԃ�


		switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//���ɍs��������߂�l�Ƃ���֐����Ă�
		{
			case front:					//�������܂Ƃ߂đ���悤�ɂ���
				straight_count++;
				break;
			
			case right:
				if(turn_vel == 0)
				{
					straight(SECTION*straight_count,fast_accel,fast_speed,0.0);
					turn(90,TURN_ACCEL,TURN_SPEED,turn_vel,RIGHT,SPIN_MODE);				//�E�ɋȂ�����
					straight_count = 1;			//���钼���̋��������Z�b�g
				}else{
					straight_length = straight_count * SECTION - HALF_SECTION + SLALOM_OFFSET + straight_offset;
					straight(straight_length,fast_accel,fast_speed,turn_vel);
					turn(90,SLALOM_ANG_ACC,SLALOM_ANG_VEL,turn_vel,RIGHT,SPIN_MODE);				//�E�ɋȂ�����
					straight_offset = -HALF_SECTION + SLALOM_OFFSET;
					straight_count = 1;			//���钼���̋��������Z�b�g
				}
				break;
			
			case left:
				if(turn_vel == 0)
				{
					straight(SECTION*straight_count,fast_accel,fast_speed,0.0);
					turn(90,TURN_ACCEL,TURN_SPEED,turn_vel,LEFT,SPIN_MODE);				//���ɋȂ�����
					straight_count = 1;			//���钼���̋��������Z�b�g
				}else{
					straight_length = straight_count * SECTION - HALF_SECTION + SLALOM_OFFSET + straight_offset;
					straight(straight_length,fast_accel,fast_speed,turn_vel);
					turn(90,SLALOM_ANG_ACC,SLALOM_ANG_VEL,turn_vel,LEFT,SPIN_MODE);				//�E�ɋȂ�����
					straight_offset = -HALF_SECTION + SLALOM_OFFSET;
					straight_count = 1;			//���钼���̋��������Z�b�g
				}
				break;
			
			case rear:
				if(turn_vel == 0)
				{
					straight(SECTION*straight_count,fast_accel,fast_speed,0.0);
					turn(180,TURN_ACCEL,TURN_SPEED,turn_vel,LEFT,SPIN_MODE);				//���ɋȂ�����
					straight_count = 1;			//���钼���̋��������Z�b�g
				}else{
					straight_length = straight_count * SECTION + straight_offset;
					straight(straight_length,fast_accel,fast_speed,0.0);
					turn(180,TURN_ACCEL,TURN_SPEED,0,LEFT,SPIN_MODE);				//���ɋȂ�����
					straight_offset = 0;
					straight_count = 1;			//���钼���̋��������Z�b�g
				}
				break;
		}
	
		mypos.dir = glob_nextdir;	//�����̌������C��
		
		//�����������ɂ���Ď����̍��W���X�V����
		switch(mypos.dir)
		{
			case north:
				mypos.y++;	//�k������������Y���W�𑝂₷
				break;
				
			case east:
				mypos.x++;	//��������������X���W�𑝂₷
				break;
				
			case south:
				mypos.y--;	//�������������Y���W�����炷
				break;
			
			case west:
				mypos.x--;	//�����������Ƃ���X���W�����炷
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
