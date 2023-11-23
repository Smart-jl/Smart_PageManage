#include "page_manager.h"
#include "lcd.h"


static page_manager_t	page_manager = {.g_event_f = NULL};

/**
  * @brief 	设置界面管理器初始化函数
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
  * @brief 	绑定当前界面的事件处理函数和退出函数
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
  * @brief 	切换界面函数为循环函数
	* @param  None
  * @retval None
  */
void Pmg_ChangeLoop(display_f func){
    page_manager.dis_f = func;
}
/**
  * @brief 	设置界面管理器当前运行界面的类型
	* @param  None
  * @retval None
  */
void Pmg_SetType(page_type_t type){
    page_manager.type = type;
}
/**
  * @brief 	获取界面管理器当前运行界面的类型
	* @param  None
  * @retval None
  */
page_type_t Pmg_GetType(void){
    return page_manager.type;
}
/**
	* @brief 	向界面发送消息
	* @param  message：消息队列指针
	* @param  num：消息数量
	* @retval 消息是否发送成功
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
	* @brief 	读取向界面发送的消息
	* @param  None
	* @retval 消息队列指针
  */
uint8_t* Pmg_Read_Message(void){
    page_manager.page_message_busy = false;
    return page_manager.page_message;
}
/**
	* @brief 	读取界面消息队列是否忙线
	* @param  None
	* @retval 消息队列状态
  */
bool Pmg_Read_Message_Busy(void){
    return page_manager.page_message_busy;
}
/**
	* @brief 	向界面发送事件
	* @param  event_value：事件值
	* @retval None
  */
void Pmg_SendEvent(uint8_t event_value){
    page_manager.event_value = event_value;
}
/**
	* @brief 	向界面发送事件
	* @param  event_value：事件值
	* @retval None
	*	@note		立刻执行
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
  * @brief 	页面管理器界面更新函数
	* @param  None
  * @retval None
  */
void Pmg_Update(void){
    if(page_manager.dis_f != NULL)
        page_manager.dis_f();
}
/**
  * @brief 	页面管理器事件句柄处理函数
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
  * @brief  页面管理器初始化
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
