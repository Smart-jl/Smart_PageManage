#include "page_manager.h"
#include "lcd.h"


static page_manager_t	page_manager = {.g_event_f = NULL};

/**
  * @brief 	���ý����������ʼ������
	* @param  None
  * @retval None
  */
void Pmg_SetFunc(display_f func){
    if(page_manager.exti_f != NULL)
        page_manager.exti_f();
//    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
    LCD_Clear();
    page_manager.dis_f = func;
}
/**
  * @brief 	�󶨵�ǰ������¼����������˳�����
	* @param  None
  * @retval None
  */
void Pmg_BindRelevantFunc(display_event_f event_func,display_f	exit_func){
    if(event_func != NULL){
        page_manager.dis_event_f = event_func;
    }
    if(exit_func != NULL){
        page_manager.exti_f = exit_func;
    }
}
/**
  * @brief 	�л����溯��Ϊѭ������
	* @param  None
  * @retval None
  */
void Pmg_ChangeLoop(display_f func){
    page_manager.dis_f = func;
}
/**
  * @brief 	���ý����������ǰ���н��������
	* @param  None
  * @retval None
  */
void Pmg_SetType(page_type_t type){
    page_manager.type = type;
}
/**
  * @brief 	��ȡ�����������ǰ���н��������
	* @param  None
  * @retval None
  */
page_type_t Pmg_GetType(void){
    return page_manager.type;
}
/**
	* @brief 	����淢����Ϣ
	* @param  message����Ϣ����ָ��
	* @param  num����Ϣ����
	* @retval ��Ϣ�Ƿ��ͳɹ�
  */
bool Pmg_Send_Message(uint8_t* message,uint8_t num){
    if(Pmg_Read_Message_Busy())
        return false;
    memset(page_manager.page_message,0,sizeof(page_manager.page_message));
    for(uint8_t i = 0;i < num; i++){
        page_manager.page_message[i] = *message;
        message ++;
    }
    page_manager.page_message_busy = true;
    return true;
}
/**
	* @brief 	��ȡ����淢�͵���Ϣ
	* @param  None
	* @retval ��Ϣ����ָ��
  */
uint8_t* Pmg_Read_Message(void){
    page_manager.page_message_busy = false;
    return page_manager.page_message;
}
/**
	* @brief 	��ȡ������Ϣ�����Ƿ�æ��
	* @param  None
	* @retval ��Ϣ����״̬
  */
bool Pmg_Read_Message_Busy(void){
    return page_manager.page_message_busy;
}
/**
	* @brief 	����淢���¼�
	* @param  event_value���¼�ֵ
	* @retval None
  */
void Pmg_SendEvent(uint8_t event_value){
    page_manager.event_value = event_value;
}
/**
	* @brief 	����淢���¼�
	* @param  event_value���¼�ֵ
	* @retval None
	*	@note		����ִ��
  */
void Pmg_CarryEvent(uint8_t event_value){
    if(page_manager.dis_event_f != NULL){
        page_manager.dis_event_f(event_value);
    }
    if(page_manager.g_event_f != NULL){
        page_manager.g_event_f(event_value);
    }
}
/**
  * @brief 	ҳ�������������º���
	* @param  None
  * @retval None
  */
void Pmg_Update(void){
    if(page_manager.dis_f != NULL)
        page_manager.dis_f();
}
/**
  * @brief 	ҳ��������¼����������
	* @param  None
  * @retval None
  */

void Pmg_Event_Handler(void){
    if(page_manager.event_value != 0){
        if(page_manager.dis_event_f != NULL){
            page_manager.dis_event_f(page_manager.event_value);
        }
        if(page_manager.g_event_f != NULL){
            page_manager.g_event_f(page_manager.event_value);
        }
        page_manager.event_value = 0;
    }
}
/**
  * @brief  ҳ���������ʼ��
	* @param  None
  * @retval None
  */
void Pmg_Init(void){
    LCD_Init();
    page_manager.dis_f = Page_Poweron_Setup;
//    page_manager.dis_f = Page_Custom_Location_Setup;
//    page_manager.dis_f = Page_Poweron_Setup;
//    page_manager.dis_f = Page_Servo_calibration_Setup;
//      page_manager.dis_f = Page_Parameter_Setting_Setup;

}
