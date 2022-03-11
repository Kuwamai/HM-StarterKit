/***********************************************************************/
/*                                                                     */
/*  FILE        :spi.c			                               */
/*  DATE        :Tue, Jun 08, 2017                                     */
/*  DESCRIPTION :SPI Program                                           */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "iodefine.h"
#include "mathf.h"
#include "sci.h"
#include "init.h"
#include "spi.h"
#include "parameters.h"
#include "glob_var.h"
#include "mytypedef.h"
#include "portdef.h"
#include "interface.h"

extern wait_ms(int wtime);

void straight(float len, float acc, float max_sp, float end_sp){
	//LED(0x01);
	I_tar_ang_vel = 0;
	I_ang_vel = 0;
	I_tar_speed = 0;
	I_speed = 0;
	//���s���[�h�𒼐��ɂ���
	run_mode = STRAIGHT_MODE;
	//�ǐ����L���ɂ���
	con_wall.enable = true;
	//�ڕW�������O���[�o���ϐ��ɑ������
	len_target = len;
	//�ڕW���x��ݒ�
	end_speed = end_sp;
	//�����x��ݒ�
	accel = acc;
	//�ō����x��ݒ�
	max_speed = max_sp;
	
	//���[�^�o�͂�ON
	MOT_POWER_ON;	
	
	if(end_speed == 0){	//�ŏI�I�ɒ�~����ꍇ
		//�����������n�߂�ׂ��ʒu�܂ŉ����A�葬��Ԃ𑱍s
		while(len_target - len_mouse >  1000.0*((float)(tar_speed * tar_speed) - (float)(end_speed * end_speed))/(float)(2.0*accel));
		//LED(0x03);
		//���������J�n
		accel = -acc;					//�������邽�߂ɉ����x�𕉂̒l�ɂ���	
		while(len_mouse < len_target -1){		//��~�����������̏�����O�܂Ōp��
			//��葬�x�܂Ō���������Œ�쓮�g���N�ő��s
			if(tar_speed <= MIN_SPEED){	//�ڕW���x���Œᑬ�x�ɂȂ�����A�����x��0�ɂ���
				accel = 0;
				tar_speed = MIN_SPEED;
			}
		}
		accel = 0;
		tar_speed = 0;
		//���x��0�ȉ��ɂȂ�܂ŋt�]����
		//LED(0x07);
		while(speed >= 0.0);
			
	}else{
		//�����������n�߂�ׂ��ʒu�܂ŉ����A�葬��Ԃ𑱍s
		while(len_target - len_mouse >  1000.0*((float)(tar_speed * tar_speed) - (float)(end_speed * end_speed))/(float)(2.0*accel));
		//LED(0x03);
		//���������J�n
		accel = -acc;					//�������邽�߂ɉ����x�𕉂̒l�ɂ���	
		while(len_mouse < len_target){		//��~�����������̏�����O�܂Ōp��
			//��葬�x�܂Ō���������Œ�쓮�g���N�ő��s
			if(tar_speed <= end_speed){	//�ڕW���x���Œᑬ�x�ɂȂ�����A�����x��0�ɂ���
				accel = 0;
				//tar_speed = end_speed;
			}
		}
	}
	//�����x��0�ɂ���
	accel = 0;
	//���݋�����0�Ƀ��Z�b�g
	len_mouse = 0;
	//LED(0x00);
}

void turn(int deg, float ang_accel, float max_ang_velocity, float turn_speed, short dir, int turn_mode){
	LED(0x01 | 0x08);
	if(turn_speed == 0){
		wait_ms(WAIT_TIME);
	}
	I_tar_ang_vel = 0;
	I_ang_vel = 0;
	I_tar_speed = 0;
	I_speed = 0;
	tar_degree = 0;

	float	local_degree = 0;
	accel = 0;
	tar_speed = turn_speed;
	tar_ang_vel = 0;
	run_mode = turn_mode;

	//��]������`
	TURN_DIR = dir;	
	
	//�ԑ̂̌��݊p�x���擾
	local_degree = degree;
	tar_degree = 0;
	
	//�p�����x�A�����x�A�ō��p���x�ݒ�
	MOT_POWER_ON;
	if(dir == LEFT){
		ang_acc = ang_accel;			//�p�����x��ݒ�
		max_ang_vel = max_ang_velocity;
		max_degree = deg;
		while( (float)(max_degree - (degree - local_degree) + HAYAME_DEG)*PI/180.0 > (float)(tar_ang_vel*tar_ang_vel/(float)(2.0 *  ang_acc)));
		
	}else if(dir == RIGHT){
		ang_acc = -ang_accel;			//�p�����x��ݒ�
		max_ang_vel = -max_ang_velocity;
		max_degree = -deg;
		while(-(float)(max_degree - (degree - local_degree) + HAYAME_DEG)*PI/180.0 > (float)(tar_ang_vel*tar_ang_vel/(float)(2.0 * -ang_acc)));
	}

	LED(0x03 | 0x08);
	//BEEP();
	//�p������Ԃɓ��邽�߁A�p�����x�ݒ�
	MOT_POWER_ON;
	if(turn_speed == 0){
		if(dir == LEFT){
			ang_acc = -ang_accel;			//�p�����x��ݒ�
			//������ԑ��s
			while((degree - local_degree) < max_degree){
				if(tar_ang_vel < TURN_MIN_SPEED){
					ang_acc = 0;
					tar_ang_vel = TURN_MIN_SPEED;
				}
			}
			
			ang_acc = 0;
			tar_ang_vel = 0;
			tar_degree = max_degree;
			
		}else if(dir == RIGHT){
			ang_acc = +ang_accel;			//�p�����x��ݒ�
			//������ԑ��s
			while((degree - local_degree) > max_degree){
				if(-tar_ang_vel < TURN_MIN_SPEED){
					ang_acc = 0;
					tar_ang_vel = -TURN_MIN_SPEED;
				}
			}
			ang_acc = 0;
			tar_ang_vel = 0;
			tar_degree = max_degree;
		}
		LED(0x07 | 0x08);
		while(ang_vel >= 0.1 || ang_vel <= -0.1 );
	}

	if(dir == LEFT){
		ang_acc = -ang_accel;			//�p�����x��ݒ�
		//������ԑ��s
		while((degree - local_degree) < max_degree && tar_ang_vel > 0.1);
		ang_acc = 0;
		tar_ang_vel = 0;
		tar_degree = max_degree;
		
	}else if(dir == RIGHT){
		ang_acc = +ang_accel;			//�p�����x��ݒ�
		//������ԑ��s
		while((degree - local_degree) > max_degree && tar_ang_vel < -0.1);
		ang_acc = 0;
		tar_ang_vel = 0;
		tar_degree = max_degree;
	}
	
	tar_ang_vel = 0;
	ang_acc = 0;
	//���݋�����0�Ƀ��Z�b�g
	len_mouse = 0;
	if(turn_speed == 0){
		wait_ms(WAIT_TIME);
	}
	LED(0x00);
}
