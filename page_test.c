#include "page_test.h"
#include "page_manager.h"
#include "display_tv.h"
#include "camera.h"
#include "servos.h"
#include "output.h"
#include "voiceassistant.h"
#include "kl_screen.h"
#include "HAL.h"
#include "typedefs.h"
#include "HAL_Def.h"
#include "page_scroll_display_info.h"
#include "rtc.h"

u8 numms = 0;
u8 test_buf[30] = {0};
typedefs_data_t *test_data;

char voice_set[6] = {0x7E,0x04,0x31,0x0A,0x2C,0xEF};
typedefs_data_t *page_test_data = &hal_data;

char modes[4][6] = {"NO","MODE1","MODE2","MODE3"};
char colors[5][7] = {"NO","red","green","blue","yellow"};
char sharps[6][10] = {"NO","circle","square","pentagon","triangle","hexagon"};
char backgrounds[3][5] = {"NO","w","b"};


static void Page_Test_Loop(void);
static void Page_Test_Event(uint8_t event_value);
static void Page_Test_Exti(void);
void Set_data(void);

/* 四种模式分别为   静态图片
 *               低速视频
 *               高速视频
 *               自定义坐标 */

/**
  * @brief 	四种模式菜单选择界面
  * @param  None
  * @retval None
  */
void Page_Test_Setup(void){
    Pmg_SetType(page_type_test);
    Output_Control(output_laserpen,DISABLE);
//    LCD_ShowChinese(32,0,"测试界面",RED,WHITE,32,0);
    LCD_ShowString(160,0,"Test_Page",RED,WHITE,32,0);

    Pmg_BindRelevantFunc(Page_Test_Event,Page_Test_Exti);
    Pmg_ChangeLoop(Page_Test_Loop);
}
/**
  * @brief 	主菜单循环函数
  * @param  None
  * @retval None
  */

static void Page_Test_Loop(void){
//    test_data = HAL_Receice_Data();
//    Set_data();
    numms++;
    LCD_ShowIntNum(340, 260, numms, 3, RED, WHITE, 32);
//    LCD_ShowIntNum(110,260,temp,3,RED,WHITE,32);
}

static void Page_Test_Event(uint8_t event_value){
    if (event_value == key_one){

    }
    else if (event_value == KEY_E){
        Pmg_SetFunc(Page_Menu_Setup);
    }
}

static void Page_Test_Exti(void){

}

void Set_data(void){
    u8 i = 0;
    u8 row = 0;
    for (i = 0; i < 6; i++) {
        sprintf((char*)test_buf,"%02d:%02d:%02d,%s,%s,%s,%s",
                rhour,
                rmin,
                rsec,
                modes[i],
                backgrounds[i],
                colors[i],
                sharps[i]);
        strcpy(page_scroll_camera_records[i],(char*)test_buf);
    }
}



