#ifndef	__PAGE_MANAGER_H
#define __PAGE_MANAGER_H

#include <stm32f10x.h>
#include <string.h>
#include "typedefs.h"
#include "display.h"
#include "Matrix_KEYBoard.h"
#include "camera.h"
#include "HAL.h"
#include "HAL_Def.h"
#include "count.h"


typedef void (*display_f)(void);//��ʾ���溯��
typedef void (*display_event_f)(uint8_t event_value);//��ʾ�����¼��ص�����

typedef enum {
    page_type_poweron,
    page_type_menu,
    page_type_parameter_setting,  //��������
    page_type_still_picture,    //��ֹͼƬģʽ
    page_type_low_speed_video,  //������Ƶģʽ
    page_type_high_speed_video, //������Ƶģʽ
    page_type_custom_location,  //�Զ���λ��
    page_type_test,
    page_type_show_records,     //��ʾ��¼����Ϣ
    page_type_scrolling,        //��������
    page_type_null,
}page_type_t;


extern void Page_Poweron_Setup(void);
extern void Page_Parameter_Setting_Setup(void);
extern void Page_Menu_Setup(void);
extern void Page_Still_Picture_Setup(void);
extern void Page_Low_Speed_Video_Setup(void);
extern void Page_Hight_Speed_Video_Setup(void);
extern void Page_Custom_Location_Setup(void);
extern void Page_Test_Setup(void);
extern void Page_Servo_calibration_Setup(void);
extern void Page_Scroll_dis_info_Setup(void);
extern void Page_Turning_Setup(void);
extern void Page_Set_value_Setup(void);
extern void Page_Show_Records_Setup(void);




extern void Page_Null_Setup(void);

struct s_page_manager{
    page_type_t	type;	//��������
    display_f dis_f;//���溯��
    display_event_f	dis_event_f;//�����¼�����
    display_event_f g_event_f;	//ȫ���¼�����
    display_f	exti_f;		//�����˳�����
    uint8_t     event_value;	//�¼�ֵ
    uint8_t			page_message[50];	//����ͽ���֮�䴫����Ϣ
    bool			page_message_busy;
    uint8_t			daemon_message[50];	//����ͺ�̨֮�䴫����Ϣ
    bool			daemon_message_busy;
};
typedef struct s_page_manager page_manager_t;


#ifdef __cplusplus
extern "C"{
#endif

void Pmg_SetFunc(display_f func);
void Pmg_BindRelevantFunc(display_event_f event_func,display_f	exit_func);
void Pmg_ChangeLoop(display_f func);
void Pmg_SetType(page_type_t type);
page_type_t Pmg_GetType(void);
void Pmg_SendEvent(uint8_t event_value);
void Pmg_CarryEvent(uint8_t event_value);
bool Pmg_Send_Message(uint8_t* message,uint8_t num);
uint8_t* Pmg_Read_Message(void);
bool Pmg_Read_Message_Busy(void);
void Pmg_Event_Handler(void);
void Pmg_Update(void);
void Pmg_Init(void);

#ifdef __cplusplus
}
#endif







#endif






