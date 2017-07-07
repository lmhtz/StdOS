#ifndef _W25QXXX_H
    #define _W25QXXX_H

    #include "Kernel\Sys.h"
    #include "Device\Spi.h"

    // W25Q64存储Flash
    class W25Q64
    {
        private:
            Spi *_spi; // 内部Spi对象

            // 设置操作地址
            void SetAddr(uint addr);
            // 等待操作完成
            bool WaitForEnd();

            // 读取编号
            uint ReadID();
            void WriteEnable(void);
            void StartReadSequence(uint ReadAddr);

        public:
            uint ID; // 芯片ID
            uint DeviceID; // 设备ID
            ushort PageSize; // 页大小
            ushort Retry; // 等待重试次数

            W25Q64(Spi *spi);
            ~W25Q64();

            // 擦除扇区
            bool Erase(uint sector);
            // 擦除页
            bool ErasePage(uint pageAddr);

            // 写入一页
            bool WritePage(uint addr, byte *buf, uint count);
            // 读取一页
            bool ReadPage(uint addr, byte *buf, uint count);
            // 写入数据
            bool Write(uint addr, byte *buf, uint count);
            // 读取数据
            bool Read(uint addr, byte *buf, uint count);

            uint ReadDeviceID(void); //Reads FLASH identification.
            //Erases the entire FLASH.
            void BulkErase(void);
            void WakeUp(void); //唤醒
            void PowerDown(void); //进入掉电模式	
    };

    /*
    AT45DB041中的数据按页存放,主存共2048页,每页 264字节,所以总容量为528K字节（约4M比特）。存放在主存中的数据掉电不丢失。
    除了主存以外,AT45DB041还有两个容量为264字节的数据缓存。缓存可以用作主存与外部进行数据交换时的缓冲区域,也可以暂存一些临时数据。
    缓存读写方便迅速,但掉电数据会丢失。AT45DB041数据读写采用串行方式,读写速度快,从页到缓存的传输时间为80 s左右,并且兼容CMOS和TTL输入和输出。

    数据读取 
    读缓存：通过不同的操作码可选择读取两个缓存中的其中一个（操作码54H用作读缓存1,而操作码56H用作读缓存2）。
    为了实现读缓存的操作,在8位操作码后必须跟有15位任意码,9位地址码和8位任意码。其中9位地址码（BFA8-BFA0）被用作指定要读取的首字节。
    在轮换时钟SCK的控制下,从SI载入操作码、地址码、任意码。当载入结束后,在SCK轮换时钟的控制下,缓存中的数据就可以从SO读出。
    当读到缓存的末尾时,设备将继续从缓存的开端重读。在这整个过程中/CS必须保持低电平。读缓存结束后,/CS上一个从低到高的电平跳变将终止读操作。
    主存页到缓存的传送：一页数据可以从主存传至缓存1或2。
    8位操作码（53H用于缓存1,55H用于缓存2）后跟有4位保留位,11位用于指定目的页的地址位（PA10-PA0）,和9位任意码,在轮换时钟SCK的控制下从SI载入。
    在这一过程中/CS管脚必须保持低电位。当载入结束后,在/CS上检测到一个由低到高的电平跳变后,主存页中的数据开始传送至缓存。
    在数据传送的过程中,状态寄存器将指示状态忙。 

    数据写入 
    写缓存：在SCK的控制下,8位的操作码（84H用于缓存1,87H用于缓存2）后面跟着15位任意码和9位地址码（BFA8-BFA0）由SI载入,
    其中9位地址码指定了缓存中被写的首字节,数据紧随着地址码输入。/CS上一个由低到高的跳变,将结束写缓存操作。
    带有内置擦除的缓存至主存页的传送：8位的操作码（83H用于缓存 1,86H用于缓存2）后跟有4位保留位,11位指定要写入的主存页的地址码（PA10-PA0）,
    和9位任意码,在轮换时钟SCK的控制下从SI载入。当/CS上检测到一个由低到高的跳变时,器件将首先擦除被选中的主存页,然后将储存在缓存中的数据写入该页。
    擦除和写入的过程都是自动进行的,这一进程不超过20ms。在这个时间里,状态寄存器将指示状态忙。状态寄存器值读取:读状态寄存器的值可以用来确定设备的忙闲状态。
    忙闲状态通过寄存器的第7位指示。如果第7位为1,则设备位于空闲状态并可接收下一条指令。如果为0,则设备忙。在载入8位操作码57H后,从SO上可以读出1字节的状态寄存器的值。
     */
#endif
