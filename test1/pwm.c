#include <reg52.h>
#include <intrins.h>

// 定义电机控制引脚（根据实际电路连接修改）
sbit EN1 = P1^0;  // 左电机使能
sbit EN2 = P1^1;  // 右电机使能
sbit IN1 = P1^2;  // 左电机方向1
sbit IN2 = P1^3;  // 左电机方向2
sbit IN3 = P1^4;  // 右电机方向1
sbit IN4 = P1^5;  // 右电机方向2

// 定义编码器输入引脚（外部中断）
sbit LEFT_ENCODER = P3^2;  // 左电机编码器信号(INT0)
sbit RIGHT_ENCODER = P3^3; // 右电机编码器信号(INT1)

// PWM控制变量
unsigned char pwmval_left = 0;          // 左电机当前PWM占空比
unsigned char pwmval_right = 0;         // 右电机当前PWM占空比
unsigned char pwmval_left_init = 10;   // 左电机初始占空比(0-20)
unsigned char pwmval_right_init = 10;  // 右电机初始占空比(0-20)
bit right_pwm = 1;   // 右电机使能开关
bit left_pwm = 1;    // 左电机使能开关

// 编码器计数和速度变量
unsigned int left_encoder_count = 0;    // 左电机编码器脉冲计数
unsigned int right_encoder_count = 0;   // 右电机编码器脉冲计数
unsigned int left_speed = 0;            // 左电机速度（cm/s）
unsigned int right_speed = 0;           // 右电机速度（cm/s）
unsigned int speed_calc_timer = 0;      // 速度计算间隔计数器

// 目标速度（单位：cm/s）
#define TARGET_SPEED 30  // 目标速度30cm/s

// 轮子参数
#define WHEEL_CIRCUMFERENCE 20.5  // 轮子周长20.5cm
#define ENCODER_SLOTS 20          // 编码器栅格数

// 定时器0初始化 (1ms中断 - 24MHz晶振)
void Timer0_Init(void)
{
    TMOD &= 0xF0;     // 清除T0设置
    TMOD |= 0x01;     // 设置T0为模式1(16位定时器)
    TH0 = 0xF8;       // 1ms定时初值(24MHz晶振)
    TL0 = 0x30;
    ET0 = 1;          // 允许T0中断
    TR0 = 1;          // 启动T0
    EA = 1;           // 开启总中断
}

// 定时器1初始化 (2ms中断 - 24MHz晶振)
void Timer1_Init(void)
{
    TMOD &= 0x0F;     // 清除T1设置
    TMOD |= 0x10;     // 设置T1为模式1(16位定时器)
    TH1 = 0xF0;       // 2ms定时初值(24MHz晶振)
    TL1 = 0x60;
    ET1 = 1;          // 允许T1中断
    TR1 = 1;          // 启动T1
}

// 外部中断初始化
void External_Interrupt_Init(void)
{
    IT0 = 1; // 设置INT0为下降沿触发
    IT1 = 1; // 设置INT1为下降沿触发
    EX0 = 1; // 使能INT0中断
    EX1 = 1; // 使能INT1中断
}

// 左电机PWM控制函数
void left_moto(void)
{  
    if(left_pwm)  // 左电机使能开关
    {
        if(pwmval_left <= pwmval_left_init) {
            EN1 = 1;  // 使能有效
        }
        else {
            EN1 = 0;  // 使能关闭
        }
        if(pwmval_left >= 20) {
            pwmval_left = 0;  // 重置计数器
        }
    }
    else {
        EN1 = 0;  // 关闭电机
    }
}

// 右电机PWM控制函数
void right_moto(void)
{  
    if(right_pwm)  // 右电机使能开关
    {
        if(pwmval_right <= pwmval_right_init) {
            EN2 = 1;  // 使能有效
        }
        else {
            EN2 = 0;  // 使能关闭
        }
        if(pwmval_right >= 20) {
            pwmval_right = 0;  // 重置计数器
        }
    }
    else {
        EN2 = 0;  // 关闭电机
    }
}

// 外部中断0服务函数（左电机编码器）
void INT0_ISR(void) interrupt 0
{
    // 简单消抖 - 延时10μs后再次检测
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    
    if(LEFT_ENCODER == 0) { // 确认低电平
        left_encoder_count++;  // 左电机编码器脉冲计数加1
    }
}

// 外部中断1服务函数（右电机编码器）
void INT1_ISR(void) interrupt 2
{
    // 简单消抖 - 延时10μs后再次检测
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    
    if(RIGHT_ENCODER == 0) { // 确认低电平
        right_encoder_count++; // 右电机编码器脉冲计数加1
    }
}

// 定时器0中断服务函数 (1ms - PWM控制)
void Timer0_ISR(void) interrupt 1
{
    TH0 = 0xF8;  // 重装初值(24MHz) 手动重置保证定时时间为1ms 
    TL0 = 0x30;
    
    pwmval_left++;
    pwmval_right++;
    
    left_moto();   // 更新左电机PWM
    right_moto();  // 更新右电机PWM
}

// 定时器1中断服务函数 (2ms - 速度计算)
void Timer1_ISR(void) interrupt 3
{
    TH1 = 0xF0;  // 重装初值(24MHz)
    TL1 = 0x60;
    
    speed_calc_timer++;
    
    // 每1000ms(1秒)计算一次速度
    if(speed_calc_timer >= 500) { // 500 * 2ms = 1000ms
        // 计算速度（cm/s）= (脉冲数 / 栅格数) * 轮子周长
        left_speed = (unsigned int)((left_encoder_count * WHEEL_CIRCUMFERENCE) / ENCODER_SLOTS);
        right_speed = (unsigned int)((right_encoder_count * WHEEL_CIRCUMFERENCE) / ENCODER_SLOTS);
        
        // 根据实际速度调整PWM（简单比例控制）
        adjust_pwm_based_on_speed();
        
        // 重置计数器和定时器
        left_encoder_count = 0;
        right_encoder_count = 0;
        speed_calc_timer = 0;
        
        // 这里可以添加显示函数，如OLED显示速度
        // display_speeds();
    }
}

// 根据实际速度调整PWM
void adjust_pwm_based_on_speed(void)
{
    // 左电机速度控制（简单比例控制）
    if(left_speed < TARGET_SPEED) {
        // 低于目标速度，增加PWM
        if(pwmval_left_init < 20) pwmval_left_init++;
    } else if(left_speed > TARGET_SPEED) {
        // 高于目标速度，减小PWM
        if(pwmval_left_init > 1) pwmval_left_init--;
    }
    
    // 右电机速度控制
    if(right_speed < TARGET_SPEED) {
        if(pwmval_right_init < 20) pwmval_right_init++;
    } else if(right_speed > TARGET_SPEED) {
        if(pwmval_right_init > 1) pwmval_right_init--;
    }
}

// 设置电机方向(前进)
void set_forward_direction(void)
{
    // 设置左电机前进方向
    IN1 = 1;
    IN2 = 0;
    
    // 设置右电机前进方向
    IN3 = 1;
    IN4 = 0;
}

// 初始化系统
void System_Init(void)
{
    External_Interrupt_Init(); // 初始化外部中断（编码器）
    Timer0_Init();             // 初始化PWM定时器
    Timer1_Init();             // 初始化速度计算定时器
    set_forward_direction();   // 设置前进方向
    
    // 使能电机
    left_pwm = 1;
    right_pwm = 1;
}

// 主函数
void main(void)
{
    System_Init(); // 初始化系统
    
    while(1) {
        // 主循环可以添加其他功能
        // 如：按键处理、显示更新、速度调整等
    }
}