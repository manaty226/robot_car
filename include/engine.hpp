#ifndef __ENGINE_GUARD__
#define __ENGINE_GUARD__

#include<iostream>
#include<vector>
#include<fcntl.h>
#include<sys/mman.h>
#include<thread>
#include"iengine.hpp"


#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0
#define MOTOR_1_PWM     5
#define MOTOR_2_PWM     6
#define MOTOR_3_PWM     13
#define MOTOR_4_PWM     19


class Engine: public IEngine {
public:
    Engine():BLOCKSIZE(1024*4),halfPWMPeriod(5000) {
        motor_pwm[0] = 5;
        motor_pwm[0] = 6;
        motor_pwm[0] = 13;
        motor_pwm[0] = 19;
        this->setupIo();
    };
    void Start() {
        t1 = new std::thread(&Engine::threadMain, this);
    }
    ~Engine() {
        t1->detach();
    }
private:
    void setupIo();
    void myPWMInit();
    void threadMain();
    void mySoftPwmController(int idx, int speed);
    uint64_t get_pwm_timestamp();
    volatile unsigned* gpio;
    volatile void* gpio_map;
    const unsigned int BLOCKSIZE;
    const unsigned int halfPWMPeriod;
    int prev_time[4];
    int curr_time[4];
    unsigned char flag[4];
    int time_stamp[4];
    unsigned int motor_pwm[4];
    std::thread* t1;
};


void Engine::setupIo()
{
    int mem_fd;
  /* open /dev/mem */
  if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC) ) < 0) {
    std::cout << "can't open /dev/mem \n" << std::endl;
    std::exit(-1);
  }
  /* mmap GPIO */
  gpio_map = mmap(
               NULL,             //Any adddress in our space will do
               BLOCKSIZE,       //Map length
               PROT_READ | PROT_WRITE, // Enable reading & writting to mapped memory
               MAP_SHARED,       //Shared with other processes
               mem_fd,           //File to map
               0xFE000000 + 0x200000//GPIO_BASE         //Offset to GPIO peripheral
             );

  close(mem_fd); //No need to keep mem_fd open after mmap

  if (gpio_map == MAP_FAILED) {
    std::cout << "mmap error " << std::endl;//errno also set!
    exit(-1);
  }
  // Always use volatile pointer!
  gpio = (volatile unsigned *)gpio_map;
} // setup_io

void Engine::myPWMInit() 
{
  // Switch GPIO 7..11 to output mode
  INP_GPIO(MOTOR_1_PWM); // must use INP_GPIO before we can use OUT_GPIO
  OUT_GPIO(MOTOR_1_PWM);
  INP_GPIO(MOTOR_2_PWM); // must use INP_GPIO before we can use OUT_GPIO
  OUT_GPIO(MOTOR_2_PWM);
  INP_GPIO(MOTOR_3_PWM); // must use INP_GPIO before we can use OUT_GPIO
  OUT_GPIO(MOTOR_3_PWM);
  INP_GPIO(MOTOR_4_PWM); // must use INP_GPIO before we can use OUT_GPIO
  OUT_GPIO(MOTOR_4_PWM);
}

void Engine::threadMain() {
    mySoftPwmController(0, 5000);
    mySoftPwmController(1, 5000);
    mySoftPwmController(2, 5000);
    mySoftPwmController(3, 5000);
}

void Engine::mySoftPwmController(int idx, int speed) 
{

  int* prev_time_ptr = &prev_time[idx];
  int* curr_time_ptr = &curr_time[idx];
  int* time_stamp_ptr = &time_stamp[idx];
  unsigned char* flag_ptr = &flag[idx];

  if(!(*flag_ptr)) {
      *flag_ptr = 1;
      *prev_time_ptr = get_pwm_timestamp();
  }
  *curr_time_ptr = get_pwm_timestamp();
  *time_stamp_ptr = *curr_time_ptr - *prev_time_ptr;

  if(*time_stamp_ptr > 0 && *time_stamp_ptr <= 2 * halfPWMPeriod) {
    if(*time_stamp_ptr <= speed) GPIO_SET = 1 << motor_pwm[idx];
    else GPIO_CLR = 1 << motor_pwm[idx];
  }
  if(*time_stamp_ptr > 2 * halfPWMPeriod) *flag_ptr = 0;

}

uint64_t Engine::get_pwm_timestamp()
{
  struct timespec t;
  if (clock_gettime(CLOCK_MONOTONIC_RAW, &t) != 0) {
    return 0;
  }
  return (uint64_t) t.tv_sec * 1000000 + t.tv_nsec / 1000;
}


#endif